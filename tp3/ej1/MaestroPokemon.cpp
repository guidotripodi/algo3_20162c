
#include "MaestroPokemon.hpp"
using namespace std;

bool MaestroPokemon::eleccionValida(Eleccion eleccion) const
{
	//XD
	if (this->destinos_visitados[eleccion.id])
	{
		return false;
	}
		
	if (eleccion.tipo == PP){
		//Si ya esta llena, enotnces no tiene sentido ir, porque la distancia a otro gym directamente
		//es menor.
		if (this->cantidad_pociones == this->capacidad_mochila)
		{
			return false;
		}
	}else{
		//Si es un gimnasio entonces:
		//Si la cantidad de pociones disponibles no es suficiente entonces no puedo ir
		if (this->cantidad_pociones < eleccion.pocionesNecesarias)
		{
			return false;
		}
	}

}


void MaestroPokemon::printEleccion(Eleccion eleccion) const
{
	//cout << "Eleccion id: "<<std::to_string(eleccion.id)<<": #arq = "<<eleccion.cantArqueologos<<" #can = "<<eleccion.cantCanibales<<" t: "<<eleccion.tiempo<<"\n";
}


void MaestroPokemon::printStatus() const
{
	//cout<<"Escenario   paso:"<<this->decisiones->size()<<"\n\t Islas       |\tA \tB\n\t canibales   |\t"<<this->cant_canibales_ladoA <<"\t"<<this->cant_canibales_ladoB<<"\n\t arqueologos |\t"<<this->cant_arqueologos_ladoA<<"\t"<<this->cant_arqueologos_ladoB<<"\n Con tiempo: "<<this->tiempo<<"\n";
}


MaestroPokemon::MaestroPokemon(const int cant_gimnasios, const int cant_pokeParadas, const int * cap_mochila, const pair <pair <int,int>, int>* gyms, pair <int,int> posiciones_pp){
	
	this->cant_gimnasios = cant_gimnasios;
	this->cant_gimnasios_por_ganar = cant_gimnasios;
	this->cant_pokeParadas = cant_pokeParadas;
	this->capacidad_mochila = cap_mochila;
	this->cantidad_pociones = 0; 
	this->gyms = gyms;
	this->posiciones_pp = posiciones_pp; 
	

	this->decisiones = new list<MaestroPokemon::Eleccion>();
	
	this->distancia=0;
	
	
	for (int i = 0; i < this->cant_gimnasios + this->cant_pokeParadas; i++)
	{
		this->destinos_visitados[i]=0;
	}

	this->eleccionActual = Eleccion(this);

	

}

MaestroPokemon::~MaestroPokemon(){
	delete decisiones;
	delete[] destinos_visitados;
}

MaestroPokemon::Eleccion MaestroPokemon::eleccionPosible()
{

	while (this->eleccionActual.posible && !this->eleccionValida(this->eleccionActual))
	{
		 this->eleccionActual.recalcular();
	}

	this->eleccionActual.posible = this->eleccionActual.posible && this->eleccionValida(this->eleccionActual);

	return eleccionActual;
}


void MaestroPokemon::elegir(Eleccion eleccion){

	//Guardo la decision en la rama que estoy explorando
	this->decisiones->push_back(eleccion);
	
	//Marco al destino como visitado
	this->destinos_visitados[eleccion.id] = 0;	

	//Incremento la distancia
	this->distancia = this->distancia + eleccion.distancia;

	if (eleccion.tipo == GIMNASIO)
	{
		this->cant_gimnasios_por_ganar--;
		this->cantidad_pociones= this->cantidad_pociones - eleccion.pocionesNecesarias;
	}else{
		this->cantidad_pociones+=3;//HARDCODE!!!
	}

	this->eleccionActual = Eleccion(this);
	

}

bool MaestroPokemon::deshacerEnvio()
{
	if(this->decisiones->empty()){
		return false;
	}

	Eleccion eleccionADeshacer = this->decisiones->back();
	this->decisiones->pop_back();

	this->destinos_visitados[eleccionADeshacer.id] = 1;

	this->distancia = this->distancia - eleccionADeshacer.distancia;

	if (eleccionADeshacer.tipo == GIMNASIO)
	{
		this->cant_gimnasios_por_ganar++;
		this->cantidad_pociones= this->cantidad_pociones + eleccionADeshacer.pocionesNecesarias;
	}else{
		this->cantidad_pociones-=3;//HARDCODE!!!
	}


	this->eleccionActual = eleccionADeshacer;
	this->eleccionActual.recalcular();

	return true;
}  	


int MaestroPokemon::gane()
{
	return this->cant_gimnasios_por_ganar == 0;
}


