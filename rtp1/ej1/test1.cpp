
void mismavelocidad(){
int j,x,h;
	int cant_canibales;
	int cant_arqueologos;
	int * tiempos_arqueologos[6];
	int * tiempos_canibales[6];
	i = 0;
	while(i + j <7){
		j = 0;
		while(i+j <7 && j<i){
			j++;
			x = 1;
			while(x < 50){
				cant_arqueologos = i;
				cant_canibales = j;
				h = 0;
				while(h < i){
					tiempos_arqueologos[h] = x;
					h++;
				}
				h = 0;
				while(h < j){
					tiempos_canibales[h] = x;
					h++;
				}
				algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
				x++;
		}
	}
	i++;
	}
}

void distintavelocidad(){
	int i,j,x,h;
	int cantidad_canival;
	int cantidad_arqueologo;
	int * tiempo_arqueologo[6];
	int * tiempo_canibal[6];
	i = 0;
	while(i + j <7){
		j = 0;
		while(i+j <7 && j<i){
			j++;
			x = 1000;
			while(x < 10000){
				cantidad_arqueologo = i;
				cantidad_canival = j;
				h = 0;
				while(h < i){
					tiempo_arqueologo[h] = x+h;
					h++;
				}
				h = 0;
				while(h < j){
					tiempo_canibal[h] = x-h;
					h++;
				}
				algoritmoResolucion(cantidad_arqueologo, cantidad_canival, tiempo_arqueologo, tiempo_canibal);
				x=x+1000;
		}
	}
	i++;
	}
}




void noHayCanibales(){
	int i,j,x,h;
	int cantidad_arqueologo;
	int * tiempo_arqueologo[6];
	i = 0;
	j = 0;
	while(i + j <7){
			x = 1000;
			while(x < 10000){
				cantidad_arqueologo = i;
				cantidad_canival = j;
				h = 0;
				while(h < i){
					tiempo_arqueologo[h] = x+h;
					h++;
				}
				algoritmoResolucion(cantidad_arqueologo, 0, tiempo_arqueologo, 0);
				x=x+1000;
			}
		i++;
	}
}

void hayMasCanibalesQueArqueologos(){

int j,x,h;
	int cant_canibales;
	int cant_arqueologos;
	int * tiempos_arqueologos[6];
	int * tiempos_canibales[6];
	i = 0;
	while(i + j <7){
		j = 0;
		while(i + j <7 && j<i){
			j++;
			x = 1;
			while(x < 50){
				cant_arqueologos = j;
				cant_canibales = i;
				h = 0;
				while(h < i){
					tiempos_arqueologos[h] = x+h;
					h++;
				}
				h = 0;
				while(h < j){
					tiempos_canibales[h] = x+h;
					h++;
				}
				algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
				x++;
		}
				if (j+1 == i || j+1 + i == 7){
					break;
				}
	}
	if (j == 3){
		j = 0;
	}
	i++;
	}

}


/* TIEMPO */

/* COMPLEJIDAD */

void complejidad(){
	int i,x,j,l,h,x;
	l = 0;
	while(l < 6){
		h = 0;
		while(h < 6){
			x = 0;
			while(x < 6){
				i = 0;
				while(i < 6){
					j = 0;
					while(j < i)
						j++;
					}
				i++;
			}
			x++;
		}
		h++;
	}
	l++;
}

