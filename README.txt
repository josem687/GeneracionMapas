*****************************************************
********************** ALLEGRO **********************
*****************************************************

Este proyecto utiliza la librer�a Allegro.
Esta librer�a debe ser obtenida a partir del site oficial (https://www.allegro.cc/files/) y, una vez a�adida al directorio C:\ debe ser configurada de la siguiente manera, a partir de las Propriedades de la soluci�n:

- Configuration Properties->C/C++->General: introduzca c:\allegro\include en Additional Include Directories. 
- Configuration Properties->Linker->General: introduzca c:\allegro\lib en Additional Library Directories. 
- Configuration Properties->Linker->Input: a�ada allegro-5.0.10-monolith-md-debug.lib a Additional Dependencies. 
- Configuration Properties->Debugging: introduzca PATH=c:\allegro\bin;%PATH% en Environment. 

Para m�s informaci�n sobre como configurar el proyecto, consulte https://wiki.allegro.cc/index.php?title=Windows,_Visual_Studio_2010_and_Allegro_5


**************************************************
*********** MAPAS CREADOS MEDIANTE DFS ***********
**************************************************

Ha sido implementada la creaci�n de mapas de celdas triangulares, cuadradas y hexagonales usando el algoritmo de B�squeda en Profundidad (DFS), lo que supone que existe siempre un camino entre dos celdas cualquieras. Sin embargo, la naturaleza recursiva del algoritmo requiere mucha utilizaci�n de memoria para mapas grandes, por lo que es posible que para dimensiones superiores a 50x50 la aplicaci�n falle en tiempo de ejecuci�n.

Por otro lado, una vez creado el mapa, es posible hallar el camino m�s corto entre dos celdas mediante el algoritmo A*. En este caso se ha utilizado la distancia Manhattan como funci�n heur�stica para estimar el coste de llegada a la celda de destino. Aparte de ser dibujado en pantalla, el camino obtenido y su coste tambi�n son indicados en la consola.



**************************************************
*** MAPAS CREADOS MEDIANTE AUT�MATAS CELULARES ***
**************************************************

Las reglas utilizadas para configurar los varios tipos de mapa consideran, como celdas vecinas a una celda (i,j), las celdas (i-1,j), (i+1,j), (i,j-1) y (i,j+1), o sea, las que se encuentran a la izquierda, derecha, arriba y abajo. Esto parece limitar la calidad de los resultados ya que, al no considerar las celdas en las diagonales, la informaci�n con la cual debemos decidir el nuevo estado de la celda actual es menor.

Tanto las reglas como la configuraci�n inicial de las celdas y el n�mero de generaciones var�an seg�n el tipo de mapa que se pretende. Estas han sido obtenidas a base de prueba y error, pero los resultados no son los ideales (los mapas �Monta�a y Llanura� son los que presentan mejores resultados).

A�n as�, se ha de llamar la atenci�n para el hecho de que, con el fin de reducir el tiempo de creaci�n de estos mapas, se han paralelizados varias partes del c�digo con ciclos for largos: la inicializaci�n de las celdas y la funci�n evoluciona, que deben recorrer todas las celdas varias veces.