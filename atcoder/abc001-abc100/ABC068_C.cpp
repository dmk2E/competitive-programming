/*アルゴリズムと工夫点(Cat Snuke and a Voyage/CPU: 62 ms  Memory: 16128 KB  Length: 672 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 200000
using namespace std;

int n,m;
vector<int> adj[MAX_N];

bool bfs(){
	int i,visited[MAX_N];
	queue<int> que;
	rep(i,n)
		visited[i]=MAX_N+1;
	que.push(0);
	visited[0]=0;
	while(que.size()){
		i=que.front();que.pop();
		for(int x:adj[i]){
			if(visited[x]==MAX_N+1){
				visited[x]=visited[i]+1;
				que.push(x);
			}
		}
	}
	return visited[n-1]<=2;
}

int main() {
	int i,j;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d",&i,&j);
		adj[i-1].push_back(j-1);
		adj[j-1].push_back(i-1);
	}
	printf("%s\n",bfs()?"POSSIBLE":"IMPOSSIBLE");
	return 0;
}