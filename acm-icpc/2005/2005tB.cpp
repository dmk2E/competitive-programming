/*アルゴリズムと工夫点(Make Purse Light/CPU: 210 ms  Memory: 3528 KB  Length: 1330 B)
支払うために、どうしても財布の中の硬貨の合計枚数が増えてしまうことがあることに注意。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_C 20
using namespace std;

typedef struct coin{
	int m,c;
}Coin;

int m,ans[4];
Coin purse[4];

int countReturn(int sum) {
	int i,cnt=0;
	for (i = 3; i >= 0; i--) {
		cnt += sum / purse[i].m;
		sum %= purse[i].m;
	}
	return cnt;
}

int main() {
	int i, j, k, l, sum=0,max,temp;
	bool flag = false;
	purse[0].m = 10; purse[1].m = 50; purse[2].m = 100; purse[3].m = 500;
	while (1) {
		//scanf_s("%d",&m);
		scanf("%d", &m);
		if (!m)
			break;
		if (flag) 
			puts("");
		else
			flag = true;
		//scanf_s("%d%d%d%d",&purse[0].c,&purse[1].c,&purse[2].c,&purse[3].c);
		scanf("%d%d%d%d", &purse[0].c, &purse[1].c, &purse[2].c, &purse[3].c);
		max = -MAX_C*20-1;
		rep(i, purse[0].c + 1) {
			sum += purse[0].m * i;
			rep(j, purse[1].c + 1) {
				sum += purse[1].m * j;
				rep(k, purse[2].c + 1) {
					sum += purse[2].m * k;
					rep(l, purse[3].c + 1) {
						sum += purse[3].m * l;
						if (sum - m >= 0 && max < (temp=i+j+k+l-countReturn(sum-m))) {
							max = temp;
							ans[0] = i; ans[1] = j; ans[2] = k; ans[3] = l;
						}
						sum -= purse[3].m * l;
					}
					sum -= purse[2].m * k;
				}
				sum -= purse[1].m * j;
			}
			sum -= purse[0].m * i;
		}
		rep(i, 4) {
			if (ans[i] > 0)
				printf("%d %d\n",purse[i].m, ans[i]);
		}
	}
	return 0;
}