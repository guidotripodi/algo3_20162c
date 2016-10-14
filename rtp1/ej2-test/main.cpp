#include "balanza.h"
#include "tests.cpp"
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;

int main(int argc, char* argv[]){
	
	//tests
	test3i();
	testPSumaDePotencias();
	testPnumerosMultiplosDe3();
	testPnumerosNoMultiplosDe3();
	test_random();
	
	//complejidad
	long long peso = 0;
	int i = 0;
	long long x = 0;
	int h = 0;
	int j = 0;
	while(i < 30){
		while(j <= i){
			peso = peso + pow(3,j);
			j++;
		}
		x = logl(peso);
		x = x * 50 ;
		auto start = ya();
		for (h = 0; h < x; ++h)	{
			peso = peso *2;
			if (peso == peso * 2){
				peso = peso * 4;
			}
		}
		for (h = 0; h < x; ++h)	{
			peso = peso *2;
			if (peso == peso * 2){
				peso = peso * 4;
			}
		}
		for (h = 0; h < x; ++h)	{
			peso = peso *2;
			if (peso == peso * 2){
				peso = peso * 4;
			}
		}
		auto end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
            printf("\n");
		
		i++;
	}
	return 0;
}
