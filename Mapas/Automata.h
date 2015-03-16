#pragma once
#include "Celda.h"
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Automata
{
public:
	Automata();
	~Automata();
	Automata(int m,int n, int opcion);

	ALLEGRO_DISPLAY * dibujaMapa();

private:
	Celda** celdas1;
	Celda** celdas2;

	int m;
	int n;

	bool isVecRight(int currentJ,int vecJ);
	bool isVecDown(int currentI,int vecI);

	int reglaMonta�aLlanura(Celda** celdas, int i, int j);
	int reglaMonta�aLlanuraMar(Celda** celdas, int i, int j);
	int reglaPangea(Celda** celdas, int i, int j);
	int reglaIslas(Celda** celdas, int i, int j);
	int reglaGranContinente(Celda** celdas, int i, int j);

	void evoluciona(int opcion);

	void iniciaMonta�aLlanura();
	void iniciaMonta�aLlanuraAgua();
	void iniciaPangea();
	void iniciaIslas();
	void iniciaGranContinentes();

};

