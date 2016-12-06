#ifndef _PROMEDIO_COLAS_H_
#define _PROMEDIO_COLAS_H_

#include <vector>
using namespace std;


void agregarTamano(size_t n);
double obtenerPromedio();

class LargoPromedioCola{
  private:

    vector<size_t> valores;

  public:
    LargoPromedioCola();

    void agregarTamano(size_t n);

    double obtenerPromedio();



};




#endif
