from pylab import *

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
	for ((x, y), p) in instance[0]:
	    plot(x, y, 'ro')
	
	for (x, y) in instance[1]:
	    plot(x, y, 'bo')
	
	show()


###############################################
#				INSTANCIAS
def randomInstance(n):
	gyms = randomPositions(n/2)
	pps = randomPositions(n/2, gyms)
	gymsD = randomPotions(gyms, pps, 10)

	return gymsD, pps


def circularInstance(cant_gyms, cant_pp):
	gyms = circularPositions([1, 2], cant_gyms)
	pps = circularPositions([0.5, 1.5], cant_pp)
	gymsD = randomPotions(gyms, pps, 10)

	return gymsD, pps

def noBagInstance(cant_gyms, cant_pp)
	gyms = circularPositions([1, 2], cant_gyms)
	pps = circularPositions([0.5, 1.5], cant_pp)
	gymsD = randomPotions(gyms, pps, 0)

	return gymsD, pps 

def noPPInstance(n):
	gyms = randomPositions(n)
	gymsD = randomPotions(gyms, pps, 10)

###############################################
#				MAIN

plotInstance(randomInstance(1000))
plotInstance(circularInstance(100, 10))
