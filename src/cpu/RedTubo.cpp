#include "RedTubo.hpp"


RedTubo::RedTubo(std::initializer_list<std::shared_ptr<CPU>> il): Process("RedTubo"){
  for(auto cpu: il){
    cpu->setEnvioMensajeCallback([this](Id destino, MessagePE message){
        this->enviarMensaje(destino, message);
      });
    this->cpus.push_back(cpu);
  }
}

void RedTubo::enviarMensaje(Id destino, MessagePE message){
  this->input_buffer.push(std::make_tuple(destino, message));
  this->activate();
}


void RedTubo::inner_body(){
  while(this->run){
    if(this->input_buffer.empty()){
      this->passivate();
    }

    Id destino;
    MessagePE message;

    std::tie(destino, message) = this->input_buffer.front();
    this->input_buffer.pop();

    // tenemos el mensaje, ahora debemos ver cuanto vamos a esperar. Dividimos
    // el mensaje en paquetes donde cada uno debe esperar

    for(unsigned int restante = message.getSize();restante > 0;restante = restante - PACKET_SIZE){
      hold(LATENCIA_RED);
    }

    // ya simulamos la transmision de los paquetes, ahora tenemos que mansar el
    // paquete a la CPU que tenga el PE de destino

    auto it = find_if(this->cpus.begin(), this->cpus.end(), [destino](const CPU_ptr &cpu){
          return cpu->contienePE(destino);
        });

    assert(it != this->cpus.end());

    (*it)->recibirMessage(destino, message);
  }
}
