#include "stdio.h"
#include "string.h"
#include "vector"
#include "algorithm"
#include <list>
using namespace std;
#define nodos pair<int, int>
#define arista pair<int, nodos>
#define F first
#define S second

struct baldoza{
    int fuerza;
    std::list<int> nodos;
};


vector <arista> grafo;
vector <baldoza> grafo_baldoza;

int n, e;
int T;

void Kruskal_algoritmo()
{
    UF UF(n);
    int u, v;

    for (int i = 0; i < e; ++i)
    {
        //second first (primer nodo u)
        u = grafo[i].S.F; 
        //second second (segundo nodo u)
        v = grafo[i].S.S;
        if( !UF.find(u, v) )
        {
            //uno al total del agm
            UF.unir(u, v);
            //sumo al peso total del agm
            T += grafo[i].F;  
        }
    }
}


int main(int argc, char* argv[])
{

    /*

    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    YA ESTA ECHO KRUSKAL Y UF VER COMO CONVERTIR LOS NUMEROS A VECTOR DE ARISTAS!!
    

    */
    grafo_baldoza.resize(filas*columnas);
    int aristas = 0;
    int u, v, c;
    for (int i = 1; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cin << elemento;
            if ( 49 <= (int)elemento && (int)elemento <= 57) {
                //es numero osea arista
                grafo_baldoza[(i * filas) + j].fuerza = (int)elemento;
                grafo_baldoza[(i * filas) + j].nodos = NULL;
                aristas++;

            }else{
                if ((int)elemento == 46){
                    grafo_baldoza[(i * filas) + j].fuerza = 0;
                    grafo_baldoza[(i * filas) + j].nodos = NULL;    
                    if (i > 1 && i < filas && grafo_baldoza[((i-1) * filas) + j].fuerza == 0){
                        //si no estoy en el borde y el de arriba no es pared lo agregamos como adyacente
                        grafo_baldoza[((i-1) * filas) + j].nodos.push_back((i * filas) + j);  
                        grafo_baldoza[(i * filas) + j].nodos.push_back(((i-1) * filas) + j);    
                    }
                    if (i > 1 && i < filas && grafo_baldoza[((i-1) * filas) + j].fuerza > 0){
                        //si no estoy en el borde y el de arriba no es pared lo agregamos como adyacente
                        grafo_baldoza[((i-2) * filas) + j].nodos.push_back((i * filas) + j);  
                        grafo_baldoza[(i * filas) + j].nodos.push_back(((i-2) * filas) + j);    
                    }
                    if(j > 1 && j < columnas && grafo_baldoza[((i) * filas) + j-1].fuerza == 0){
                        //si no estoy en el borde y el de izquierda no es pared lo agregamos como adyacente
                        grafo_baldoza[(i * filas) + j-1].nodos.push_back((i * filas) + j);  
                        grafo_baldoza[(i * filas) + j].nodos.push_back(((i) * filas) + j-1);    
                    }
                    if(j > 1 && j < columnas && (j > 2 && grafo_baldoza[((i) * filas) + j-1].fuerza > 0)){
                        //si no estoy en el borde y el de izquierda no es pared lo agregamos como adyacente
                        grafo_baldoza[(i * filas) + j-2].nodos.push_back((i * filas) + j);  
                        grafo_baldoza[(i * filas) + j].nodos.push_back(((i) * filas) + j-2);    
                    }

                }else{
                    grafo_baldoza[(i * filas) + j].fuerza = -1;
                    grafo_baldoza[(i * filas) + j].nodos = NULL;
                }
            }
        }
    }
    
    grafo.resize(aristas);

    input(&n);    //transformo los nodos
    input(&e);    //transformo aristas
    

    for (int i = 0; i < e; ++i)
    {
        input(&u);    //enter vertex u
        input(&v);    //enter vertex v
        input(&c);    //enter cost of edge (u,v)
        u--;
        v--;
        grafo[i] = arista( c, nodos(u,v));
    }
    sort(grafo.begin(), grafo.end());   //sort the edges in increasing order of cost

    T = 0;
    Kruskal_algoritmo();
    printf("%lld\n",T);
    return 0;
}