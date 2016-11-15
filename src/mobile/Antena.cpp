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
  this->cola_ms.push_back(std::make_tuple(id_device, m));
  this->activate();
}

void Antena::inner_body(){
  while(this->run){
    if(this->cola_ms.empty()){
      this->traza->puntoRed3G(time(), "No hay más mensajes por enviar a dispositivos en la antena, esperando...");
      this->passivate();
    }
    else{
      std::vector<std::vector<std::tuple<Id, MessageMD>>::iterator> a_eliminar;
      for(auto it = this->cola_ms.begin(); it != this->cola_ms.end();it++){
        auto tupla = *it;
        Id id_device = std::get<0>(tupla);
        MessageMD mensaje = std::get<1>(tupla);

      /*  std::stringstream ss;
        ss << "Enviando mensaje a dispositivo";
        ss << id_device;
        ss << " con mensaje ";
        ss << mensaje.getId();
        ss << ", vamos a esperar ";
        ss << LATENCIA_RED;
        this->traza->puntoRed3G(time(), ss);*/

        hold(LATENCIA_RED);

        //(*mensaje)->setTag();
        a_eliminar.push_back(tupla);
        //a_eliminar.push_back(std::make_tuple(id_device,mensaje));

      }
      for(auto m: a_eliminar){
        this->cola_ms.erase(m);
        std::pop_heap(this->cola_ms.begin(), this->cola_ms.end());
      }

    }
    
  }
}
