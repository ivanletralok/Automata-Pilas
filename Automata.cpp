#include <iostream>
#include <vector>
#include <stack>

using namespace std;
#include "librerias/clases.h"

#define INICIAL '#'




int main(){
	Grafo g(30);
	g.crearVertice("A",1);
	g.crearVertice("B",2);
	g.crearVertice("C",2);
	g.crearVertice("D",2);
	g.crearVertice("E",3);
	g.crearVertice("F",3);

	formato f;
	f.cinta = 'A';
	f.desapila = "#";
	f.apila = "ABA";
	g.crearArco("A","E",f);

	f.cinta = 'B';
	g.crearArco("A","E",f);

	f.apila = "BB";
	f.desapila = "A";
	g.crearArco("A","E",f);
	g.imprimirVertices();



}
