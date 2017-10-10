#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>


using namespace std;

#include "librerias/clases.h"

int main(){
	Automata a(20);
	RecorrerAutomata *ra = new RecorrerAutomata();
	condicion f;

	int opcion,tipo;
	string o,d;
	do{
		switch(opcion){
				case 1:
           		        system("clear");
				cout<<"\t\tCrear estado\n\nNombre: ";
				cin>>o;
				cout<<"\n\nTipo\n1. Inicial\n2. Transicion\n3.Aceptacion\nEscoja una opcion: ";
				cin>>tipo;
				a.crearEstado(o,tipo);
             			   system("pause>0");
				break;
				case 2:
                		system("clear");
				cout<<"\t\tCrear condicion\n\nEstado origen: ";
				cin>>o;
				cout<<"Estado destino: ";
				cin>>d;
				cout<<"\n\nRestricciones\n1. Caracter leido de la cinta: ";
				cin>>f.cinta;
				cout<<"Desapila: ";
				cin>>f.desapila;
				cout<<"Apila: ";
				cin>>f.apila;
				a.crearCondicion(o,d,f);
             		        system("pause>0");
				break;
				case 3:
				system("clear");
				cout<<"\t\tVer estados\n\n";
				a.imprimirEstados();
				system("pause>0");
				break;
				case 4:
				system("clear");
				cout<<"\t\tVer condiciones\n\n";
				a.imprimirCondiciones();
				system("pause>0");
				break;
				case 5:
				system("clear");
				cout<<"\t\tProcesar expresion\n\n";
				cout<<(ra->procesarExpresion(a) ? "\nExpresion aceptada" : "\nExpresion no aceptada");
				system("pause>0");
				break;
				case 6:
				cout<<"Fin del programa!";
				break;
				default:
				cout<<"Opcion invalida intente nuevamente...";
		}
	}while(opcion != 6);
		
}
