
# MEMORIA PRÁCTICA 1 INTELIGENCIA ARTIFICIAL


**[1. Análisis del problema (entorno, características del agente, etc.) ](#head1)
[2. Descripción de la solución planteada.](head2)
[3. Resultados obtenidos por la solución aportada en los distintos mapas.](head3)**



### <a name="head1"></a>1. Análisis del problema (entorno, características del agente, etc.).

En esta práctica vamos a estudiar y programar el comportamiento de un agente reactivo, en este caso vamos a usar un simulador de una aspiradora robótica la cual sólo posee 2 sensores, uno para detectar si ha chocado contra un objeto o pared y otro para detectar si la casilla en la que se encuentra está sucia. De por si este agente no conoce nada más. Además el agente puede realizar las siguientes acciones: girar izquierda 90º, girar derecha 90º , avanzar hacia delante una casilla, aspirar la casilla donde está o no hacer nada. Las 3 primeras acciones consumen 1 punto de energía, aspirar consume 2 y no hacer nada 0.

Acerca del entorno conocemos que el mundo en el simulador es un mapa cuadriculado de 10x10 donde cada casilla tiene una probabilidad de ensuciarse por cada unidad de tiempo que pasa (normalmente de 0.01).




### <a name="head2"></a>2. Descripción de la solución planteada.

El principal problema con el que nos encontramos es que no podemos saber a priori que casillas están sucias más allá de la casilla en la que nos encontramos ni tampoco por donde ya he limpiado anteriormente. Un problema añadido es además que no tenemos conocimiento alguno de donde están los objetos con los que podríamos chocar. Chocar continuamente con estos objetos supondría un malgasto de tiempo y energía del agente. Para solucionar este problema he optado por dotar al agente de una memoria en forma de matriz circular de enteros de dimensiones 10x10 en la cual el agente tiene una representación particular del espacio en el que se encuentra. En dicha matriz se plasma:

- La posición de los obstáculos que se indicá en la matriz (mundo_) con un -1.

- En que momento fue la ultima vez qué el agente estuvo en cada casilla en concreto en caso de que en dicha casilla no se halle ningún obstáculo.

El agente obtiene y plasma dicha información de la siguiente forma:

Posee un contador interno (tiempo_transcurrido) que muestra cuantos turnos lleva activo desde que se realizó la primera acción y que se incrementa en 1 cada vez que el agente realiza una acción.

Además se le han añadido 2 variables para que reflejar en todo momento su posición y su orientación (miOrientación).

De está forma el agente plasma en cada casilla en la que se encuentra el momento actual, de modo que al abandonar dicha casilla en su representación del mundo esta marca la última vez que estuvo en ella.

De antemano el agente no puede saber cuando en la casilla de delante hay objeto, sin embargo una vez choca con él por primera vez. En su representación interna del mundo lo graba en la casilla correspondiente. De modo que cada vez que el agente va a realizar una acción revisa su representación interna del mundo y evita las casillas donde ya tiene conocimiento de que hay obstáculos.




Haciendo uso de estas características al agente se le ha dotado de un comportamiento basado en lo siguiente:

- Inicialmente todas las posiciones de la matriz se encuentran a 0.

- El agente intenta siempre moverse a la posición inmediata de su izquierda/delante/derecha que hace más tiempo que no ha visitado. Esto se hace así porque dicha posición será posiblemente la más sucia de las cercanas debido a es la que el agente lleva más tiempo sin limpiar. Para tomar esta decisión no se tienen en cuenta las posiciones que contienen obstáculos.

- En caso de que 2 o 3 de sus posiciones inmediatas izquierda/delante/derecha contengan el valor de inicialización (0) intenta dirigirse a cualquiera de ellas arbitrariamente.




### <a name="head3"></a> 3. Resultados obtenidos por la solución aportada en los distintos mapas.




**Resultados obtenidos para Life Time = 2000 y Test case = 10:**




**agent.map:** Average Dirty Degree = 68.969,600

Average Consumed Energy = 2.911,000




**mapa1.map:** Average Dirty Degree = 95.793,600

Average Consumed Energy = 2.997,600




**mapa2.map:** Average Dirty Degree = 93.872,500

Average Consumed Energy = 2.957,100




**mapa3.map:** Average Dirty Degree = 126.830,200

Average Consumed Energy = 2.992,300
