/*アルゴリズムと工夫点(Card Eater/CPU: 24 ms  Memory: 8376 KB  Length: 571 B)
1枚数以上あるカードの内、奇数枚あるカードは、その同じ数字のカード3枚を選び続ければ必ず1枚になるため、その枚数-1の数だけ全体の数から引く。偶数枚では必ず2枚になるから、その数をsumに記録しておく。sumの値は必ず偶数
であり、同じ数字のカードは2枚ずつ存する。数字iの2枚、数字jの2枚の4枚を1セットとし、そのセット内でカードを食べていくと、必ず数字iとjの2種類が1枚ずつ残る。従って、sumが4の倍数なら、(sum/4)*2、そうでなければ、
余った2枚の分をなくして同様に計算すればよい。故にO(n)で十分高速に動作する。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

typedef pair<int, int> p;

int n;
map<int,int> d;

int main() {
	int i,tmp,sum=0;
	cin >> n;
	rep(i, n) {
		//scanf_s("%d",&tmp);
		scanf("%d", &tmp);
		d[tmp]++;
	}
	for (p temp : d) {
		//printf("(%d,%d)\n",temp.first,temp.second);
		if (temp.second > 1) {
			if (temp.second % 2 == 0) {
				n -= temp.second;
				sum += 2;
			}
			else 
				n -= temp.second - 1;
		}
		//printf("n:%d sum:%d\n",n,sum);
	}
	n += (sum / 4)*2;   //整数型の商は小数点以下は切り捨てられることを利用した。
	printf("%d\n",n);
	return 0;
}