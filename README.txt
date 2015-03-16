*****************************************************
********************** ALLEGRO **********************
*****************************************************

Este proyecto utiliza la librería Allegro.
Esta librería debe ser obtenida a partir del site oficial (https://www.allegro.cc/files/) y, una vez añadida al directorio C:\ debe ser configurada de la siguiente manera, a partir de las Propriedades de la solución:

- Configuration Properties->C/C++->General: introduzca c:\allegro\include en Additional Include Directories. 
- Configuration Properties->Linker->General: introduzca c:\allegro\lib en Additional Library Directories. 
- Configuration Properties->Linker->Input: añada allegro-5.0.10-monolith-md-debug.lib a Additional Dependencies. 
- Configuration Properties->Debugging: introduzca PATH=c:\allegro\bin;%PATH% en Environment. 

Para más información sobre como configurar el proyecto, consulte https://wiki.allegro.cc/index.php?title=Windows,_Visual_Studio_2010_and_Allegro_5


**************************************************
*********** MAPAS CREADOS MEDIANTE DFS ***********
**************************************************

Ha sido implementada la creación de mapas de celdas triangulares, cuadradas y hexagonales usando el algoritmo de Búsqueda en Profundidad (DFS), lo que supone que existe siempre un camino entre dos celdas cualquieras. Sin embargo, la naturaleza recursiva del algoritmo requiere mucha utilización de memoria para mapas grandes, por lo que es posible que para dimensiones superiores a 50x50 la aplicación falle en tiempo de ejecución.

Por otro lado, una vez creado el mapa, es posible hallar el camino más corto entre dos celdas mediante el algoritmo A*. En este caso se ha utilizado la distancia Manhattan como función heurística para estimar el coste de llegada a la celda de destino. Aparte de ser dibujado en pantalla, el camino obtenido y su coste también son indicados en la consola.



**************************************************
*** MAPAS CREADOS MEDIANTE AUTÓMATAS CELULARES ***
**************************************************

Las reglas utilizadas para configurar los varios tipos de mapa consideran, como celdas vecinas a una celda (i,j), las celdas (i-1,j), (i+1,j), (i,j-1) y (i,j+1), o sea, las que se encuentran a la izquierda, derecha, arriba y abajo. Esto parece limitar la calidad de los resultados ya que, al no considerar las celdas en las diagonales, la información con la cual debemos decidir el nuevo estado de la celda actual es menor.

Tanto las reglas como la configuración inicial de las celdas y el número de generaciones varían según el tipo de mapa que se pretende. Estas han sido obtenidas a base de prueba y error, pero los resultados no son los ideales (los mapas “Montaña y Llanura” son los que presentan mejores resultados).

Aún así, se ha de llamar la atención para el hecho de que, con el fin de reducir el tiempo de creación de estos mapas, se han paralelizados varias partes del código con ciclos for largos: la inicialización de las celdas y la función evoluciona, que deben recorrer todas las celdas varias veces.