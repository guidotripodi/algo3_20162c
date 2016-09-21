void sinSolucion(){
	int F = 100;
	int C = 100;
	int Pmax = 3;

	for (int l = 5; l < 50; ++l){
		F = l;
		C = l+4;


	char map[F*C];
		for (int i = 0; i < h; ++i)	{
				for (int j = 0; j < x; ++j)	{
					if (i == 0 || j == 0 || j == x-1 || i == h-1)	{
						map[(i*x)+j] = '#';
					}else{ if (i == 1 && j == x-2){
							map[(i*x)+j] = 'x';
						 }else{ if (i == 1 && j == 1) {
						 			map[(i*x)+j] = 'o';
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
		funcionEj1();
}

}

void caminoSinRomperParedes(){
	int F = 100;
	int C = 100;
	int Pmax = 3;

	for (int l = 5; l < 50; ++l){
		F = l;
		C = l+4;

				  char map[F*C];

                 int h = F;
                 int x = C;

			//armando matriz			
			for (int i = 0; i < h; ++i)	{
				for (int j = 0; j < x; ++j)	{
					if (i == 0 || j == 0 || j == x-1 || i == h-1)	{
						map[(i*x)+j] = '#';
					}else{ if (i == 1 && j == x-2){
							map[(i*x)+j] = 'x';
						 }else{ if (i == 1 && j == 1) {
						 			map[(i*x)+j] = 'o';
						 		}else{
						 			if ((i < h-2 && j % 2 == 0) || (i < h-2 && j % 2 == 0)){
						 				map[(i*x)+j] = '#';
						 			}else{
						 				map[(i*x)+j] = '.';
						 			}

						 		}
							}
						}
					
				}
				
		}
		funcionEj1();


}

}


void rompiendoPparedes(){
	int F = 100;
	int C = 100;
	int Pmax = 3;

	for (int l = 5; l < 50; ++l){
		F = l;
		C = l+4;

				  char map[F*C];

                 int h = F;
                 int x = C;

			//armando matriz			
				for (int i = 0; i < h; ++i)	{
				for (int j = 0; j < x; ++j)	{
					if (i == 0 || j == 0 || j == x-1 || i == h-1)	{
						map[(i*x)+j] = '#';
					}else{ if (i == 1 && j == x-2){
							map[(i*x)+j] = 'x';
						 }else{ if (i == 1 && j == 1) {
						 			map[(i*x)+j] = 'o';
						 		}else{
						 			if ((j % 2 == 0)){
						 				map[(i*x)+j] = '#';

						 			}else{
						 				map[(i*x)+j] = '.';
						 			}

						 		}
							}
						}
					
				}
				
		}
		PMax = x/2;
		funcionEj1();

}
}