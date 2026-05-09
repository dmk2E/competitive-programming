/*アルゴリズムと工夫点(Diversity of Scores/CPU: 183 ms  Memory: 16924 KB  Length: 551 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 200000
using namespace std;

int n,t;
long long player2Point[MAX_N]={0};
map<long long,int> point2Count;

int main() {
	int i,j;
	long long v;
	scanf("%d%d",&n,&t);
	point2Count[0]=n;
	v=1;
	while(t--){
		scanf("%d%d",&i,&j);
		point2Count[player2Point[i-1]]--;
		if(point2Count[player2Point[i-1]]==0)
			v--;
		if(point2Count[player2Point[i-1]+=(long long)j]==0)
			v++;
		point2Count[player2Point[i-1]]++;
		printf("%lld\n",v);
	}
	return 0;
}