
void sinSolucion(){
	//grafo K_cantidadEstaciones-1 con ninguna arista a la salida
	int estacionesMax = 50;
	
	for(int cantidadEstaciones = 2; cantidadEstaciones < estacionesMax; cantidadEstaciones++){
		int cantidadVias;
		int vias[3*cantidadVias];
			for(int j = 0; j < cantidadVias; j++){//generar vias
			}
		//tiempo
		buscarCaminoMinimo(cantidadEstaciones, cantidadVias, vias);
		//tiempo end
		//guardar tiempos
	
	}
}






/*
void sinSolucion(){
	int F = 100;
	int C = 100;
	
	for (int l = 5; l < 50; ++l){
        F = l;
        C = l+4;
        char map[F*C];
        int h = F;
        int x = C;

        for (int i = 0; i < h; ++i) {
                for (int j = 0; j < x; ++j) {
                    if (i == 0 || j == 0 || j == x-1 || i == h-1)   {
                        map[(i*x)+j] = '#';
                    }
                    if ((i == 1 && j == x-3 )||( i == 1 && j == x-4 )||( i == 2 && j == x-2 )||( i == 2 && j == x-3 ) ||( i == 3 && j == x-2 )||( i == 3 && j == x-3 ) ){
                        map[(i*x)+j] = '#';
                    }else{
                        map[(i*x)+j] = '.';
                        }
                   }
                            }
		funcionEj2(F, C, map);
}

}


void sinEsfuerzo(){
	int F = 100;
	int C = 100;
	
	for (int l = 5; l < 50; ++l){
        F = l;
        C = l+4;
        char map[F*C];
        int h = F;
        int x = C;

        for (int i = 0; i < h; ++i) {
                for (int j = 0; j < x; ++j) {
                    if (i == 0 || j == 0 || j == x-1 || i == h-1)   {
                        map[(i*x)+j] = '#';
                    }else{
                          map[(i*x)+j] = '.';
                    }

                }
        }
                 
		funcionEj2(F, C, map);
}

}

void grafoAGM(){
	int F = 100;
	int C = 100;
	int cont;
	
	for (int l = 5; l < 50; ++l){
        F = l;
        C = l+4;
        char map[F*C];
        int h = F;
        int x = C;
        z = 1;
        y = 2;
        cont = 0;

        for (int i = 0; i < h; ++i) {
                for (int j = 0; j < x; ++j) {
                    if (i == 0 || j == 0 || j == x-1 || i == h-1)   {
                        map[(i*x)+j] = '#';
                    } 
                   if (j % 2 == 0){
                        map[(i*x)+j] = '#';
                   }
                   if (j % 2 == 1) {
                   		map[(i*x)+j] = '.';
                   }
                   if (z < h-1 && y < x-1) {
                   		z++;
                   		y++;
                   		map[(z*x)+y] = char(cont +48);
                   }
                    if (cont < 9){
                       cont++;
                   }else{
                        cont = 1;
                   }                           
                }
        }
                 
		funcionEj2(F, C, map);
}

}

void grafoConMuchosCiclos(){
	int F = 100;
	int C = 100;
	
	  for (int l = 5; l < 50; ++l){
        F = l;
        C = l+4;
        char map[F*C];
        int h = F;
        int x = C;
        int cont = 0;
        for (int i = 0; i < h; ++i) {
                for (int j = 0; j < x; ++j) {
                   if (j % 2 == 1 && j != 0 && j != x-1) {
                        map[(i*x)+j] = '.';
                   }
                    if (i == 0 || j == 0 || j == x-1 || i == h-1)   {
                        map[(i*x)+j] = '#';
                    } 
                   if (j % 2 == 0){
                        map[(i*x)+j] = '#';
                   }
                   if (j % 2 == 0 && i % 2 == 0 && j != 0 && i != 0 && j < x-1 && i < h-1){
                       map[(i*x)+j] = char(cont +48);
                   }
                   if (cont < 9){
                       cont++;
                   }else{
                        cont = 1;
                   }
                }
        }
		funcionEj2(F, C, map);
        }         
}
*/
