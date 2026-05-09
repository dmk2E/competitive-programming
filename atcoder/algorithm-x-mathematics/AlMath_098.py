'''アルゴリズムと工夫点(Polygon and Point/CPU: 234 ms Memory: 121092 KB  Length: 1080 B)
幾何学が知識が必要な問題．
ある多角形P と，それに含まれるか判定する点Tが存在することを考える．
実は判定は，「点Tのx軸正の方向の半直線が，多角形Pの1辺を奇数回跨いでいるか」で判定できる．
最悪計算量は，O(N) < 10 ^ 6 となり十分高速．
※ 今回は外積のみを用いたが，多角形の任意の辺上に存在するかも判定したい場合，内積も必要になる
'''
import sys

n = 0

class Point: 
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y
    
    def __sub__(self, other): 
        return Point(x=self.x - other.x, y=self.y - other.y)


def cross(vec1: Point, vec2: Point) -> int: 
    return vec1.x * vec2.y - vec2.x * vec1.y

def main(argv: list[str]):
    global n
    n = int(input())
    # 入力を受け取る
    polygon: list[Point] = []
    for i in range(n): 
        x, y = map(int, input().split())
        polygon.append(Point(x=x, y=y))
    a, b = map(int, input().split())
    t_p = Point(x=a, y=b)

    # 判定処理
    judge = False
    now_id = 0
    while now_id < n: 
        vec1 = polygon[now_id] - t_p
        vec2 = polygon[(now_id + 1) % n] - t_p
        if vec1.y > vec2.y: 
            vec1, vec2 = vec2, vec1
        if vec1.y <= 0 and vec2.y > 0 and cross(vec1=vec1, vec2=vec2) > 0: 
            judge = not(judge)
        now_id += 1
    print("INSIDE" if judge else "OUTSIDE")

if __name__ == "__main__":
    main(argv=sys.argv[1:])