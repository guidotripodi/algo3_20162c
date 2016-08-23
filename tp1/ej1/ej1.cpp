//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
using namespace std;

bool tienenLampara = true;
int arq_totales;
int arq_destino = 0;
int can_totales;
int can_destino = 0;  
int * parActual_x_paso;
int paso = 0;

int * arqueologo_origen;
int * canibal_origen;

int main(int argc, char* argv[])
{

	bool exitoBackPar = true;
	bool exitoBackLampara = true;

	while(exitoBackLampara || exitoBackPar){
		if (tienenLampara)//flag
		{
			par = parPosible();
			if (par>-1)//Busco en el casillero del paso si me quedan pares posibles
			{
				enviarPar(par);//flag + anotacion en arreglos + 1 paso más
			}else{
				exitoBackLampara = backtrackRetorno(farolero);//vuelve al paso anterior
			}
		}else{
			farolero = retornoPosible();
			if (farolero>-1)//busco en el casillero
			{
				retornarLampara(farolero);//flag + anotacion en arreglos + 1 paso más
			}else{
				 exitoBackPar = backtrackPar(par);//vuelve al paso anterior y cambia de rama
				}
			}

			if (pasaronTodos())
			{
				guardarTiempo();
			}
		}


	}

	int parPosible(){
		int parEvaluar = parActual_x_paso[paso] + 1;
		int tot_pares = arq_totales*can_totales;
		while(!parValido(parEvaluar) && parEvaluar<=tot_pares){
			parEvaluar += 1;
		}

		if (parEvaluar<=tot_pares)
		{
			return parEvaluar;
		}else{
			return -1;
		}
		
	}

	bool parValido(par){
		int aux_arq_destino = arq_destino;
		int aux_can_destino = can_destino;  

		//Checkeo de que no me vaya de los limites (un par valido)
		if (par>arq_totales*can_totales)
		{
			return false;
		}
		//parseo los datos de la tupla
		a = primero(par);
		b = segundo(par);

		if (!((esCanibal(a) || esArquitecto(a)) && (esCanibal(b) || esArquitecto(b)))) {
			return false; //persona invalida
		}

		//checkeo que el balance siga valiendo
		aux_can_destino += esCanibal(a) && canibal_origen[a];
		aux_arq_destino += esArquitecto(a) && arquitecto_origen[a];

		aux_can_destino += esCanibal(b) && canibal_origen[b];
		aux_arq_destino += esArquitecto(b) && arquitecto_origen[b];
		
		int arq_origen = arq_totales - aux_arq_destino;
		int can_origen = can_totales - aux_can_destino;

		return arq_origen >= can_origen && arq_destino>=can_destino;
	}

void enviarPar(par){
	parActual_x_paso[paso] = par;
	tienenLampara = 0;
	paso++;

	//actualizar estructura
}