#include "Antena.hpp"


Antena::Antena(double _x, double _y, double _radio): Process("Antena"){
  this->x = _x;
  this->y = _y;
  this->radio = _radio;
}

double Antena::distancia(handle<Device> device) const{
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

void Antena::recibirMessage(Id id_device, MessageMD m){

  //se asume que vienen los paquetes reconstruidos desde la red3g, donde fueron simulados.
  // se añade el mensaje a una cola de mensajes.
  this->cola_ms.push(std::make_tuple(id_device, m));
  this->activate();
}

void Antena::inner_body(){
  while(this->run){
    if(this->cola_ms.empty()){
      this->traza->puntoRed3G(time(), "No hay más mensajes por enviar a dispositivos en la antena, esperando...");
      this->passivate();
    }else{

      //obtenemos el mensaje de la cola
      auto m = std::get<1>(this->cola_ms.front());
      this->cola_ms.pop();

      hold(LATENCIA_RED);

      m.setTag();
      this->red_movil->enviarMensajeHaciaCluster(m);
      this->responder_mensaje(m);

    }
    
  }
}



void Antena::setResponderCallback(std::function<void(MessageMD)> callback){
  this->responder_mensaje = callback;
}

void Antena::setRedMovil(handle<Network3G> red_movil){
  this->red_movil = red_movil;
}