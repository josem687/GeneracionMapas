#pragma once
#include "stdafx.h"
#include "Celda.h"
#include <time.h> 
#include <algorithm>  

/*
	Define los vecinos horizontales (inmediatamente a la izquierda o a la derecha) de la celda cuadrada (i,j)
*/
void Celda::setVecinosHorizontalesCuad(int i, int j, int maxJ){
	if(maxJ!=0){ //hay mas que una columna
		Vecino v;
		v.abierto=false;
		v.i=i;
		if(j==0){
			v.j=1;
			vecinos.push_back(v);
		}else if(j==maxJ){
			v.j=j-1;
			vecinos.push_back(v);
		}else{
			v.j=j-1;
			vecinos.push_back(v);
			v.j=j+1;
			vecinos.push_back(v);
		}
	}
}

/*
	Define los vecinos verticales (inmediatamente arriba o abajo) de la celda cuadrada (i,j)
*/
void Celda::setVecinosVerticalesCuad(int i, int j, int maxI){
	if(maxI!=0){ //hay mas que una fila
		Vecino v;
		v.abierto=false;
		v.j=j;
		if(i==0){
			v.i=1;
			vecinos.push_back(v);
		}else if(i==maxI){
			v.i=i-1;
			vecinos.push_back(v);
		}else{
			v.i=i-1;
			vecinos.push_back(v);
			v.i=i+1;
			vecinos.push_back(v);
		}

	}
}

/*
	Define los vecinos horizontales (inmediatamente a la izquierda o a la derecha) de la celda triangular (i,j)
*/
void Celda::setVecinosHorizontalesTriang(int i, int j, int maxJ){
	if(maxJ!=0){ //hay mas que una columna
		Vecino v;
		v.abierto=false;
		v.i=i;
		if(j==0){
			v.j=1;
			vecinos.push_back(v);
		}else if(j==maxJ){
			v.j=j-1;
			vecinos.push_back(v);
		}else{
			v.j=j-1;
			vecinos.push_back(v);
			v.j=j+1;
			vecinos.push_back(v);
		}
	}
}

/*
	Define los vecinos verticales (inmediatamente arriba o abajo) de la celda triangular (i,j)
*/
void Celda::setVecinosVerticalesTriang(int i, int j, int maxI){
	if(maxI!=0){ //hay mas que una fila
		Vecino v;
		v.abierto=false;
		v.j=j;
		if(i==0){
			if(j%2!=0){
				v.i=1;
				vecinos.push_back(v);
			}
		}else if(i==maxI){
			if((i%2==0 && j%2==0)||(i%2!=0 && j%2!=0)){
				v.i=i-1;
				vecinos.push_back(v);
			}			
		}else{
			if(i%2==0){
				if(j%2!=0){
					v.i=i+1;
					vecinos.push_back(v);
				}else{
					v.i=i-1;
					vecinos.push_back(v);
				}
			}else{				
				
				if(j%2==0){
					v.i=i+1;
					vecinos.push_back(v);
				}else{
					v.i=i-1;
					vecinos.push_back(v);
				}
			}
		}

	}
}

/*
	Define los vecinos verticales (Norte y Sur) de la celda hexagonal (i,j)
*/
void Celda::setVecinosVerticalesHexag(int i, int j, int maxI){
	
	if(maxI!=0){ //hay mas que una fila
		Vecino v;
		v.abierto=false;
		v.j=j;
		if(i==0){
			v.i=1;
			vecinos.push_back(v);
		}else if(i==maxI){
			v.i=i-1;
			vecinos.push_back(v);
		}else{
			v.i=i-1;
			vecinos.push_back(v);
			v.i=i+1;
			vecinos.push_back(v);
		}

	}
		
}

/*
	Define el vecino al noroeste de la celda hexagonal (i,j)
*/
void Celda::setVecinoHexagNW(int i, int j, int maxI, int maxJ){
	if(j!=0){
		Vecino v;
		v.abierto=false;
		v.j=j-1;
		if(i==0){
			if(j%2!=0){
				v.i=i;
				vecinos.push_back(v);
			}
		} else{
			if(j%2==0){
				v.i=i-1;
				vecinos.push_back(v);
			}else{
				v.i=i;
				vecinos.push_back(v);
			}
		}
	}
			
}

/*
	Define el vecino al noreste de la celda hexagonal (i,j)
*/
void Celda::setVecinoHexagNE(int i, int j, int maxI, int maxJ){
	if(j!=maxJ){
		Vecino v;
		v.abierto=false;
		v.j=j+1;
		if(i==0){
			if(j%2!=0){
				v.i=i;
				vecinos.push_back(v);
			}
		} else{
			if(j%2==0){
				v.i=i-1;
				vecinos.push_back(v);
			}else{
				v.i=i;
				vecinos.push_back(v);
			}
		}
	}
}

/*
	Define el vecino al sudoeste de la celda hexagonal (i,j)
*/
void Celda::setVecinoHexagSW(int i, int j, int maxI, int maxJ){
	if(j!=0){
		Vecino v;
		v.abierto=false;
		v.j=j-1;
		if(i==maxI){
			if(j%2==0){
				v.i=i;
				vecinos.push_back(v);
			}
		} else{
			if(j%2==0){
				v.i=i;
				vecinos.push_back(v);
			}else{
				v.i=i+1;
				vecinos.push_back(v);
			}
		}
	}
}

/*
	Define el vecino al sudeste de la celda hexagonal (i,j)
*/
void Celda::setVecinoHexagSE(int i, int j, int maxI, int maxJ){
	if(j!=maxJ){
		Vecino v;
		v.abierto=false;
		v.j=j+1;
		if(i==maxI){
			if(j%2==0){
				v.i=i;
				vecinos.push_back(v);
			}
		} else{
			if(j%2==0){
				v.i=i;
				vecinos.push_back(v);
			}else{
				v.i=i+1;
				vecinos.push_back(v);
			}
		}
	}
}

Celda::Celda(){};

/*
	Define el puntero que apunta a la celda precursora en el camino actual
*/
void Celda::setPrecursora(Celda * vec){
	precursora=vec;
}

/*
	Devuelve la coordenada i de la celda
*/
int Celda::getI(){
	return i;
}

/*
	Devuelve la coordenada j de la celda
*/
int Celda::getJ(){
	return j;
}

/*
	Constructor
*/
Celda::Celda(int i, int j, int maxI, int maxJ, int numlados)
{
	precursora = NULL;
	visitado = false;
	color = NULL;
	vecinos = vector<Vecino>();
	maxI = maxI-1;
	maxJ = maxJ-1;
	this->i = i;
	this->j = j;

	int number = rand() % 100;
	
	switch(numlados){
	case 4:
		if(number%2==0){
			setVecinosHorizontalesCuad(i,j,maxJ);
			setVecinosVerticalesCuad(i,j,maxI);
		} else{
			setVecinosVerticalesCuad(i,j,maxI);
			setVecinosHorizontalesCuad(i,j,maxJ);
		}	
		break;
	case 3:
		if(number%2==0){
			setVecinosHorizontalesTriang(i,j,maxJ);
			setVecinosVerticalesTriang(i,j,maxI);
		} else{
			setVecinosVerticalesTriang(i,j,maxI);
			setVecinosHorizontalesTriang(i,j,maxJ);
		}	

		break;
	case 6:
		setVecinosVerticalesHexag(i,j,maxI);

		setVecinoHexagNW(i, j, maxI, maxJ);
		setVecinoHexagNE(i, j, maxI, maxJ);
		setVecinoHexagSW(i, j, maxI, maxJ);
		setVecinoHexagSE(i, j, maxI, maxJ);
		random_shuffle ( vecinos.begin(), vecinos.end() );
	
		break;
	}

	
}

/*
	Devuelve la distancia estimada de la celda a la posicionada en (destI,destJ) según la distancia Manhattan
*/
int Celda::getCosteEstimadoADestino(int destI,int destJ){
	return abs(destI-i)+abs(destJ-j);
}

/*
	Devuelve true si la celda está en la posición (i,j)
*/
bool Celda::is(int i, int j){
	return (i==this->i && j==this->j);
}

Celda::~Celda()
{
}

/*
	Devuelve el vector de los vecinos de la celda (accesibles o no directamente)
*/
vector<Vecino> Celda::getVec(){
	return vecinos;
}

/*
	Devuelve true si la celda ha sido visitada con el algoritmo de busqueda en profundidad
*/
bool Celda::isVisitado(){
	return visitado;
}

/*
	Cambia la celda al estado de visitada, segun el algoritmo de busqueda en profundidad
*/
void Celda::visitar(){
	this->visitado = true;
}

/*
	Abre un acceso con la celda vecina posicionada en (i,j)
*/
void Celda::abrir(int i, int j){

	int k=0;
	for(auto vec: vecinos){

		if(vec.i==i && vec.j==j){
			vecinos[k].abierto=true;
			break;
		}
		++k;
	}
}

/*
	Devuelve un puntero a la celda precursora segun el camino buscado actualmente
*/
Celda* Celda::getPrecursora(){
	return precursora;
}

/*
	Devuelve un integer que representa un color
*/
int Celda::getColor(){
	return color;
}

/*
	Modifica el color de la celda segun un integer que lo representa
*/
void Celda::setColor(int color){
	this->color=color;
}
