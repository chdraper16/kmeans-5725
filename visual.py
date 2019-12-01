import matplotlib.pyplot as plt


cx = []
cy = []
c = []
x= []
y = []
n,d,k = input().split(" ")

for a in range(0,int(k)):
	t1, t2 = input().split(" ")
	cx.append(float(t1))
	cy.append(float(t2))
for a in range(0,int(n)):
	t, t1,t2  = input().split(" ")
	c.append(int(t))
	x.append(float(t1))
	y.append(float(t2))

s = int(int(n)/1000)
if s == 0:
	s = 1

for a in range(0,int(n), s):
	if c[a] ==0:
		plt.plot(x[a],y[a],"bo")
	elif c[a] == 1:
		plt.plot(x[a],y[a],"go")
	elif c[a] == 2:
		plt.plot(x[a],y[a],"ro")
	elif c[a] == 3:
		plt.plot(x[a],y[a],"co")
	elif c[a] == 4:
		plt.plot(x[a],y[a],"mo")
	elif c[a] == 5:
		plt.plot(x[a],y[a],"yo")
	elif c[a] == 6:
		plt.plot(x[a],y[a],"cv")
	elif c[a] == 7:
		plt.plot(x[a],y[a],"rv")
	elif c[a] == 8:
		plt.plot(x[a],y[a],"bv")
	elif c[a] == 9:
		plt.plot(x[a],y[a],"gv")
	

for a in range(0,int(k)):
	plt.plot(cx[a],cy[a],"kx")



plt.show()
