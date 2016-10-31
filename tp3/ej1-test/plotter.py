import sys
from pylab import *

lines = [line.rstrip('\n') for line in open(sys.argv[1])]
h = []
points = []
g = 0
p = 0
for line in lines:
	if len(h)==0:
		h = line.split(" ",3) 
	else:
		if p==int(h[1]):
			line = line.split(" ", g + p)
			p_v = None
			for c in line:
				c = int(c) -1
				if p_v!=None:
					#arrow(p_v[0],p_v[1], points[c][0]-p_v[0],points[c][1]-p_v[1], head_length=0.1, head_width=0.1,length_includes_head=True)
					annotate("", xy=p_v, xytext=points[c],    arrowprops=dict(arrowstyle="->"))
				p_v= points[c]

			break
			
		if g==int(h[0]):
			p = p+1
			line = line.split(" ", 2)
			plot(int(line[0]), int(line[1]), "co", markersize=20)
			points.append((int(line[0]), int(line[1])))
		else:
			g = g + 1
			line = line.split(" ", 3)
			plot(int(line[0]), int(line[1]), "ro",  markersize=20)
			annotate(line[2], xy = (line[0], line[1]), xytext = (3.5, -6), textcoords = 'offset points', ha = 'right', va = 'bottom')
			points.append((int(line[0]), int(line[1])))

show()
			

