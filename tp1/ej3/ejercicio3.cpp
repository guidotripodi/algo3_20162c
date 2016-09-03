#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M1 1
#define M2 2
#define M3 3

int M = 0;
int N = 0;
int *objectsWeights = NULL;
int *objectsValues = NULL;
int *knapSacksCapacities = NULL;

int max(int a, int b){
    return (a > b) ? a : b;
}

void simpleKnapSackProblem() {
    int i, w;
    
    int knapSackCapacity = knapSacksCapacities[M];
    
    int K[N][knapSackCapacity + 1]; // la mochila con peso 0 es para finalizar
    
    for (i = 0; i < N; i++) {
        for (w = 0; w <= knapSackCapacity; w++) {
            if (w == 0){
                K[i][w] = 0;
            }else if (objectsWeights[i] <= w){
                // condiciones adicionales: que esta mochila maximize para el objeto, y que no se haya usado en otra que tambien maximize
                if (i == 0) {
                    K[i][w] = objectsValues[i];
                }else {
                    K[i][w] = max(objectsValues[i] + K[i - 1][w - objectsWeights[i]], K[i - 1][w]);
                }
            }else {
                //entra acá si no habia espacio o el objeto no me convenia meterlo en la mochila knapsack
                if (i == 0) {
                    K[i][w] = 0;
                }else {
                    K[i][w] = K[i - 1][w];
                }
            }
            printf("%d |", K[i][w]);
        }
        printf("\n");
    }
    printf("\n");
    
    int actualCol = knapSackCapacity;
    int actualRow = N-1;
    while (actualRow >= 0 && actualCol >= 0) {
        if (actualCol == 0) {
            actualCol=-1;
        }else if (actualRow == 0) {
            if (K[actualRow][actualCol]) {
                printf("used object (%d, %d) \n", objectsValues[actualRow], objectsWeights[actualRow]);
            }
            actualRow=-1;
        }else if (K[actualRow-1][actualCol] != K[actualRow][actualCol]) {
            printf("used object (%d, %d) \n", objectsValues[actualRow], objectsWeights[actualRow]);
            actualCol = abs(actualCol-objectsWeights[actualRow]); // por si acaso, valor absoluto.
            actualRow--;
        }else{
            actualRow--;
        }
    }
    
    printf("} \n");
    
    printf("maximo logrado %d", K[N-1][knapSackCapacity]);
}

void bidimentionalKnapSackProblem() {
	
	int* K[knapSacksCapacities[0] +1][knapSacksCapacities[1] + 1];
	
	int max = 0;
	int k1Max = 0;
	int k2Max = 0;
	
	for(int i = 0; i < N; i++) {
		int objectWeight = objectsWeights[i];
	
		for(int k2 = knapSacksCapacities[1]; k2 >= objectWeight; k2--){
			for(int k1 = knapSacksCapacities[0]; k1 >= objectWeight; k1--){
				if(K[k1][k2] == NULL){
					K[k1][k2] = new int[3](); // maximo, objeto, mochilas
					K[k1][k2][2] = -1;
				}
				
				if(K[k1-objectWeight][k2][0] > K[k1][k2][0] && K[k1-objectWeight][k2][0] > K[k1][k2-objectWeight][0]){
					K[k1][k2][0] = K[k1-objectWeight][k2][0] + objectsValues[i];
					K[k1][k2][1] = i;
					K[k1][k2][2] = M1;					
				}else if (K[k1][k2-objectWeight][0] > K[k1][k2][0] && K[k1][k2-objectWeight][0] > K[k1-objectWeight][k2][0]) {
					K[k1][k2][0] = K[k1][k2-objectWeight][0] + objectsValues[i];
					K[k1][k2][1] = i;
					K[k1][k2][2] = M2;
				}
				
				if(K[k1][k2][0] > max) {
					max = K[k1][k2][0];
					k1Max = k1;
					k2Max = k2;
				}
			}
		}
	}
	
	int maxAux = max;
	
	printf("Mochilas: \n");
	
	while (maxAux > 0) {
		
		int knapsack = K[k1Max][k2Max][2];
		int weight = objectsWeights[K[k1Max][k2Max][1]];
		int value = objectsValues[K[k1Max][k2Max][1]];
		printf("objeto %d, %d en mochila %d \n\n", value, weight, knapsack);
		
		if(knapsack == M1){
			k1Max = k1Max - weight;
		}else {
			k2Max = k2Max - weight;
		}
		
		maxAux -= value;
	}

	printf("maximo logrado %d", max);
}

void tridimentionalKnapSackProblem() {
	
	int* K[knapSacksCapacities[0] +1][knapSacksCapacities[1] + 1][knapSacksCapacities[2] + 1];
	
	for (int x = 0; x <= knapSacksCapacities[0]; x++) {
		for (int y = 0; y <= knapSacksCapacities[1]; y++) {
			for (int z = 0; z <= knapSacksCapacities[2]; z++) {
				K[x][y][z] = new int[3](); // maximo, objeto, mochilas
				K[x][y][z][0] = 0;
				K[x][y][z][1] = 0;
				K[x][y][z][2] = -1;
			}
		}
	}
	
	int max = 0;
	int k1Max = 0;
	int k2Max = 0;
	int k3Max = 0;
	
	printf("N es %d", N);
	
	int k1 = 0;
	int k2 = 0;
	int k3 = 0;
	
	for(int i = 0; i < N; i++) {
		int objectWeight = objectsWeights[i];
	
		for(k3 = knapSacksCapacities[2]; k3 >= 0; k3--){
			for(k2 = knapSacksCapacities[1]; k2 >= 0; k2--){
				for(k1 = knapSacksCapacities[0]; k1 >= 0; k1--){
					
					int m0 = K[k1][k2][k3][0];
					int m1 = 0;
					int m2 = 0;
					int m3 = 0;
					
					if(k1 >= objectWeight){
						m1 = K[k1-objectWeight][k2][k3][0];
					}
					
					if(k2 >= objectWeight){
						m2 = K[k1][k2-objectWeight][k3][0];
					}
					 
					if(k3 >= objectWeight){
						m3 = K[k1][k2][k3-objectWeight][0];
					}
					
					int value = objectsValues[i];
					
					if(k1 >= objectWeight && m1 + value >= m0 && 	
					   m1 + value >= m2 + value &&
					   m1 + value >= m3 + value){
						
						//printf("entre con valor %d \n\n", K[k1-objectWeight][k2][k3][0] + objectsValues[i]);
				
						K[k1][k2][k3][0] = m1 + value;
						K[k1][k2][k3][1] = i;
						K[k1][k2][k3][2] = M1;	
											
					}else if (k2 >= objectWeight && m2 + value >= m0 && 	
					          m2 + value >= m1 + value &&
					          m2 + value >= m3 + value) {
						
						//printf("entre con valor %d \n\n", K[k1][k2-objectWeight][k3][0] + objectsValues[i]);
						
						K[k1][k2][k3][0] = m2 + value;
						K[k1][k2][k3][1] = i;
						K[k1][k2][k3][2] = M2;
					
					}else if (k3 >= objectWeight && m3 + value >= m0 && 	
					          m3 + value >= m1 + value &&
					          m3 + value >= m2 + value) {
					
						//printf("entre con valor %d \n\n", K[k1][k2][k3-objectWeight][0] + objectsValues[i]);
					
						K[k1][k2][k3][0] = m3 + value;
						K[k1][k2][k3][1] = i;
						K[k1][k2][k3][2] = M3;
					
					}
				
					
					printf ("maximo obtenido %d con objeto %d, %d \n", K[k1][k2][k3][0], objectsValues[K[k1][k2][k3][1]], objectsWeights[K[k1][k2][k3][1]]);
				
					if(K[k1][k2][k3][0] > max) {
						max = K[k1][k2][k3][0];
						k1Max = k1;
						k2Max = k2;
						k3Max = k3;
					}
				}
			}
		}
	}
	
	int maxAux = max;
	
	printf("Mochilas: \n");
	
	while (maxAux > 0) {
		
		int knapsack = K[k1Max][k2Max][k3Max][2];
		int weight = objectsWeights[K[k1Max][k2Max][k3Max][1]];
		int value = objectsValues[K[k1Max][k2Max][k3Max][1]];
		printf("k1: %d, k2: %d, k3: %d \n", k1Max, k2Max, k3Max);
		printf("objeto %d, %d en mochila %d \n\n", value, weight, knapsack);
		
		if(knapsack == M1){
			k1Max = k1Max - weight;
		}else if(knapsack == M2){
			k2Max = k2Max - weight;
		}else {
			k3Max = k3Max - weight;
		}
		
		maxAux -= value;
	}
	
	printf("maximo logrado %d \n", max);
}

int main(){
    
    int knapSacks[] = {3, 5, 7};
    
    int values[] = {7, 3, 5, 5, 7};
    
    int weights[] = {2, 3, 3, 5, 7};
  
//    int values[] = {7, 3, 5, 1, 2};
    
//    int weights[] = {2, 3, 3, 5, 7};
    
    N = 5;
    M = 3;
    objectsWeights = weights;
    objectsValues = values;
    knapSacksCapacities = knapSacks;
 
 	tridimentionalKnapSackProblem();
    
	return 0;
}
