//includes necesarios
#include <iostream>
#include <vector>
// Forma 1: vectores
	std::vector<int> knapSacks;
   	std::vector<int> values;
   	std::vector<int> weights;
	
	int i = 0;
	int aux;
	std::cin >> M;
	std::cin >> N;
	
	while(i < M){
		std::cin >> aux;
		knapSacks.push_back(aux);
		i++;
	}
	i = 0;
	while(i < N){ //N es cantidad de tipos de objeto
		int cant;
		int weight;
		int value;
		std::cin >> cant;
		std::cin >> weight;
		std::cin >> value;
		for(int j = 0; j < cant; j++){
			weights.push_back(weight);
			values.push_back(value);
		}
		i++;
	}



// Forma 2: arreglos
    
	int i = 0;

	std::cin >> M;

	
    int knapSacks[M];
	
	while(i < M){
		std::cin >> knapSacks[i];
		i++;
	}
	std::cin >> N;
	int cantidad; //o sea la posta
	i = 0;

    int* values = new int[N];
    int* weights = new int[N];
	int* amounts = new int[N];

	while(i < N){ //N es cantidad de tipos de objeto
		int cant;
		int weight;
		int value;
		std::cin >> cant;
		std::cin >> weight;
		std::cin >> value;
		cantidad = cantidad + cant;
		weights[i] = weight;
		values[i] = value;
		amounts[i] = cant;
		i++;
	}
	
	int* auxval = new int[cantidad];
	int* auxweight = new int[cantidad];



	i = 0;
	while(i < N){ //N es cantidad de tipos de objeto
		
		for(int j = 0; j < amounts[i]; j++){
			auxweight[i + j] = weights[i];
			auxval[i + j] = values[i];
		}
		i++;
	}

	delete[](values);
	delete[](weights);

	values = auxval;
	weights = auxweight;
//hacer delete[] de values y weights al final tambien
	
