
#include "Escenario2.hpp"
using namespace std;

bool Escenario2::envioValido(Eleccion eleccion) const
{
	
	//Me fijo que ambos esten presentes en el lado A
	
	if (eleccion.cant_pokebolas < tamañoGym){
		
		return true;
	}else{
		return false;
	}

	
}
bool Escenario2::retornoValido(Eleccion eleccion) const
{
	//Me fijo que este del lado B

	if(eleccion.primero.lado == LADO_A || eleccion.segundo.lado == LADO_A)
	{
		
		return false;
	}

	//Calculo cuantos quedarian de cada lado
	if (!this->estaBalanceadoRetornandoEleccion(eleccion))
	{

		return false;
	}

	if (this->historial->ocurrioEstado(eleccion, LADO_A))
	{
		
		
		return false;
	}
	return true;
}

void Escenario2::printEleccion(Eleccion eleccion) const
{
	//cout << "Eleccion id: "<<std::to_string(eleccion.id)<<": #arq = "<<eleccion.cantArqueologos<<" #can = "<<eleccion.cantCanibales<<" t: "<<eleccion.tiempo<<"\n";
}


void Escenario2::printStatus() const
{
	//cout<<"Escenario   paso:"<<this->decisiones->size()<<"\n\t Islas       |\tA \tB\n\t canibales   |\t"<<this->cant_canibales_ladoA <<"\t"<<this->cant_canibales_ladoB<<"\n\t arqueologos |\t"<<this->cant_arqueologos_ladoA<<"\t"<<this->cant_arqueologos_ladoB<<"\n Con tiempo: "<<this->tiempo<<"\n";
}

bool Escenario2::estaBalanceadoEnviandoEleccion(Eleccion eleccion) const
{

	int cant_canibales_A =  this->cant_canibales_ladoA - eleccion.cantCanibales;
	int cant_arqueologos_A =  this->cant_arqueologos_ladoA - eleccion.cantArqueologos;
	int cant_canibales_B =  this->cant_canibales_ladoB + eleccion.cantCanibales;
	int cant_arqueologos_B =  this->cant_arqueologos_ladoB + eleccion.cantArqueologos;


	bool balanceA = cant_canibales_A <= cant_arqueologos_A || cant_arqueologos_A==0;
	bool balanceB = cant_canibales_B <= cant_arqueologos_B || cant_arqueologos_B==0;

	return  balanceA && balanceB;
}

bool Escenario2::estaBalanceadoRetornandoEleccion(Eleccion eleccion) const
{

	int cant_canibales_A =  this->cant_canibales_ladoA + eleccion.cantCanibales;
	int cant_arqueologos_A =  this->cant_arqueologos_ladoA + eleccion.cantArqueologos;
	int cant_canibales_B =  this->cant_canibales_ladoB - eleccion.cantCanibales;
	int cant_arqueologos_B =  this->cant_arqueologos_ladoB - eleccion.cantArqueologos;


	bool balanceA = cant_canibales_A <= cant_arqueologos_A || cant_arqueologos_A==0;
	bool balanceB = cant_canibales_B <= cant_arqueologos_B || cant_arqueologos_B==0;

	return  balanceA && balanceB;
}


Escenario2::Escenario2(const int cantA, const int cantC, const int * tiempos_arqueologos, const int * tiempos_canibales){
	
	this->tiempos_arqueologos = tiempos_arqueologos;
	this->tiempos_canibales = tiempos_canibales;
	this->personas_totales = cantA + cantC;

	
	//Guardo para no hacer las sumas despues y ensuciar el codigo
	this->cant_arqueologos_ladoA = cantA; 
	this->cant_canibales_ladoA = cantC;
	this->cant_arqueologos_ladoB = 0; 
	this->cant_canibales_ladoB = 0;


	this->decisiones = new list<Escenario2::Eleccion>();
	this->personas_ladoA = new int[this->personas_totales];

	this->tiempo=0;
	this->tienenLampara=1;
	
	for (int i = 0; i < this->personas_totales; i++)
	{
		this->personas_ladoA[i]=1;
	}

	this->eleccionActual = Eleccion(this);

	this->historial = new HistoricoEstados(this);
	historial->marcarHistoria();
	

}

Escenario2::~Escenario2(){
	delete historial;
	delete decisiones;
	delete[] personas_ladoA;
}

Escenario2::Eleccion Escenario2::envioPosible()
{

	while (this->eleccionActual.posible && !this->envioValido(this->eleccionActual))
	{
		 this->eleccionActual.recalcular();
	}

	this->eleccionActual.posible = this->eleccionActual.posible && this->envioValido(this->eleccionActual);

	return eleccionActual;
}

Escenario2::Eleccion Escenario2::retornoPosible()
{
	
	while (this->eleccionActual.posible && !this->retornoValido(this->eleccionActual))
	{
		 //this->printEleccion(this->eleccionActual);
		 this->eleccionActual.recalcular();
	}

	this->eleccionActual.posible = this->eleccionActual.posible && this->retornoValido(this->eleccionActual) ;

	return this->eleccionActual;

}
void Escenario2::enviarEleccion(Eleccion eleccion){

	//Guardo la decision en la rama que estoy explorando
	this->decisiones->push_back(eleccion);
	

	//Actualizo el estado del sistema en base a la decision que tome
	this->cant_canibales_ladoA =  this->cant_canibales_ladoA - eleccion.cantCanibales;
	this->cant_arqueologos_ladoA =  this->cant_arqueologos_ladoA - eleccion.cantArqueologos;
	this->cant_canibales_ladoB =  this->cant_canibales_ladoB + eleccion.cantCanibales;
	this->cant_arqueologos_ladoB =  this->cant_arqueologos_ladoB + eleccion.cantArqueologos;
	
	//Marco a las personas como que viajaron al lado B
	this->personas_ladoA[eleccion.primero.id] = 0;
	this->personas_ladoA[eleccion.segundo.id] = 0;

	//El par se lleva la lampara al lado B
	this->tienenLampara = 0;

	//El tiempo que se insume es el del mas lento
	this->tiempo = this->tiempo + eleccion.tiempo;

	this->eleccionActual = Eleccion(this);

	this->historial->marcarHistoria();

	

}
void Escenario2::retornarEleccion(const Eleccion eleccion)
{
	//Guardo la decision en la rama que estoy explorando
	this->decisiones->push_back(eleccion);
	

	//------Actualizo el estado del sistema en base a la decision que tome-------
	this->cant_canibales_ladoA =  this->cant_canibales_ladoA + eleccion.cantCanibales;
	this->cant_arqueologos_ladoA =  this->cant_arqueologos_ladoA + eleccion.cantArqueologos;
	this->cant_canibales_ladoB =  this->cant_canibales_ladoB - eleccion.cantCanibales;
	this->cant_arqueologos_ladoB =  this->cant_arqueologos_ladoB - eleccion.cantArqueologos;
	
	//Marco a las personas como que viajaron al lado B
	this->personas_ladoA[eleccion.primero.id] = 1;
	this->personas_ladoA[eleccion.segundo.id] = 1;

	//El par se lleva la lampara al lado B
	this->tienenLampara = 1;

	this->tiempo = this->tiempo + eleccion.tiempo;

	this->eleccionActual = Eleccion(this);

	this->historial->marcarHistoria();


}
bool Escenario2::deshacerEnvio()
{
	if(this->decisiones->empty()){
		return false;
	}

	Eleccion eleccionADeshacer = this->decisiones->back();
	this->decisiones->pop_back();

//------Actualizo el estado del sistema en base a la decision que deshice-------
	this->cant_canibales_ladoA =  this->cant_canibales_ladoA + eleccionADeshacer.cantCanibales;
	this->cant_arqueologos_ladoA =  this->cant_arqueologos_ladoA + eleccionADeshacer.cantArqueologos;
	this->cant_canibales_ladoB =  this->cant_canibales_ladoB - eleccionADeshacer.cantCanibales;
	this->cant_arqueologos_ladoB =  this->cant_arqueologos_ladoB - eleccionADeshacer.cantArqueologos;

	//Marco a las personas como que retornaron al lado A
	this->personas_ladoA[eleccionADeshacer.primero.id] = 1;
	this->personas_ladoA[eleccionADeshacer.segundo.id] = 1;

	//Se deshace la ida del par, y con ellos vuelve la lampara al lado A
	this->tienenLampara=1;


	this->tiempo = this->tiempo - eleccionADeshacer.tiempo;

	//this->decisiones->pop_back(); //recalculo el paso previo
	this->historial->borrarHistoria(eleccionADeshacer, LADO_B);
	this->eleccionActual = eleccionADeshacer;
	this->eleccionActual.recalcular();

	return true;
}  	
bool Escenario2::deshacerRetorno()
{
	if(this->decisiones->empty()){
		return false;
	}

	Eleccion eleccionADeshacer = this->decisiones->back();
	this->decisiones->pop_back();

//------Actualizo el estado del sistema en base a la decision que deshice-------
	this->cant_canibales_ladoA =  this->cant_canibales_ladoA - eleccionADeshacer.cantCanibales;
	this->cant_arqueologos_ladoA =  this->cant_arqueologos_ladoA - eleccionADeshacer.cantArqueologos;
	this->cant_canibales_ladoB =  this->cant_canibales_ladoB + eleccionADeshacer.cantCanibales;
	this->cant_arqueologos_ladoB =  this->cant_arqueologos_ladoB + eleccionADeshacer.cantArqueologos;

	//Marco a las personas como que retornaron al lado A
	this->personas_ladoA[eleccionADeshacer.primero.id] = 0;
	this->personas_ladoA[eleccionADeshacer.segundo.id] = 0;

	//Se deshace la ida del par, y con ellos vuelve la lampara al lado A
	this->tienenLampara=0;


	this->tiempo = this->tiempo - eleccionADeshacer.tiempo;

	//this->decisiones->pop_back();
	this->historial->borrarHistoria(eleccionADeshacer, LADO_A);
	this->eleccionActual = eleccionADeshacer;
	this->eleccionActual.recalcular();

	return true;
}

int Escenario2::pasaronTodos()
{
	return (this->cant_canibales_ladoA + this->cant_arqueologos_ladoA) == 0;
}


