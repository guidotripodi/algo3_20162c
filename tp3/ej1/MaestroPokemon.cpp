
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
	cout << "Eleccion id: "<<std::to_string(eleccion.id)<<": #TIPO = "<<eleccion.tipo<<" (X,Y) = "<<eleccion.posicion.first<<" "<<eleccion.posicion.second<<" pocionesNecesarias: "<<eleccion.pocionesNecesarias<<"\n";
}


void MaestroPokemon::printStatus() const
{
	cout<<"Maestro Pokemon   paso:"<<this->decisiones->size()<<"";
}


MaestroPokemon::MaestroPokemon(int cant_gimnasios, int cant_pokeParadas, int cap_mochila, const pair <pair <int,int>, int> gyms[], const pair <int,int> posiciones_pp[]){
	cout << "INICIALIZANDO\n";
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
	this->printEleccion(Eleccion(this));
	

}

MaestroPokemon::~MaestroPokemon(){

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

bool MaestroPokemon::deshacerEleccion()
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


bool MaestroPokemon::gane()
{
	return this->cant_gimnasios_por_ganar == 0;
}


