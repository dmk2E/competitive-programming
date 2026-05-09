'''アルゴリズムと工夫点(Intersection/CPU: 58 ms Memory: 76724 KB  Length: 1881 B)
3点の位置関係を判定する関数ccwを応用して，交差判定を行う．
※先にSegment型を確保してから，map使って直接アンパックすると，アドレスの関係か上手くいかない
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

class Segment:
    def __init__(self,a:Point=Point(),b:Point=Point()):
        self.p0=a
        self.p1=b

def dot(a:Point,b:Point)->float:
    return a.x*b.x+a.y*b.y
def cross(a:Point,b:Point)->float:
    return a.x*b.y-a.y*b.x

COUNTER_CLOCKWISE=-1
CLOCKWISE=1
ONLINE_BACK=-2
ONLINE_FRONT=2
ON_SEGMENT=0

def ccw(p0:Point,p1:Point,p2:Point)->int:
    a=p1-p0
    b=p2-p0
    if cross(a,b)>EPS:
        return COUNTER_CLOCKWISE
    if cross(a,b)<-EPS:
        return CLOCKWISE
    if dot(a,b)<-EPS:
        return ONLINE_BACK
    return ONLINE_FRONT if a.norm()<b.norm() else ON_SEGMENT

def intersect(s0:Segment,s1:Segment)->bool:
    return ccw(s0.p0,s0.p1,s1.p0)*ccw(s0.p0,s0.p1,s1.p1)<=0 and ccw(s1.p0,s1.p1,s0.p0)*ccw(s1.p0,s1.p1,s0.p1)<=0

x1,y1=map(int,input().split())
x2,y2=map(int,input().split())
s0=Segment(Point(x1,y1),Point(x2,y2))
x1,y1=map(int,input().split())
x2,y2=map(int,input().split())
s1=Segment(Point(x1,y1),Point(x2,y2))
print("Yes" if intersect(s0,s1) else "No")