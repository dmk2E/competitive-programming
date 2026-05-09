/*アルゴリズムと工夫点(ケーキカット/CPU: 0 ms  Memory: 3244 KB  Length: 3491 B)
分割したケーキは、リスト構造で保持する。新しいものほど後ろに並ぶため、カットするケーキをリストから消去し、生成された2つのケーキをリストの末端に追加することを繰り返せばよい。
最悪計算量は、O(n^2) ≒10^4 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

typedef struct point {
	int y, x;

	point(int a=0, int b=0) {
		y = a;
		x = b;
	}

	point operator+(const point& k) {
		return point(y+k.y,x+k.x);
	}

	point operator-(const point& k) {
		return point(y - k.y, x - k.x);
	}

	bool operator<(const point& k) const {
		return x == k.x ? y < k.y : x < k.x;
	}

	int length() {
		return x == 0 ? abs(y) : abs(x);
	}
}Point;

typedef Point Segment;

typedef struct cake {
	Point p0, p1, p2, p3;   //北西の点を始点とし、時計回りの順にp0→p1→p2→p3
	int s,len;

	cake(point a=Point(0,0), point b=Point(0, 0), point c=Point(0, 0), point d=Point(0,0)) {
		p0 = a; p1 = b; p2 = c; p3 = d;
		Segment w = b - a, h = c - b;
		s = w.length() * h.length();
	}

	bool operator< (const cake& k) const {
		return s < k.s;
	}

}Cake;

int n, w, d, pp, s;
list<Cake> p;

Cake getC(int num) {   //リストの先頭からnum番目の要素を消去して取り出す関数。計算量はO(n)
	int i;
	Cake tmp;
	list<Cake>::iterator it;
	for (it = p.begin(),i=1; it != p.end(); it++,i++) {
		if (i == num) {
			tmp = *it;
			p.erase(it);
			break;
		}
	}
	return tmp;
}

int main() {
	Segment ww, dd;
	Cake tmp, temp;
	priority_queue<int> PQ;
	while (1) {
		scanf("%d%d%d", &n, &w, &d);
		if (!(n || w || d))
			break;
		p.push_back(Cake(Point(0,0),Point(0,w),Point(d,w),Point(d,0)));
		while (n--) {
			scanf("%d%d", &pp, &s);
			tmp = getC(pp);
			ww = tmp.p1 - tmp.p0;
			dd = tmp.p2 - tmp.p1;
			s %= 2 * ww.length() + 2 * dd.length();
			//printf("%d[(%d,%d)-(%d,%d)-(%d,%d)-(%d,%d)]->",tmp.s,tmp.p0.y,tmp.p0.x,tmp.p1.y,tmp.p1.x,tmp.p2.y,tmp.p2.x,tmp.p3.y,tmp.p3.x);
			if (s - ww.length() < 0) {
				temp = Cake(tmp.p0,tmp.p0+Point(0,s),tmp.p3+Point(0,s), tmp.p3);
				tmp = Cake(tmp.p0 + Point(0, s),tmp.p1,tmp.p2, tmp.p3 + Point(0, s));
			}
			else if (s - ww.length() - dd.length()<0) {
				s -= ww.length();
				temp = Cake(tmp.p0, tmp.p1, tmp.p1 + Point(s, 0), tmp.p0 + Point(s, 0));
				tmp = Cake(tmp.p0 + Point(s, 0), tmp.p1 + Point(s, 0), tmp.p2, tmp.p3);
			}
			else if (s - 2*ww.length() - dd.length() < 0) {
				s -= ww.length() + dd.length();
				temp = Cake(tmp.p0, tmp.p1 - Point(0, s), tmp.p2 - Point(0, s), tmp.p3);
				tmp = Cake(tmp.p1 - Point(0, s), tmp.p1, tmp.p2, tmp.p2 - Point(0, s));
			}
			else {
				s -= 2 * ww.length() + dd.length();
				temp = Cake(tmp.p0, tmp.p1, tmp.p2 - Point(s, 0), tmp.p3 - Point(s, 0));
				tmp = Cake(tmp.p3 - Point(s, 0), tmp.p2 - Point(s, 0), tmp.p2, tmp.p3);
			}
			if (temp < tmp) {
				p.push_back(temp);
				//printf("%d[(%d,%d)-(%d,%d)-(%d,%d)-(%d,%d)]+", temp.s, temp.p0.y, temp.p0.x, temp.p1.y, temp.p1.x, temp.p2.y, temp.p2.x, temp.p3.y, temp.p3.x);
				p.push_back(tmp);
				//printf("%d[(%d,%d)-(%d,%d)-(%d,%d)-(%d,%d)]\n", tmp.s, tmp.p0.y, tmp.p0.x, tmp.p1.y, tmp.p1.x, tmp.p2.y, tmp.p2.x, tmp.p3.y, tmp.p3.x);
			}
			else {
				p.push_back(tmp);
				//printf("%d[(%d,%d)-(%d,%d)-(%d,%d)-(%d,%d)]+", tmp.s, tmp.p0.y, tmp.p0.x, tmp.p1.y, tmp.p1.x, tmp.p2.y, tmp.p2.x, tmp.p3.y, tmp.p3.x);
				p.push_back(temp);
				//printf("%d[(%d,%d)-(%d,%d)-(%d,%d)-(%d,%d)]\n", temp.s, temp.p0.y, temp.p0.x, temp.p1.y, temp.p1.x, temp.p2.y, temp.p2.x, temp.p3.y, temp.p3.x);
			}
		}
		for (Cake c : p)
			PQ.push(-c.s);
		while (PQ.size()-1>0) {
			printf("%d ", -PQ.top()); PQ.pop();
		}
		printf("%d\n", -PQ.top()); PQ.pop();
		p.clear();   //リスト構造の初期化
	}
	return 0;
}