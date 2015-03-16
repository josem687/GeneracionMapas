#include "stdafx.h"
#include "Mazmorra.h"
#include <stack>


#define SCALE 15
#define NUMLADOSCUAD 4
#define NUMLADOSTRIANG 3
#define NUMLADOSHEXAG 6

Mazmorra::Mazmorra(){};

Mazmorra::~Mazmorra(){
	delete celdas;
}

/*
Constructor, que recibe las dimensiones del mapa
*/
Mazmorra::Mazmorra(int m, int n, int numlados){

	this->m = m;
	this->n = n;
	this->numlados = numlados;

	celdas = new Celda*[m];

	for (int i = 0; i < m; ++i){
		celdas[i] = new Celda[n];
		for (int j = 0; j < n; ++j){
			celdas[i][j] = Celda(i, j, m, n,numlados);
		}
	}

	int initI = rand()%m;
	int initJ = rand()%n;
	destruirParedes(initI, initJ);

}

/*
Devuelve true si la lista closed contiene la celda que representa al vecino vec.
*/
bool Mazmorra::closedContiene(Vecino vec){
	for(auto celda: closed){
		if(celda->is(vec.i,vec.j)) return true;
	}

	return false;
}

/*
Devuelve true si la lista opened contiene la celda que representa al vecino vec.
*/
bool Mazmorra::openedContiene(Vecino vec){
	for(auto celda: opened){
		if(celda.first->is(vec.i,vec.j)) return true;
	}
	return false;
}

/* Encuentra el camino más corto entre dos celdas y lo dibuja en pantalla.
Una vez que, en este caso, el coste de ir de una celda A a una celda B es igual a ir de B a A, hacemos el camino al revés para ahorrarnos un ciclo for para la impresión en la consola del camino.
*/
ALLEGRO_DISPLAY * Mazmorra::pathfinding(int initI, int initJ, int destI, int destJ){

	printf("Calculando camino...\n");
	opened.push_back(pair<Celda*,int>(&celdas[destI][destJ],0));
	while(!opened.empty()){
		Celda * mejorCelda = NULL;
		int costeMinimo = 9999;
		list<pair<Celda*,int>>::iterator itMejorCelda;
		for(auto it = opened.begin(); it != opened.end(); it++){
			if((it->second+it->first->getCosteEstimadoADestino(initI,initJ))<costeMinimo){
				costeMinimo=it->second+it->first->getCosteEstimadoADestino(initI,initJ);
				mejorCelda = it->first;
				itMejorCelda = it;
			}
		}

		int nuevoCoste = 1+itMejorCelda->second;
		opened.erase(itMejorCelda);

		if(mejorCelda->getI()==initI && mejorCelda->getJ()==initJ) break;

		closed.push_back(mejorCelda);
		for(auto vec: mejorCelda->getVec()){

			if(vec.abierto && !closedContiene(vec)){
				bool isInOpened = openedContiene(vec);
				int costeVecino = nuevoCoste + celdas[vec.i][vec.j].getCosteEstimadoADestino(initI,initJ);
				if( ( !isInOpened ) || costeVecino < (nuevoCoste-1)+mejorCelda->getCosteEstimadoADestino(initI,initJ)){
					celdas[vec.i][vec.j].setPrecursora(mejorCelda);
					if(!isInOpened){
						opened.push_back(pair<Celda*,int>(&celdas[vec.i][vec.j],nuevoCoste));
					}

				}
			}

		}

	}

	switch(numlados){
	case NUMLADOSCUAD:
		return dibujaPathfindingCuad(initI,initJ,destI,destJ);
	case NUMLADOSTRIANG:
		return dibujaPathfindingTriang(initI,initJ,destI,destJ);
	case NUMLADOSHEXAG:
		return dibujaPathfindingHexag(initI,initJ,destI,destJ);
	}

	return NULL;
}

/*
	Dibuja el resultado del pathfinding con celdas cuadradas en la pantalla y muestra el camino y el coste en la consola
*/
ALLEGRO_DISPLAY * Mazmorra::dibujaPathfindingCuad(int initI, int initJ, int destI, int destJ){

	ALLEGRO_DISPLAY * display = dibujaMazmorra();
	al_set_new_window_position(100, 100);
	Celda * actual = &celdas[initI][initJ];
	int coste = -1;
	int i, j;

	printf("\nEl camino mas corto es:\n");
	while(actual!=NULL){

		i = actual->getI();
		j = actual->getJ();

		actual = actual->getPrecursora();

		if(i==initI && j==initJ){
			al_draw_filled_rectangle(initJ*SCALE+1, initI*SCALE+1, (initJ+1)*SCALE-1, (initI+1)*SCALE-1, al_map_rgb(255,0,0));
		}else{
			printf("-");
			al_draw_filled_rounded_rectangle(j*SCALE+3, i*SCALE+3, (j+1)*SCALE-3, (i+1)*SCALE-3, 3, 3, al_map_rgb(0,255,0));
		}

		printf("(%d,%d)",i,j);
		al_flip_display();
		coste++;
	}



	al_draw_filled_rectangle(destJ*SCALE+1, destI*SCALE+1, (destJ+1)*SCALE-1, (destI+1)*SCALE-1, al_map_rgb(0,0,255));
	al_flip_display();
	printf("\nCoste: %d\n",coste);

	for(auto c: opened){
		c.first->setPrecursora(NULL);
	}

	for(auto c: closed){
		c->setPrecursora(NULL);
	}
	opened.clear();
	closed.clear();

	return display;

}


/*
	Dibuja el resultado del pathfinding con celdas triangulares en la pantalla y muestra el camino y el coste en la consola
*/
ALLEGRO_DISPLAY * Mazmorra::dibujaPathfindingTriang(int initI, int initJ, int destI, int destJ){

	ALLEGRO_DISPLAY * display = dibujaMazmorra();
	al_set_new_window_position(100, 100);
	Celda * actual = &celdas[initI][initJ];
	int coste = -1;
	int i, j;

	printf("\nEl camino mas corto es:\n");
	while(actual!=NULL){

		i = actual->getI();
		j = actual->getJ();

		actual = actual->getPrecursora();

		if(i==initI && j==initJ){
			al_draw_filled_circle((initJ+1)*0.5*SCALE, (initI+0.5)*SCALE, 0.15*SCALE, al_map_rgb(255,0,0));
		}else{
			printf("-");
			al_draw_filled_circle((j+1)*0.5*SCALE, (i+0.5)*SCALE, 0.1*SCALE, al_map_rgb(0,255,0));
		}

		printf("(%d,%d)",i,j);
		al_flip_display();
		coste++;
	}



	al_draw_filled_circle((destJ+1)*0.5*SCALE, (destI+0.5)*SCALE, 0.15*SCALE, al_map_rgb(0,0,255));
	al_flip_display();
	printf("\nCoste: %d\n",coste);

	for(auto c: opened){
		c.first->setPrecursora(NULL);
	}

	for(auto c: closed){
		c->setPrecursora(NULL);
	}
	opened.clear();
	closed.clear();

	return display;

}

/*
	Dibuja el resultado del pathfinding con celdas hexagonales en la pantalla y muestra el camino y el coste en la consola
*/
ALLEGRO_DISPLAY * Mazmorra::dibujaPathfindingHexag(int initI, int initJ, int destI, int destJ){

	ALLEGRO_DISPLAY * display = dibujaMazmorra();
	al_set_new_window_position(100, 100);
	Celda * actual = &celdas[initI][initJ];
	int coste = -1;
	int i, j;

	printf("\nEl camino mas corto es:\n");
	while(actual!=NULL){

		i = actual->getI();
		j = actual->getJ();

		actual = actual->getPrecursora();

		if(i==initI && j==initJ){
			if(j%2==0){
				al_draw_filled_circle((initJ+0.75)*SCALE, (initI+0.5)*SCALE, 0.2*SCALE, al_map_rgb(255,0,0));
			}else{
				al_draw_filled_circle((initJ+0.75)*SCALE, (initI+1)*SCALE, 0.2*SCALE, al_map_rgb(255,0,0));
			}
		}else{
			printf("-");
			if(j%2==0){
				al_draw_filled_circle((j+0.75)*SCALE, (i+0.5)*SCALE, 0.15*SCALE, al_map_rgb(0,255,0));
			}else{
				al_draw_filled_circle((j+0.75)*SCALE, (i+1)*SCALE, 0.15*SCALE, al_map_rgb(0,255,0));
			}
		}

		printf("(%d,%d)",i,j);
		al_flip_display();
		coste++;
	}


		if(destJ%2==0){
			al_draw_filled_circle((destJ+0.75)*SCALE, (destI+0.5)*SCALE, 0.2*SCALE, al_map_rgb(0,0,255));
		}else{
			al_draw_filled_circle((destJ+0.75)*SCALE, (destI+1)*SCALE, 0.2*SCALE, al_map_rgb(0,0,255));
		}

	al_flip_display();
	printf("\nCoste: %d\n",coste);

	for(auto c: opened){
		c.first->setPrecursora(NULL);
	}

	for(auto c: closed){
		c->setPrecursora(NULL);
	}
	opened.clear();
	closed.clear();

	return display;

}

/*
Devuelve true si la celda con j=vecJ está inmediatamente a la derecha de la celda con j=currentJ
*/
bool Mazmorra::isVecRight(int currentJ,int vecJ){
	return vecJ==currentJ+1;
}

/*
Devuelve true si la celda con i=vecI está inmediatamente a la izquierda de la celda con j=currentJ
*/
bool Mazmorra::isVecLeft(int currentJ,int vecJ){
	return vecJ==currentJ-1;
}

/*
Devuelve true si la celda con i=vecI está inmediatamente abajo de la celda con i=currentI
*/
bool Mazmorra::isVecDown(int currentI,int vecI){
	return vecI==currentI+1 ;
}

/*
Define las lineas que componen el mapa en la pantalla
*/
ALLEGRO_DISPLAY * Mazmorra::dibujaMazmorra(){

	switch(numlados){
		case NUMLADOSCUAD: return dibujaMazmorraCuad();
		case NUMLADOSTRIANG: return dibujaMazmorraTriang();
		case NUMLADOSHEXAG: return dibujaMazmorraHexag();
	}

	return NULL;

}

/*
Define las lineas que componen el mapa de celdas triangulares en la pantalla
*/
ALLEGRO_DISPLAY * Mazmorra::dibujaMazmorraTriang(){

	ALLEGRO_DISPLAY *display = NULL;
	al_set_new_window_position(100, 100);
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return NULL;
	}

	display = al_create_display((n+1)*0.5*SCALE, m*SCALE);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return NULL;
	}

	al_clear_to_color(al_map_rgb(137, 91, 52));
	al_init_primitives_addon();

	//pintar espacios sin celdas a la izquierda
	for(int i=0;i<m;i++){
		if(i%2==0){
			al_draw_filled_triangle(0,i*SCALE,0,(i+1)*SCALE,0.5*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
		}else{
			al_draw_filled_triangle(0,i*SCALE,0.5*SCALE,i*SCALE,0,(i+1)*SCALE,al_map_rgb(0,0,0));
		}

	}

	//pintar espacios sin celdas a la derecha
	for(int i=0;i<m;i++){
		if(n%2!=0){
			if(i%2==0){
				al_draw_filled_triangle((n+1)*0.5*SCALE,i*SCALE,(n+1)*0.5*SCALE,(i+1)*SCALE,n*0.5*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
			}else{
				al_draw_filled_triangle(n*0.5*SCALE,i*SCALE,(n+1)*0.5*SCALE,i*SCALE,(n+1)*0.5*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
			}
		}else{ 
			if(i%2==0){
				al_draw_filled_triangle((n+1)*0.5*SCALE,i*SCALE,n*0.5*SCALE,i*SCALE,(n+1)*0.5*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
			}else{
				al_draw_filled_triangle((n+1)*0.5*SCALE,i*SCALE,n*0.5*SCALE,(i+1)*SCALE,(n+1)*0.5*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
			}
		}
	}


	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){

			vector<Vecino> vecinos = celdas[i][j].getVec();
			ALLEGRO_COLOR color;
			int grosor;
			for (Vecino vec : vecinos){

				if(vec.abierto){
					color = al_map_rgb(153, 76,0);
					grosor = 0.5;
				}else{
					color = al_map_rgb(41,31,21);
					grosor = 1;
				}

				if(isVecDown(i,vec.i)){
					al_draw_line(j*0.5*SCALE, vec.i*SCALE, (j+2)*0.5*SCALE, vec.i*SCALE, color, grosor); 
				}else if(isVecRight(j,vec.j)){

					if(i%2==0){
						if(j%2==0){ 
							al_draw_line(((j+1)*0.5)*SCALE, (i+1)*SCALE, (j+2)*0.5*SCALE, i*SCALE, color, grosor); 
						}else{
							al_draw_line(((j+1)*0.5)*SCALE, i*SCALE, (j+2)*0.5*SCALE, (i+1)*SCALE, color, grosor);
						}

					}else{
						if(j%2==0){ 
							al_draw_line(((j+1)*0.5)*SCALE, i*SCALE, (j+2)*0.5*SCALE, (i+1)*SCALE, color, grosor);
						}else{
							al_draw_line(((j+1)*0.5)*SCALE, (i+1)*SCALE, (j+2)*0.5*SCALE, i*SCALE, color, grosor); 
						}

					}
				}
			}
		}
	}
	return display;

}

/*
Define las lineas que componen el mapa de celdas hexagonales en la pantalla
*/
ALLEGRO_DISPLAY * Mazmorra::dibujaMazmorraHexag(){

	ALLEGRO_DISPLAY *display = NULL;
	al_set_new_window_position(100, 100);
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return NULL;
	}

	display = al_create_display((n+0.25)*SCALE, (m+0.5)*SCALE);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return NULL;
	}

	al_clear_to_color(al_map_rgb(137, 91, 52));
	al_init_primitives_addon();

	//pintar espacios sin celdas a la izquierda
	for(int i=0;i<m+1;i++){
		al_draw_filled_triangle(0,i*SCALE,0,(i+0.5)*SCALE,0.25*SCALE,i*SCALE,al_map_rgb(0,0,0));
		al_draw_filled_triangle(0,(i+0.5)*SCALE,0,(i+1)*SCALE,0.25*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
	}

	
	//pintar espacios sin celdas a la derecha
	for(int i=0;i<m+1;i++){
		if(n%2!=0){
			al_draw_filled_triangle(n*SCALE,i*SCALE,(n+0.25)*SCALE,i*SCALE,(n+0.25)*SCALE,(i+0.5)*SCALE,al_map_rgb(0,0,0));
			al_draw_filled_triangle(n*SCALE,(i+1)*SCALE,(n+0.25)*SCALE,(i+0.5)*SCALE,(n+0.25)*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
		}else{ 
			al_draw_filled_triangle(n*SCALE,(i+0.5)*SCALE,(n+0.25)*SCALE,i*SCALE,(n+0.25)*SCALE,(i+0.5)*SCALE,al_map_rgb(0,0,0));
			al_draw_filled_triangle(n*SCALE,(i+0.5)*SCALE,(n+0.25)*SCALE,(i+0.5)*SCALE,(n+0.25)*SCALE,(i+1)*SCALE,al_map_rgb(0,0,0));
		}
	}

	//pintar espacios sin celdas de arriba
	for(int j=1;j<n;j=j+2){
			al_draw_filled_triangle(j*SCALE,0,(j+0.25)*SCALE,0,(j+0.25)*SCALE,0.5*SCALE,al_map_rgb(0,0,0));
			al_draw_filled_rectangle((j+0.25)*SCALE,0,(j+1)*SCALE,0.5*SCALE,al_map_rgb(0,0,0));
			al_draw_filled_triangle((j+1)*SCALE,0.5*SCALE,(j+1)*SCALE,0,(j+1.25)*SCALE,0,al_map_rgb(0,0,0));
	}


	//pintar espacios sin celdas de abajo
	for(int j=0;j<n;j=j+2){
			al_draw_filled_triangle(j*SCALE,(m+0.5)*SCALE,(j+0.25)*SCALE,m*SCALE,(j+0.25)*SCALE,(m+0.5)*SCALE,al_map_rgb(0,0,0));
			al_draw_filled_rectangle((j+0.25)*SCALE,m*SCALE,(j+1)*SCALE,(m+0.5)*SCALE,al_map_rgb(0,0,0));
			al_draw_filled_triangle((j+1)*SCALE,(m+0.5)*SCALE,(j+1)*SCALE,m*SCALE,(j+1.25)*SCALE,(m+0.5)*SCALE,al_map_rgb(0,0,0));
	}

	
	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){

			vector<Vecino> vecinos = celdas[i][j].getVec();
			ALLEGRO_COLOR color;
			int grosor;
			for (Vecino vec : vecinos){

				if(vec.abierto){
					color = al_map_rgb(153, 76,0);
					grosor = 0.5;
				}else{
					color = al_map_rgb(41,31,21);
					grosor = 1;
				}

				
				if(isVecDown(i,vec.i) && j==vec.j){
					if(j%2==0){
						al_draw_line((j+0.25)*SCALE, vec.i*SCALE, (j+1)*SCALE, vec.i*SCALE, color, grosor); 
					}else{
						al_draw_line((j+0.25)*SCALE, (vec.i+0.5)*SCALE, (j+1)*SCALE, (vec.i+0.5)*SCALE, color, grosor); 
					}
				}else if(isVecLeft(j,vec.j)){

					if(j%2==0){
						if(i==vec.i){ 
							al_draw_line(j*SCALE, (i+0.5)*SCALE, (j+0.25)*SCALE, (i+1)*SCALE, color, grosor);
						}
					}else{
						if(i!=vec.i){ 
							al_draw_line(j*SCALE, (i+1)*SCALE, (j+0.25)*SCALE, (i+1.5)*SCALE, color, grosor);
						}

					}
				}else if(isVecRight(j,vec.j)){

					if(j%2==0){
						if(i==vec.i){ 
							al_draw_line((j+1.25)*SCALE, (i+0.5)*SCALE, (j+1)*SCALE, (i+1)*SCALE, color, grosor);
						}
					}else{
						if(i!=vec.i){ 
							al_draw_line((j+1.25)*SCALE, (i+1)*SCALE, (j+1)*SCALE, (i+1.5)*SCALE, color, grosor);
						}

					}
				}
			}
		}
	}
	
	return display;

}


/*
Define las lineas que componen el mapa de celdas cuadradas en la pantalla
*/
ALLEGRO_DISPLAY * Mazmorra::dibujaMazmorraCuad(){

	ALLEGRO_DISPLAY *display = NULL;
	al_set_new_window_position(100, 100);
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return NULL;
	}

	display = al_create_display(n*SCALE, m*SCALE);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return NULL;
	}

	al_clear_to_color(al_map_rgb(137, 91, 52));
	al_init_primitives_addon();

	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){

			vector<Vecino> vecinos = celdas[i][j].getVec();
			ALLEGRO_COLOR color;
			
			for (Vecino vec : vecinos){
				
				if(vec.abierto){
					color = al_map_rgb(153, 76,0);
				}else{
					color = al_map_rgb(41,31,21);
				}

				if(isVecDown(i,vec.i)){
					al_draw_line(j*SCALE, vec.i*SCALE, (j+1)*SCALE, vec.i*SCALE, color, 1);
				}else if(isVecRight(j,vec.j)){
					al_draw_line(vec.j*SCALE, i*SCALE, vec.j*SCALE, (i+1)*SCALE, color, 1);
				}
			}
		}

		
	}

	return display;

}

/*
Destruye algunas paredes entre las varias celdas del mapa, de modo a generar un mapa tipo Dungeon con el algoritmo de busqueda en profundidad. (currentI,currentJ) definen la próxima celda que se visita.
*/
void Mazmorra::destruirParedes(int currentI, int currentJ){

	celdas[currentI][currentJ].visitar();

	for (Vecino elem : celdas[currentI][currentJ].getVec()){

		if (!celdas[elem.i][elem.j].isVisitado()){
			celdas[elem.i][elem.j].abrir(currentI, currentJ);
			celdas[currentI][currentJ].abrir(elem.i, elem.j);
			destruirParedes(elem.i, elem.j);
		}
	}

}
