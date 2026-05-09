/*アルゴリズムと工夫点(Come Back in One Piece/CPU: 75 ms  Memory: 21216 KB  Length: 1021 B)
「SCC(強連結成分分解)」というアルゴリズムを用いて解くことができる。
<i>DFSで、各頂点vに対して頂点vから進めなくなった順番を記録する。これは配列に先頭から「頂点の数」を代入していくことで実現する(添え字が順番の番号を示す)。
<ii><i>で振った番号の降順に、辺の向きを反転させたグラフ上でDFSを行う。各DFSで訪問した頂点の数cntとすると、その強連結成分の個数は cnt*(cnt-1)/2 と求めることができる。
※有向グラフ上で、頂点x,yのそれぞれから互いに到達可能であることを「強連結」という。
*/
#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
#define NIL 0
using namespace std;

int n,m;
vector<int> adj[MAX_N],rAdj[MAX_N];

void dfs(int now,vector<int>& t,bool color[]){
	color[now]=true;
	for(int x:adj[now]){
		if(color[x]==false)
			dfs(x,t,color);
	}
	t.push_back(now);
}

int ddfs(int now,bool color[]){
	int cnt=1;
	color[now]=true;
	for(int x:rAdj[now]){
		if(color[x]==false)
			cnt+=ddfs(x,color);
	}
	return cnt;
}

int main() {
	int i,j;
	long long cnt=0;
	vector<int> t;
	bool color[MAX_N]={0};
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d",&i,&j);
		i--;j--;
		adj[i].push_back(j);
		rAdj[j].push_back(i);
	}
	rep(i,n){
		if(color[i]==false)
			dfs(i,t,color);
	}
	reverse(t.begin(),t.end());
	rep(i,n)
		color[i]=false;
	rep(i,n){
		if(color[t[i]]==false){
			j=ddfs(t[i],color);
			cnt+=(long long)j*(j-1)/2;
		}
	}
	printf("%lld\n",cnt);
	return 0;
}