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
#include "mobile/Traza.hpp"


#include "pe/PEBigram.hpp"
#include "pe/PENHashtags.hpp"
#include "pe/PENMentions.hpp"
#include "pe/PEPHashtags.hpp"
#include "pe/PEPMentions.hpp"
#include "pe/PEPOStag.hpp"
#include "pe/PESizetweet.hpp"
#include "pe/PEUnigram.hpp"
#include "pe/PEAdapter.hpp"
#include "pe/PECollector.hpp"
#include "pe/PEBroker.hpp"
#include "pe/PETrainer.hpp"
#include "pe/PEFilter.hpp"
#include "pe/PEModel.hpp"
#include "pe/PEFSelection.hpp"
#include "pe/PEAssembler.hpp"

#include "common/Distribution.hpp"

#include "metric/LargoPromedioCola.hpp"


using namespace std;

void test_simulacion_basica();
void test_simulacion_completa();
void test_problema();

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
    //std::shared_ptr<Traza> traza;

  public:
    TestBasicSource(double et, handle<RedTubo> red_tubo, std::shared_ptr<Traza> traza): Source(et, red_tubo, traza){

    }

    void inner_body(){

      //auto distribucion = std::shared_ptr<Distribution>(new Distribution(AMOUNT_OF_TWEETS, TWEET_PER_SECOND));

      std::stringstream ss;
      ss << "Iniciando simulación, tiempo final: ";
      ss << this->end_time;

      this->traza->puntoSource(time(), ss);
      unsigned int cantidad_menajes = 0;
      while(time() < this->end_time && cantidad_menajes < 1){
        //auto tiempo_arribo = distribucion->GeneradorExp();
        //this->porcentaje();
        // TODO: Hacer el envío de los mensajes a la red
        // Cuando se terminen de enviar mensajes, hacer break

        auto destino = PEName::MockPE;
        auto mensaje = MessagePE(DEFAULT_MESSAGE_SIZE);
        this->traza->puntoSource(time(), "Generando un nuevo mensaje");

        this->red_tubo->enviarMensaje(destino, mensaje);
        //enviamos un mensaje cada 0.5 segundos
        //hold(tiempo_arribo);
        hold(10);
        cantidad_menajes++;
      }

      this->traza->puntoSource(time(), "No hay más mensajes a generar");

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

  handle<TestBasicSource> src(new TestBasicSource(END_SIM_TIME, red_tubo, traza));
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

  // creamos los dispositivos móviles


  trazas_devices trazas = parsear_traza("traza_limpia.csv");







  //probemos primero la red tubo con una CPU básica 

  //creamos una CPU que va a ejecutar dos PEs, uno que es el sink node y otro
  //que es el mockPE, entonces desde el source se va a enviar el mensaje a
  //MockPE y de ahi al sinknode

  auto traza = std::shared_ptr<Traza>(new Traza);

  auto peAdapter = std::shared_ptr<PE>(new PEAdapter);
  auto peCollector = std::shared_ptr<PE>(new PECollector);
  auto peFilter = std::shared_ptr<PE>(new PEFilter);
  auto peBroker = std::shared_ptr<PE>(new PEBroker);

  auto peBigram = std::shared_ptr<PE>(new PEBigram);
  auto peNHashtags = std::shared_ptr<PE>(new PENHashtags);
  auto peNMentions = std::shared_ptr<PE>(new PENMentions);
  auto pePHashtags = std::shared_ptr<PE>(new PEPHashtags);

  auto pePMentions = std::shared_ptr<PE>(new PEPMentions);
  auto pePOStag = std::shared_ptr<PE>(new PEPOStag);
  auto pePSizetweet = std::shared_ptr<PE>(new PESizetweet);
  auto peUnigram = std::shared_ptr<PE>(new PEUnigram);

  auto peModel = std::shared_ptr<PE>(new PEModel);
  auto peAssembler = std::shared_ptr<PE>(new PEAssembler);
  auto peFSelection = std::shared_ptr<PE>(new PEFSelection);
  auto peTrainer = std::shared_ptr<PE>(new PETrainer);


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

  auto cpu3 = handle<CPU>(new CPU({
        peAdapter,
        peCollector,
        peFilter,
        peBroker
      }));

  auto cpu4 = handle<CPU>(new CPU({
        peModel,
        peAssembler,
        peFSelection,
        peTrainer
      }));


  cpu1->setTraza(traza);
  cpu2->setTraza(traza);
  cpu3->setTraza(traza);
  cpu4->setTraza(traza);
  cpu1->setNumber(1);
  cpu2->setNumber(2);
  cpu3->setNumber(3);
  cpu4->setNumber(4);

  auto red_tubo = handle<RedTubo>(new RedTubo{
        cpu1,
        cpu2,
        cpu3,
        cpu4
      });

  red_tubo->setTraza(traza);

  vector<handle<Device>> devices;

  vector<handle<Antena>> antenas;

  antenas.push_back(new Antena(3497.2485983592023, 7191.88031045605, 2000));
  antenas.push_back(new Antena(3872.978286460858, 6722.218200328981, 2000));
  antenas.push_back(new Antena(4214.101292763677, 6306.938018742941, 2000));
  antenas.push_back(new Antena(3432.979046447077, 6667.836271787952, 2000));
  antenas.push_back(new Antena(3521.967656786943, 5852.1073436725155, 2000));
  antenas.push_back(new Antena(4481.067123783274, 6692.555330215692, 2000));
  antenas.push_back(new Antena(4901.291117054862, 5802.6692268170345, 2000));
  antenas.push_back(new Antena(5751.626726969136, 5525.815772426341, 2000));
  antenas.push_back(new Antena(5351.177980439739, 6692.555330215692, 2000));
  antenas.push_back(new Antena(6171.8507202407245, 6148.736044805401, 2000));
  antenas.push_back(new Antena(7101.287317123767, 5950.9835773834775, 2000));
  antenas.push_back(new Antena(6512.973726543543, 6870.532550895424, 2000));
  antenas.push_back(new Antena(6443.76036294587, 7473.677576532292, 2000));


  unsigned int i = 0;
  for(auto t: trazas){
    auto trz = t.second;

    devices.push_back(handle<Device>(new Device(
            trz
      )));

    if(i >= 1){
      break;
    }

    i++;
  }


  handle<Network3G> network3g = new Network3G({devices}, {antenas}, red_tubo->getCallbackEnvioMensaje());
  red_tubo->setRedMovil(network3g);



  handle<Source> src(new Source(END_SIM_TIME, red_tubo, traza));
  src->activate();

  src->addEndCallback(red_tubo);
  src->addEndCallback(cpu1);
  src->addEndCallback(cpu2);
  src->addEndCallback(cpu3);
  src->addEndCallback(cpu4);

  sim->run();

  // Listo!
  sim->end_simulation();


}


//class Clase2: public process{

  //public:

    //function<void(Clase2*, double)> run;

    //Clase2(): process("Clase 2"){
    //}
    //void inner_body(){
      //while(true){
        //this->run(this, 10);
      //}
    //}


//};


//class Clase1: public process{
  //private:
    

  //public:
    //Clase1(handle<Clase2> c2): process("Clase1"){
      //c2->run = [this](Clase2 *that, double to_hold){
        //that->passivate();
        //cout << "Vamos a esperar " << to_hold;
      //};
    //}
    //void inner_body(){
      //while(true){
        
      //}
    //}
//};



//void test_problema(){
 //auto sim = std::unique_ptr<simulation>(simulation::instance());
 //sim->begin_simulation(new sqsDll());
 //handle<Clase2> c2(new Clase2);
 //handle<Clase1> c1(new Clase1(c2));
 //c1->activate();

 //sim->run();



 //// Listo!
 //sim->end_simulation();
//}







int main(int argc, char *argv[])
{
  //test_simulacion_basica();
  test_simulacion_completa();

  cout << "Largo promedio de las colas " << obtenerPromedio() << endl;

  //test_problema();
  
  return 0;
}

#endif
