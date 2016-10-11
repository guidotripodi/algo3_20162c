#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;

#define M1 1
#define M2 2
#define M3 3

int M = 0;
int N = 0;
int *objectsWeights = NULL;
int *objectsValues = NULL;
int *objectsUsed = NULL;
int *knapSacksCapacities = NULL;
int**** objects3dMatrices = NULL;
int*** objects2dMatrices = NULL;

int max(int a, int b){
    return (a > b) ? a : b;
}

int simpleKnapSackProblem(int knapsack) {
    int i, w;
    
    int knapSackCapacity = knapSacksCapacities[knapsack];
    
    int K[N][knapSackCapacity + 1]; // la mochila con peso 0 es para finalizar
    
    for (i = 0; i < N; i++) {
        for (w = 0; w <= knapSackCapacity; w++) {
            if (w == 0){
                K[i][w] = 0;
            }else if (objectsWeights[i] <= w && objectsUsed[i] == false){ 
                // condiciones adicionales: que esta mochila maximize para el objeto, y que no se haya usado en otra que tambien maximize
                if (i == 0) {
                    K[i][w] = objectsValues[i];
                }else {
                    K[i][w] = max(objectsValues[i] + K[i - 1][w - objectsWeights[i]], K[i - 1][w]);
                }
            }else {
                //entra acá si no habia espacio o el objeto ya fue usado
                if (i == 0) {
                    K[i][w] = 0;
                }else {
                    K[i][w] = K[i - 1][w];
                }
            }
        }
    }
    
    int actualCol = knapSackCapacity;
    int actualRow = N-1;
    while (actualRow >= 0 && actualCol >= 0) {
        if (actualCol == 0) {
            actualCol=-1;
        }else if (actualRow == 0) {
            if (K[actualRow][actualCol]) {
                objectsUsed[actualRow] = knapsack+1;
            }
            actualRow=-1;
        }else if (K[actualRow-1][actualCol] != K[actualRow][actualCol]) {
            objectsUsed[actualRow] = knapsack+1;
            actualCol = abs(actualCol-objectsWeights[actualRow]); // por si acaso, valor absoluto.
            actualRow--;
        }else{
            actualRow--;
        }
    }
    
    int max = K[N-1][knapSackCapacity];
    return max;
}

void create3dMatrices() {
    
    int km1 = knapSacksCapacities[0];
    int km2 = knapSacksCapacities[1];
    int km3 = knapSacksCapacities[2];
    
    for (int i = 0; i < N; i++) {
        int*** K = new int**[km1 +1];
        
        for (int x = 0; x <= km1; x++) {
            K[x] = new int*[km2 +1];
            
            for (int y = 0; y <= km2; y++) {
                K[x][y] = new int[km3 +1];
                
                for (int z = 0; z <= km3; z++) {
                    K[x][y][z] = 0;
                }
            }
        }
    
        objects3dMatrices[i] = K; 
    }
}

void create2dMatrices() {
    
    int km1 = knapSacksCapacities[0];
    int km2 = knapSacksCapacities[1];
    
    for (int i = 0; i < N; i++) {
        int** K = new int*[km1 +1];
        
        for (int x = 0; x <= km1; x++) {
            K[x] = new int[km2 +1];
            
            for (int y = 0; y <= km2; y++) {
                K[x][y] = 0;
            }
        }
        
        objects2dMatrices[i] = K;
    }
}

void delete2d(){
    for(int i = 0; i < N; i++){
        int** matrix = objects2dMatrices[i];
        for(int x = 0; x <= knapSacksCapacities[0]; x++){
            delete[](matrix[x]);    
        }
        delete[](matrix);
    }
    delete[](objects2dMatrices);
}

void delete3d(){

    for(int i = 0; i < N; i++){
        int*** matrix = objects3dMatrices[i];
        for(int x = 0; x <= knapSacksCapacities[0]; x++){
            for(int y = 0; y <= knapSacksCapacities[1]; y++){
                delete[](matrix[x][y]); 
            }
            delete[](matrix[x]);
        }
        delete[](matrix);

    }   
    delete[](objects3dMatrices);
}

void copy3dMatrixTo(int i) {
    
    int km1 = knapSacksCapacities[0];
    int km2 = knapSacksCapacities[1];
    int km3 = knapSacksCapacities[2];

    for (int x = 0; x <= km1; x++) {
        for (int y = 0; y <= km2; y++) {
            for (int z = 0; z <= km3; z++) {
                objects3dMatrices[i][x][y][z] = objects3dMatrices[i-1][x][y][z];
            }
        }
    }
}

void copy2dMatrixTo(int i) {
    
    int km1 = knapSacksCapacities[0];
    int km2 = knapSacksCapacities[1];
    
    for (int x = 0; x <= km1; x++) {
        for (int y = 0; y <= km2; y++) {
            objects2dMatrices[i][x][y] = objects2dMatrices[i-1][x][y];
        }
    }
}

void tridimentionalKnapSackProblem() {
    
    int km1 = knapSacksCapacities[0];
    int km2 = knapSacksCapacities[1];
    int km3 = knapSacksCapacities[2];
    
    create3dMatrices();
    
    int max = 0;
    int k1Max = 0;
    int k2Max = 0;
    int k3Max = 0;
    int objectMax = 0;
    
    int k1 = 0;
    int k2 = 0;
    int k3 = 0;
    
    for(int i = 0; i < N; i++) {
        int weight = objectsWeights[i];
        int value = objectsValues[i];
        
        if (i>0) {
            copy3dMatrixTo(i);
        }
        
        int ***K = objects3dMatrices[i];
        
        for(k3 = km3; k3 >= 0; k3--){
            for(k2 = km2; k2 >= 0; k2--){
                for(k1 = km1; k1 >= 0; k1--){
                    
                    int m0 = K[k1][k2][k3];
                    int m1 = 0;
                    int m2 = 0;
                    int m3 = 0;
                    
                    if(k1 >= weight){
                        m1 = K[k1-weight][k2][k3];
                    }
                    
                    if(k2 >= weight){
                        m2 = K[k1][k2-weight][k3];
                    }
                     
                    if(k3 >= weight){
                        m3 = K[k1][k2][k3-weight];
                    }
                    
                    if(k1 >= weight && m1 + value >= m0 &&
                       m1 + value >= m2 + value &&
                       m1 + value >= m3 + value) {
                
                        K[k1][k2][k3] = m1 + value;
                                            
                    }else if (k2 >= weight && m2 + value >= m0 &&
                              m2 + value >= m1 + value &&
                              m2 + value >= m3 + value) {
                        
                        K[k1][k2][k3] = m2 + value;
                        
                    }else if (k3 >= weight && m3 + value >= m0 &&
                              m3 + value >= m1 + value &&
                              m3 + value >= m2 + value) {
                    
                        K[k1][k2][k3] = m3 + value;
                        
                    }
                    if(K[k1][k2][k3] > max) {
                        max = K[k1][k2][k3];
                        k1Max = k1;
                        k2Max = k2;
                        k3Max = k3;
                        objectMax = i;
                    }
                }
            }
        }
    }
    
    
    int i = objectMax;
    
    while (i > 0) {
        int weight = objectsWeights[i];
        int value = objectsValues[i];
        
        int ***Ki = objects3dMatrices[i];
        int ***Kj = objects3dMatrices[i-1]; // j = i-1
        
        // no uso el actual (i) sigo con i-1
        if (!(Ki[k1Max][k2Max][k3Max] == Kj[k1Max][k2Max][k3Max])) {
            // entiendo que seguro sucede que: kj[k1Max][k2Max][k1Max] + objectsValue[i] = kj[k1Max][k2Max][k1Max]
            if (k1Max >= weight && Kj[k1Max-weight][k2Max][k3Max] + value == Ki[k1Max][k2Max][k3Max]) {
                k1Max -= weight;
                objectsUsed[i] = 1;
            }else if(k2Max >= weight && Kj[k1Max][k2Max-weight][k3Max] + value == Ki[k1Max][k2Max][k3Max]) {
                k2Max -= weight;
                objectsUsed[i] = 2;
            }else {
                k3Max -= weight;
                objectsUsed[i] = 3;
                // deberia ser obligatorio...por alguna vino
            }
        }
        
        i--;
    }
    
    if (i == 0 && max) {
        int weight = objectsWeights[0];
        
        if (k1Max >= weight) {
            objectsUsed[0] = 1;
        }else if (k2Max >= weight) {
            objectsUsed[0] = 2;
        }else {
            objectsUsed[0] = 3;
        }
    }

    printf("%d\n", max);
}

void bidimentionalKnapSackProblem() {
    
    int km1 = knapSacksCapacities[0];
    int km2 = knapSacksCapacities[1];
    
    create2dMatrices();
    
    int max = 0;
    int k1Max = 0;
    int k2Max = 0;
    int objectMax = 0;
    
    int k1 = 0;
    int k2 = 0;
    
    for(int i = 0; i < N; i++) {
        int weight = objectsWeights[i];
        int value = objectsValues[i];
        
        if (i>0) {
            copy2dMatrixTo(i);
        }
        
        int **K = objects2dMatrices[i];
    
        for(k2 = km2; k2 >= 0; k2--){
            for(k1 = km1; k1 >= 0; k1--){
                
                int m0 = K[k1][k2];
                int m1 = 0;
                int m2 = 0;
                
                if(k1 >= weight){
                    m1 = K[k1-weight][k2];
                }
                
                if(k2 >= weight){
                    m2 = K[k1][k2-weight];
                }
                
                if(k1 >= weight && m1 + value >= m0 &&
                   m1 + value >= m2 + value) {
                    
                    K[k1][k2] = m1 + value;
                    
                }else if (k2 >= weight && m2 + value >= m0 &&
                          m2 + value >= m1 + value) {
                    
                    K[k1][k2] = m2 + value;
                    
                }
                
                if(K[k1][k2] > max) {
                    max = K[k1][k2];
                    k1Max = k1;
                    k2Max = k2;
                    objectMax = i;
                }
            }
        }
    }
    
    
    int i = objectMax;
    
    while (i > 0) {
        int weight = objectsWeights[i];
        int value = objectsValues[i];
        
        int **Ki = objects2dMatrices[i];
        int **Kj = objects2dMatrices[i-1]; // j = i-1
        
        // no uso el actual (i) sigo con i-1
        if (!(Ki[k1Max][k2Max] == Kj[k1Max][k2Max])) {
            // entiendo que seguro sucede que: kj[k1Max][k2Max][k1Max] + objectsValue[i] = kj[k1Max][k2Max][k1Max]
            if (k1Max >= weight && Kj[k1Max-weight][k2Max] + value == Ki[k1Max][k2Max]) {
                k1Max -= weight;
                objectsUsed[i] = 1;
            }else {
                k2Max -= weight;
                objectsUsed[i] = 2;
                // deberia ser obligatorio...por alguna vino
            }
        }
        i--;
    }
    
    if (i == 0 && max) {
        int weight = objectsWeights[0];
        
        if (k1Max >= weight) {
            objectsUsed[0] = 1;
        }else {
            objectsUsed[0] = 2;
        }
    }
    
    printf("%d\n", max);
}

void initArrOfObjectsUsed() {
    objectsUsed = new int[N];
    
    for(int i = 0; i < N; i++) {
        objectsUsed[i] = 0;
    }
}

int main(){
    int x = 5;
    while(x < 50){
        objectsWeights = NULL;
        objectsValues = NULL;
        knapSacksCapacities = NULL;
    int i = 0;
    int cantidad = x; 
    M = 3;
    N = 0;
    
    int knapSacks[M];
    
    while(i < M){
        knapSacks[i] = i*10;
        i++;
    }

    i = 0;

    int* values = new int[cantidad];
    int* weights = new int[cantidad];
    int* amounts = new int[cantidad];

    
    while(i < cantidad){ //cantidad de tipos de objeto
        int cant = 1;
        int weight = 0;
        if (i < 4){
            weight = 20;
        }else{
            weight = 50;
        }
        int value = i*5;
        N = N + cant; // N es la cantidad total de objetos para el algoritmo
        weights[i] = weight;
        values[i] = value;
        amounts[i] = cant;
        i++;
    }
    
    
    int* auxval = new int[N];
    int* auxweight = new int[N];
    
    
    i = 0;
    
    int j = 0;
    while(i < cantidad){ //cantidad de tipos de objeto
        int z = 0;
        int w = weights[i];
        int v = values[i];
        while (z < amounts[i]) {
            auxweight[j] = w;
            auxval[j] = v;
            z++;
            j++;
        }
        i++;
    }
    
    
    delete[](values);
    delete[](weights);

    values = auxval;
    weights = auxweight;
    
    
    objectsWeights = weights;
    objectsValues = values;
    knapSacksCapacities = knapSacks;
    printf("cantidad de objetos: %d\n",x);
    /*Para correr medicion de test descomentar el start y end del final y
     comentar los printf para mejor medicion*/
    //auto start = ya();
    initArrOfObjectsUsed();
    
    if (M == 1) {
        int max = simpleKnapSackProblem(0);
        printf("%d\n", max);
    }else if (M == 2) {
        objects2dMatrices = new int**[N];
        bidimentionalKnapSackProblem(); //imprime el maximo
    }else {
        objects3dMatrices = new int***[N];
        tridimentionalKnapSackProblem();//imprime el maximo 
    }

    
    //Contar clases
    
    int claseM1[N];
    int claseM2[N];
    int claseM3[N];
    int cantM1 = 0;
    int cantM2 = 0;
    int cantM3= 0;
    int claseActual = 0; // clases de 1 a N
    int pesoActual = 0;
    int valorActual = 0;

    for(int j = 0; j < cantidad; j++){
        claseM1[j] = 0;
        claseM2[j] = 0;
        claseM3[j] = 0;
    }
    
    for(int i = 0; i < N; i++){
        if(objectsValues[i] != valorActual || objectsWeights[i] != pesoActual){
            //la primera vez entra si o si
            claseActual++;
            valorActual = objectsValues[i];
            pesoActual = objectsWeights[i];
        }

        switch(objectsUsed[i]){
            case 1:
                claseM1[cantM1] = claseActual;
                cantM1++;
                break;
            case 2:
                claseM2[cantM2] = claseActual;
                cantM2++;
                break;
            case 3:
                claseM3[cantM3] = claseActual;
                cantM3++;
                break;
            default:
                //este objeto no se uso en ninguna mochila
                break;
        }
    }
    
    //Imprimir resultado
    printf("%d ", cantM1);  
    for(int k = 0; k < cantM1; k++){
        printf("%d ", claseM1[k]);
    }
    printf("\n");
    
    if(M>=2){
        printf("%d ", cantM2);  
        for(int k = 0; k < cantM2; k++){
            printf("%d ", claseM2[k]);
        }
        printf("\n");
    }
    
    if(M==3){
        printf("%d ", cantM3);  
        for(int k = 0; k < cantM3; k++){
            printf("%d ", claseM3[k]);
        }
        printf("\n");
    }
    
    //Limpiar memoria

    delete[](values);
    delete[](weights);
    delete[](amounts);
    delete[](objectsUsed);
    if( objects2dMatrices != NULL ) delete2d();
    if( objects3dMatrices != NULL ) delete3d();
/*auto end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
            printf("\n");*/
    x = x +5;
}
    return 0;
}
