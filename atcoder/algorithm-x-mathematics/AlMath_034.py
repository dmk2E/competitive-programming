'''アルゴリズムと工夫点(Nearest Points/CPU: 101 ms Memory: 82836 KB  Length: 1184 B)
N<=2000より，単純に全ての2組について距離を計算し，最小値を出力すればよい．
最悪計算量は O(N^2)
'''
import math

EPS=1e-12
class Point:
    def __init__(self,x=0.0,y=0.0):
        self.x=x
        self.y=y

    def __add__(self,other):
        return Point(self.x+other.x,self.y+other.y)
    def __sub__(self,other):
        return Point(self.x-other.x,self.y-other.y)
    def __mul__(self,other):
        return Point(self.x*other,self.y*other)
    def __truediv__(self,other):
        return Point(self.x/other,self.y/other)
    def __floordiv__(self,other):
        return Point(self.x//other,self.y//other)

    def __eq__(self,other):
        return abs(self.x-other.x)<EPS and abs(self.y-other.y)<EPS
    def __lt__(self,other):
        return self.y<other.y if self.x==other.x else self.x<other.x

    def norm(self):
        return self.x*self.x+self.y*self.y
    def abs(self):
        return math.sqrt(self.norm())

def getDistance(a:Point,b:Point):
    return (b-a).abs()

MAX=1e6

n=int(input())
ps=[]
while n>0:
    x,y=map(int,input().split())
    ps.append(Point(x,y))
    n-=1

mn=MAX**2+1

for i in range(0,len(ps)):
    for j in range(i+1,len(ps)):
        mn=min(mn,getDistance(ps[i],ps[j]))
print("{:.10f}".format(mn))