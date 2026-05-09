/*アルゴリズムと工夫点(Three Days Ago/CPU: 8 ms  Memory: 4200 KB  Length: 399 B)

※ローカル変数として確保できるメモリは約8MB程までに限られており、それを超えるとsegmentation error が発生してしまうことに注意。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_NUM 1024
using namespace std;

int state[MAX_NUM]={0};
string s;

int main() {
	int i,now=0;
	long long ans=0;
	cin>>s;
	state[now]++;
	rep(i,s.length()){
		now^=1<<((int)s[i]-(int)'0');
		state[now]++;
	}
	rep(i,MAX_NUM)
		ans+=(long long)state[i]*(state[i]-1)/2;
	printf("%lld\n",ans);
	return 0;
}