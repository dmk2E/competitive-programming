/*アルゴリズムと工夫点(Even Digits/CPU: 1 ms  Memory: 3812 KB  Length: 1021 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX 18
using namespace std;

typedef long long ll;

char num[] = "02468";
ll n, d[MAX + 2], sumD[MAX + 2];

int main() {
	int i;
	d[0] = 5;
	sumD[0] = 0;
	rep(i, MAX+1) {
		sumD[i + 1] = d[i] + sumD[i];
		d[i + 1] = 4 * sumD[i + 1];
		//printf("%lld %lld\n", d[i], sumD[i]);
	}
	scanf("%lld", &n);
	rep(i, MAX + 1) {
		if (sumD[i] >= n)
			break;
	}
	//iが桁数
	//printf("i:%d\n",i);
	if (i - 1 > 0) {
		if(n%sumD[i-1]==0)
			printf("%c", num[n / sumD[i - 1] - 1]);
		else
			printf("%c", num[n / sumD[i - 1]]);
		n %= sumD[i - 1];
		i--;
		//printf("(n:%lld)\n", n);
		while (i - 1 > 0) {
			if (n % sumD[i - 1] == 0)
				printf("%c", num[n / sumD[i - 1] - 1<0?4: n / sumD[i - 1] - 1]);
			else
				printf("%c", num[n / sumD[i - 1]]);
			n %= sumD[i - 1];
			//printf("(n:%lld)\n", n);
			i--;
		}
		printf("%c\n", num[n - 1 < 0 ? 4 : n - 1]);
	}
	else
		printf("%c\n", num[n - 1]);
	return 0;
}