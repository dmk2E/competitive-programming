/*アルゴリズムと工夫点(AtCounter/CPU: 13 ms  Memory: 3948 KB  Length: 693 B)
2^n通りの全探索は次のような状態遷移型DPで解くことができる。dp[i][j]:Item[0,i)についてのみ、「選ぶ」or「選ばない」を決めたときに状態jになる時の求める値。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_T 7
#define MOD 1000000007
using namespace std;

int n;
long long dp[2][MAX_T+1]={0};
string s,t("atcoder"),subT[MAX_T+1];

int main() {
	int i,now=0,j,last;
	rep(i,MAX_T+1)
		subT[i]=t.substr(0,i);
	scanf("%d",&n);
	cin>>s;
	dp[now++][0]=1;
	rep(i,n){
		last=(now+1)%2;
		rep(j,MAX_T+1)
			dp[now][j]=dp[last][j];
		rep(j,MAX_T)
			if(dp[last][j]>0&&(subT[j]+s[i])==subT[j+1]){
				dp[now][j+1]+=dp[last][j];
				dp[now][j+1]%=MOD;
			}
		/*
		rep(j,MAX_T+1)
			printf("%lld ",dp[now][j]);
		puts("");
		*/
		now=(now+1)%2;
	}
	printf("%lld\n",dp[(now+1)%2][MAX_T]);
	return 0;
}