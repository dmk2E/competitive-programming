/*アルゴリズムと工夫点(Statue of Chokudai/CPU: 2 ms  Memory: 4176 KB  Length: 402 B)
ある時刻における観覧車の座標が (0,y,z) である時、求める俯角αとすると、tan(α)=Z/√(X^2+(Y-y)^2) と求めることができる。ここで条件より、y=-L/2*sin(2*π*E/T),z=L/2(1-cos(2*π*E/T)) となることから、mathライブラリを用いて
一つのクエリに対して、O(1)で答えを出せる。したがって、全体の最悪計算量はO(Q)<10^4 となり十分高速。
※単項式毎に型が決定していくから、オーバーフローに注意。
※atan2(y,x) で、arctan(y/x)の値をラジアンで返す便利な関数。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int t,l,x,y,q,e;

int main() {
	double yy,z;
	scanf("%d%d%d%d",&t,&l,&x,&y);
	scanf("%d",&q);
	while(q--){
		scanf("%d",&e);
		e%=t;
		yy=-(double)l/2*sin(2.0*M_PI/t*e);
		z=(double)l/2*(1.0-cos(2.0*M_PI/t*e));
		printf("%.8f\n",180/M_PI*atan2(z,sqrt((double)x*x+(yy-y)*(yy-y))));//int型のオーバーフローを考慮できてなかった。
	}
	return 0;
}