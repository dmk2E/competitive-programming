/*アルゴリズムと工夫点(Moonlight Farm/CPU: 0 ms  Memory: 3392 KB  Length: 794 B)
各作物について、与えられた条件の通りに収入効率pを計算し、作物の名前lとpを組としたデータを作物毎に保持する。その後、昇順にソートして出力すればよい。注意点として、浮動小数点数型の等価演算があげられ、今回はEPS
を用いた方法で行った。最悪計算量はO(n+n*log2(n))=O(n*log2(n))<10^3 より十分高速。

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 50
#define MAX_S 20
#define EPS (1e-10)
using namespace std;

typedef struct crop {
	string name;
	double p;

	crop(string nname=string("0"), double pp=0.0) :name(nname), p(pp) {}

	bool operator<(const crop& k) const {
		return p < k.p || (fabs(p - k.p) < EPS && name > k.name);
	}
}Crop;

int n, p, a, b, c, d, e, f, s, m;
char l[MAX_S + 1];
Crop crop[MAX_N];

int main() {
	int i;
	while (1) {
		scanf("%d", &n);
		if (!n)
			break;
		rep(i, n) {
			scanf("%s%d%d%d%d%d%d%d%d%d", l, &p, &a, &b, &c, &d, &e, &f, &s, &m);
			crop[i] = Crop(string(l), (double)(f * m * s - p) / (a + b + c + (d + e) * m));
		}
		sort(crop, crop + n);
		rep(i, n)
			cout << crop[n - 1 - i].name << endl;
		puts("#");
	}
	return 0;
}