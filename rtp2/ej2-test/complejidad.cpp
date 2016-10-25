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
    int F,C;
for (int l = 5; l < 50; ++l){
                 
        F = l;
        C = l+4;
        int lob = log(F*C*25);
    auto start = ya();
     for (int i = 0; i < F*C*25; ++i) {
        for (int j = 0; j < lob; ++j)
        {
            valido++;
            valido = valido *5;
        }
        if (valido % 5 == 0) {
            valido =1;
        }else{
            valido++;
        }
     }
    auto end = ya();
    cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
    printf("\n");
}



    
    
        return 0;
}
                
