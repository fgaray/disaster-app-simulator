# Simulador para el ramo "Microsimulaciones sociales"

## Etapas

### Etapa 1

Consiste en la implementación de la simulación de PE (Process Elements) que van
a procesar los mensajes de la aplicación sobre un cluster.

### Etapa 2

Implementar como los PE se mapean sobre procesadores y cores reales y como estos
se comunican mediante una red FAT TREE de switchs.

### Etapa 3

Comunicación entre la aplicación corriendo sobre PE y la red de comunicación
3g/4g con los voluntarios de acuerdo a un modelo de movilidad de las personas.

### Etapa 4

Agregar métricas de evaluación y mejorar el modelo de movilidad.


## Organización del código

El código se encuentra en src/ y se puede compiar con make. Se utiliza la
libreria [libcppsim](http://www.moreno.marzolla.name/software/).

Para compilar es necesario definir la variable de entorno LIBCPPSIM_ROOT para
que apunte a la raiz del directorio de libcppsim.

```
export LIBCPPSIM_ROOT=/home/user/libcppsim/
```
