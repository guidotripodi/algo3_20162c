class Mochilas {
private:
	//Guardo numeros de pares intercalados con el numero de los faroleros que viajan en cada paso
	

public:

	Mochilas(const int cantidad, const int * capacidades, const int cantTiposElementos, const int * tiposElementos );
	~Mochilas();
	//Genera solucion al problema de la mochila simple
	void generarSolucion();
	int siguienteElementoOptimo();
	int getOptimoParaMochilasSinElemento(const int mochila1, const int mochila2, const int elemento) const;
	void asignarElementoAMochila(const int elemento, const int mochila);


};