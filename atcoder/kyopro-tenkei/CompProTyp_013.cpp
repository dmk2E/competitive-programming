/*アルゴリズムと工夫点(Passing/CPU: 63 ms  Memory: 12268 KB  Length: 938 B)
都市nからの最短経路問題(単一終点最短経路問題)と都市1からの最短経路問題をそれぞれ1回のダイクストラ法で解き、(都市1から都市kまでの最短経路)+(都市kから都市nまでの最短経路) を出力すればよい。
最悪計算量はO(2*(N+M)*log2(N+M))=(N+M)*log2(N+M)<10^7 となるから、高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX ((1e9)+1)
using namespace std;

typedef struct pair<int,int> p;

int n,m;
vector<int> s2K,n2K;
vector<vector<p> > adj;

void dijk(int s,vector<int>& mmin){
	p now;
	priority_queue<p> PQ;
	PQ.push(make_pair(0,s));
	while(PQ.size()){
		do{
			now=PQ.top();PQ.pop();
		}while(PQ.size()&&mmin[now.second]!=MAX);
		if(mmin[now.second]!=MAX)
			break;
		else
			mmin[now.second]=-now.first;
		for(p x:adj[now.second]){
			if(mmin[x.first]==MAX)
				PQ.push(make_pair(now.first-x.second,x.first));
		}
	}
	return ;
}

int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	s2K.resize(n,MAX);n2K.resize(n,MAX);adj.resize(n);
	while(m--){
		scanf("%d%d%d",&i,&j,&k);
		adj[i-1].push_back(make_pair(j-1,k));
		adj[j-1].push_back(make_pair(i-1,k));
	}
	dijk(0,s2K);dijk(n-1,n2K);
	rep(i,n)
		printf("%d\n",s2K[i]+n2K[i]);
	return 0;
}