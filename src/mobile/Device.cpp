#include "Device.hpp"

static Id current_id = 0;

Device::Device(std::queue<position> posiciones): Process("Device"){

  std::tie(std::ignore, this->x, this->y) = posiciones.front();

  this->posiciones = posiciones;
  this->id = current_id;
  current_id++;



  this->movimiento = handle<Movimiento>(
      new Movimiento(
        [this](double x, double y){
          this->x = x;
          this->y = y;
          this->move_device(this);
          position next = this->posiciones.front();
          if(this->posiciones.size() > 1){
            // En caso de tener más de una siguiente posicion, sacamos el que
            // está en la cima de la cola para representar el movimiento
            this->posiciones.pop();
          }
          return next;
        }));

}


Id Device::getId() const{
  return this->id;
}

void Device::inner_body(){
  while(this->run){
    if(this->mensajes.empty()){
      this->passivate();
    }

    MessageMD mensaje = this->mensajes.front();
    this->mensajes.pop();

    //this->mensaje.setTag();
    hold(TIEMPO_ESPERA_TAGEO_PERSONA);

    this->send_message(mensaje);

  }
}


void recibirPaquetesAntena(Id id_antena, PacketMD p){

} 

void Device::agregarPosicion(double time, double _x, double _y){
  this->posiciones.push(std::make_tuple<>(time, _x, _y));
}


double Device::getX() const{
  return this->x;
}

double Device::getY() const{
  return this->y;
}


void Device::endSimulation(){
  this->movimiento->endSimulation();
  Process::endSimulation();
}


void Device::setSendCallback(send_callback callback){
  this->send_message = callback;
}

void Device::setMoveCallback(std::function<void(Device*)> callback){
  this->move_device = callback;
}


void Device::iniciar_mov(){
  this->movimiento->setNext(posiciones.front());
}
