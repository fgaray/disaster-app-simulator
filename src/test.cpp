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


#include "pe/PEBigram.hpp"
#include "pe/PENHashtags.hpp"
#include "pe/PENMentions.hpp"
#include "pe/PEPHashtags.hpp"
#include "pe/PEPMentions.hpp"
#include "pe/PEPOStag.hpp"
#include "pe/PESizetweet.hpp"
#include "pe/PEUnigram.hpp"


using namespace std;

void test_simulacion_basica();
void test_simulacion_completa();

class MockPE: public PE{
  public:
    double getCostTime(){
      return 1000;
    }

    std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message){
      return {std::make_tuple(PEName::SinkNode, message)};
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


void test_simulacion_basica(){
  auto sim = std::unique_ptr<simulation>(simulation::instance());
  sim->begin_simulation(new sqsDll());

  //probemos primero la red tubo con una CPU básica 

  //creamos una CPU que va a ejecutar dos PEs, uno que es el sink node y otro
  //que es el mockPE, entonces desde el source se va a enviar el mensaje a
  //MockPE y de ahi al sinknode

  auto traza = std::shared_ptr<Traza>(new Traza);

  auto mock_pe = std::shared_ptr<PE>(new MockPE);
  auto sink_node = std::shared_ptr<PE>(new SinkNode);

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
}


void test_simulacion_completa(){
  auto sim = std::unique_ptr<simulation>(simulation::instance());
  sim->begin_simulation(new sqsDll());

  //probemos primero la red tubo con una CPU básica 

  //creamos una CPU que va a ejecutar dos PEs, uno que es el sink node y otro
  //que es el mockPE, entonces desde el source se va a enviar el mensaje a
  //MockPE y de ahi al sinknode

  auto traza = std::shared_ptr<Traza>(new Traza);

  auto peBigram = std::shared_ptr<PE>(new PEBigram);
  auto peNHashtags = std::shared_ptr<PE>(new PENHashtags);
  auto peNMentions = std::shared_ptr<PE>(new PENMentions);
  auto pePHashtags = std::shared_ptr<PE>(new PEPHashtags);
  auto pePMentions = std::shared_ptr<PE>(new PEPMentions);
  auto pePOStag = std::shared_ptr<PE>(new PEPOStag);
  auto pePSizetweet = std::shared_ptr<PE>(new PESizetweet);
  auto peUnigram = std::shared_ptr<PE>(new PEUnigram);


  //una vez tenemos los PEs, tenemos que asignarlos a una CPU

  auto cpu1 = handle<CPU>(new CPU({
        peBigram,
        peNHashtags,
        peNMentions,
        pePHashtags
      }));

  auto cpu2 = handle<CPU>(new CPU({
        pePMentions,
        pePOStag,
        pePSizetweet,
        peUnigram
      }));


  cpu1->setTraza(traza);
  cpu2->setTraza(traza);

  auto red_tubo = handle<RedTubo>(new RedTubo{
        cpu1,
        cpu2
      });

  red_tubo->setTraza(traza);

  handle<TestBasicSource> src(new TestBasicSource(END_SIM_TIME, red_tubo));
  src->setTraza(traza);
  src->activate();

  src->addEndCallback(red_tubo);
  src->addEndCallback(cpu1);
  src->addEndCallback(cpu2);

  sim->run();

  // Listo!
  sim->end_simulation();


}




int main(int argc, char *argv[])
{
  test_simulacion_basica();
  test_simulacion_completa();
  
  return 0;
}

#endif
