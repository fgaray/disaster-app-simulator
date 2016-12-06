#ifndef _H_CORE_H_
#define _H_CORE_H_

#include "../common/Process.hpp"
#include "../pe/PE.hpp"
#include "../pe/MessagePE.hpp"



class Core: public Process{
  private:
    PE_ptr current_pe;

    /* Callback para informar a la CPU que hemos terminado de ejecutar
     * */
    std::function<void(std::vector<std::tuple<PEName, MessagePE>>)> cpu_callback;
    MessagePE message;
    bool isEmpty;
    size_t id;


    double tiempo_iddle, tiempo_uso;
    double tiempo_parada;

  public:
    Core();
    void inner_body();
    void set_cpu_callback(std::function<void(std::vector<std::tuple<PEName, MessagePE>>)> fn);
    bool empty() const;
    bool ejecutando(PE_ptr pe) const;
    void ejecutar(PE_ptr pe, MessagePE message);
    double utilizacion();

};

#endif
