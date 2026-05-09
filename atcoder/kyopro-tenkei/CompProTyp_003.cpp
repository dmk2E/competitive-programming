/*アルゴリズムと工夫点(Longest Circular Road/CPU: 38 ms  Memory: 9824 KB  Length: 1104 B)
グラフの頂点数N,辺の数Mとすると、1回のbfsの計算量はO(N+M)となる。今回の問題は与えられた都市をグラフとし、それを木とみなし、「木の直径」を求め、それに+1した値を出力すればよい。
任意の点を始点とし、その始点から最も遠い点sとしたとき、その点sから最も遠い点eとすると、2点s,t間の距離が木の直径となる。そのためbfs2回で求めることができる。最悪計算量はO(2*(N+N))=O(N)<10^6となり、
十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
#define NIL -1
using namespace std;

int n;
vector<int> adj[MAX_N];

int bfs(int s){   //始点sからbfsを行った時に、そこから最も遠い点の頂点番号を返す。
	int now,max=s,cnt=1;
	vector<int> color(n,NIL);
	queue<int> que;
	color[s]=0;
	que.push(s);
	while(que.size()){
		now=que.front();que.pop();
		for(int x:adj[now]){
			if(color[x]==NIL){
				color[x]=color[now]+1;
				que.push(x);
				cnt++;
				if(color[max]<color[x])
					max=x;
			}
		}
		if(cnt==n)
			break;
	}
	return max;
}

int bbfs(int s){   //始点sからbfsを行った時に、そこから最も遠い点との距離を返す。
	int now,max=s,cnt=1;
	vector<int> color(n,NIL);
	queue<int> que;
	color[s]=0;
	que.push(s);
	while(que.size()){
		now=que.front();que.pop();
		for(int x:adj[now]){
			if(color[x]==NIL){
				color[x]=color[now]+1;
				que.push(x);
				cnt++;
				if(color[max]<color[x])
					max=x;
			}
		}
		if(cnt==n)
			break;
	}
	return color[max];
}

int main() {
	int i,j,k;
	scanf("%d",&n);
	rep(k,n){
		scanf("%d%d",&i,&j);
		adj[i-1].push_back(j-1);
		adj[j-1].push_back(i-1);
	}
	printf("%d\n",bbfs(bfs(0))+1);
	return 0;
}