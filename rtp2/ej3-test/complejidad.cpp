#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;


int main() {
    
    int valido = 0;
    int F;
for (int l = 2; l < 50; ++l){
                 
        F = l;
        int lob = log(F);
          auto start = ya();
    for (int z = 0; z < 1; ++z){
        for (int i = 0; i < F*20; ++i) {
            for (int j = 0; j < 0; ++j){
                for (int x = 0; x < 0; ++x){
                    for (int h = 0; h < 0; ++h)
                    {
                        valido++;
                        valido = valido *5;
                        if (valido % 5 == 0) {
                            valido =1;
                        }else{
                            valido++;
                        }
                    }
                }
            }
         }
    }
    auto end = ya();
    cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
    printf("\n");
}



    
    
        return 0;
}
                
