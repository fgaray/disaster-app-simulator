- Dado que tenemos 2 redes, hay que modelarlas de manera genérica.
- Cada CPU puede ejecutarse sobre un rack o nodo móvil, es una clase compartida.
- La red también es compartida, pero la tabla de routeo se va modificando.



# Trazas de BonnMotion y The ONE

Las trazas van a estar convertidas a un archivo CSV de, donde cada línea tiene
una tupla de la forma:

(i, t, x, y).

i: ID del nodo
t: Tiempo de simulación.
x,y: Posición del nodo en el tiempo t.


# 3g

LTE Hard Handover algorithm

Recepción de destino > recepcion de fuente + HO


# Fat Tree

Encontrar un k^3/4 que nos de la cantidad de nodos en un k-fat tree

Las direcciones IP 


10.pod.switch.1 => switch e k


Switch core: 10.k.j.i


Procesador:
10.pow.switch.id id => 2


El enrutamiento utiliza 2 tablas:

- Tabla de prefijos.
- Tabla de sufijos.


El byte que hay que mirar depende de la capa y de si el destino está abajo.

Si el destino está abajo entonces se miran los N bytes de la capa, en caso
contrario se utiliza el último byte y la tabla secundaria.

K = Cantidad de puertos del switch

El máximo nivel de un fat tree (este tipo) es de 3 niveles
