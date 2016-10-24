#ifdef TEST

#include <cassert>
#include <sstream>
#include <vector>
#include "pe/PE.hpp"
#include "pe/PEName.hpp"
#include "pe/SinkNode.hpp"
#include "cpu/CPU.hpp"
#include "cpu/RedTubo.hpp"
#include "Source.hpp"
#include "common/Traza.hpp"
using namespace std;


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

    PEName getName(){
      return PEName::MockPE;
    }
};

class TestBasicSource: public Source{
  private:
    std::shared_ptr<Traza> traza;

  public:
    TestBasicSource(double et, handle<RedTubo> red_tubo): Source(et, red_tubo){

    }

    void inner_body(){


      std::stringstream ss;
      ss << "Iniciando simulación, tiempo final: ";
      ss << this->end_time;

      this->traza->puntoSource(time(), ss);
      while(time() < this->end_time){
        //this->porcentaje();
        // TODO: Hacer el envío de los mensajes a la red
        // Cuando se terminen de enviar mensajes, hacer break

        auto destino = PEName::MockPE;
        auto mensaje = MessagePE(DEFAULT_MESSAGE_SIZE);

        this->red_tubo->enviarMensaje(destino, mensaje);
        //enviamos un solo mensaje
        break;
      }


      // Esperamos a que termine la simulación, vamos mostrando el porcentaje de
      // ejecución completo
      while(time() < this->end_time){
        this->porcentaje();
        hold(1000);
      }

      //Hay que notificar a los demás objetos de la simulación que terminen de procesar


      this->traza->puntoSource(time(), "Terminando simulación");
      for(auto callback: this->end_callbacks){
        callback();
      }
    }

    void setTraza(std::shared_ptr<Traza> traza){
      this->traza = traza;
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

  auto traza = std::shared_ptr<Traza>(new Traza);

  auto mock_pe = std::shared_ptr<PE>(new MockPE("MockPE"));
  auto sink_node = std::shared_ptr<PE>(new SinkNode("SinkNode"));

  //una vez tenemos los PEs, tenemos que asignarlos a una CPU

  auto cpu = handle<CPU>(new CPU({
        mock_pe,
        sink_node
      }));
  cpu->setTraza(traza);

  auto red_tubo = handle<RedTubo>(new RedTubo{
        cpu
      });

  red_tubo->setTraza(traza);

  handle<TestBasicSource> src(new TestBasicSource(END_SIM_TIME, red_tubo));
  src->setTraza(traza);
  src->activate();

  src->addEndCallback(red_tubo);
  src->addEndCallback(cpu);

  sim->run();

  // Listo!
  sim->end_simulation();
  
  return 0;
}

#endif
