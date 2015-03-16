#include "stdafx.h"
#include "Automata.h"

#include <ppl.h>

#define	MONTA�A 0
#define LLANURA 1
#define AGUA 2

#define CICLOSML 15
#define CICLOSMLM 4
#define CICLOSP 4
#define CICLOSI 3 
#define CICLOSGC 10 

#define SCALE 5

using namespace concurrency;

Automata::Automata(){}

Automata::~Automata()
{
	delete celdas1;
	delete celdas2;
}

/*
Constructor, que recibe las dimensiones del mapa y el tipo
*/
Automata::Automata(int m, int n, int opcion){

	this->m = m;
	this->n = n;

	celdas1 = new Celda*[m];
	celdas2 = new Celda*[m];

	switch (opcion){
	case 1:
		iniciaMonta�aLlanura();
		break;
	case 2:
		iniciaMonta�aLlanuraAgua();
		break;
	case 3:
		iniciaPangea();
		break;
	case 4:
		iniciaIslas();
		break;
	case 5:
		iniciaGranContinentes();
		break;
	}

	evoluciona(opcion);

}

/*
	Inicializa las celdas para mapa de tipo Monta�a y Llanura
*/
void Automata::iniciaMonta�aLlanura(){
	parallel_for(int(0), m, [&](int i){
		celdas1[i] = new Celda[n];
		celdas2[i] = new Celda[n];
		for (int j = 0; j < n; ++j){
			celdas1[i][j] = Celda(i, j, m, n,4);
			celdas2[i][j] = Celda(i, j, m, n,4);
			int color = rand() % 2;

			celdas1[i][j].setColor(color);
			celdas2[i][j].setColor(color);
		}
	});
}

/*
	Inicializa las celdas para mapa de tipo Monta�a, Llanura y Mar
*/
void Automata::iniciaMonta�aLlanuraAgua(){

parallel_for(int(0), m, [&](int i){
	
		celdas1[i] = new Celda[n];
		celdas2[i] = new Celda[n];
		for (int j = 0; j < n; ++j){
			celdas1[i][j] = Celda(i, j, m, n,4);
			celdas2[i][j] = Celda(i, j, m, n,4);

			int color = rand() % 100;
			if(color<5){
				if(color<3) color=LLANURA;
				else color=MONTA�A;
				celdas1[i][j].setColor(color);
				celdas2[i][j].setColor(color);
			}else{
			celdas1[i][j].setColor(AGUA);
			celdas2[i][j].setColor(AGUA);
			}
		}
		
	});

	int maxRandoms = ((2*m/6)*(2*n/6))*0.1;
	for (int k = 0; k < maxRandoms; k++){
		int i = (m/6)+rand()%(4*m/6);
		int j = (2*n/6)+rand()%(2*n/6);
		int color = rand() % 100;
		if(color<60){
			celdas1[i][j].setColor(LLANURA);
			celdas2[i][j].setColor(LLANURA);
		}else{
			celdas1[i][j].setColor(MONTA�A);
			celdas2[i][j].setColor(MONTA�A);
		}
	}
}

/*
	Inicializa las celdas para mapa de tipo Pangea
*/
void Automata::iniciaPangea(){

	parallel_for(int(0), m, [&](int i){
	
		celdas1[i] = new Celda[n];
		celdas2[i] = new Celda[n];
		for (int j = 0; j < n; ++j){
			celdas1[i][j] = Celda(i, j, m, n,4);
			celdas2[i][j] = Celda(i, j, m, n,4);
			if(rand()%100<2){
				celdas1[i][j].setColor(MONTA�A);
				celdas2[i][j].setColor(MONTA�A);
			}else{
			celdas1[i][j].setColor(AGUA);
			celdas2[i][j].setColor(AGUA);
			}
			
		}
		
	});

	int maxRandoms = ((2*m/6)*(2*n/6))*0.2;
	for (int k = 0; k < maxRandoms; k++){
		int i = (2*m/6)+rand()%(2*m/6);
		int j = (2*n/6)+rand()%(2*n/6);
		int color = rand() % 100;
		if(color<10){
			celdas1[i][j].setColor(AGUA);
			celdas2[i][j].setColor(AGUA);
		}else if(color<50){
			celdas1[i][j].setColor(LLANURA);
			celdas2[i][j].setColor(LLANURA);
		}else{
			celdas1[i][j].setColor(MONTA�A);
			celdas2[i][j].setColor(MONTA�A);
		}
	}

}

/*
	Inicializa las celdas para mapa de tipo Islas
*/
void Automata::iniciaIslas(){
	parallel_for(int(0), m, [&](int i){
		celdas1[i] = new Celda[n];
		celdas2[i] = new Celda[n];
		for (int j = 0; j < n; ++j){
			celdas1[i][j] = Celda(i, j, m, n,4);
			celdas2[i][j] = Celda(i, j, m, n,4);
			celdas1[i][j].setColor(AGUA);
			celdas2[i][j].setColor(AGUA);
		}
	});

	int maxRandoms = (m*n)*0.1;
	for (int k = 0; k < maxRandoms; k++){
		int i = rand() % m;
		int j = rand() % n;
		int color = rand() % 2;
		celdas1[i][j].setColor(color);
		celdas2[i][j].setColor(color);
	}
}

/*
	Inicializa las celdas para mapa de tipo Gran Continentes
*/
void Automata::iniciaGranContinentes(){
	parallel_for(int(0), m, [&](int i){
		celdas1[i] = new Celda[n];
		celdas2[i] = new Celda[n];
		for (int j = 0; j < n; ++j){
			celdas1[i][j] = Celda(i, j, m, n,4);
			celdas2[i][j] = Celda(i, j, m, n,4);
			celdas1[i][j].setColor(AGUA);
			celdas2[i][j].setColor(AGUA);
		}
	});

	for(int k=0; k<5; k++){
		int i=rand()%m;
		int j=rand()%n;
		int color = rand()%2;
		celdas1[i][j].setColor(color);
		celdas2[i][j].setColor(color);
	}
}


/*
	Devuelve el nuevo color de la celda (i,j) segun las reglas definidas para el tipo de mapa Monta�a y Llanura
*/
int Automata::reglaMonta�aLlanura(Celda** celdas, int i, int j){

	int vecinosMonta�a = 0;
	int vecinosLlanura = 0;
	int color;

	for(auto vecino : celdas[i][j].getVec()){
		color = celdas[vecino.i][vecino.j].getColor();
		switch(color){
		case MONTA�A:
			vecinosMonta�a++;
			break;
		case LLANURA:
			vecinosLlanura++;
			break;
		}

	}


	if(vecinosLlanura>vecinosMonta�a){
		return LLANURA;
	}

	if(vecinosLlanura<vecinosMonta�a){
		return MONTA�A;
	}

	return celdas[i][j].getColor();
	
}

/*
	Devuelve el nuevo color de la celda (i,j) segun las reglas definidas para el tipo de mapa Monta�a,Llanura y Mar
*/
int Automata::reglaMonta�aLlanuraMar(Celda** celdas, int i, int j){

	int vecinosMonta�a = 0;
	int vecinosLlanura = 0;
	int vecinosAgua = 0;
	int currentColor=celdas[i][j].getColor();
	int color;

	for(auto vecino : celdas[i][j].getVec()){
		color = celdas[vecino.i][vecino.j].getColor();
		switch(color){
		case MONTA�A:
			vecinosMonta�a++;
			break;
		case LLANURA:
			vecinosLlanura++;
			break;
		case AGUA:
			vecinosAgua++;
			break;
		}

	}

	if(currentColor==MONTA�A || vecinosMonta�a>2) return MONTA�A;

	if(vecinosMonta�a>0){
		if(vecinosAgua>0) return LLANURA;
		return MONTA�A;
	}

	if(vecinosLlanura>2 && vecinosAgua>0){
		return LLANURA;
	}

	if(vecinosLlanura>vecinosMonta�a){
		return LLANURA;
	}

	return celdas[i][j].getColor();
	
}


/*
	Devuelve el nuevo color de la celda (i,j) segun las reglas definidas para el tipo de mapa Gran Continentes
*/
int Automata::reglaGranContinente(Celda** celdas, int i, int j){

	
	int coloractual = celdas[i][j].getColor();

	if(coloractual==MONTA�A) return MONTA�A;

	int vecinosAgua = 0;
	int vecinosMonta�a = 0;
	int vecinosLlanura = 0;
	int color;

	for(auto vecino : celdas[i][j].getVec()){

		color = celdas[vecino.i][vecino.j].getColor();

		switch(color){
		case AGUA: 
			vecinosAgua++;
			break;
		case MONTA�A:
			vecinosMonta�a++;
			break;
		case LLANURA:
			vecinosLlanura++;
			break;
		}

	}

	if(vecinosMonta�a>0 && coloractual==AGUA){
		return MONTA�A;
	}

	if(vecinosLlanura>0 && coloractual==AGUA){
		return LLANURA;
	}

	if(coloractual!=AGUA){
		return LLANURA;
	}

	return celdas[i][j].getColor();

}

/*
	Devuelve el nuevo color de la celda (i,j) segun las reglas definidas para el tipo de mapa Islas
*/
int Automata::reglaIslas(Celda** celdas, int i, int j){

	int vecinosAgua = 0;
	int vecinosMonta�a = 0;
	int vecinosLlanura = 0;
	int colorActual = celdas[i][j].getColor();
	int color;

	for(auto vecino : celdas[i][j].getVec()){

		color = celdas[vecino.i][vecino.j].getColor();

		switch(color){
		case AGUA: 
			vecinosAgua++;
			break;
		case MONTA�A:
			vecinosMonta�a++;
			break;
		case LLANURA:
			vecinosLlanura++;
			break;
		}

	}

	
	if (colorActual == MONTA�A){
		if (vecinosAgua == 4) return AGUA;
		return MONTA�A;
	}

	if(vecinosMonta�a==4){
		return MONTA�A;
	}
	if (vecinosMonta�a == 2 && vecinosAgua!=2){
		return MONTA�A;
	}

	if (vecinosLlanura == 4){
		color = rand() % 2;
		return color;
	}

	if (vecinosMonta�a == vecinosAgua || vecinosLlanura>0){
		return LLANURA;
	}

	return celdas[i][j].getColor();

}

/*
	Devuelve el nuevo color de la celda (i,j) segun las reglas definidas para el tipo de mapa Pangea
*/
int Automata::reglaPangea(Celda** celdas, int i, int j){
	
	int vecinosMonta�a = 0;
	int vecinosLlanura = 0;
	int vecinosAgua = 0;
	int currentColor=celdas[i][j].getColor();
	int color;

	for(auto vecino : celdas[i][j].getVec()){
		color = celdas[vecino.i][vecino.j].getColor();
		switch(color){
		case MONTA�A:
			vecinosMonta�a++;
			break;
		case LLANURA:
			vecinosLlanura++;
			break;
		case AGUA:
			vecinosAgua++;
			break;
		}

	}

	if(currentColor==MONTA�A && vecinosMonta�a>0) return MONTA�A;

	if(currentColor==LLANURA && vecinosLlanura==0) return AGUA;

	if(vecinosMonta�a>0){
		if(vecinosAgua>0) return LLANURA;
		return MONTA�A;
	}

	if(vecinosLlanura>2 && vecinosAgua>0){
		return LLANURA;
	}

	if(vecinosLlanura>vecinosMonta�a){
		return LLANURA;
	}

	if(vecinosLlanura<vecinosMonta�a){
		return MONTA�A;
	}

	return celdas[i][j].getColor();
	
	
}

/*
Crea sucesivas generaciones del mapa seg�n la reglas del tipo de mapa
*/
void Automata::evoluciona(int opcion){


	bool iteracionPar = true;
	Celda** celdasAnteriores = NULL;
	Celda** celdasNuevas = NULL;
	int color, numciclos;

	switch(opcion){
	case 1:
		numciclos = CICLOSML;
		break;
	case 2:
		numciclos = CICLOSMLM;
		break;
	case 3:
		numciclos = CICLOSP;
		break;
	case 4:
		numciclos = CICLOSI;
		break;
	case 5:
		numciclos = CICLOSGC;
		break;
	}


	for(int k=0; k<numciclos; ++k){

		if(iteracionPar){
			celdasAnteriores = celdas1;
			celdasNuevas = celdas2;

		}else{
			celdasAnteriores = celdas2;
			celdasNuevas = celdas1;

		}

		parallel_for(int(0), m, [&](int i){
			for(int j=0; j<n; ++j){
				switch(opcion){
				case 1:
					color = reglaMonta�aLlanura(celdasAnteriores,i,j);
					break;
				case 2:
					color = reglaMonta�aLlanuraMar(celdasAnteriores,i,j);
					break;
				case 3:
					color = reglaPangea(celdasAnteriores,i,j);
					break;
				case 4:
					color = reglaIslas(celdasAnteriores,i,j);
					break;
				case 5:
					color = reglaGranContinente(celdasAnteriores,i,j);
					break;
				}
				celdasNuevas[i][j].setColor(color);

			}
		});

		iteracionPar = !iteracionPar;
	}

	
}

/*
	Dibuja el mapa
*/
ALLEGRO_DISPLAY * Automata::dibujaMapa(){
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
	int color;
	ALLEGRO_COLOR al_color;
	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){
			color = celdas1[i][j].getColor();

			switch(color){
			case MONTA�A:
				al_color = al_map_rgb(60,30,0);
				break;
			case LLANURA:
				al_color = al_map_rgb(87,193,17);
				break;
			case AGUA:
				al_color = al_map_rgb(22,140,243);
				break;
			}

			al_draw_filled_rectangle(j*SCALE, i*SCALE, (j+1)*SCALE, (i+1)*SCALE, al_color);
		}
	}

	return display;

}


