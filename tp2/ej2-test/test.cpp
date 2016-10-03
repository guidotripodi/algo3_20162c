void sinSolucion(){
	int F = 100;
	int C = 100;
	
	for (int l = 5; l < 100; ++l){
        F = l;
        C = l+4;
        char map[F*C];
        int h = F;
        int x = C;

        for (int i = 0; i < h; ++i) {
                for (int j = 0; j < x; ++j) {
                    if (i == 0 || j == 0 || j == x-1 || i == h-1)   {
                        map[(i*x)+j] = '#';
                    }else{ if (i == 1 && j == x-2){
                            map[(i*x)+j] = '1';
                         }else{ if (i == 1 && j == 1) {
                                    map[(i*x)+j] = '1';
                                }else{
                                    if ((i == 1 && j == x-3 )||( i == 1 && j == x-4 )||( i == 2 && j == x-2 )||( i == 2 && j == x-3 ) ||( i == 3 && j == x-2 )||( i == 3 && j == x-3 ) ){
                                        map[(i*x)+j] = '#';
                                    }else{
                                        map[(i*x)+j] = '.';
                                    }

                                }
                            }
                        }                
                }               
            } 
		funcionEj1(F, C, map);
}

}


void sinEsfuerzo(){
	int F = 100;
	int C = 100;
	
	for (int l = 5; l < 100; ++l){
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
                 
		funcionEj1(F, C, map);
}

}