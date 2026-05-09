/*アルゴリズムと工夫点(Gomamayo Sequence/CPU: 27 ms  Memory: 10312 KB  Length: 654 B)
初め、dpっぽいことを実装していたがTLEになってしまっていて、dpを3次元にとるという発想ができなかった。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 200000
#define INF (1e18)
using namespace std;

int n,c;
string s;
long long dp[MAX_N][2][2];

int main() {
	int i,j;
	scanf("%d",&n);
	cin>>s;
	scanf("%d",&c);
	rep(i,n){
		rep(j,2){
			dp[i][j][0]=INF;
			dp[i][j][1]=INF;
		}
	}
	dp[0][0][s[0]-(int)'0']=0;
	dp[0][0][(s[0]-(int)'0')^1]=c;
	for(i=1;i<n;i++){
		scanf("%d",&c);
		for(j=0;j<2;j++){
			dp[i][0][j]=dp[i-1][0][j^1]+((s[i]-'0')==j?0:c);
			dp[i][1][j]=min(dp[i-1][0][j],dp[i-1][1][j^1])+((s[i]-'0')==j?0:c);
		}
	}
	printf("%lld\n",min(dp[n-1][1][0],dp[n-1][1][1]));
	return 0;
}