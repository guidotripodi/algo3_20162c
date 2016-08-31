#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int M = 0;
int N = 0;
int *objectsWeights = NULL;
int *objectsValues = NULL;
int *knapSacksCapacities = NULL;

struct KnapSackMaxForObject {
    int M3;
    int M2;
    int M1;
    
    KnapSackMaxForObject() : M3(0),M2(0),M1(0){}
    
    //pre: M3 >= M2 >= M1
    //pre: M == 3 or M == 2
    void create(int objectValue, int objectWeight)
    {
        int kM3 = 0;
        int kM2 = 0;
        int kM1 = 0;
        
        kM2 = knapSacksCapacities[1];
        kM1 = knapSacksCapacities[0];
        
        if(M == 3){
            kM3 = knapSacksCapacities[2];
            if(kM3 >= objectWeight){
                M3 = objectValue;
            }
        }
        
        if(kM2 >= objectWeight){
            M2 = objectValue;
            if(kM1 >= objectWeight){
                M1 = objectValue;
            }
        }
    }
};

KnapSackMaxForObject **objectsCalculation = NULL;


int max(int a, int b){
    return (a > b) ? a : b;
}

void maxProfitForAnObjectInAKnapSack(int objectUsed, int **objectsInfo){
    int i, w;
    
    int maxCapacity = knapSacksCapacities[M-1];
    
    int K[N][maxCapacity + 1]; // la mochila con peso 0 es para finalizar
    
    printf("calculating profit if i put object (%d, %d) for each knapsack: \n", objectsValues[objectUsed], objectsWeights[objectUsed]);
    for (i = 0; i < N; i++) {
        for (w = 0; w <= maxCapacity; w++) {
            if (w == 0){
                K[i][w] = 0;
            }else if (objectsWeights[i] <= w && i != objectUsed){
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
            printf("%d |", K[i][w]);
        }
        printf("\n");
    }
    printf("\n");
    
    // no se cuantas mochilas hay
    int maxM1Profit = -1;
    int maxM2Profit = -1;
    int maxM3Profit = -1;
    
    //la mochila en donde meti el objeto usado (j) tiene menos capacidad: capacidad(mochila usada)-peso(objeto usado)
    for (int knapSackUsed = 0; knapSackUsed < M; knapSackUsed++) {
        int actualKnapSackCapacity = knapSacksCapacities[knapSackUsed]-objectsWeights[objectUsed];
    
        // si pasa esto el objeto no entra en la mochila porque es mas pesado
        if (actualKnapSackCapacity < 0) {
            if (knapSackUsed == 0) {
                maxM1Profit = 0;
            }else if (knapSackUsed == 1) {
                maxM2Profit = 0;
            }else {
                maxM3Profit = 0;
            }
        }else {
            if (knapSackUsed == 0) {
                maxM1Profit = K[N-1][actualKnapSackCapacity];
            }else if (knapSackUsed == 1) {
                maxM2Profit = K[N-1][actualKnapSackCapacity];
            }else {
                maxM3Profit = K[N-1][actualKnapSackCapacity];
            }
            
            for (int z = 0; z < M; z++) {
                if (z != knapSackUsed) {
                    if (knapSackUsed == 0) {
                        maxM1Profit += K[N-1][knapSacksCapacities[z]];
                    }else if (knapSackUsed == 1) {
                        maxM2Profit += K[N-1][knapSacksCapacities[z]];
                    }else {
                        maxM3Profit += K[N-1][knapSacksCapacities[z]];
                    }
                }
            }
        }
    }
    
    int maxKnapSack = maxM1Profit;
    
    if (maxM2Profit >= maxM1Profit && maxM2Profit >= maxM3Profit) {
        maxKnapSack = maxM2Profit;
    }
    
    if (maxM3Profit >= maxM1Profit && maxM3Profit >= maxM2Profit) {
        maxKnapSack = maxM3Profit;
    }
    
    // si hay dos maximos quiere decir que ese objeto no influye, por lo tanto no conviene meterlo en esas mochilas.
    // esto parece que se genera cuando un objeto entra justo en una mochila dejando 0 capacidad a esa mochila y las otras dos maximizan igual.
    // tengo un caso en donde hay dos objetos que entran justo, utilizo la regla anterior pero luego, como es de esperar uno de los objetos sobra y se lo podria haber llevado otra mochila.
    
    if (maxM1Profit == maxKnapSack || maxM2Profit == maxM3Profit) {
        objectsInfo[objectUsed][0] = 0;
        objectsInfo[objectUsed][1] = -1;
        objectsInfo[objectUsed][2] = -1;
    }else if (maxM2Profit == maxKnapSack || maxM1Profit == maxM3Profit) {
        objectsInfo[objectUsed][0] = -1;
        objectsInfo[objectUsed][1] = 1;
        objectsInfo[objectUsed][2] = -1;
    }else if (maxM3Profit == maxKnapSack || maxM2Profit == maxM1Profit) {
        objectsInfo[objectUsed][0] = -1;
        objectsInfo[objectUsed][1] = -1;
        objectsInfo[objectUsed][2] = 2;
    }
    
    objectsInfo[objectUsed][3] = false; // no usado
    
    printf("knapsacks that maximize object %d, %d, %d \n\n", objectsInfo[objectUsed][0], objectsInfo[objectUsed][1], objectsInfo[objectUsed][2]);
    printf("object (%d,%d) maximums are (%d, %d, %d) \n\n", objectsValues[objectUsed], objectsWeights[objectUsed], maxM1Profit, maxM2Profit, maxM3Profit);
}

int profitForAKnapSack(int **objectsInfo, int knapSack, int knapSackCapacity) {
    int i, w;
    
    int K[N][knapSackCapacity + 1]; // la mochila con peso 0 es para finalizar
    
    // Build table K[][] in bottom up manner
    printf("profit for a knapsack %d: \n", knapSack);
    for (i = 0; i < N; i++) {
        for (w = 0; w <= knapSackCapacity; w++) {
            //printf("\n\n object (%d, %d) for knapsack: %d used: %d \n\n", objectsValues[i], objectsWeights[i], objectsInfo[i][knapSack], objectsInfo[i][3]);
            if (w == 0){
                K[i][w] = 0;
            }else if (objectsWeights[i] <= w && objectsInfo[i][knapSack] == knapSack && objectsInfo[i][3] == false){
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
    printf("objects used in knapsack %d of capacity %d { \n\n", knapSack, knapSackCapacity);
    while (actualRow >= 0 && actualCol >= 0) {
        if (actualCol == 0) {
            actualCol=-1;
        }else if (actualRow == 0) {
            if (K[actualRow][actualCol]) {
                objectsInfo[actualRow][3] = true; // usado
                printf("used object (%d, %d) \n", objectsValues[actualRow], objectsWeights[actualRow]);
            }
            actualRow=-1;
        }else if (K[actualRow-1][actualCol] != K[actualRow][actualCol]) {
            objectsInfo[actualRow][3] = true; // usado
            printf("used object (%d, %d) \n", objectsValues[actualRow], objectsWeights[actualRow]);
            actualCol = abs(actualCol-objectsWeights[actualRow]); // por si acaso, valor absoluto.
            actualRow--;
        }else{
            actualRow--;
        }
    }
    
    printf("} \n");
    
    return K[N-1][knapSackCapacity];
}

void multipleKnapSackProblem() {
    
    // Asumo para hacer mas simple por ahora que las mochilas vienen ordenadas por peso, lo mismo los objetos de menor a mayor.
    // Y que las clases son resueltas antes de esta llamada. Por lo tanto N es el TOTAL de objetos.
    
    int **objectsInfo = new int*[N];
    for (int i = 0; i < N; i++)
        objectsInfo[i] = new int[4]; // (maximiza M1, maximiza M2, maximiza M3, usado)
    
    int j = 0;
    while (j < N) {
        maxProfitForAnObjectInAKnapSack(j, objectsInfo);
        
        j++;
    }
    
    int totalValue = 0;
    
    for (int knapSack = 0; knapSack < M; knapSack++) {
        totalValue += profitForAKnapSack(objectsInfo, knapSack, knapSacksCapacities[knapSack]);
    }
    
    printf("\n total value: %d \n", totalValue);
    
    for(int i = 0; i < N; i++)
        delete [] objectsInfo[i];

    delete [] objectsInfo;
}

int calculateMaxForKnapSackWithKof(int kM, int i, KnapSackMaxForObject *maxObjecti){
    int objectValue = objectsValues[i];
    int totalValue = objectValue;
    int objectWeight = objectsWeights[i];
    
    int restWeight = kM - objectWeight;
    //voy a iterar desde el peso que me sobra hasta 1 buscando cuanto es lo maximo que puedo sumar llenando con objetos de pesos desde restWeight hasta 1.
    //cuando restWeight decremente es posible que pueda meter mas de un objeto con ese nuevo peso de sobra.
    for (int z = restWeight; z > 0; z--) {
        int maxProfitForRestWeight = 0;
        
        int untilObjectWeightWereFilled = z;
        int j = 0;
        while (untilObjectWeightWereFilled+objectWeight <= kM){
            int maxValueFoundForRestWeight = 0;
            
            //busco un objeto que maximize el valor para el peso que me sobra
            //notar que puedo buscar varios objetos para ese peso restante porque a medida que voy decrementando restWeight
            //hay posibilidades de meter mas de un objeto de ese peso. Asi que se conserva j para continuar desde j+1 encontrado
            while (j < N) {
                int iteratedWeight = objectsWeights[j];
                int iteratedValue = objectsValues[j];
                //busco el maximo para ese peso restante
                if (j != i && iteratedWeight == z && iteratedValue > maxValueFoundForRestWeight) {
                    maxValueFoundForRestWeight = iteratedValue;
                }
                j++;
            }
            
            if (maxValueFoundForRestWeight) {
                maxProfitForRestWeight+=maxValueFoundForRestWeight;
                //si todavia no lleno la mochila sigo buscando
                untilObjectWeightWereFilled+=restWeight;
            }else {
                //invalido la guarda: finalizo el ciclo porque no encontre ningun valor para ese peso restante
                untilObjectWeightWereFilled = kM;
            }
        }
        
        if (objectValue+maxProfitForRestWeight > totalValue) {
            totalValue = objectValue+maxProfitForRestWeight; //guardo el mejor beneficio para esa mochila calculado con el resto actual
        }
    }
    
    printf("object (%d, %d) maximize with value %d for knapsack %d kg \n\n", objectsValues[i], objectsWeights[i], totalValue, kM);
    
    return totalValue;
}

int markObjectsUsed(int knapsack, int *objectsUsed){
    int maxMObject = -1;
    int maxMValue = 0;
    KnapSackMaxForObject *maxObjecti = NULL;
    // busco el objeto que mas aporta en esa mochila
    for (int i = 0; i < N; i++) {
        maxObjecti = objectsCalculation[i];
        if (knapsack == 2 && maxObjecti->M3 > maxMValue && objectsUsed[i] == false) {
            maxMObject = i;
            maxMValue = maxObjecti->M3;
        }else if (knapsack == 1 && maxObjecti->M2 > maxMValue && objectsUsed[i] == false) {
            maxMObject = i;
            maxMValue = maxObjecti->M2;
        }else if (knapsack == 0 && maxObjecti->M1 > maxMValue && objectsUsed[i] == false) {
            maxMObject = i;
            maxMValue = maxObjecti->M1;
        }
    }
    
    int realMaxValue = 0;
    
    if (maxMObject >= 0) {
        objectsUsed[maxMObject] = knapsack+1;
        
        int weight = objectsWeights[maxMObject];
        realMaxValue = objectsValues[maxMObject];
        // busco los objetos con quien aporta esa cantidad
        int knapsackWeight = knapSacksCapacities[knapsack];
    
        knapsackWeight = knapsackWeight-weight;
        
        for (int i = maxMObject+1; i < N; i++) {
            if (knapsackWeight > 0){
                maxObjecti = objectsCalculation[i];
                if (knapsack == 2 && maxObjecti->M3 == maxMValue && knapsackWeight == objectsWeights[i] && objectsUsed[i] == false) {
                    knapsackWeight -= objectsWeights[i];
                    objectsUsed[i] = knapsack+1;
                    realMaxValue += objectsValues[i];
                }else if (knapsack == 1 && maxObjecti->M2 == maxMValue && knapsackWeight == objectsWeights[i] && objectsUsed[i] == false) {
                    knapsackWeight -= objectsWeights[i];
                    objectsUsed[i] = knapsack+1;
                    realMaxValue += objectsValues[i];
                }else if (knapsack == 0 && maxObjecti->M1 == maxMValue && knapsackWeight == objectsWeights[i] && objectsUsed[i] == false) {
                    knapsackWeight -= objectsWeights[i];
                    objectsUsed[i] = knapsack+1;
                    realMaxValue += objectsValues[i];
                }
            }else{
                break;
            }
        }
    }

    return realMaxValue;
}

void realMultipleKnapSackProblem(){
    
    // Asumo para hacer mas simple por ahora que las mochilas vienen ordenadas por peso, lo mismo los objetos de menor a mayor.
    // Y que las clases son resueltas antes de esta llamada. Por lo tanto N es el TOTAL de objetos.
    
    objectsCalculation = new KnapSackMaxForObject*[N];
    
    for(int i = 0; i < N; i++){
        // la diferencia con new ObjectWithKnapSacksStr; es que con parentisis inicializa atributos.
        KnapSackMaxForObject *maxObjecti = new KnapSackMaxForObject();
        maxObjecti->create(objectsValues[i], objectsWeights[i]);
        objectsCalculation[i] = maxObjecti;
    }
    
    for(int i = 0; i < N; i++){
        KnapSackMaxForObject *maxObjecti = objectsCalculation[i];
        
        int objectWeight = objectsWeights[i];
        
        int kM3 = 0;
        int kM2 = 0;
        int kM1 = 0;
        
        // M == 3 or M == 2
        if (M == 3) {
            kM3 = knapSacksCapacities[2];
        }
        
        kM2 = knapSacksCapacities[1];
        kM1 = knapSacksCapacities[0];
        
        if (kM3 >= objectWeight) {
            maxObjecti->M3 = calculateMaxForKnapSackWithKof(kM3, i, maxObjecti);
        }
        
        if (kM2 >= objectWeight) {
            maxObjecti->M2 = calculateMaxForKnapSackWithKof(kM2, i, maxObjecti);
        }
        
        if (kM1 >= objectWeight) {
            maxObjecti->M1 = calculateMaxForKnapSackWithKof(kM1, i, maxObjecti);
        }
    }
    
    if (M == 3) {
        int *objectsUsedM3First = new int[N]();
        int maxM3First = 0;
        
        maxM3First = markObjectsUsed(2, objectsUsedM3First);
        maxM3First += markObjectsUsed(1, objectsUsedM3First); // tendria que ser lo mismo luego quien mire (?
        maxM3First += markObjectsUsed(0, objectsUsedM3First);
        
        printf("max m3 first %d \n\n", maxM3First);
        
        for (int i = 0; i < N; i++) {
            printf("object %d, %d in %d \n\n", objectsValues[i], objectsWeights[i], objectsUsedM3First[i]);
        }
    }
    
    int *objectsUsedM2First = new int[N]();
    int maxM2First = 0;
    
    maxM2First = markObjectsUsed(1, objectsUsedM2First);
    maxM2First += markObjectsUsed(2, objectsUsedM2First); // tendria que ser lo mismo luego quien mire (?
    maxM2First += markObjectsUsed(0, objectsUsedM2First);
    
    printf("max m2 first %d \n\n", maxM2First);
    
    for (int i = 0; i < N; i++) {
        printf("object %d, %d in %d \n\n", objectsValues[i], objectsWeights[i], objectsUsedM2First[i]);
    }
    
    int *objectsUsedM1First = new int[N]();
    int maxM1First = 0;
    
    maxM1First = markObjectsUsed(0, objectsUsedM1First);
    maxM1First += markObjectsUsed(2, objectsUsedM1First); // tendria que ser lo mismo luego quien mire (?
    maxM1First += markObjectsUsed(1, objectsUsedM1First);
    
    printf("max m2 first %d \n\n", maxM1First);
    
    for (int i = 0; i < N; i++) {
        printf("object %d, %d in %d \n\n", objectsValues[i], objectsWeights[i], objectsUsedM1First[i]);
    }
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
    
    //multipleKnapSackProblem();
    
    realMultipleKnapSackProblem();
    
	return 0;
}
