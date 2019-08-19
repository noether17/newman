from math import sin
from numpy import arange
from pylab import plot, xlabel, ylabel, show

def f(x, t):
    return -x**3 + sin(t)

a = 0.0         #start of the interval
b = 10.0        #end of the interval
N = 1000        #number of steps
h = (b - a) / N #size of a single step
x = 0.0         #initial condition

tpoints = arange(a, b, h)
xpoints = []
for t in tpoints:
    xpoints.append(x)
    x += h * f(x, t)

plot(tpoints, xpoints)
xlabel("t")
ylabel("x(t)")
show()
