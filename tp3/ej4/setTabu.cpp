#include "setTabu.h"

SetTabu::SetTabu(){}
SetTabu::~SetTabu(){}

void SetTabu::push(Arista nueva)
{
	if(conjunto.find(nueva) == conjunto.end()) //O(log(n))
	{
		conjunto.insert(nueva);//log
		cola.push(nueva);//O(1)
	}
}

Arista SetTabu::pop()
{
	Arista paraBorrar = cola.front();
	cola.pop();
	conjunto.erase(paraBorrar);
	return paraBorrar;
}

long long SetTabu::size()
{
	return conjunto.size();
}

bool SetTabu::belongs(Arista buscada)
{
	bool pertenece = conjunto.find(buscada) != conjunto.end();
	return pertenece;
}

