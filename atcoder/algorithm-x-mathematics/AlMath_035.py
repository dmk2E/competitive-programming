'''アルゴリズムと工夫点(Two Circles/CPU: 61 ms Memory: 76808 KB  Length: 1446 B)
高校数学Ⅱの知識で解ける．
2円の位置関係は，円の中心と半径に着目すればよい．
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

class Circle:
    def __init__(self,c:Point=Point(),r:float=0.0):
        self.c=c
        self.r=r

def getDistance(a:Point,b:Point):
    return (b-a).abs()

x,y,r=map(int,input().split())
c1=Circle(Point(x,y),r)
x,y,r=map(int,input().split())
c2=Circle(Point(x,y),r)

if c1.r+c2.r<getDistance(c1.c,c2.c):
    print(5)
elif abs(c1.r+c2.r-getDistance(c1.c,c2.c))<EPS:
    print(4)
elif abs(c1.r-c2.r)-getDistance(c1.c,c2.c)<-EPS and getDistance(c1.c,c2.c)-c1.r-c2.r<-EPS:
    print(3)
elif abs(getDistance(c1.c,c2.c)-abs(c1.r-c2.r))<EPS:
    print(2)
else:
    print(1)