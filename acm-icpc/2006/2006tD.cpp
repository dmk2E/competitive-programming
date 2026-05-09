/*アルゴリズムと工夫点(Railroad Conflict/CPU: 20 ms  Memory: 3400 KB  Length: 2881 B)
「A駅とB駅の間の線分」と既存路線との交点を求め、A駅との距離の昇順でソートする。その後、A駅からB駅への方向に交点を順に訪問していき、線路が高架か地下かを決定し、出入口の数を求めればよい。
計算量はO(n) となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define EPS (1e-10)
using namespace std;

typedef enum ccw {
	COUNTER_CLOCKWISE=1,
	CLOCKWISE=-1,
	ONLINE_FRONT=2,
	ONLINE_BACK=-2,
	ON_SEGMENT=0
}CCW;

typedef struct point {
	double x, y;

	point(double a=0, double b=0) {
		x = a;
		y = b;
	}

	point operator+ (const point& k) {
		return point(x + k.x, y + k.y);
	}

	point operator- (const point& k) {
		return point(x - k.x, y - k.y);
	}

	point operator* (double k) {
		return point(x * k, y * k);
	}

	point operator/ (double k) {
		return point(x / k, y / k);
	}

	bool operator< (point k) const {
		return fabs(x - k.x) < EPS ? y < k.y : x < k.x;
	}

	bool operator== (const point& k) const {
		return fabs(x - k.x) < EPS && fabs(y - k.y)<EPS;
	}

	double norm() {
		return x * x + y * y;
	}

	double abs() {
		return sqrt(norm());
	}

}Point;

typedef struct segment {
	point p1, p2;
}Segment;

typedef Point Vector;
typedef Segment Line;

typedef struct cpoint {
	double x, y, o, l, len;

	bool operator< (const cpoint& k) const {
		return len < k.len;
	}
}CPoint;

int nn,n;
Segment a;
priority_queue<CPoint> PQ;

double getDistance(point a, point b) {
	Vector s = a - b;
	return s.abs();
}

double dot(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}

double cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}

int ccw(point p0, point p1, point p2) {
	Vector a = p1 - p0, b = p2 - p0;
	if (cross(a, b) > EPS)
		return COUNTER_CLOCKWISE;
	else if (cross(a, b) < -EPS)
		return CLOCKWISE;
	else if (dot(a, b) < -EPS)
		return ONLINE_BACK;
	else if (a.norm() < b.norm())
		return ONLINE_FRONT;
	return ON_SEGMENT;
}

bool intersect(point p0, point p1, point p2, point p3) {
	return (ccw(p0, p1, p2) * ccw(p0, p1, p3) <= 0 && ccw(p2, p3, p0) * ccw(p2, p3, p1) <= 0);
}

point crossPoint(Segment s1, Segment s2) {
	double d1, d2;
	Vector base = s2.p2 - s2.p1;
	d1 = fabs(cross(base, s1.p1 - s2.p1));
	d2 = fabs(cross(base, s1.p2 - s2.p1));
	return s1.p1 + (s1.p2 - s1.p1) * d1 / (d1 + d2);
}

int main() {
	int cnt;
	bool o, l, now;
	Segment tmp;
	Point temp;
	CPoint c;
	scanf("%d",&nn);
	while (nn--) {
		scanf("%lf%lf%lf%lf",&a.p1.x,&a.p1.y,&a.p2.x,&a.p2.y);
		scanf("%d",&n);
		while (n--) {
			scanf("%lf%lf%lf%lf", &tmp.p1.x, &tmp.p1.y, &tmp.p2.x, &tmp.p2.y);
			cin >> o >> l;
			if (intersect(a.p1,a.p2,tmp.p1,tmp.p2)) {
				temp = crossPoint(a,tmp);
				c.x = temp.x; c.y = temp.y;
				c.o = o; c.l = l;
				c.len = -getDistance(a.p1,temp);
				PQ.push(c);
				//printf("(%.3lf,%.3lf)\n",c.x,c.y);
			}
		}
		cnt = 0;
		if (PQ.size()) {
			c = PQ.top(); PQ.pop();
			now = c.o == true ? c.l : !c.l;
		}
		while (PQ.size()) {
			c = PQ.top(); PQ.pop();
			if (c.o) {
				if (now != c.l) {
					cnt++;
					now = c.l;
				}
			}
			else {
				if (now == c.l) {
					cnt++;
					now = !c.l;
				}
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}