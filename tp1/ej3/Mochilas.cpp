Mochilas::Mochilas(const int cantidad, const int * capacidades, const int cantTiposElementos, const int * tiposElementos )
{
	//Los tipos de elementos tienen que venir ordenados
	this->cantidadMochilas = cantidad;
	this->capacidades = capacidades;
	this->cantTiposElementos = cantTiposElementos;
	this->tiposElementos = tiposElementos;

	this->cantElementos = 0;
	for (int i = 0; i < cantTiposElementos; i++)
	{
		this->cantElementos = this->cantElementos + tiposElementos[i];
	}
	int KMochilaMasGrande = this->capacidades[this->cantidadMochilas-1];
	this->M = new int[this->cantElementos][KMochilaMasGrande];

	for (int i = 0; i < cantElementos; i++)
	{
		this->M[i][0] = 0;
	}
}
Mochilas::~Mochilas()
{
	//Genera solucion al problema de la mochila simple
}
void Mochilas::generarSolucion()
{
	int KMochilaMasGrande = this->capacidades[this->cantidadMochilas-1];
	for (int i = 0; i < this->cantElementos; i++)
	{
		for (int i = 1; i < KMochilaMasGrande; i++)
		{
			/* code */
		}
	}
}
int Mochilas::siguienteElementoOptimo(){

}
int Mochilas::getOptimoParaMochilasSinElemento(const int mochila1, const int mochila2, const int elemento) const
{

}
void Mochilas::asignarElementoAMochila(const int elemento, const int mochila)
{

}


