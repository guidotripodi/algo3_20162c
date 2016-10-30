from pylab import *

 # Como utilizar
 #Para armar una instancia hay que determinar:
 #			- Un método que posicione los elementos : Seccion GENERADORES DE POSICIONES
 #			- Un metodo que asigne de determinada forma las pociones a los gimnasios: Seccion GENERADORES DE POCIONES
 #			- Un metodo que genere lainstancia con lo anterior: Seccion INSTANCIAS
 #			
 # Ploteo
 # Para cisualizar lainstancia se debe pasar a la funcion de ploeteo el nombre de la funcion generadora de instancias (verejemplo)


###############################################
#			GENERADORES DE POSICIONES
def randomPositions(n, notin=[]):
	li = []
	for x in xrange(1,n):	
		t = 2*pi*random()
		r = sqrt(random())
		v =(r*cos(t), r*sin(t))
		if v in notin or v in li:
			x = x - 1
			continue

		li.append(v)
	return li	

def circularPositions(rad_circ, n):
	obj_x_circ = n/len(rad_circ)
	li = []
	for r_i in range(0,len(rad_circ)):
		r = rad_circ[r_i]	
		for y in xrange(0,obj_x_circ):
			t = 2*pi/obj_x_circ * y
			v = (r*cos(t), r*sin(t))
			
			li.append(v)
	
	return li	


###############################################
#			GENERADORES DE POCIONES

#En base a la cantidadde cada tipo de lugar y la capacidad de mochila
#asigna pociones de forma que hayasolucion (osea que no muera en las podas basicas)
def randomPotions(gyms, pps, k_bag):
	gym_res = []
	pociones_totales = 3*len(pps)
	
	for gym in gyms:
		pociones = randint(0, min(k_bag, pociones_totales))
		gym_res.append((gym, pociones))
		pociones_totales = pociones_totales - pociones
	return gym_res


###############################################
#				UTILITARIOS
def plotInstance(instance):
	i = instance()
	for ((x, y), p) in i[0]:
	    plot(x, y, 'ro')
	
	for (x, y) in i[1]:
	    plot(x, y, 'bo')
	
	show()


###############################################
#				INSTANCIAS

 #Random: Determinado N
 #		  Posiciones random
 #		  Pociones random pero con solucion
 #		  #gyms y #pp random
 #		  mochila K=10
def randomInstance(n):
	cg = randint(0,n)
	gyms = randomPositions(n-cg)
	pps = randomPositions(n/2, gyms)
	gymsD = randomPotions(gyms, pps, 10)

	return gymsD, pps

 #Disposicio circular: Determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  #gyms y #pp random
 #		  mochila K=10
def circularInstance(cant_gyms, cant_pp):
	gyms = circularPositions([1, 2], cant_gyms)
	pps = circularPositions([0.5, 1.5], cant_pp)
	gymsD = randomPotions(gyms, pps, 10)

	return gymsD, pps


 #Mochila de capacidad 0: determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  mochila K=0
def noBagInstance(cant_gyms, cant_pp)
	gyms = circularPositions([1, 2], cant_gyms)
	pps = circularPositions([0.5, 1.5], cant_pp)
	gymsD = randomPotions(gyms, pps, 0)

	return gymsD, pps 

 #Todos gimnasios: Determinado N (se parametriza cuanto de uno y de otro)
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  #pp = 0
 #		  mochila K=10
def noPPInstance(n):
	gyms = randomPositions(n)
	gymsD = randomPotions(gyms, pps, 10)



###############################################
#				MAIN



plotInstance(randomInstance)
plotInstance(circularInstance)
