/*アルゴリズムと工夫点(Encyclopedia of Parentheses/CPU: 29 ms  Memory: 6644 KB  Length: 669 B)
nが奇数なら解は存在しない。nが偶数の時の正しいかっこ列の集合を、dp[(n-2)/2]とし、全探索的な動的計画法で解いた。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX 10
using namespace std;

int n;
map<string,bool> dp[MAX];

int main() {
	int cnt=0,i;
	dp[0]["()"]=true;
	scanf("%d",&n);
	if(n%2==0){
		while(2*(cnt+1)<n){
			for(pair<string,bool> x:dp[cnt])
				dp[cnt+1]["("+x.first+")"]=true;
			for(i=0;i<=cnt/2;i++){
				for(pair<string,bool> x:dp[i]){
					for(pair<string,bool> y:dp[cnt-i]){
						dp[cnt+1][x.first+y.first]=true;
						dp[cnt+1][y.first+x.first]=true;
					}
				}
			}
			//printf("size:%d\n",(int)nowV.size());
			cnt++;
		}
		for(pair<string,bool> x:dp[cnt])
			cout<<x.first<<endl;
	}
	return 0;
}