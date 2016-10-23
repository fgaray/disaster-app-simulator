#ifdef TEST

#include <cassert>
#include <iostream>
#include <vector>
#include "pe/PE.hpp"
#include "pe/PEName.hpp"
#include "pe/SinkNode.hpp"
#include "cpu/CPU.hpp"
#include "cpu/RedTubo.hpp"
#include "Source.hpp"


class MockPE: public PE{
  public:
    MockPE(const char *nombre): PE(nombre){

    }
    double getCostTime(){
      return 1000;
    }

    std::vector<std::tuple<PEName, MessagePE>> nextPE(const MessagePE &message){
      return {std::make_tuple(PEName::SinkNode, MessagePE())};
    }
};

class TestBasicSource: public Source{

  public:
    TestBasicSource(double et, std::shared_ptr<RedTubo> red_tubo): Source(et, red_tubo){

    }

    void inner_body(){
      while(time() < this->end_time){
        this->porcentaje();
        // TODO: Hacer el envío de los mensajes a la red
        // Cuando se terminen de enviar mensajes, hacer break

        auto destino = PEName::MockPE;
        auto mensaje = MessagePE();

        this->red_tubo->enviarMensaje(destino, mensaje);
      }


      // Esperamos a que termine la simulación, vamos mostrando el porcentaje de
      // ejecución completo
      while(time() < this->end_time){
        this->porcentaje();
      }

      //Hay que notificar a los demás objetos de la simulación que terminen de procesar


      for(auto callback: this->end_callbacks){
        callback();
      }
    }



};




int main(int argc, char *argv[])
{

  auto sim = std::unique_ptr<simulation>(simulation::instance());
  sim->begin_simulation(new sqsDll());



  //probemos primero la red tubo con una CPU básica 

  //creamos una CPU que va a ejecutar dos PEs, uno que es el sink node y otro
  //que es el mockPE, entonces desde el source se va a enviar el mensaje a
  //MockPE y de ahi al sinknode


  auto mock_pe = std::shared_ptr<PE>(new MockPE("MockPE"));
  auto sink_node = std::shared_ptr<PE>(new SinkNode("SinkNode"));

  //una vez tenemos los PEs, tenemos que asignarlos a una CPU

  auto cpu = std::shared_ptr<CPU>(new CPU({
        mock_pe,
        sink_node
      }));

  auto red_tubo = std::shared_ptr<RedTubo>(new RedTubo{
        cpu
      });

  handle<TestBasicSource> src(new TestBasicSource(END_SIM_TIME, red_tubo));
  src->activate();
  sim->run();

  // Listo!
  sim->end_simulation();
  
  return 0;
}

#endif
