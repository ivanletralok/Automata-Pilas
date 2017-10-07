#ifndef CLASES_H
#define CLASES_H

#define NOVISITADO 0
#define VISITADO 1
#define EXISTE -1

struct condicion{
	char cinta;
	string desapila; //Desapila
	string apila; //Apila (Izquiera a derecha)
};

class Estado{
	private:
		string nombre;
		int numDelEstado;
		int tipo;  //1. Transicion, 2. Inicial y 3 de aceptacion
	public:
		//Constructores
		Estado(){}
		
		Estado(string n, int nd){
			nombre = n;
			numDelEstado = nd;
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
		string getNombreDelEstado(){
			return this->nombre;
		}
		
		void setTipo(int t){
			tipo = t;
		}
		
		void setNombre(string n){
			nombre = n;
		}
		
		void setNumDelEstado(int n){
			numDelEstado = n;
		}
};

class Automata{
	private:
		stack<char> caracteres;
		int maxEstados;
		int numEstados;
		Estado *estados;
		vector<condicion> **mat;
	public:
		//Constructores
		Automata(){} //Por defecto
		
		Automata(int max){ //Sobrecargado
			caracteres.push('Z');
			numEstados = 0;
			maxEstados = max;
			estados = new Estado[max];
			mat = new vector<condicion>*[max];
			for(int i=0;i<max;i++)
				mat[i] = new vector<condicion>[max];
		}
		
		int getNumDelEstado(string n){
			bool b=false;
			for(int i=0;i<numEstados && !b;i++){
				if((estados[i].getNombreDelEstado() == n))
					return i;
			}
			return -1;
		}
		
		bool adyacente(int a, int b){
			return !mat[a][b].empty();
		}
		
		void imprimirMatAd(){
			for(int i=0;i<maxEstados;i++){
				for(int j=0;j<maxEstados;j++){
					//cout<<mat[i][j]<<ends;
				}
				cout<<endl;
			}
		}
		
		void crearEstado(string n, int tipo){
			if(getNumDelEstado(n) < 0){
				Estado v;
				v.setNombre(n);
				v.setTipo(tipo);
				v.setNumDelEstado(numEstados);
				estados[numEstados++] = v;
				cout<<"\nEstado creado!";
			}else{
				cout<<"\nEl estado ya existe!";
			}
		}
		
		void crearCondicion(string a, string  b, condicion f){ //Convertir mas adelante
			int va=getNumDelEstado(a),vb= getNumDelEstado(b);
			if(va<0 || vb<0){
				cout<<"\nError al crear el arco!";
			}else{
				mat[va][vb].push_back(f);
				cout<<"\nArco creado exitosamente!";
			}
		}
		
		void imprimirEstados(){
			cout<<"\nESTADOS = {";
			for(int i=0;i<numEstados;i++){
				cout<<"("<<estados[i].getNombreDelEstado()<<","<<estados[i].getTipo()<<")";
				if(i != numEstados-1)
					cout<<" - ";
			}
			cout<<"}\n";
		}
		
		void imprimirCondiciones(){
			for(int i=0;i<numEstados;i++){
				for(int j=0;j<numEstados;j++){
					if(!mat[i][j].empty()){
						cout<<"\ncondiciones de "<<estados[i].getNombreDelEstado()<<" -> "<<estados[j].getNombreDelEstado()<<endl;
						for(int k=0;k<mat[i][j].size();k++){
							cout<<"Lee: "<<mat[i][j][k].cinta<<", "<<"desapila: "<<mat[i][j][k].desapila<<", apila: "<<mat[i][j][k].apila<<endl;
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
		
		int getNumEstados(){
			return numEstados;
		}
		
		Estado getEstado(int n){
			return estados[n];
		}
};

class RecorrerAutomata{
	private:
		bool encontrado;
	public:
		//Constructores
		RecorrerAutomata(){} //Constructor por defecto
		
		void reiniciar(vector<int> &marcas){
			for(int i=0;i<marcas.size();i++){
				marcas[i]=NOVISITADO;
			}
			this->encontrado = false;
		}
		
		void buscarCamino(Automata a, string o, string d,vector<int> &marcas){
			if(!encontrado){
				int n = a.getNumDelEstado(o);
				if(n != EXISTE){
					if(marcas[n] == NOVISITADO){
						marcas[n] = VISITADO;
						cout<<"Marcado "<<o<<endl;
						for(int i=0;i<a.getNumEstados();i++){
							if(a.adyacente(n,i)){
								if(a.getEstado(i).getNombreDelEstado() == d){
									this->encontrado = true;
									cout<<"Marcado "<<d<<endl;
									cout<<"Camino encontrado";
								}else{
									buscarCamino(a,a.getEstado(i).getNombreDelEstado(),d,marcas);
								}
							}
						}
					}
				}
			}
		}
		
		bool procesarExpresion(Automata a){
			vector<int> marcas(a.getNumEstados());
			this->reiniciar(marcas);
			for(int i=0;i<a.getNumEstados();i++){
				if(a.getEstado(i).getTipo() == "Inicial"){
					for(int j=0;j<a.getNumEstados();j++){
						if(a.getEstado(j).getTipo() == "Aceptacion"){
							buscarCamino(a,a.getEstado(i).getNombreDelEstado(),a.getEstado(j).getNombreDelEstado(),marcas);
						}
					}
					break;
				}
			}
			return this->encontrado;
		}
};

#endif
