


void mismasMochilas(){
int j,x,h,i;
    int cant_mochilas = 3;
    int cant_objetos = 0;
    int * objetos[100*3];
    int * capacidad_mochilas[cant_mochilas];
    i = 0;
    while(i < cant_mochilas){
        capacidad_mochilas[i] = 10;
        x = 0;
        cant_objetos = 0;
        while(cant_objetos < 100){
            cant_objetos++;
            while(x < cant_objetos){
                objetos[x] = cantidad_libre/3; //cantidad  
                cantidad_libre = cantidad_libre - objetos[x];
                objetos[x+1] = x; //peso  
                objetos[x+2] = x; //valor
                x = x + cantidad_libre;
            }
                printf("Cantidad de mochilas: %d cantidad de Objetos: %d\n",cant_mochilas, cant_objetos);
                algoritmoResolucion(cant_objetos, cant_mochilas, capacidad_mochilas, objetos);
        }
    i++;
    }
}

void mismosObjetos(){
int j,x,h,i;
    int cant_mochilas = 3;
    int cant_objetos;
    int * capacidad_mochilas[cant_mochilas];
    int * objetos[100*3];
    i = 0;
    while(i < cant_mochilas){
        capacidad_mochilas[i] = i*10;
        x = 0;
        cant_objetos = 0;
        while(cant_objetos < 100){
            while(x < cant_objetos){
                objetos[x] = cant_objetos; //cantidad  
                cantidad_libre = cantidad_libre - objetos[x];
                objetos[x+1] = x; //peso  
                objetos[x+2] = x; //valor
                x = x + cantidad_libre;
            }
                printf("Cantidad de mochilas: %d cantidad de Objetos: %d\n",cant_mochilas, cant_objetos);
                algoritmoResolucion(cant_objetos, cant_mochilas, capacidad_mochilas, objetos);
            cant_objetos++;
        }
    i++;
    }
}

void todosObjetoCon1(){
int j,x,h,i;
    int cant_mochilas = 3;
    int cant_objetos = 0;
    int * objetos[100*3];
    int * capacidad_mochilas[cant_mochilas];
    i = 0;
    while(i < cant_mochilas){
        capacidad_mochilas[i] = i*10;
        x = 0;
        cant_objetos = 0;
        while(cant_objetos < 100){
            cant_objetos++;
            while(x < cant_objetos){
                objetos[x] = cantidad_libre/3; //cantidad  
                cantidad_libre = cantidad_libre - objetos[x];
                objetos[x+1] = 1; //peso  
                objetos[x+2] = x; //valor
                x = x + cantidad_libre;
            }
                printf("Cantidad de mochilas: %d cantidad de Objetos: %d\n",cant_mochilas, cant_objetos);
                algoritmoResolucion(cant_objetos, cant_mochilas, capacidad_mochilas, objetos);
        }
    i++;
    }
}

void MochilasDistintasPesosObjetosIguales(){
int j,x,h,i;
    int cant_mochilas = 3;
    int cant_objetos = 0;
    int * objetos[100*3];
    int * capacidad_mochilas[cant_mochilas];
    i = 0;
    while(i < cant_mochilas){
        capacidad_mochilas[i] = 10+i;
        x = 0;
        cant_objetos = 0;
        while(cant_objetos < 100){
            cant_objetos++;
            while(x < cant_objetos){
                objetos[x] = cantidad_libre/3; //cantidad  
                cantidad_libre = cantidad_libre - objetos[x];
                objetos[x+1] = 3; //peso  
                objetos[x+2] = x; //valor
                x = x + cantidad_libre;
            }
                printf("Cantidad de mochilas: %d cantidad de Objetos: %d\n",cant_mochilas, cant_objetos);
                algoritmoResolucion(cant_objetos, cant_mochilas, capacidad_mochilas, objetos);
        }
    i++;
    }
}


void MochilasDistintasPesosObjetosDistintos(){
int j,x,h,i;
    int cant_mochilas = 3;
    int cant_objetos = 0;
    int * objetos[100*3];
    int * capacidad_mochilas[cant_mochilas];
    i = 0;
    while(i < cant_mochilas){
        capacidad_mochilas[i] = 10+i;
        x = 0;
        cant_objetos = 0;
        while(cant_objetos < 100){
            cant_objetos++;
            while(x < cant_objetos){
                objetos[x] = cantidad_libre/3; //cantidad  
                cantidad_libre = cantidad_libre - objetos[x];
                objetos[x+1] = x; //peso  
                objetos[x+2] = x*x; //valor
                x = x + cantidad_libre;
            }
                printf("Cantidad de mochilas: %d cantidad de Objetos: %d\n",cant_mochilas, cant_objetos);
                algoritmoResolucion(cant_objetos, cant_mochilas, capacidad_mochilas, objetos);
        }
    i++;
    }
}


/*PARA TIEMPO*/

/*----------------------FUNCION PARA COMPLEJIDAD -----------------*/

void complejidad(){
    int j,x,h,i;
    int cant_mochilas = 3;
    int cant_objetos;
    int * objetos[cant_objetos*3];
    i = 0;
    while(i < cant_objetos){
        x= 0;
         while(x < cant_mochilas){
            j = 0;
            while(j < cant_mochilas){
                h = 0;
                while(h < cant_mochilas){
                    h++;
                }   
                j++;
            }   
            x++;
        }
    i++;
    }
}
