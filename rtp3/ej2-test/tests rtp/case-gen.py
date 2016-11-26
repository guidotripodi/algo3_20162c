from pylab import *

import random

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

def circularPositions(n, notin=[], rad_circ=10, dist_anillos = 10):
	li = []
	while n>0:

		noSePisaron = True
		y = 0
		while noSePisaron and n>0	:
			t = y
			v = (int(rad_circ*cos(t)), int(rad_circ*sin(t)))

			if v in notin or v in li:
				rad_circ = rad_circ + dist_anillos
				noSePisaron = False
				continue

			li.append(v)
			n = n-1
			y = y+1

	return li

def circularPositions2(n, rad_circ=10):
	li=[]
	incremento = 2*pi / n
	arc=incremento
	for i in range(0, n):
		v = (int(rad_circ*cos(arc)), int(rad_circ*sin(arc)))
		arc = arc + incremento
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

def randomPotions2(gyms, pps):
	gym_res = []
	pociones_totales = 3*len(pps)

	total = 0

	for gym in gyms:
		pociones = randint(0, pociones_totales)
		if total+pociones < pociones_totales:
			gym_res.append((gym, pociones))
			total+= pociones
		else:
			gym_res.append((gym, 0))
			
	return gym_res

def kPotions(gyms, k):
	gym_res = [];
	for gym in gyms:
		pociones = k
		gym_res.append((gym, pociones))
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

	#print(file)

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
def randomInstance(pp = 1, gms = 1):
	gyms = randomPositions(gms)
	pps = randomPositions(pp, gyms)
	gymsD = randomPotions2(gyms, pps)
	
	return gymsD, pps

 #Disposicio circular: Determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  #gyms y #pp random
 #		  mochila K=10
def circularInstance(cant_gyms, cant_pp):
	mochila = 10
	gyms = circularPositions(cant_gyms,rad_circ=20, dist_anillos= 30)
	pps = circularPositions(cant_pp, notin=gyms, rad_circ=50, dist_anillos = 10)
	gymsD = randomPotions(gyms, pps, mochila)

	return gymsD, pps, mochila

def circularInstance2(cant_gyms, cant_pp):
	mochila = cant_gyms*6
	gyms = circularPositions2(cant_gyms,rad_circ=5)
	pps = circularPositions2(cant_pp, rad_circ=10)
	gymsD = kPotions(gyms,3)

	return gymsD, pps, mochila

 #Mochila de capacidad 0: determinado numero de gimnasios y pp
 #		  Posiciones en forma de anillos concentricos de radios 2, 1.5 1 0.5
 #		  Pociones random pero con solucion
 #		  mochila K=0
def noBagInstance(cant_gyms, cant_pp):
	pass

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

random.seed(45)

fileNameWeak = "randomWeak.txt"
fileNameStrong = "randomStrong.txt"

open(fileNameWeak, 'w+').close()
open(fileNameStrong, 'w+').close()

acum = 0

for i in xrange(5, 20):
	lim = i
	tam = i
	
	for j in xrange(1, tam):
		pp = randint(1, tam)
		gms = tam-pp

		while pp*3 < gms:
			pp = randint(1, tam)
			gms = tam-pp
		
		r = randomInstance(pp, gms)

		gymsD = r[0]
		
		powers = [b for a,b in gymsD]
		
		kBag = max(powers) + 3
			
		rOut = (r[0], r[1], kBag)
		saveInstance(rOut,fileNameWeak,"a")
		
		kBag = sum([b for a,b in gymsD])
		
		rOut = (r[0], r[1], kBag)
		saveInstance(rOut,fileNameStrong,"a")

		acum = acum + 1

for i in xrange(20, 500, 50):
	lim = i
	tam = i
	
	lim = lim*(0.10)
	lim = int(lim)
	
	for j in xrange(1, tam):
		pp = randint(1, tam)
		gms = tam-pp

		while pp*3 < gms:
			pp = randint(1, tam)
			gms = tam-pp
		
		r = randomInstance(pp, gms)

		gymsD = r[0]
		
		powers = [b for a,b in gymsD]
		
		kBag = max(powers) + 3
			
		rOut = (r[0], r[1], kBag)
		saveInstance(rOut,fileNameWeak,"a")
				
		kBag = sum([b for a,b in gymsD])
		
		rOut = (r[0], r[1], kBag)
		saveInstance(rOut,fileNameStrong,"a")

		acum = acum + 1

	if i == 120:
		print(acum)
	elif i == 270:
		print(acum)
			 
print(acum)
