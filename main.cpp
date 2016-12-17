#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include "position.hpp"
#include "piece.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "pawn.hpp"

using namespace std;
void Cargar(Piece***);
Piece*** crearTablero(int rows, int cols);
void Guardar(Piece***);
void destruirTablero(Piece*** tablero, int rows, int cols);
void imprimir(Piece*** tablero);
void chessInit(Piece*** tablero);
int charToInt(char coordenada);
bool ganar(Piece*** tablero);

int main(int argc, char const *argv[]){
	const int ROWS = 8;
	const int COLS = 8;
	int opcion= 0;
	//Se le da la opcion a cargar la partida mas reciente, o iniciar de nuevo;
	std::cout << "Desea cargar partida? 1/2 " << std::endl;
	while(!(opcion>0 && opcion <3)){
		std::cin >> opcion;
		if (opcion> 0 && opcion <3) {
			 break;
		}
		std::cout << "vuelva a intentarlo" << std::endl;
	}

	Piece*** tablero =crearTablero(ROWS,COLS);

	if (opcion ==1) {
		Cargar(tablero );
		std::cout << "Se continuara con la partida anterior." << std::endl;
	}

	if (opcion ==2) {
		std::cout << "Se continuara con una nueva partida." << std::endl;
	}


	string nombre1,nombre2;
	cout<<"Jugador1 ingrese su nombre: "<<endl;
	cin>>nombre1;
	cout<<"Jugador2 ingrese su nombre: "<<endl;
	cin>>nombre2;
	int turno=0;
	bool gano=false;
	char coordenada1, coordenada2;
	while(!gano){
		bool valid = false;//variable de validacion
		imprimir(tablero);
		turno++;
		int x=0,y=0,x1=0,y1=0;
		if (turno % 2 == 1) {
			while(!valid){//ciclo de validacion
				cout<<"Turno de: "<<nombre1<<endl;
				cout<<"Ingrese columna de la pieza que desea mover: ";
				/*Validar que la posicion ingresada no se salga del rango

				*/
				while( !(x>0 && x<9) ){
					cin>>x;
					if(x>0 && x<9){
						break;
					}
					std::cout << "Debe estar dentro del rango[1,8], por favor ingrese de nuevo: " << std::endl;
				}

				x--;
				cout<<"Ingrese fila de la pieza que desea mover: ";
				cin >> coordenada1;
				y = charToInt(coordenada1);
				cout<<"Ingrese columna a la desea mover la pieza: ";
				cin>>x1;
				x1--;
				cout<<"Ingrese fila a la desea mover la pieza: : ";
				cin >> coordenada2;
				y1 = charToInt(coordenada2);
				Position pos(x1,y1);
				if (tablero[y][x]->getColor()=='B' && tablero[y][x] != NULL){//validacion de mover
					if(tablero[y][x]->moveTo(tablero,pos))
						valid = true;//variable de validacion
					else
						valid = false;
				}else{
					cerr << "No se puede mover las piezas del juagdor opuesto" << endl;
				}
			}
			Guardar(tablero);
		}else{
			while(!valid){//ciclo de validacion
				cout<<"Turno de: "<<nombre2<<endl;
				cout<<"Ingrese columna de la pieza que desea mover: ";

				/*Validar que la posicion ingresada no se salga del rango
				*/
				while( !(x>0 && x<9) ){
					cin>>x;
					if(x>0 && x<9){
						break;
					}
					std::cout << "Debe estar dentro del rango[1,8], por favor ingrese de nuevo: " << std::endl;
				}
				x--;
				cout<<"Ingrese fila de la pieza que desea mover: ";
				cin >> coordenada1;
				y = charToInt(coordenada1);
				cout<<"Ingrese columna a la desea mover la pieza: ";
				cin>>x1;
				x1--;
				cout<<"Ingrese fila a la desea mover la pieza: : ";
				cin >> coordenada2;
				y1 = charToInt(coordenada2);

				Position pos(x1,y1);
				if (tablero[y][x]->getColor()=='N' && tablero[y][x] != NULL){//validacion de mover
					if(tablero[y][x]->moveTo(tablero,pos))
						valid = true;//variable de validacion
					else
						valid = false;
				}else{
					cerr << "No se puede mover las piezas del jugador opuesto" << endl;
				}
			}
			Guardar(tablero);
		}
		//Guardar(tablero);
		gano = ganar(tablero);
	}

	destruirTablero(tablero,ROWS,COLS);
	return 0;
}
Piece*** crearTablero(int rows, int cols){
	Piece*** retval = new Piece**[rows];
	for (int i = 0; i < rows; ++i)	{
		retval[i] = new Piece*[cols];
	}
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			retval[i][j] = NULL;
		}
	}
	chessInit(retval);
	return retval;
}
void destruirTablero(Piece*** tablero, int rows, int cols){
	for (int i = 0; i < cols; ++i)	{
		delete[] tablero[i];
	}
	delete[] tablero;
}
void imprimir(Piece*** tablero){//imprimir tablero
	char letras[] = "ABCDEFGH";
	int numeros[] = {1,2,3,4,5,6,7,8};
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j)	{
			if(tablero[i][j] != NULL)
				cout << "[" << tablero[i][j]->toString() << "]";
			else
				cout << "[ ]";
		}
		cout << letras[i] << endl;
	}
	for (int i = 0; i < 8; ++i)	{
		cout << " " << numeros[i] << " ";
	}
	cout << endl;
}
void chessInit(Piece*** tablero){//Inicializar tablero

	//piezas blancas
	//torres
	tablero[0][0] = new Rook('B',0,0);
	tablero[0][7] = new Rook('B',7,0);
	//caballos
	tablero[0][1] = new Knight('B',1,0);
	tablero[0][6] = new Knight('B',6,0);
	//alfiles
	tablero[0][2] = new Bishop('B',2,0);
	tablero[0][5] = new Bishop('B',5,0);
	//rey
	tablero[0][3] = new King('B',3,0);
	//reina
	tablero[0][4] = new Queen('B',4,0);
	//peones
	for (int i = 0; i < 8; ++i){
		tablero[1][i] = new Pawn('B',i,1);
	}
	//piezas negras
	//torres
	tablero[7][0] = new Rook('N',0,7);
	tablero[7][7] = new Rook('N',7,7);
	//caballos
	tablero[7][1] = new Knight('N',1,7);
	tablero[7][6] = new Knight('N',6,7);
	//alfiles
	tablero[7][2] = new Bishop('N',2,7);
	tablero[7][5] = new Bishop('N',5,7);
	//rey
	tablero[7][3] = new King('N',3,7);
	//reina
	tablero[7][4] = new Queen('N',4,7);
	//peones
	for (int i = 0; i < 8; ++i){
		tablero[6][i] = new Pawn('N',i,6);
	}
}
int charToInt(char coordenada){
	switch (coordenada){
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		case 'd':
			return 3;
		case 'e':
			return 4;
		case 'f':
			return 5;
		case 'g':
			return 6;
		case 'h':
			return 7;
		case 'A':
			return 0;
		case 'B':
			return 1;
		case 'C':
			return 2;
		case 'D':
			return 3;
		case 'E':
			return 4;
		case 'F':
			return 5;
		case 'G':
			return 6;
		case 'H':
			return 7;
		default:
			return -1;
	}
}
bool ganar(Piece*** tablero){
	int cont=0;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if(dynamic_cast<King*>(tablero[i][j]) != NULL){
				King* king = dynamic_cast<King*>(tablero[i][j]);
				cont++;
			}
		}
	}
	if (cont==1)
	{
		return true;
	}
	return false;
}

void Guardar(Piece*** tablero ){

	ofstream archivo;
	archivo.open("Tablero.txt");

	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if(tablero[i][j] != NULL){
				archivo<<tablero[i][j]->toString()<<";";
			}
			else{
				archivo << " "<<";";
			}
		}
		//archivo<<endl;
	}
	archivo.close();

}

void Cargar(Piece*** tablero){
	ifstream primero;
	primero.open("Tablero.txt");
	ifstream archivo;
	archivo.open("Tablero.txt");

	string fila = "";
	string caracter = "";

	int cont = 1;
	for (size_t i = 0; i < 8; i++) {
		  //getline(archivo,fila);
		for (size_t j = 0; j < 8; j++) {
				if(cont == 0){
					getline(primero,fila);
					if(fila[0] == 'P' ){
						tablero[0][0] = new Pawn('N',i,j);
					}

					if(fila[0] == 'p' ){
						tablero[0][0] = new Pawn('B',i,j);

					}
					//Cargar Caballero
					if(fila[0] == 'C' ){
						tablero[0][0] = new Knight('N',i,j);
					}

					if(fila[0] == 'c' ){
						tablero[0][0] = new Knight('B',i,j);

					}

					//Cargar Alfiles
					if(fila[0] == 'A' ){
						tablero[0][0] = new Bishop('N',i,j);
					}

					if(fila[0] == 'a' ){
						tablero[0][0] = new Bishop('B',i,j);

					}

					//Cargar Caballero
					if(fila[0] == 'T' ){
						tablero[0][0] = new Rook('N',i,j);
					}

					if(fila[0] == 't' ){
						tablero[0][0] = new Rook('B',i,j);

					}

					//Cargar Rey
					if(fila[0] == 'R' ){
						tablero[0][0] = new King('N',i,j);
					}

					if(fila[0] == 'r' ){
						tablero[0][0] = new King('B',i,j);

					}

					//Cargar Reina

					if(fila[0] == 'Q' ){
						tablero[0][0] = new Queen('N',i,j);
					}

					if(fila[0] == 'q' ){
						tablero[0][0] = new Queen('B',i,j);
					}
					//Cargar Nulo
					if(fila[0] == ' '){
						tablero[0][0] = NULL;
					}
						cont++;
				}
				getline(archivo,caracter,';');

				//Cargar Peones
				if(caracter == "P" ){
					tablero[i][j] = new Pawn('N',i,j);
				}

				if(caracter == "p" ){
					tablero[i][j] = new Pawn('B',i,j);

				}
				//Cargar Caballero
				if(caracter == "C" ){
					tablero[i][j] = new Knight('N',i,j);
				}

				if(caracter == "c" ){
					tablero[i][j] = new Knight('B',i,j);

				}

				//Cargar Alfiles
				if(caracter == "A" ){
					tablero[i][j] = new Bishop('N',i,j);
				}

				if(caracter == "a" ){
					tablero[i][j] = new Bishop('B',i,j);

				}

				//Cargar Caballero
				if(caracter == "T" ){
					tablero[i][j] = new Rook('N',i,j);
				}

				if(caracter == "t" ){
					tablero[i][j] = new Rook('B',i,j);

				}

				//Cargar Rey
				if(caracter == "R" ){
					tablero[i][j] = new King('N',i,j);
				}

				if(caracter == "r" ){
					tablero[i][j] = new King('B',i,j);

				}

				//Cargar Reina

				if(caracter == "Q" ){
					tablero[i][j] = new Queen('N',i,j);
				}

				if(caracter == "q" ){
					tablero[i][j] = new Queen('B',i,j);
				}
				//Cargar Nulo
				if(caracter == " "){
					tablero[i][j] = NULL;
				}
		}

	}
	archivo.close();

}
