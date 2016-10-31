from pylab import *

 # Como utilizar
 #Para armar una instancia hay que determinar:
 #			- Un metodo que posicione los elementos : Seccion GENERADORES DE POSICIONES
 #			- Un metodo que asigne de determinada forma las pociones a los gimnasios: Seccion GENERADORES DE POCIONES
 #			- Un metodo que genere lainstancia con lo anterior: Seccion INSTANCIAS
 #			
 # Ploteo
 # Para cisualizar lainstancia se debe pasar a la funcion de ploeteo el nombre de la funcion generadora de instancias (verejemplo)


###############################################
#			GENERADORES DE POSICIONES
def randomPositions(n, notin=[]):
	li = []
	x = 1
	while len(li)<n:	
		t = 2*pi*rand()
		r = sqrt(randint(0,1000))
		v =(int(r*cos(t)), int(r*sin(t)))

		if v in notin or v in li:
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
			v = (int(r*cos(t)), int(r*sin(t)))
			
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
def plotInstance(i):

	for ((x, y), p) in i[0]:
	    plot(x, y, 'ro')
	
	for (x, y) in i[1]:
	    plot(x, y, 'bo')
	
	show()

def saveInstance(instance, file, mode="w"):
	g = instance[0]
	p = instance[1]
	m = instance[2]

	target = open(file, mode)

	target.write(str(len(g))+" "+str(len(p))+" "+str(m)+"\n")

	for gym in g:
		target.write(str(gym[0][0])+" "+str(gym[0][1])+" "+str(gym[1])+"\n")
	for pp in p:
		target.write(str(pp[0])+" "+str(pp[1])+"\n")
	
	target.close()







###############################################
#				INSTANCIAS

 #Random: Determinado N
 #		  Posiciones random
 #		  Pociones random pero con solucion
 #		  #gyms y #pp random
 #		  mochila K=10
def randomInstance(n):
	cg = randint(1,n-1)
	mochila = 10
	gyms = randomPositions(n-cg)
	pps = randomPositions(n-len(gyms), gyms)
	gymsD = randomPotions(gyms, pps, mochila)

	return gymsD, pps, mochila

 #Disposicio circular: Determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  #gyms y #pp random
 #		  mochila K=10
def circularInstance(cant_gyms, cant_pp):
	mochila = 10
	gyms = circularPositions([1, 2], cant_gyms)
	pps = circularPositions([0.5, 1.5], cant_pp)
	gymsD = randomPotions(gyms, pps, mochila)

	return gymsD, pps, mochila


 #Mochila de capacidad 0: determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  mochila K=0
def noBagInstance(cant_gyms, cant_pp):
	gyms = circularPositions([1, 2], cant_gyms)
	pps = circularPositions([0.5, 1.5], cant_pp)
	gymsD = randomPotions(gyms, pps, 0)

	return gymsD, pps, 0 

 #Todos gimnasios: Determinado N (se parametriza cuanto de uno y de otro)
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  #pp = 0
 #		  mochila K=10
def noPPInstance(n):
	gyms = randomPositions(n)
	gymsD = randomPotions(gyms, pps, 10)
	return gymsD, [], 10



###############################################
#				MAIN

plotInstance(circularInstance(10, 10))

#for i in xrange(3,1000):
#	r = randomInstance(i)
#	#plotInstance(r)
#	saveInstance(r, "test1.in","a")
#	pass