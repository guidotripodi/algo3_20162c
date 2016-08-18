class Escenario {
private:
	int * parActual_x_paso;
	int pares_totales = 0;

	int * personas_ladoA;
	int cant_canibales_ladoA;
	int cant_arqueologos_ladoA;

	int cant_canibales_ladoB;
	int cant_arqueologos_ladoB;

	bool parValido(int par) const
	{
		int a  = this.primer(par);
		int b  = this.segundo(par);

			//Me fijo que ambos esten presentes en el lado A
		if (!(personas_ladoA[a] && personas_ladoA[b]))
		{
			return false;
		}

			//Calculo cuantos quedarian de cada lado
		int cant_canibales_A =  this.cant_canibales_ladoA - this.isCanibal(a) - this.isCanibal(b);
		int cant_arqueologos_A =  this.cant_canibales_ladoA - !this.isCanibal(a) - !this.isCanibal(b);
		int cant_canibales_B =  this.cant_canibales_ladoB + this.isCanibal(a) + this.isCanibal(b);
		int cant_arqueologos_B =  this.cant_canibales_ladoAB + !this.isCanibal(a) + !this.isCanibal(b);

		return cant_canibales_A <= cant_arqueologos_A && cant_canibales_B<=cant_arqueologos_B;



	}

	bool faroleroValido(int persona) const
	{
			//Me fijo que este del lado B
		if(persona_ladoA[persona])
		{
			return false;
		}

			//Calculo cuantos quedarian de cada lado
		int cant_canibales_A =  this.cant_canibales_ladoA - this.isCanibal(a);
		int cant_arqueologos_A =  this.cant_canibales_ladoA - !this.isCanibal(a);
		int cant_canibales_B =  this.cant_canibales_ladoB + this.isCanibal(a);
		int cant_arqueologos_B =  this.cant_canibales_ladoAB + !this.isCanibal(a);

		return cant_canibales_A <= cant_arqueologos_A && cant_canibales_B<=cant_arqueologos_B;
	}

	bool isCanibal(int persona) const
	{
			//En la estructura, se listan primero los arqueologos y despues los canibales, ppor lo cual es un canibal si esta en los indices m{s altos
		return persona > this.cant_arqueologos_ladoA + this.cant_arqueologos_ladoB - 1;
	}

	int primero(int par) const
	{
		int cant_personas = this.cant_arqueologos_ladoA + this.cant_arqueologos_ladoB + this.cant_canibales_ladoA + this.cant_canibales_ladoB
		return par \ cant_personas;
	}

	int segundo(int par) const
	{
		int cant_personas = this.cant_arqueologos_ladoA + this.cant_arqueologos_ladoB + this.cant_canibales_ladoA + this.cant_canibales_ladoB
		return par % cant_personas;
	}

public:
	int tiempo = 0;

	Escenario(){

	}

	int parPosible() const
	{
		int parEvaluar = this.parActual_x_paso[this.paso] + 1;

		while(!parValido(parEvaluar) && parEvaluar<=this.pares_totales){
			parEvaluar += 1;
		}

		if (parEvaluar<=this.tot_pares)
		{
			return parEvaluar;
		}else{
			return -1;
		}
	}
	int faroleroPosible() const
	{
		int faroleroAEvaluar = this.parActual_x_paso[this.paso] + 1;

		while(!faroleroValido(parEvaluar) && faroleroAEvaluar<=this.personas_totales){
			faroleroAEvaluar += 1;
		}

		if (faroleroAEvaluar<=this.personas_totales)
		{
			return faroleroAEvaluar;
		}else{
			return -1;
		}

	}
	void enviarPar(const int par){
		//Guardo el paso que funciono
		this.parActual_x_paso[this.paso] = par;

		//Recalculo el balance
		int a  = this.primer(par);
		int b  = this.segundo(par);

		this.cant_canibales_ladoA -= this.isCanibal(a) - this.isCanibal(b);
		this.cant_arqueologos_ladoA -= !this.isCanibal(a) - !this.isCanibal(b);
		this.cant_canibales_ladoB += this.isCanibal(a) + this.isCanibal(b);
		this.cant_arqueologos_ladoB += !this.isCanibal(a) + !this.isCanibal(b);

		//Marco a las personas como que viajaron al lado B
		this.personas_ladoA[a] = 0;
		this.personas_ladoA[b] = 0;

		//Avanzo el paso
		this.paso += 1;
		//Reseteo las personas a probar, la primer persona a ser evaluada va a ser la 0
		this.parActual_x_paso[this.paso] = 0;

		//El par se lleva la lampara al lado B
		this.tienenLampara = 0;

		this.tiempo += max(this.getTiempoPersona(a),this.getTiempoPersona(b));
	}
	void enviarFarolero(const int persona)
	{
			//Guardo el paso que funciono
		this.parActual_x_paso[this.paso] = persona;

			//Recalculo el balance

		this.cant_canibales_ladoA += this.isCanibal(persona);
		this.cant_arqueologos_ladoA += !this.isCanibal(persona);
		this.cant_canibales_ladoB -= this.isCanibal(persona);
		this.cant_arqueologos_ladoB -= !this.isCanibal(persona);

			//Marco a las personas como que viajaron al lado B
		this.personas_ladoA[persona] = 1;

			//Avanzo el paso
		this.paso += 1;
			//Reseteo las tuplas a probar, la primer tupla a probar va a ser la de cardinalidad 0
		this.parActual_x_paso[this.paso] = 0;

		//El farolero retorna la lampara al lado A
		this.tienenLampara=1;

		this.tiempo += this.getTiempoPersona(persona);


	}
	void backtrackPar()
	{
		//Si no hay más pasos para atras entonces devuelvo false
		if (this.paso--<0)
		{
			return false;
		} 

		//De lo contrario busco el par que produjo el backtrack y lo hago volver al lado A
		par = this.parActual_x_paso[this.paso];

		int a  = this.primer(par);
		int b  = this.segundo(par);

		this.cant_canibales_ladoA += this.isCanibal(a) + this.isCanibal(b);
		this.cant_arqueologos_ladoA += !this.isCanibal(a) + !this.isCanibal(b);
		this.cant_canibales_ladoB -= this.isCanibal(a) - this.isCanibal(b);
		this.cant_arqueologos_ladoB -= !this.isCanibal(a) - !this.isCanibal(b);

		//Marco a las personas como que retornaron al lado A
		this.personas_ladoA[a] = 1;
		this.personas_ladoA[b] = 1;

		//Se deshace la ida del par, y con ellos vuelve la lampara al lado A
		this.tienenLampara=1;

		this.tiempo -= max(this.getTiempoPersona(a),this.getTiempoPersona(b));

		return true;
	}  	
	void backtrackFarolero()
	{
		//Si no hay más pasos para atras entonces devuelvo false
		if (this.paso--<0)
		{
			return false;
		} 

		//De lo contrario busco el par que produjo el backtrack y lo hago volver al lado A
		persona = this.parActual_x_paso[this.paso];

		int a  = this.primer(par);
		int b  = this.segundo(par);

		this.cant_canibales_ladoA -= this.isCanibal(persona);
		this.cant_arqueologos_ladoA -= !this.isCanibal(persona);
		this.cant_canibales_ladoB += this.isCanibal(persona);
		this.cant_arqueologos_ladoB += !this.isCanibal(persona);

		//Marco a las personas como que retornaron al lado A
		this.personas_ladoA[persona] = 0;

		//Como se deshizo la vuelta del farolero, entonces en A no tienen lampara
		this.tienenLampara=0;

		this.tiempo -= this.getTiempoPersona(persona);

		return true;
	}

	int pasaronTodos()
	{
		return cant_canibales_ladoA + cant_arqueologos_ladoA == 0;
	}

}