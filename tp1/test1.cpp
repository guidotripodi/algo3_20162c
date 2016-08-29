
void mismavelocidad(){
	int i,j,x;
	int cantidad_canival;
	int cantidad_arqueologo;
	int * tiempo_arqueologo[6];
	int * tiempo_canibal[6];
	i = 0;
	while(i + j <7){
		j = 0;
		while(i+j <7){
			x = 1000;
			while(x < 10000){
				cantidad_arqueologo = i;
				cantidad_canival = j;
				h = 0;
				while(h < i){
					tiempo_arqueologo[h] = x;
					h++;
				}
				h = 0;
				while(h < j){
					tiempo_canibal[h] = x;
					h++;
				}
				algoritmoResolucion(cantidad_arqueologo, cantidad_canival, tiempo_arqueologo, tiempo_canibal);
				x=x+1000;
		}
		j++;
	}
	i++;
	}
}

void noHayCanibales(){
	int i,j,x;
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