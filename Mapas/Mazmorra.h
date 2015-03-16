#pragma once
#include "Celda.h"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

class Mazmorra
{
public:
	Mazmorra(int m,int n, int numlados);
	Mazmorra();
	~Mazmorra();
	
	ALLEGRO_DISPLAY * pathfinding(int initI, int initJ, int destI, int destJ);
	ALLEGRO_DISPLAY * dibujaMazmorra();

private:
	Celda** celdas;
	list<pair<Celda*,int>> opened;
	list<Celda*> closed;
	int m;
	int n;
	int numlados;
	bool closedContiene(Vecino vec);
	bool openedContiene(Vecino vec);

	bool isVecRight(int currentJ,int vecJ);
	bool isVecLeft(int currentJ,int vecJ);
	bool isVecDown(int currentI,int vecI);

	void destruirParedes(int currentI, int currentJ);

	ALLEGRO_DISPLAY * dibujaMazmorraCuad();
	ALLEGRO_DISPLAY * dibujaMazmorraTriang();
	ALLEGRO_DISPLAY * dibujaMazmorraHexag();
	ALLEGRO_DISPLAY * dibujaPathfindingCuad(int initI, int initJ, int destI, int destJ);
	ALLEGRO_DISPLAY * dibujaPathfindingTriang(int initI, int initJ, int destI, int destJ);
	ALLEGRO_DISPLAY * dibujaPathfindingHexag(int initI, int initJ, int destI, int destJ);
	
};




