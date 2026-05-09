/*アルゴリズムと工夫点(F - S = 1/CPU: 1 ms  Memory: 3956 KB  Length: 763 B)
2点(0,0),(X,Y)を通る直線lは,y=(Y/X)xであるから、Yx-Xy=0 と表せる。この2点を底辺とする三角形を考えると、高さhとして条件より、(1/2)*h*√(X^2+Y^2)=1 h=2/√(X^2+Y^2)-①となる。点(A,B)と直線lの距離はhと等しく、点と直線の距離の公式より、
h=|YA-XB|/√(X^2+Y^2) となる。これを①に代入して整理すると、|YA-XB|=2を満たせばよく、拡張ユークリッドの互除法で解ける。最悪計算量はO(log2(min(A,B)))となる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

typedef long long ll;

ll x, y;

ll gcd(ll a, ll b) {
	return b==0?a:gcd(b, a % b);
}

ll extgcd(ll a, ll b, ll& x, ll& y) {
	ll d = a;
	if (b > 0) {
		d = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	else {
		x = 1;
		y = 0;
	}
	return d;
}

int main() {
	ll a, b;
	bool flagX = false, flagY = false;
	scanf("%lld%lld", &x, &y);
	if (x < 0) {
		flagX = true;
		x = -x;
	}
	if (y < 0) {
		flagY = true;
		y = -y;
	}
	if (gcd(y,x)<=2){
		extgcd(y, x, a, b);
		if (flagX==false)
			b = -b;
		if (flagY)
			a = -a;
		a *= 2 / gcd(x, y);
		b *= 2 / gcd(x, y);
		printf("%lld %lld\n", a, b);
	}
	else
		puts("-1");
	return 0;
}