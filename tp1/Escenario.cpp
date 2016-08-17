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

 	public:
		int parPosible() const
		{
			int parEvaluar = parActual_x_paso[paso] + 1;

			while(!parValido(parEvaluar) && parEvaluar<=this.pares_totales){
				parEvaluar += 1;
			}

			if (parEvaluar<=tot_pares)
			{
				return parEvaluar;
			}else{
				return -1;
			}
		}
		int faroleroPosible() const;
		void enviarPar(const int par);
		void enviarFarolero(const int persona);
		void backtrackPar();  	
		void backtrackFarolero();

}