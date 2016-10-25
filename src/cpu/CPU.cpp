#include "CPU.hpp"

#include "../pe/PEName.hpp"

void CPU::inner_body(){
  while(this->run){
    if(!this->existePlanificacion() && this->input_buffer.empty()){
      intentar_agregar();
      this->passivate();
    }

    if(this->existePlanificacion()){

      //buscamos la CPU/PE que tenga el tiempo más proximo a salir desde la CPU


      std::sort(this->cores.begin(), this->cores.end(),
          [](const Planificacion &p1, const Planificacion &p2){
            return p1.restante() < p2.restante();
          });

      //seleccionamos un core que esté vacio

      Planificacion &core = this->getCorePlanificado();

      core.setCurrentTime(time());
      double to_hold = core.restante();

      //restamos el tiempo esperado a todos los cores
      for(auto &p: this->cores){
        if(p.contienePlanificacion()){
          p.ejecutar(to_hold);
          std::stringstream ss2;
          ss2 << ">>>Ejecutando en core, ";
          ss2 << peNameToString(p.getPE()->getName());
          ss2 << ", le quedan a este PE ";
          ss2 << "" << p.restante();
          ss2 << " en próxima ejecución";
          this->traza->puntoCPU(time(), ss2);
        }
      }

      //vamos a esperar el tiempo que le queda a este core por ejecutarse
      std::stringstream ss2;
      ss2 << "Ejecutando en core, tenemos que esperar ";
      ss2 << to_hold;
      this->traza->puntoCPU(time(), ss2);
      hold(to_hold);

      std::vector<std::tuple<PEName, MessagePE>> nexts;

      if(core.getPE()->getName() == PEName::PEAssembler){
        cout << nexts.size() << endl;
      }
      
      //eliminar los PEs que hayan cumplido sus tiempos
      for(auto &p: this->cores){
        if(p.restante() <= 0 && p.contienePlanificacion()){
          auto v = p.getPE()->nextPE(p.getMessage());
          for(auto &m: v){
            nexts.push_back(m);
          }
          this->ejecutando.erase(p.getPE()->getId());
          p.remove();
        }
      }



      for(auto n: nexts){
        PEName name = std::get<0>(n);
        MessagePE m = std::get<1>(n);
        std::stringstream ss;
        ss << "Enviando el mensaje " << m.getId();
        ss << " " << nexts.size();
        this->traza->puntoCPU(time(), ss);
        this->enviarMensaje(name, m);
      }


    }
    
    if(!this->input_buffer.empty()){
      this->intentar_agregar();
    }
  }
}

CPU::CPU(std::initializer_list<std::shared_ptr<PE>> il): Process("CPU"){
  for(auto p: il){
    this->pes.push_back(p);
  }
  this->numero_cores = 4;
  this->run = true;

  for(unsigned int i = 0; i < this->numero_cores; i++){
    this->cores.push_back(Planificacion());
  }

}

void CPU::recibirMessage(Id destino, MessagePE message){
  this->activate();
  this->input_buffer.push_back(std::make_pair(destino, message));
}

void CPU::enviarMensaje(PEName destino, MessagePE message){
  this->envio_mensaje_callback(destino, message);
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


void CPU::intentar_agregar(){
  // intentamos agregar solamente si el buffer de entrada tiene algo

  if(!this->input_buffer.empty()){
    //buscamos algun core que esté libre

    //buscamos un PE que no se esté ejecutando actualmente


    std::vector<std::vector<std::tuple<Id, MessagePE>>::iterator> a_eliminar;
    
    for(auto it = this->input_buffer.begin(); it != this->input_buffer.end(); it++){
      auto entrada = *it;
      Id pe_destino = std::get<0>(entrada);
      auto resultado = this->ejecutando.find(pe_destino);
      if(resultado != this->ejecutando.end()){
        //continuamos dado que el PE sigue ejecutandose
        continue;
      }else{
        //podemos intentar agregar un nuevo PE, hay que ver si hay una
        //planificacion que esté libre
        for(auto &p: this->cores){
          if(!p.contienePlanificacion()){
            //buscamos un PE con ese ID

            auto found = std::find_if(this->pes.begin(), this->pes.end(),
                [pe_destino](const PE_ptr &pe){
                  return pe->getId() == pe_destino;
                });
            assert(found != this->pes.end());

            auto pe = *found;
            MessagePE m = std::get<1>(entrada);

            p.set(std::make_tuple(pe, m));
            this->ejecutando.insert({pe->getId(), true});
            a_eliminar.push_back(it);
            break;
          }
        }
      }
    }

    for(auto it: a_eliminar){
      this->input_buffer.erase(it);
    }
  }
}

bool CPU::existePlanificacion(){
  for(auto p: this->cores){
    if(p.contienePlanificacion()){
      return true;
    }
  }
  return false;
}


Planificacion &CPU::getCorePlanificado(){
  for(auto &p: this->cores){
    if(p.contienePlanificacion()){
      return p;
    }
  }
  assert(false);
}


/*********** PLANIFICACION *******************/



Planificacion::Planificacion(){
  this->contiene = false; 
}


void Planificacion::remove(){
  this->contiene = false;
}

void Planificacion::set(std::tuple<PE_ptr, MessagePE> planificacion){
  this->pe = std::get<0>(planificacion);
  this->message = std::get<1>(planificacion);
  this->contiene = true;
  this->tiempo_restante = this->pe->getCostTime();
}

void Planificacion::ejecutar(double t){
  this->tiempo_restante = this->tiempo_restante - t;
  if(this->tiempo_restante <= 0){
    this->tiempo_restante = 0;
  }
}


double Planificacion::restante() const{
  return this->tiempo_restante;
}

bool Planificacion::contienePlanificacion(){
  return this->contiene;
}



PE_ptr Planificacion::getPE(){
  assert(this->contiene == true);
  return this->pe;
}

void Planificacion::setCurrentTime(double t){
  assert(this->contiene == true);
  return this->pe->setCurrentTime(t);
}



MessagePE Planificacion::getMessage(){
  return this->message;
}
