/*アルゴリズムと工夫点(Independent Set on a Tree/CPU: 36 ms  Memory: 12032 KB  Length: 990 B)
二部グラフ:辺で直接結ばれた頂点同士が互いに違う色となるように、頂点を2色で塗ることができるグラフ。木は必ず二部グラフ。
二部グラフの特性を利用することで、O(n)で解くことができる。
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
#define RED 2
#define GREEN 1
#define NIL 0
using namespace std;

int n,color[MAX_N]={0};
vector<int> adj[MAX_N];

void dfs(int now,int c,int& red,int& green){
	color[now]=c;
	if(c==RED){
		red++;
		for(int x:adj[now]){
			if(color[x]==NIL)
				dfs(x,GREEN,red,green);
		}
	}else{
		green++;
		for(int x:adj[now]){
			if(color[x]==NIL)
				dfs(x,RED,red,green);
		}
	}
}

int main() {
	int i,j,k;
	queue<int> que;
	scanf("%d",&n);
	rep(i,n-1){
		scanf("%d%d",&j,&k);
		j--;k--;
		adj[j].push_back(k);
		adj[k].push_back(j);
	}
	j=k=0;
	rep(i,n)
		if(color[i]==NIL)
			dfs(i,RED,j,k);
	if(j<=k){
		rep(i,n)
			if(color[i]==GREEN)
				que.push(i+1);
	}else{
		rep(i,n)
			if(color[i]==RED)
				que.push(i+1);
	}
	n/=2;
	while(--n){
		printf("%d ",que.front());
		que.pop();
	}
	printf("%d\n",que.front());
	return 0;
}