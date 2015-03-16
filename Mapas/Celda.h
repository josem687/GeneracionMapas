#pragma once
#include <vector>

using namespace std;

struct Vecino{
	int i;
	int j;
	bool abierto;
};

class Celda
{
public:

	bool isVisitado();
	void visitar();
	void abrir(int i, int j);
	void setPrecursora(Celda * vec);
	vector<Vecino> getVec();
	int getCosteEstimadoADestino(int destI, int destJ);
	Celda* getPrecursora();
	int getI();
	int getJ();
	int getColor();
	void setColor(int color);
	bool is(int i, int j);
	Celda(int i, int j, int maxI, int maxJ, int numlados);
	Celda();
	~Celda();

private:
	int i;
	int j;
	int color;
	Celda* precursora;
	bool visitado;
	vector<Vecino> vecinos;
	void setVecinosHorizontalesCuad(int i, int j, int maxJ);
	void setVecinosVerticalesCuad(int i, int j, int maxI);
	void setVecinosHorizontalesTriang(int i, int j, int maxJ);
	void setVecinosVerticalesTriang(int i, int j, int maxI);
	void setVecinosHexag(int i, int j, int maxI, int maxJ);
	void setVecinosVerticalesHexag(int i, int j, int maxI);
	void setVecinoHexagNW(int i, int j, int maxI, int maxJ);
	void setVecinoHexagNE(int i, int j, int maxI, int maxJ);
	void setVecinoHexagSW(int i, int j, int maxI, int maxJ);
	void setVecinoHexagSE(int i, int j, int maxI, int maxJ);

};

