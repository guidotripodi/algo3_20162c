class Escenario {
private:
	//Guardo numeros de pares intercalados con el numero de los faroleros que viajan en cada paso
	int * eleccion_x_paso;
	int pares_totales;

	int * personas_ladoA;
	int cant_canibales_ladoA;
	int cant_arqueologos_ladoA;

	int cant_canibales_ladoB;
	int cant_arqueologos_ladoB;

	const int * tiempos_arqueologos;
	const int * tiempos_canibales; 
	int personas_totales;

	bool parValido(int par) const;
	bool faroleroValido(int persona) const;
	bool isCanibal(int persona) const;
	bool estaBalanceadoPasandoFarolero(int persona) const;
	bool estaBalanceadoPasandoPar(int par) const;
	int primero(int par) const;
	int segundo(int par) const;
	int getTiempoPersona(int persona);
	int sigPar() const;

public:
	int tiempo;
	int tienenLampara;
	int paso;

	Escenario(const int cantA, const int cantC, const int * tiempos_arqueologos, const int * tiempos_canibales);
	~Escenario();
	int parPosible() const;
	int faroleroPosible() const;
	void enviarPar(const int par);
	void enviarFarolero(const int persona);
	bool backtrackPar();
	bool backtrackFarolero();
	int pasaronTodos();

	//Para ver el estado del sistema
	void printPar(int par) const;
	void printPersona(int persona) const;
	void printStatus()const;
	

};