
#include "MaestroPokemon.hpp"
using namespace std;

bool MaestroPokemon::eleccionValida(Eleccion eleccion) const
{
	//printEleccion(eleccion);
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
	//cout<<"Es valida\n";
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


MaestroPokemon::MaestroPokemon(int cant_gimnasios, int cant_pokeParadas, int cap_mochila, const pair <pair <int,int>, int> gyms[], const pair <int,int> posiciones_pp[], int idInicial){

	this->cant_gimnasios = cant_gimnasios;
	this->cant_gimnasios_por_ganar = cant_gimnasios;
	this->cant_pokeParadas = cant_pokeParadas;
	this->capacidad_mochila = cap_mochila;
	this->cantidad_pociones = 0;
	this->gyms = gyms;
	this->posiciones_pp = posiciones_pp;
	this->paso=0;


	this->decisiones = new list<MaestroPokemon::Eleccion>();
	this->opciones = new list<int>;


	this->distancia=0;


	for (int i = idInicial; i < this->cant_gimnasios + this->cant_pokeParadas; i++)
	{
		opciones->push_back(i);
	}
	for (int i = 0; i < idInicial; i++)
	{
		opciones->push_back(i);
	}

	this->eleccionActual = Eleccion(this);
	this->eleccionActual.id=idInicial;
	this->eleccionActual.recalcular();


}

MaestroPokemon::~MaestroPokemon(){
	delete this->decisiones;
	delete this->opciones;
}

bool MaestroPokemon::eleccionGolosa(){
	Eleccion eleccion = Eleccion(this);
	long long minima = -1;
	bool minimo_es_gym = false;

	std::list<int>::iterator itm;

	for (std::list<int>::iterator it=opciones->begin(); it != opciones->end(); ++it){
	//	cout<<i++<<"\n";
		eleccion.id = *it;
		eleccion.recalcular();
		//printEleccion(eleccion);
		bool es_minima = (eleccion.distancia < minima) || minima==-1 ; 
		bool minimo_es_pp_yyo_gym = !minimo_es_gym && eleccion.tipo==GIMNASIO; // minimo es pp y eleccion es gimnasio

		//Si la minima fue pp, entonces la eleccion puede ser substituida por cualquier gym valido
		if ((es_minima || minimo_es_pp_yyo_gym) && eleccionValida(eleccion) )
		{
			//Si el anterior minimo fue un gym, y el nuevo minimo es una PP...entonces me quedo con el gym
			//Si el anterior minimo no fue un gym, entonces me quedo con el minimo que calcule

			if (!(minimo_es_gym && eleccion.tipo==PP))//minimo es pp o soy gimnasio
			{
				minima = eleccion.distancia;
				minimo_es_gym = eleccion.tipo!=PP;
				itm=std::list<int>::iterator(it);
				
			}else{
				//cout<<"el minimo ya es un gym y soy una pp\n";
			}
		}else{
			//cout<<"no es minima o no es valida\n";
		}
	}

	if (minima == -1)
	{
		return false;
	}

	//cout<<*itm<<" ";

	paso = decisiones->size();

	eleccionActual.id=*itm;
	eleccionActual.recalcular();
	decisiones->push_back(eleccionActual);

	opciones->erase(itm);
	//Incremento la distancia
	//printf("[distancia 0]  %d  \n", distancia );
	if (decisiones->size()>1)
	{
		distancia += eleccionActual.distancia;
	}
	//printf("[distancia 1]  %d  \n", distancia );

	if (eleccionActual.tipo == GIMNASIO)
	{

		cant_gimnasios_por_ganar--;
		cantidad_pociones= cantidad_pociones - eleccionActual.pocionesNecesarias;
	}else{

		cantidad_pociones = min(cantidad_pociones+3,this->capacidad_mochila);//HARDCODE!!!
	}
	//cout <<"Elegida\n";
	return true;

}




bool MaestroPokemon::gane()
{
	return this->cant_gimnasios_por_ganar == 0;
}


std::list<int> * MaestroPokemon::caminoRecorrido(const pair <int,int> pp_aux[]){

	std::list<int> * camino = new list<int>();
	for (std::list<Eleccion>::iterator it=this->decisiones->begin(); it != this->decisiones->end(); ++it){
		pair <int, int> posicion;
		posicion.first = (*it).posicion.first;
		posicion.second = (*it).posicion.second;
		/*Como se realizan pp ramas tengo que ver cual es el id inicial ya que fue cambiando*/

		for (int i = 0; i < cant_pokeParadas; ++i){
			if (pp_aux[i].first == posicion.first && pp_aux[i].second == posicion.second ){

				camino->push_back(i+cant_gimnasios+1);
				
			}
			if(i <= cant_gimnasios){
				if (gyms[i].first.first == posicion.first && gyms[i].first.second == posicion.second ){
					camino->push_back(i+1);
				}
			}
		}
		if (camino->size() < this->decisiones->size()){
			for (int i = cant_pokeParadas; i < cant_gimnasios; ++i)	{
				if (gyms[i].first.first == posicion.first && gyms[i].first.second == posicion.second ){

					camino->push_back(i+1);
				}
			}
		}

	}
	return camino;


}
