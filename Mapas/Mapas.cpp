// Mapas.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#include "Mazmorra.h"
#include "Automata.h"
#include <time.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

/*
Parte del programa dedicado a los mapas creados mediante busqueda en profundidad
*/
int modoMazmorra(int m, int n){

	int opcion;
	ALLEGRO_DISPLAY * display = NULL;
	Mazmorra * miMazmorra = NULL;

	while (true){

		cout<<endl<<"Indique que tipo de celdas desea:"<<endl;
		cout<<"1: Rectangulares"<<endl;
		cout<<"2: Triangulares"<<endl;
		cout<<"3: Hexagonales"<<endl;
		cout<<"4: REGRESAR A INICIO"<<endl;
		cout<<"» ";
		cin>>opcion;

		if(opcion<1 || opcion>4){
			cout<<endl<<"!Opcion invalida!"<<endl;
		}else{
			if(display!=NULL){
				al_destroy_display(display);
				delete miMazmorra;
			}

			if(opcion==4){
				return 0;
			}

			switch(opcion){
			case 1:
				cout<<endl<<"Creando mapa Mazmorra con celdas rectangulares..."<<endl;
				miMazmorra = new Mazmorra(m,n,4);
				display = miMazmorra->dibujaMazmorra();
				al_flip_display();
				cout<< "Mazmorra construida..."<<endl;
				break;
			case 2:
				cout<<endl<<"Creando mapa Mazmorra con celdas triangulares..."<<endl;
				miMazmorra = new Mazmorra(m,n,3);
				display = miMazmorra->dibujaMazmorra();
				al_flip_display();
				cout<< "Mazmorra construida..."<<endl;
				break;
			case 3:
				cout<<endl<<"Creando mapa Mazmorra con celdas hexagonales..."<<endl;
				miMazmorra = new Mazmorra(m,n,6);
				display = miMazmorra->dibujaMazmorra();
				al_flip_display();
				cout<< "Mazmorra construida..."<<endl;
				break;
			}
			
			if(opcion==1 || opcion==2 || opcion==3){
			bool continua = true;
			while (continua){
				cout<<endl<<"Indique que desea hacer:"<<endl;
				cout<<"1: Encontrar camino mas corto entre dos puntos"<<endl;
				cout<<"2: VOLVER ATRAS"<<endl;
				cout<<"» ";
				cin>>opcion;

				switch(opcion){
				case 1:
					int initI, initJ, destI,destJ;
					cout << endl<<"Indique el origen y el destino en la forma OrigX OrigY DestX DestY: ";
					cin >> initI >> initJ >> destI >> destJ;

					if (initI >= m || initJ >= n || destI >=m || destJ>=n){
						cout << "Posiciones invalidas." << endl;
					}else{
						al_destroy_display(display);
						display = miMazmorra->pathfinding(initI,initJ,destI,destJ);
					}
					break;
				case 2:
					continua = false;
					break;
				default:
					cout<<endl<<"!Opcion invalida!"<<endl;
				}
			}
			}
		}
	}

	return 0;
}

/*
Parte del programa dedicado a los mapas creados mediante autómatas celulares
*/
int modoAutomata(int m, int n){

	int opcion;
	ALLEGRO_DISPLAY * display = NULL;
	Automata * miAutomata = NULL;

	while (true){

		cout<<endl<<"Indique que tipo de mapa desea:"<<endl;
		cout<<"1: Montaña y llanuras"<<endl;
		cout<<"2: Montaña, llanuras y mar"<<endl;
		cout<<"3: Pangea"<<endl;
		cout<<"4: Islas"<<endl;
		cout<<"5: REGRESAR A INICIO"<<endl;
		cout<<"» ";
		cin>>opcion;

		if(opcion<1 || opcion>5){
			cout<<endl<<"!Opcion invalida!"<<endl;
		}else{
			if(display!=NULL){
				al_destroy_display(display);
				delete miAutomata;
			}

			if(opcion==5){
				return 0;
			}

			switch(opcion){
			case 1:
				cout<<endl<<"Creando mapa de tipo Montañas y Llanuras con Automata Celular..."<<endl;
				break;
			case 2:
				cout<<endl<<"Creando mapa de tipo Montañas, Llanuras y Mar con Automata Celular..."<<endl;
				break;
			case 3:
				cout<<endl<<"Creando mapa de tipo Pangea con Automata Celular..."<<endl;
				break;
			case 4:
				cout<<endl<<"Creando mapa de tipo Islas con Automata Celular..."<<endl;
				break;
			}

			miAutomata = new Automata(m,n,opcion);
			display = miAutomata->dibujaMapa();
			al_flip_display();
			cout << "Mapa construido..."<<endl;
		}

	}

	return 0;

}

/*
Programa principal
*/
int main(int argc, char **argv)
{
	bool init = false;

	int m, n, opcion;

	cout << "\n\n";
	
	while (!init){
		cout << "Indique el numero de filas y de columnas: ";
		cin >> m >> n;
		if (m < 1 || n < 1 ){
			cout << "Dimensiones invalidas." << endl;
		}
		else{
			init = true;
		}

	}

	srand (time(NULL));
	while(true){
		cout<<endl<<"Indique que desea hacer:"<<endl;
		cout<<"1: Crear mapa Mazmorra (con Busqueda en Profundidad)"<<endl;
		cout<<"2: Crear mapa con Automata Celular"<<endl;
		cout<<"3: SALIR"<<endl;
		cout<<"» ";
		cin>>opcion;

		switch(opcion){
		case 1: 
			modoMazmorra(m, n); 
			break;
		case 2:
			modoAutomata(m, n);
			break;
		case 3:
			cout<<"\n!Adios!\n"<<endl;

			return 0;
		default:
			cout<<endl<<"!Opcion invalida!"<<endl;

		}

	}

	return 0;
}
