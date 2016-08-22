#include "Escenario.hpp"
#include <algorithm>
#include <iostream>
using namespace std;
bool Escenario::parValido(int par) const
{
	int a  = this->primero(par);
	int b  = this->segundo(par);

	//No puede ser la misma persona
	if (a==b)
	{
		//cout<<"\t\t- error: misma persona "<<"\n";
		return false;
	}

	//Me fijo que ambos esten presentes en el lado A
	if (!(personas_ladoA[a] + personas_ladoA[b] == 2))
	{
		//cout<<"\t\t- error: alguna de las 2 personas no se encuentran en la isla A "<<"\n";
		return false;
	}

	//Calculo cuantos quedarian de cada lado
	if (this->estaBalanceadoPasandoPar(par))
	{
		return true;
	}
	return false;
}

void Escenario::printPar(int par) const
{
	int a  = this->primero(par);
	int b  = this->segundo(par);

	if (this->isCanibal(a))
	{
		cout <<"[C"<<a-this->cant_arqueologos_ladoA-this->cant_arqueologos_ladoB<<" ";
	}else{
		cout <<"[A"<<a<<" ";
	}

	if (this->isCanibal(b))
	{
		cout << "C"<<b-this->cant_arqueologos_ladoA-this->cant_arqueologos_ladoB<<"]";
	}else{
		cout << "A"<<b<<"]";
	}
}

void Escenario::printPersona(int a) const
{

	if (this->isCanibal(a))
	{
		cout << "C"<<a - (this->cant_arqueologos_ladoA + this->cant_arqueologos_ladoB);
	}else{
		cout << "A"<<a;
	}

}

void Escenario::printStatus() const
{
	cout<<"\tEscenario\n\t Islas       |\tA \tB\n\t canibales   |\t"<<this->cant_canibales_ladoA <<"\t"<<this->cant_canibales_ladoB<<"\n\t arqueologos |\t"<<this->cant_arqueologos_ladoA<<"\t"<<this->cant_arqueologos_ladoB<<"\n\n";

}

bool Escenario::estaBalanceadoPasandoPar(int par) const
{

	int a  = this->primero(par);
	int b  = this->segundo(par);

	int cantCanibales = this->isCanibal(a) + this->isCanibal(b);
	int cantArqueologos = !this->isCanibal(a) + !this->isCanibal(b);

	int cant_canibales_A =  this->cant_canibales_ladoA - cantCanibales;
	int cant_arqueologos_A =  this->cant_arqueologos_ladoA - cantArqueologos;
	int cant_canibales_B =  this->cant_canibales_ladoB + cantCanibales;
	int cant_arqueologos_B =  this->cant_arqueologos_ladoB + cantArqueologos;


	bool balanceA = cant_canibales_A <= cant_arqueologos_A || cant_arqueologos_A==0;
	bool balanceB = cant_canibales_B <= cant_arqueologos_B || cant_arqueologos_B==0;

	return  balanceA && balanceB;
}

bool Escenario::estaBalanceadoPasandoFarolero(int persona) const
{

	int cant_canibales_A =  this->cant_canibales_ladoA + this->isCanibal(persona);
	int cant_arqueologos_A =  this->cant_arqueologos_ladoA + !this->isCanibal(persona);
	int cant_canibales_B =  this->cant_canibales_ladoB - this->isCanibal(persona);
	int cant_arqueologos_B =  this->cant_arqueologos_ladoB - !this->isCanibal(persona);

	bool balanceA = cant_canibales_A <= cant_arqueologos_A || cant_arqueologos_A==0;
	bool balanceB = cant_canibales_B <= cant_arqueologos_B || cant_arqueologos_B==0;

	return  balanceA && balanceB;
}

bool Escenario::faroleroValido(int persona) const
{
	//Me fijo que este del lado B
	if(personas_ladoA[persona])
	{
		return false;
	}

	//Calculo cuantos quedarian de cada lado
	if (this->estaBalanceadoPasandoFarolero(persona))
	{
		return true;
	}

	return false;
}

bool Escenario::isCanibal(int persona) const
{
	//En la estructura, se listan primero los arqueologos y despues los canibales, por lo cual es un canibal si esta en los indices m{s altos
	return persona > (this->cant_arqueologos_ladoA + this->cant_arqueologos_ladoB - 1) ;
}

int Escenario::primero(int par) const
{
	return par / this->personas_totales ;
}

int Escenario::segundo(int par) const
{
	return par % this->personas_totales;
}

int Escenario::getTiempoPersona(int persona)
{
	if (this->isCanibal(persona))
	{
		int index_canibal = persona - this->cant_arqueologos_ladoA - this->cant_arqueologos_ladoB;
		return this->tiempos_canibales[index_canibal];	
	}

	return this->tiempos_arqueologos[persona];
}


Escenario::Escenario(const int cantA, const int cantC, const int * tiempos_arqueologos, const int * tiempos_canibales){
	
	this->tiempos_arqueologos = tiempos_arqueologos;
	this->tiempos_canibales = tiempos_canibales;
	this->personas_totales = cantA + cantC;
	
	//Guardo para no hacer las sumas despues y ensuciar el codigo
	this->cant_arqueologos_ladoA = cantA; 
	this->cant_canibales_ladoA = cantC;
	this->cant_arqueologos_ladoB = 0; 
	this->cant_canibales_ladoB = 0;

	//Todos los pares posibles (los irrelevantes despues se filtran)
	this->pares_totales = this->personas_totales * this->personas_totales;
	this->eleccion_x_paso = new int[this->pares_totales];
	this->personas_ladoA = new int[this->personas_totales];

	this->tiempo=0;
	this->tienenLampara=1;
	this->paso=0;


	//A cada paso lo inicializo en -1 simbolizando que ninguna pareja ni persona fue evaluada
	//cout<<"Pares: \n";
	for (int i = 0; i < this->pares_totales; i++)
	{
		//this->printPar(i);
		this->eleccion_x_paso[i]=-1;
		//cout<<"\n";
	}
	cout<<"\n";

	//Todas las personas empiezan del lado A
	for (int i = 0; i < this->personas_totales; i++)
	{
		this->personas_ladoA[i]=1;
	}


}

Escenario::~Escenario(){
/*	delete[] this->eleccion_x_paso;
	delete[] this->personas_ladoA;*/
}

int Escenario::parPosible() const
{
	//Busco, a partir del siguiente par evaluado en el paso actual, un par que exista (no se vaya de los limites) y que 
	//produzca, al cruzar el puente, una instancia valida del escenario, si no existe tal par se devuelve un -1

	int parEvaluar = this->sigPar();//this->eleccion_x_paso[this->paso] + 1;
	
	while(parEvaluar<this->pares_totales && !parValido(parEvaluar)){

		parEvaluar += 1;
	}

	if (parEvaluar<this->pares_totales && parValido(parEvaluar))
	{
		return parEvaluar;
	}else{
		return -1;
	}
}

int Escenario::faroleroPosible() const
{
	//Busco, a partir de la siguiente persona evaluado en el paso actual, una persona que exista (no se vaya de los limites) y que 
	//produzca, al cruzar el puente, una instancia valida del escenario, si no existe tal persona se devuelve un -1

	int faroleroAEvaluar = this->eleccion_x_paso[this->paso] + 1;
	//cout<<"\t> evaluando farolero "<<faroleroAEvaluar<<"\n";
	while(!faroleroValido(faroleroAEvaluar) && faroleroAEvaluar<=this->personas_totales){
		faroleroAEvaluar += 1;
	}

	if (faroleroAEvaluar<=this->personas_totales)
	{
		return faroleroAEvaluar;
	}else{
		return -1;
	}

}
void Escenario::enviarPar(const int par){
	//Asumo que es valido el par. Guardo el par a enviar en el arreglo de elecciones por paso, actualizo la cantidad
	//de personas que hay en cada lado, y marco el array las posiciones de esas personas como que ya no estan mas en A, finalmente me 
	//llevo la lampara a la isla B, avanzo de paso y guardo el tiempo que tardaron en hacer el cruce


	//Guardo el paso que funciono
	this->eleccion_x_paso[this->paso] = par;
	
	//Recalculo la cantidad de personas de cada lado
	int a  = this->primero(par);
	int b  = this->segundo(par);

	int cantCanibales = this->isCanibal(a) + this->isCanibal(b);
	int cantArqueologos = !this->isCanibal(a) + !this->isCanibal(b);

	this->cant_canibales_ladoA =  this->cant_canibales_ladoA - cantCanibales;
	this->cant_arqueologos_ladoA =  this->cant_arqueologos_ladoA - cantArqueologos;
	this->cant_canibales_ladoB =  this->cant_canibales_ladoB + cantCanibales;
	this->cant_arqueologos_ladoB =  this->cant_arqueologos_ladoB + cantArqueologos;
	
	//Marco a las personas como que viajaron al lado B
	this->personas_ladoA[a] = 0;
	this->personas_ladoA[b] = 0;

	//Avanzo el paso de ser posible
	if (this->paso<this->pares_totales)
	{
		this->paso += 1;
		//Reseteo las personas a probar, la primer persona a ser evaluada va a ser la 0
		this->eleccion_x_paso[this->paso] = -1;
		
	}

	//El par se lleva la lampara al lado B
	this->tienenLampara = 0;

	//El tiempo que se insume es el del mas lento
	this->tiempo = this->tiempo + std::max(this->getTiempoPersona(a),this->getTiempoPersona(b));

	

}
void Escenario::enviarFarolero(const int persona)
{
	//Asumo que la persona es un farolero valido. Guardo a la persona como la eleccion en el paso actual, actualizo la cantidad
	//de personas que hay en cada lado, y marco el array las posiciones de esas personas como que ya no estan mas en B, finalmente me 
	//llevo la lampara a la isla A, avanzo de paso y guardo el tiempo que tardaron en hacer el cruce

		
	//Guardo la eleccion que se tomo
	this->eleccion_x_paso[this->paso] = persona;


	//Recalculo el balance

	this->cant_canibales_ladoA = this->cant_canibales_ladoA + this->isCanibal(persona);
	this->cant_arqueologos_ladoA = this->cant_arqueologos_ladoA + !this->isCanibal(persona);
	this->cant_canibales_ladoB = this->cant_canibales_ladoB - this->isCanibal(persona);
	this->cant_arqueologos_ladoB = this->cant_arqueologos_ladoB - !this->isCanibal(persona);

	
	//Marco a las personas como que viajaron al lado B
	this->personas_ladoA[persona] = 1;


	//Avanzo el paso si es posible
	if (this->paso<this->pares_totales)
	{
		this->paso += 1;
		//Reseteo las personas a probar, la primer persona a ser evaluada va a ser la 0
		this->eleccion_x_paso[this->paso] = -1;
		
	}

	//El farolero retorna la lampara al lado A
	this->tienenLampara=1;

	//registro el tiempo que le llevo
	this->tiempo = this->tiempo + this->getTiempoPersona(persona);


}
bool Escenario::backtrackPar()
{
	//Retrocedo 1 paso, tomo el par que viajo ultimo y los mando devuelta a la isla A, llevando consigo la lampara devuelta (con todas las actualizaciones
	// de estructura que esto implica). Finalmente resto el tiempo al tiempo total de la rama evaluada.
		
	//Si no hay más pasos para atras entonces devuelvo false
	this->paso = this->paso -1;
	if (this->paso<0)
	{
		return false;
	} 

	//De lo contrario busco el par que produjo el backtrack y lo hago volver al lado A
	int par = this->eleccion_x_paso[this->paso];

	int a  = this->primero(par);
	int b  = this->segundo(par);

	int cantCanibales = this->isCanibal(a) + this->isCanibal(b);
	int cantArqueologos = !this->isCanibal(a) + !this->isCanibal(b);

	this->cant_canibales_ladoA =  this->cant_canibales_ladoA + cantCanibales;
	this->cant_arqueologos_ladoA =  this->cant_arqueologos_ladoA + cantArqueologos;
	this->cant_canibales_ladoB =  this->cant_canibales_ladoB - cantCanibales;
	this->cant_arqueologos_ladoB =  this->cant_arqueologos_ladoB - cantArqueologos;

	//Marco a las personas como que retornaron al lado A
	this->personas_ladoA[a] = 1;
	this->personas_ladoA[b] = 1;

	//Se deshace la ida del par, y con ellos vuelve la lampara al lado A
	this->tienenLampara=1;

	//Le resto el tiempo de la persona mas lenta (numero mas grande)
	this->tiempo = this->tiempo - std::max(this->getTiempoPersona(a),this->getTiempoPersona(b));

	return true;
}  	
bool Escenario::backtrackFarolero()
{
	//Si no hay más pasos para atras entonces devuelvo false
	this->paso = this->paso -1;
	if (this->paso<0)
	{
		return false;
	} 
	int persona = this->eleccion_x_paso[this->paso];
	bool canibal = this->isCanibal(persona);
	//De lo contrario busco el par que produjo el backtrack y lo hago volver al lado A

	this->cant_canibales_ladoA =this->cant_canibales_ladoA - canibal;
	this->cant_arqueologos_ladoA = this->cant_arqueologos_ladoA - !canibal;
	this->cant_canibales_ladoB = this->cant_canibales_ladoB + canibal;
	this->cant_arqueologos_ladoB = this->cant_arqueologos_ladoB + !canibal;

	//Marco a las personas como que retornaron al lado A
	this->personas_ladoA[persona] = 0;
	//Como se deshizo la vuelta del farolero, entonces en A no tienen lampara
	this->tienenLampara=0;

	//Retrocedo el tiempo
	this->tiempo =this->tiempo - this->getTiempoPersona(persona);

	return true;
}

int Escenario::pasaronTodos()
{
	return (this->cant_canibales_ladoA + this->cant_arqueologos_ladoA) == 0;
}

int Escenario::sigPar() const{

	int par = this->eleccion_x_paso[this->paso] + 1;
	int persona_1 = this->primero(par) + 1; //Para que sea en base 1 en vez de 0
	int parNoExplorado = persona_1 * persona_1 + 1;//haciendo el dibujo de la matriz se ve
	return parNoExplorado;
}

