'''アルゴリズムと工夫点(033 - Distance/CPU: 58 ms Memory: 76892 KB  Length: 1782 B)
計算幾何学の知識を用いれば，交点の座標を求めればよいから，O(1)で計算可能．
※幾何学ライブラリを用意しておくと良い
---別解---
「交点を求める」という処理でなくても，線分BC上の点(x,((cy-by)/(cx-bx))*(x-bx)+by) と点Aとの距離Lとすると，L^2は下に突つの二次関数で表される．
そのため，min(bx,cx)<=x<=max(bx,cx)の範囲で，「xの値を決め打った時のL^2の傾きの符号が正か」という条件に対する単調性を利用すると，二分探索ができる．
※探索範囲が実数となる場合，二分探索の探索終了条件は，「一定の探索回数を終えたか」でないと浮動小数点の精度の問題で終わらない可能性があることに注意．
※関数の頂点を二分探索or三分探索で求めることはあるので，覚えておこう．
※t=((cy-by)/(cx-bx)) として，L^2=(x-ax)^2 + (t*x-ay)^2 となるから，xで微分して，{L^2}'=2*(x-ax)+2*t*(t*x-ay) が傾きとなる．
'''
import math

EPS=1e-12
class Point:
    #コンストラクタ
    def __init__(self,x=0.0,y=0.0):
        self.x=x
        self.y=y
    #算術演算子オーバーロード
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
    #比較演算子オーバーロード
    def __eq__(self,other):
        return abs(self.x-other.x)<EPS and abs(self.y-other.y)<EPS
    def __lt__(self,other):
        return self.y<other.y if self.x==other.x else self.x<other.x
    #メソッド定義
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

def projection(s:Segment,p:Point)->Point:
    base=s.p1-s.p0
    t=dot(p-s.p0,base)/base.norm()
    return s.p0+base*t

def getDistance(a:Point,b:Point):
    return (b-a).abs()

def getDistanceLP(l:Segment,p:Point):
    return abs(cross(l.p1-l.p0,p-l.p0))/(l.p1-l.p0).abs()

def getDistanceSP(s:Segment,p:Point):
    if dot(s.p1-s.p0,p-s.p0)<-EPS:
        return getDistance(s.p0,p)
    elif dot(s.p0-s.p1,p-s.p1)<-EPS:
        return getDistance(s.p1,p)
    return getDistanceLP(s,p)

ax,ay=map(int,input().split())
bx,by=map(int,input().split())
cx,cy=map(int,input().split())

print("{:.7f}".format(getDistanceSP(Segment(Point(bx,by),Point(cx,cy)),Point(ax,ay))))

#二分探索Ver (CPU: 67 ms Memory: 76840 KB  Length: 639 B)
#最大探索範囲 2*10^9 に対して，10^(-6) 以下の精度が求められており，4回繰り返せば(2^4=16より)1桁値が決まるから，4*(9-(-6))=60 回程度の探索回数で良い．
# import math
# ax,ay=map(int,input().split())
# bx,by=map(int,input().split())
# cx,cy=map(int,input().split())
# if by==cy or bx==cx:
#     print("{:.7f}".format(math.sqrt(min((by-ay)*(by-ay),(cy-ay)*(cy-ay))+min((bx-ax)*(bx-ax),(cx-ax)*(cx-ax)))))
# else :
#     cnt=60
#     left=min(bx,cx)
#     right=max(bx,cx)
#     while cnt:
#         mid=(left+right)/2
#         x,y=mid,((cy-by)/(cx-bx))*(mid-bx)+by
#         if 2*(x-ax)+2*((cy-by)/(cx-bx))*(y-ay)<0:
#             left=mid
#         else:
#             right=mid
#         cnt-=1
#     x,y=left,((cy-by)/(cx-bx))*(left-bx)+by
#     print("{:.7f}".format(math.sqrt((x-ax)*(x-ax)+(y-ay)*(y-ay))))

#三分探索Ver (CPU: 58 ms Memory: 76800 KB  Length: 648 B)
# import math
# ax,ay=map(int,input().split())
# bx,by=map(int,input().split())
# cx,cy=map(int,input().split())
# if bx==cx:
#     print("{:.7f}".format(math.sqrt(min((by-ay)*(by-ay),(cy-ay)*(cy-ay))+min((bx-ax)*(bx-ax),(cx-ax)*(cx-ax)))))
# else :
#     def L2(x)->float:
#         global ax,ay,bx,by,cx,cy
#         return (x-ax)**2+(((by-cy)/(bx-cx))*(x-bx)+by-ay)**2
#     cnt=6*15
#     left,right=min(bx,cx),max(bx,cx)
#     while cnt:
#         lMid=(2*left+right)/3
#         rMid=(left+2*right)/3
#         if L2(lMid)>L2(rMid):
#             left=lMid
#         else:
#             right=rMid
#         cnt-=1
#     print("{:.7f}".format(math.sqrt(L2(left))))