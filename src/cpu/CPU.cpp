#include "CPU.hpp"

#include "../pe/PEName.hpp"
#include "../metric/LargoPromedioCola.hpp"

void CPU::inner_body(){
  while(this->run){
    //vemos si current PE puede ser ejecutado (no está en un core siendo
    //ejecutado ahora)

    auto found = std::find_if(this->cores.begin(), this->cores.end(), [this](const handle<Core> &core){
        return core->ejecutando(*(this->current_pe));
      });

    if(found == this->cores.end()){
      //entonces este PE no se está ejecutando en ningun core, hay que asignar
      //el mensaje al pe para que corra en el core
      
      //Seleccionamos el primer core que esté vacio


      //vemos si hay mensajes primero

      auto mensajes_found = this->cola_pes.find((*current_pe)->getId());
      assert(mensajes_found != this->cola_pes.end());

      auto &mensajes = (*mensajes_found).second;

      if(!mensajes.empty()){

        auto mensaje = mensajes.front();
        mensajes.pop();

        auto core_vacio_iterator = std::find_if(this->cores.begin(), this->cores.end(), [](const handle<Core> &core){
            return core->empty();
            });

        if(core_vacio_iterator != this->cores.end()){
          //encontramos un core vacio, entonces le asignamos este PE

          auto pe = *(this->current_pe);

          size_t numeroCore = std::distance(this->cores.begin(), core_vacio_iterator);

          std::stringstream ss;
          ss << "Ejecutando PE " << peNameToString(pe->getName()) << " con Id " << pe->getId();
          ss << " en el core " << numeroCore << " de la CPU " << this->number;
          this->traza->puntoCPU(time(), ss);

          (*core_vacio_iterator)->ejecutar(pe, mensaje);
        }

        agregarTamano((*mensajes_found).second.size());


      }
    }
    //en caso que no haya algun core vacio o que el PE se esté ya ejecutando,
    //tenemos que continuar probando otros pes, si probamos todos, entonces hay
    //dos posibilidades, 




    //pasamos al siguiente
    this->current_pe++;
    if(this->current_pe == this->pes.end()){
      this->current_pe = this->pes.begin();
      //no pudimos planificar ningun PE, esperamos a que nos despierten ya sea
      //por la llegada de un mensaje o por que un PE liberó un core
      passivate();
    }
  }
}


CPU::CPU(std::initializer_list<std::shared_ptr<PE>> il): Process("CPU"){
  for(auto p: il){
    this->pes.push_back(p);
    this->cola_pes.insert({p->getId(), std::queue<MessagePE>()});
  }

  this->numero_cores = 4;
  this->run = true;


  for(unsigned int i = 0; i < this->numero_cores; i++){
    auto core = handle<Core>(new Core);
    core->setTraza(this->traza);
    this->cores.push_back(core);
  }


  for(auto it = this->cores.begin(); it != this->cores.end(); it++){
    (*it)->set_cpu_callback([this](std::vector<std::tuple<PEName, MessagePE>> mensajes){
        this->notificarTerminoPE(mensajes);
      });
  }

  this->current_pe = this->pes.begin();


}




void CPU::recibirMessage(Id destino, MessagePE message){
  //acabamos de recibir un mensaje con el PE de destino, buscamos el pe
  //correspondiente primero

  auto cola_pe = this->cola_pes.find(destino);
  assert(cola_pe != this->cola_pes.end());

  //Agregamos el mensaje a la cola del pe correspondiente
  (*cola_pe).second.push(message);

  agregarTamano((*cola_pe).second.size());
  this->activate();
}


void CPU::enviarMensaje3G(Id destino, MessageMD message){

}



void CPU::setEnvioMensajeCallback(std::function<void(PEName, MessagePE)> fn){
  this->envio_mensaje_callback = fn;
}

bool CPU::contienePE(Id id){
  for(auto pe: this->pes){
    if(pe->getId() == id){
      return true;
    }
  }
  return false;
}


std::vector<Id> CPU::getIdsPEs(){
  std::vector<Id> ids;
  for(auto &pe: this->pes){
    ids.push_back(pe->getId());
  }

  return ids;
}



std::vector<std::tuple<PEName, Id>> CPU::getNamesPEs(){
  std::vector<std::tuple<PEName, Id>> names;
  for(auto pe: this->pes){
    names.push_back(std::make_tuple(pe->getName(), pe->getId()));
  }

  return names;
}



void CPU::notificarTerminoPE(std::vector<std::tuple<PEName, MessagePE>> mensajes){
  //enviamos los mensajes que nos entregan y dado que ahora quedó un Core libre,
  //hay que intentar agregar un PE al sistema

  for(auto t: mensajes){
    PEName name = std::get<0>(t);
    MessagePE message = std::get<1>(t);
    std::stringstream ss;
    ss << "Enviando mensaje hacia ";
    ss << peNameToString(name);
    this->traza->puntoCPU(time(), ss);
    this->envio_mensaje_callback(name, message);
  }


  this->activate();
}


function<void()> CPU::getEndCallback(){
  return [this](){
    for(auto &core: this->cores){
      core->endSimulation();
    }
    this->run = false;
  };
}


void CPU::setNumber(unsigned int number){
  this->number = number;
}
