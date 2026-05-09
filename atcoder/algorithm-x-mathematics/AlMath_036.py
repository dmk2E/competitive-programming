'''アルゴリズムと工夫点( : (Colon)/CPU: 59 ms Memory: 77156 KB  Length: 1268 B)
高校数学Ⅱの三角関数の知識を用いる．
半径r,中心(0,0)の円周上の点(x,y)は，動径の角度θとして，(x,y)=(r*cosθ,r*sinθ)と表せる．
これを利用して，時針と分針それぞれの0時からの角度を求めれば，それぞれの先の点の座標が求まるため，距離を計算できる．
'''
import math

MAX_H=12
MAX_M=60

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

def polar(a:float,r:float)->Point:
    return Point(r*math.cos(a),r*math.sin(a))

a,b,h,m=map(int,input().split())
print("{:.10f}".format(getDistance(polar(2.0*math.pi*(h+m/MAX_M)/MAX_H,a),polar(2.0*math.pi*m/MAX_M,b))))