/*アルゴリズムと工夫点(Kth Takoyaki Set/CPU: 264 ms  Memory: 28812 KB  Length: 530 B)
生成した要素の中で最も小さいものを常に取り出していきたいときは、優先度付きキューを用いる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n,k;
vector<int> a;
priority_queue<long long> PQ;
set<long long> v;

int main() {
	int i;
	long long temp;
	scanf("%d%d",&n,&k);
	a.resize(n);
	rep(i,n){
		scanf("%d",&a[i]);
		PQ.push(-(long long)a[i]);
	}
	while(PQ.size()){
		temp=PQ.top();PQ.pop();
		if(v.find(temp)!=v.end())
			continue;
		v.insert(temp);
		if(--k==0)
			break;
		rep(i,n)
			PQ.push(temp-a[i]);
	}
	printf("%lld\n",-temp);
	return 0;
}