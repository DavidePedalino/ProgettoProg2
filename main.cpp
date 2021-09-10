#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <limits.h>
#include <sstream>
#include <ctime>
#include "node_bst.h"

using namespace std;

ifstream in;

class Veicolo{
	protected:
		int numeroRuote;
		double prezzo;
		string tipo;
		string marca;
		string carburante;
		string motorizzazione;
	public:
		Veicolo*next;
		int cilindrata;
		
		Veicolo(int numeroRuote, double prezzo, string marca, string carburante, string motorizzazione,string tipo): numeroRuote(numeroRuote),prezzo(prezzo),marca(marca),carburante(carburante), 
		motorizzazione(motorizzazione),tipo(tipo){
			next =  NULL;
		}
		
		
		int getNumeroRuote(){return numeroRuote;}
		double getPrezzo(){return prezzo;}
		string getMarca(){return marca;}
		string getCarburante(){return carburante;}
		string getMotorizzazione(){return motorizzazione;}
		
		void setNumeroRuote(int n){numeroRuote = n;}
		void setPrezzo(double d){prezzo = d;}
		void setMarca(string s){marca = s;}
		void setCarburante(string s){carburante = s;}
		void setMotorizzazione(string s){motorizzazione = s;}
		string getTipo(){return tipo;}
		
};

class Nodo{
    public:
        Veicolo* val;
        Nodo *left;
        Nodo *right;
        Nodo *padre;  

        Nodo(Veicolo* v){
            val = new Veicolo(v->getNumeroRuote(),v->getPrezzo(),v->getMarca(),v->getCarburante(),v->getMotorizzazione(),v->getTipo());
            left = NULL;
            right = NULL;
            padre = NULL;
        }
};

class Albero{
	private:
		Node *root;
		
	    Node* _search(int key, Node *x){
	        Node *tmp = x;
	        while(tmp!=NULL && tmp->getKey()!=key){
	            if(key<=tmp->getKey()) tmp = tmp->getLeft();
	            else tmp = tmp->getRight();
	        }
	        return tmp;
	    }
		
		Node* _min(Node *x){
	        if(!x) return NULL;
	        Node *tmp = x;
	        while(tmp->getLeft()) tmp = tmp->getLeft();
	        return tmp;
	    }
	    
	    Node* _successore(Node *x){
	        if(!x) return NULL;
	        if(x->getRight())
	            return _min(x->getRight());
	        Node *tmp = x->getParent();
	        while(tmp && tmp->getKey()<x->getKey())
	            tmp = tmp->getParent();
	        return tmp;
	    }
	    
	    void _canc(int key, Node *r){
	        Node *x = _search(key, r);
	        if(x==NULL) return;
	        if(x->getLeft() && x->getRight()){
	            Node *s = _successore(x);
	            x->setKey(s->getKey());
	            s->setKey(key);
	            x = s;
	        }
	        Node *p = x->getParent();
	        Node *y = x->getLeft();
	        if(!y) y = x->getRight();
	        if(p){
	            if(key<p->getKey()) p->setLeft(y);
	            else p->setRight(y);
	        }
	        else root = y;
	        if(y) y->setParent(p);
	    }
    public:
        Nodo *radice;

        Albero(){
            radice = NULL;
        }    

        void Inserimento(Veicolo *v){
            Nodo *nuovo = new Nodo (v);
            Nodo *x = radice;
            Nodo *y = NULL;

            while(x){
                y = x;
                if(v->getMotorizzazione() < x->val->getMotorizzazione()){
                    x = x->left;
                }

                else if(v->getMotorizzazione() >= x->val->getMotorizzazione()){
                    x = x ->right;
                }
            }

            if(y == NULL){
                radice = nuovo;
            }

            else if(v->getMotorizzazione() < y->val->getMotorizzazione()){
                y->left = nuovo;
            }

            else if(v->getMotorizzazione() >= y->val->getMotorizzazione()){
                y->right = nuovo;
            }
            nuovo->padre = y;
        }

		void visitaInorder(Nodo *p){
            if(p){
                visitaInorder(p->left);
                cout << p->val->getMotorizzazione() <<" ";
                visitaInorder(p->right);
            }
        }
	    
	    void deleteCilindrata(int cil){
	    	Node *x = _search(cil, root);
	    	if(cil<x->getKey()){
	    		_canc(cil, x);
			}
		}
};



class Auto: public Veicolo{
	public:
		Auto *next;
		
		Auto(double prezzo, string marca, string carburante, string motorizzazione)
		:Veicolo(4,prezzo,marca,carburante,motorizzazione,"Auto"){
			next = NULL;
		}
};

class Moto: public Veicolo{
	public:
		Moto *next;
		
		Moto(double prezzo, string marca, string carburante, string motorizzazione)
		:Veicolo(2,prezzo,marca,"benzina",motorizzazione,"Moto"){
			next = NULL;
		}
};

class Barca: public Veicolo{
	public:
		Barca *next;
		
		Barca(double prezzo, string marca, string carburante, string motorizzazione)
		:Veicolo(0,prezzo,marca,carburante,motorizzazione,"Barca"){
			next = NULL;
		}
};

class ListaAuto
{
    public:
        Veicolo*head;
		int size;
		
        ListaAuto()
        {
            head = NULL;
            size = 0;
            
        }

        void inserimento(Veicolo *val)
        {
            if(!head)
            {
                head = val;
            }
            else if(head)
            {
                val->next = head;
				head = val;
            }
			size++;
        }
        

        void stampa_lista()
        {
            Veicolo *temp=head;
			int i = 1;
            while(temp)
            {
                cout << i << " " << temp->getMotorizzazione() <<endl;
                temp = temp->next;
				i++;
            }
			cout << endl;
        }

		Veicolo* extraction(){
			if(head){
				Veicolo *temp = head;
				head = head->next;
				return temp;
			}
			return NULL;
		}
};

class ListaBarca
{
    public:
        Veicolo*head;
		int size;
		
        ListaBarca()
        {
            head = NULL;
            size = 0;
        }

        void inserimento(Veicolo *val)
        {
            if(!head)
            {
                head = val;
            }
            else if(head)
            {
                val->next = head;
				head = val;
            }
			size++;
        }
        

        void stampa_lista()
        {
            Veicolo *temp = head;
			int i = 1;
            while(temp)
            {
                cout << i<< " " << temp->getMotorizzazione() <<endl;
                temp = temp->next;
				i++;
            }
			cout<<endl;
        }

		Veicolo* extraction(){
			if(head){
				Veicolo *temp = head;
				head = head->next;
				return temp;
			}
			return NULL;
		}
};

class ListaMoto{
    public:
        Veicolo *head;
		int size;
		
        ListaMoto()
        {
            head = NULL;
            size = 0;
            
        }

        void inserimento(Veicolo *val)
        {
            if(!head)
            {
                head = val;
            }
            else if(head)
            {
                val->next = head;
				head = val;
            }
			size++;
        }
        
        void stampa_lista()
        {
            Veicolo *temp = head;
			int i = 1;
            while(temp)
            {
                cout << i << " " << temp->getMotorizzazione() <<endl;
                temp = temp->next;
				i++;
            }
			cout<<endl;
        }

		Veicolo* extraction(){
			if(head){
				Veicolo *temp = head;
				head = head->next;
				return temp;
			}
			return NULL;
		}

};


int numVeicoli(){
	int size = 0;
	in.open("Veicoli.txt");
	while(!in.eof()){
		string line;
        getline(in,line);
		size++;
    }
	in.close();
	return size;
}

int main(){
	srand (time(NULL));
    int size = numVeicoli();
	in.open("Veicoli.txt");
	
	Veicolo **stack;
	stack = new Veicolo *[size];
	int i=0;
    while(!in.eof()){
        string v;
		string c;
		getline(in,v,',');
		getline(in,c,'\n');
		
		if(v == "MOTO"){
			stack[i] = new Veicolo (2,rand() % 10000 + 5000,"BMW","Benzina",c,"Moto");
		}
		else if(v == "AUTO"){
			stack[i] = new Veicolo (4,rand() % 20000 + 9000,"Fiat","Metano",c,"Auto");
		}
		else if(v == "BARCA"){
			stack[i] = new Veicolo (0,rand() % 50000 + 12000,"Azimut","Diesel",c,"Barca");
		}
		i++;
    }
	
	ListaAuto lista_auto;
	ListaMoto lista_moto;
	ListaBarca lista_barca;

	for(int j=0;j<size;j++){
		if(stack[j]->getTipo() == "Moto"){
			lista_moto.inserimento(stack[j]);
		}

		else if(stack[j]->getTipo() == "Auto"){
			lista_auto.inserimento(stack[j]);
		}

		else if(stack[j]->getTipo() == "Barca"){
			lista_barca.inserimento(stack[j]);
		}
	}

	lista_auto.stampa_lista();
	lista_barca.stampa_lista();
	lista_moto.stampa_lista();

	cout << lista_auto.size <<endl;
	cout << lista_moto.size <<endl;
	cout << lista_barca.size <<endl;
	
	Albero *albero_auto;
	Albero *albero_moto;
	Albero *albero_barca;
	
	albero_auto = new Albero();
	albero_moto = new Albero();
	albero_barca = new Albero();
	
	int size_lista_auto = lista_auto.size;
	int size_lista_moto = lista_moto.size;
	int size_lista_barca = lista_barca.size;


	for(int j=0;j<size_lista_auto;j++){
		albero_auto->Inserimento(lista_auto.extraction());
	}

	for(int j=0;j<size_lista_moto;j++){
		albero_moto->Inserimento(lista_moto.extraction());
		
	}

	for(int j=0;j<size_lista_barca;j++){
		albero_barca->Inserimento(lista_barca.extraction());
	}

	cout << "albero 1:" <<endl;
	albero_auto->visitaInorder(albero_auto->radice);
	cout << "albero 2:" << endl;
	albero_moto->visitaInorder(albero_moto->radice);
	cout << "albero 3:" << endl;
	albero_barca->visitaInorder(albero_barca->radice);
	
	int cilindrata;
	cout << "Inserire la cilindrata da eliminare: ";
	cin >> cilindrata;
	
	albero_auto->deleteCilindrata(cilindrata);
	albero_moto->deleteCilindrata(cilindrata);
	albero_barca->deleteCilindrata(cilindrata);
	
	albero_auto->visitaInorder(albero_auto->radice);
	albero_moto->visitaInorder(albero_moto->radice);
	albero_barca->visitaInorder(albero_barca->radice);
}

