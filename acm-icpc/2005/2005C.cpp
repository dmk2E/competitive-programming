/*アルゴリズムと工夫点(Numeral System/CPU: 0 ms  Memory: 3064 KB  Length: 1198 B)
二つのMCXI文字列を整数値に直してその和を求めた後、その和をMCXI文字列に変換して出力する。
最悪計算量はO(n*(9+9+9))≒10^4 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define swap(a,b,t){t=a,a=b,b=c}
#define MAX_S 8
using namespace std;

int n;
char s1[MAX_S+1],s2[MAX_S+1],mcxi[4 + 1] = "mcxi";

int to10s(char c) {
	switch (c) {
		case 'm':
			return 1000;
			break;
		case 'c':
			return 100;
			break;
		case 'x':
			return 10;
			break;
		default:
			return 1;
			break;
	}
	return -1;
}

int toInt(char s[]) {
	int i,keisu,sum;
	for (i =sum=0,keisu=1; s[i] != '\0'; i++) {
		if ((int)'2' <= (int)s[i] && (int)s[i] <= (int)'9')
			keisu = (int)s[i] - (int)'0';
		else {
			sum += keisu * to10s(s[i]);
			keisu = 1;
		}
	}
	return sum;
}

char* toMCXI(int sum,char s[]) {
	int i,now = 0,ten=1000;
	rep(i, 4) {
		if (sum >= ten) {
			if (sum / ten >= 2)
				s[now++] = (char)(sum / ten + (int)'0');
			s[now++] = mcxi[i];
			sum %= ten;
		}
		ten /= 10;
	}
	s[now] = '\0';
	return s;
}

int main() {
	int temp;
	char ans[MAX_S+1];
	//scanf_s("%d",&n);
	scanf("%d", &n);
	while (n--) {
		//scanf_s("%s%s",s1,MAX_S+1,s2,MAX_S+1);
		scanf("%s%s", s1, s2);
		temp = toInt(s1);
		//printf("s1:%d\n",temp);
		temp += toInt(s2);
		//printf("s1+s2:%d\n", temp);
		printf("%s\n",toMCXI(temp,ans));
	}
	return 0;
}