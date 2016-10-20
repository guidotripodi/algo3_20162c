
#include "MaestroPokemon.hpp"
using namespace std;

bool MaestroPokemon::eleccionValida(Eleccion eleccion) const
{
	//XD
	//printf("\tPruebo: ");
	//this->printEleccion(eleccion);
	if (this->destinos_visitados[eleccion.id])
	{
		//cout<<"\t\terror: ya visitado\n";
		return false;
	}

	if (eleccion.tipo == PP){
		//Si ya esta llena, enotnces no tiene sentido ir, porque la distancia a otro gym directamente
		//es menor.
		if (this->cantidad_pociones == this->capacidad_mochila)
		{
		//	cout<<"\t\terror: cantidades iguales\n";
			return false;
		}
	}else{
		//Si es un gimnasio entonces:
		//Si la cantidad de pociones disponibles no es suficiente entonces no puedo ir
		if (this->cantidad_pociones < eleccion.pocionesNecesarias)
		{
		//	cout<<"\t\terror: falta de pociones\n";
			return false;
		}
	}
	return true;

}


void MaestroPokemon::printEleccion(Eleccion eleccion) const
{
	cout << "Eleccion id: "<<std::to_string(eleccion.id)<<": tipo = "<<eleccion.tipo<<" (x,y) = "<<eleccion.posicion.first<<" "<<eleccion.posicion.second<<" pn: "<<eleccion.pocionesNecesarias<<" distancia: "<<eleccion.distancia<<" posible = "<<eleccion.posible<<"\n";
}


void MaestroPokemon::printStatus() const
{
	cout<<"\n---------------------------------------------------\nMaestro Pokemon:   paso = "<<this->paso<<" pociones = "<<this->cantidad_pociones<<" recorri = "<<this->distancia<<"\n\n";
}


MaestroPokemon::MaestroPokemon(int cant_gimnasios, int cant_pokeParadas, int cap_mochila, const pair <pair <int,int>, int> gyms[], const pair <int,int> posiciones_pp[]){
	//cout << "INICIALIZANDO:\n";
	//cout << "\t- #gim "<<cant_gimnasios<<"\n";
	//cout << "\t- #pp "<<cant_pokeParadas<<"\n";
	this->cant_gimnasios = cant_gimnasios;
	this->cant_gimnasios_por_ganar = cant_gimnasios;
	this->cant_pokeParadas = cant_pokeParadas;
	this->capacidad_mochila = cap_mochila;
	this->cantidad_pociones = 0; 
	this->gyms = gyms;
	this->posiciones_pp = posiciones_pp; 
	this->paso=0;
	

	this->decisiones = new list<MaestroPokemon::Eleccion>();
	
	this->distancia=0;
	
	
	for (int i = 0; i < this->cant_gimnasios + this->cant_pokeParadas; i++)
	{
		this->destinos_visitados[i]=0;
	}
	
	this->eleccionActual = Eleccion(this);
	

}

MaestroPokemon::~MaestroPokemon(){

}

MaestroPokemon::Eleccion MaestroPokemon::eleccionPosible()
{
 	Eleccion eleccion = this->eleccionActual; 
	bool esValida = this->eleccionValida(eleccion);
	while (eleccion.posible && !esValida)
	{
		//cout << "\tFallo validacion...recalculando\n";
		eleccion.recalcular();
		if (eleccion.posible)
		{
			esValida = this->eleccionValida(eleccion); 
		}
	}
	
	eleccion.posible = eleccion.posible && esValida;

	/*EL PROBLEMA ESTA ACA, NO PASA LA DISTANCIA NUEVA YA QUE NO RECALCULA*/
	//printf("Eleccion tipo %d, eleccion pocionesNecesarias: %d, eleccion distancia %d\n", eleccionActual.tipo, eleccionActual.pocionesNecesarias, eleccionActual.distancia );
	return eleccion;
}


void MaestroPokemon::elegir(Eleccion eleccion){

	//Guardo la decision en la rama que estoy explorando
	this->decisiones->push_back(eleccion);
	
	//Marco al destino como visitado
	this->destinos_visitados[eleccion.id] = 1;	

	//Incremento la distancia
	this->distancia = this->distancia + eleccion.distancia;
	
	if (eleccion.tipo == GIMNASIO)
	{
		this->cant_gimnasios_por_ganar--;
		this->cantidad_pociones= this->cantidad_pociones - eleccion.pocionesNecesarias;
	}else{
		this->cantidad_pociones = cantidad_pociones+3;//HARDCODE!!!
	}
	//this->printEleccion(eleccion);
	this->eleccionActual = Eleccion(this);
	//cout << "ELEGI:   ";
	//this->printEleccion(eleccion);
	this->paso = decisiones->size();
	

}

bool MaestroPokemon::deshacerEleccion()
{
	if(this->decisiones->empty()){
		return false;
	}

	Eleccion eleccionADeshacer = this->decisiones->back();
	this->decisiones->pop_back();
	this->paso = decisiones->size();

	this->destinos_visitados[eleccionADeshacer.id] = 0;

	this->distancia = this->distancia - eleccionADeshacer.distancia;
	//printf("\tDistancia sin Eleccion tomada:%d\n",this->distancia  );
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


std::list<int> * MaestroPokemon::caminoRecorrido(){
	std::list<int> * camino = new list<int>();
	for (std::list<Eleccion>::iterator it=this->decisiones->begin(); it != this->decisiones->end(); ++it){
		camino->push_back((*it).id+1);

	}
	return camino;



}
