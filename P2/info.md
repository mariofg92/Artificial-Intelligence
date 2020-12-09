# MEMORIA PRÁCTICA 2

### 1. Peculiaridades del método de búsqueda con adversario implementado.
El método de búsqueda usado es el Método MiniMax que ya venía implementado. Este
utiliza una función de valoración en cuya implementación me he centrado en dicha práctica.
### 2. Descripción de la función de valoración de los tableros.
El principal planteamiento de dicha función de valoración se basa en obtener la mayor
suciedad recogida que sea posible y para ello tener un posicionamiento en el tablero lo más
cercano a todos los puntos donde hay suciedad (ignorando los muros u obstáculos).
Explicación en profundidad de como se ha implementado:
* La función de valoración se sirve de las siguientes funciones auxiliares:
Distancia → Calcula la distancia NO euclidea a una casilla que se pasa por parámetro. La
distancia calculada no es en linea recta sino una distancia real en pasos sobre el tablero (sin
tener en cuenta obstáculos).
CosteMovimiento → Cálcula el número de pasos (incluyendo giros) que hay que dar hasta llegar
a una casilla que se le pasa por parámetro, para ello hace uso de la función Distancia. (Ignora
los obstáculos que pudiera haber entre medias).
MejorPosicion → Hace uso de la función CosteMovimiento y DirtAmount para calcular en que
casilla la aspiradora se encuentra más cercana a donde haya más suciedad.
Por último la función Valoración valora el Marcador, el posicionamiento de la aspiradora y el
marcador del contrario con este orden de prioridad.
