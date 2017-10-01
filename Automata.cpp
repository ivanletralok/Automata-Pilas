#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define INICIAL '#'

struct formato{
	char cinta;
	string desapila; //Desapila
	string apila; //Apila (Izquiera a derecha)
};

class Vertice{
	private:
		string nombre;
		int numDelVertice;
		int tipo;  //1. Transicion, 2. Inicial y 3 de aceptacion
	public:
		//Constructores
		Vertice(){}

		Vertice(string n, int nd){
			nombre = n;
			numDelVertice = nd;
		}

		string getTipo(){
			switch(tipo){
				case 1:
					return "Inicial";
				case 2:
					return "Transicion";
				case 3:
					return "Aceptacion";
				default:
					return "Sin tipo";
			}
		}
		string getNombreDelVertice(){
			return this->nombre;
		}

		void setTipo(int t){
			tipo = t;
		}

		void setNombre(string n){
			nombre = n;
		}

		void setNumDelVertice(int n){
			numDelVertice = n;
		}
};

class Grafo{
	private:
		stack<char> caracteres;
		int maxVertices;
		int numVertices;
		Vertice *vertices;
		vector<formato> **matAd;
	public:
		//Constructores
		Grafo(){} //Por defecto

		Grafo(int max){ //Sobrecargado
			caracteres.push(INICIAL);
			caracteres.push('Z');
			numVertices = 0;
			maxVertices = max;
			vertices = new Vertice[max];
			matAd = new vector<formato>*[max];
			for(int i=0;i<max;i++)
				matAd[i] = new vector<formato>[max];
		}

		int getNumDelVertice(string n){
			bool b=false;
			for(int i=0;i<numVertices && !b;i++){
				if((vertices[i].getNombreDelVertice() == n))
					return i;
			}
			return -1;
		}

		bool adyacente(int a, int b){
			return matAd[a][b].empty();
		}

		void imprimirMatAd(){
			for(int i=0;i<maxVertices;i++){
				for(int j=0;j<maxVertices;j++){
					//cout<<matAd[i][j]<<ends;
				}
				cout<<endl;
			}
		}

		void crearVertice(string n, int tipo){
			if(getNumDelVertice(n) < 0){
				Vertice v;
				v.setNombre(n);
				v.setTipo(tipo);
				v.setNumDelVertice(numVertices);
				vertices[numVertices++] = v;
				cout<<"\nVertice creado!";
			}else{
				cout<<"\nEl vertice ya existe!";
			}
		}

		void crearArco(string a, string  b, formato f){ //Convertir mas adelante
			int va=getNumDelVertice(a),vb= getNumDelVertice(b);
			if(va<0 || vb<0){
				cout<<"\nError al crear el arco!";
			}else{
				matAd[va][vb].push_back(f);
				cout<<"\nArco creado exitosamente!";
			}
		}

		void imprimirVertices(){
			cout<<"\nVERTICES = {";
			for(int i=0;i<numVertices;i++){
				cout<<"("<<vertices[i].getNombreDelVertice()<<","<<vertices[i].getTipo()<<")";
				if(i != numVertices-1)
					cout<<" - ";
			}
			cout<<"}\n";
		}

		void imprimirArcos(){
			for(int i=0;i<numVertices;i++){
				for(int j=0;j<numVertices;j++){
					if(!matAd[i][j].empty()){
						cout<<"\ncondiciones de "<<vertices[i].getNombreDelVertice()<<" -> "<<vertices[j].getNombreDelVertice()<<endl;
						for(int k=0;k<matAd[i][j].size();k++){
							cout<<"Lee: "<<matAd[i][j][k].cinta<<", "<<"desapila: "<<matAd[i][j][k].desapila<<", apila: "<<matAd[i][j][k].apila<<endl;
						}
					}
				}
			}
		}

		void imprimirPila(){
			while(!caracteres.empty()){
				cout<<caracteres.top();
				caracteres.pop();
			}
		}

		int getNumVertices(){
			return numVertices;
		}

		Vertice getVertice(int n){
			return vertices[n];
		}
};



int main(){
	Grafo g(20);
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
	g.imprimirArcos();
	g.imprimirPila();


}
