import sys
from pylab import *

def printWay(way, w):
	p_v = None
	r = []
	for c in way:
		if c=="":
			break
		c = int(c) -1
		if p_v!=None:
			#arrow(p_v[0],p_v[1], points[c][0]-p_v[0],points[c][1]-p_v[1], head_length=0.1, head_width=0.1,length_includes_head=True)
			if w!=0:
				annotate("", xy=points[c], xytext=p_v, arrowprops=dict(linewidth = 2,arrowstyle="-|>", ls=ls[w]))
			else:
				r.append((points[c],p_v))
				annotate("", xy=points[c], xytext=p_v, arrowprops=dict(linewidth = 1,arrowstyle="-|>", ls=ls[w]))
				
		p_v = points[c]

def printPP(line):
	line = line.split(" ", 2)
	plot(int(line[0]), int(line[1]), "co", markersize=20)
	points.append((int(line[0]), int(line[1])))

def printGym(line):
	line = line.split(" ", 3)
	plot(int(line[0]), int(line[1]), "ro",  markersize=20)
	annotate(line[2], xy = (line[0], line[1]), xytext = (3.5, -6), textcoords = 'offset points', ha = 'right', va = 'bottom')
	points.append((int(line[0]), int(line[1])))

def printFirstNLast(ways):
	for way in ways:
		last = points[int(way[len(way)-1])-1]
		is_gym_last = int(way[len(way)-1])<=g
		
		first = points[int(way[0])-1]
		is_gym_first = int(way[0])<=g
		
		#truco para hacerle el borde de otro color (circulo sobre circulo)
		plot(last[0], last[1], "yo", markersize=25)
		plot(first[0], first[1], "go", markersize=25)
		
		if is_gym_first:
			plot(first[0], first[1], "ro", markersize=20)
		else:
			plot(first[0], first[1], "co", markersize=20)
		
		if is_gym_last:
			plot(last[0], last[1], "ro", markersize=20)
		else:
			plot(last[0], last[1], "co", markersize=20)
	


lines = [line.rstrip('\n') for line in open(sys.argv[1])]
h = []
points = []
way=[]
g = 0
p = 0
ls= ['solid' , 'dashed', 'dashdot', 'dotted']
w = 0;

for line in lines:
	if len(h)==0:
		h = line.split(" ",3) 
	else:
		if p==int(h[1]):
			sway = line.split(" ", g + p)
			if sway[0]=="#":
				w=w+1
				continue
			printWay(sway, w)
			way.append(sway)
			w=w+1	
		elif g==int(h[0]):
			p = p+1
			printPP(line)
		else:
			g = g + 1
			printGym(line)

#logica para pintar ultimo y primero

printFirstNLast(way)
show()
			

