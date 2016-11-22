#include "Antena.hpp"


Antena::Antena(double _x, double _y, double _radio): Process("Antena"){
  this->x = _x;
  this->y = _y;
  this->radio = _radio;
}

double Antena::distancia(Device *device) const{
	double dist_x = this->x - device->getX();
	double dist_y = this->y - device->getY();
	return sqrt(pow(dist_x,2) + pow(dist_y,2));
}

Id Antena::getId(){
  return this->id;
}



double Antena::getRadio(){
  return radio;
}


void Antena::recibirPaquetes(buffer_antena paquetes){
  for(auto it = this->paquetes.begin(); it != this->paquetes.end();it++){
    auto tupla = *it;
    PacketMD p = std::get<2>(tupla);
    Id id_device = std::get<0>(tupla);
    //Id id_antena = std::get<1>(tupla);
    this->cola_ps.push_back(id_device, p); 
   /* if(p.getRemainingTime() <= 0){
      if(p.isLast()){
        this->entregarPaquetesDevice(id_device, paquetes); 
      }	    
    }*/
  }
  this->activate();

  //se asume que vienen los paquetes reconstruidos desde la red3g, donde fueron simulados.
  // se añade el mensaje a una cola de mensajes.
  //this->cola_ms.push(std::make_tuple(id_device, m));
  //this->activate();
}

void Antena::entregarPaquetesDevice(Id id_device, buffer_antena paquetes){
  auto dev = this->devices.find(id_device);
  dev->recibirPaquetesAntena(paquetes);
}

/*
void Antena::recibirMessage(Id id_device, MessageMD m){

  //se asume que vienen los paquetes reconstruidos desde la red3g, donde fueron simulados.
  // se añade el mensaje a una cola de mensajes.
  this->cola_ms.push(std::make_tuple(id_device, m));
  this->activate();
}*/

void Antena::inner_body(){
  while(this->run){
    if(this->cola_ps.empty()){
      this->traza->puntoRed3G(time(), "No hay más mensajes por enviar a dispositivos en la antena, esperando...");
      this->passivate();
    }else{
      for(auto it = this->cola_ps.begin(); it != this->cola_ps.end();it++){
        auto tupla = *it;
        Id id_antena = std::get<0>(tupla);
        Id id_device = std::get<1>(tupla);
        PacketMD p = std::get<2>(tupla);

	auto device = this->devices.find(id_device);
        if(p.isLast()){
          device->recibirPaquetesAntena(id_antena, p); 
        }	    
      
      }
      //obtenemos el mensaje de la cola
     /* auto m = std::get<1>(this->cola_ms.front());
      this->cola_ms.pop();

      hold(LATENCIA_RED);

      m.setTag();

      this->responder_mensaje(m);
      */
    }

	  
  }
}



void Antena::setResponderCallback(std::function<void(MessageMD)> callback){
  this->responder_mensaje = callback;
}
