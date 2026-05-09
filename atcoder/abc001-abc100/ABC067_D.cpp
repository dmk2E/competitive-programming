/*アルゴリズムと工夫点(Fennec VS. Snuke/CPU: 26 ms  Memory: 9360 KB  Length: 912 B)
与えられたゲームを言い換えて、簡単なbfsで判定可能な問題に言い換える問題。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
using namespace std;

typedef enum color{
	NIL=-1,
	WHITE,
	BLACK
}Color;

int n,a,b;
vector<int> adj[MAX_N];

bool bfs(){
	int i,cntB,cntW,now;
	vector<Color> color(n,NIL);
	queue<int> que;
	color[0]=BLACK;color[n-1]=WHITE;
	que.push(0);
	que.push(n-1);
	cntB=cntW=1;
	while(que.size()){
		now=que.front();que.pop();
		for(int x:adj[now]){
			if(color[x]==NIL){
				color[x]=color[now];
				switch(color[now]){
					case BLACK:
						cntB++;
						break;
					case WHITE:
						cntW++;
						break;
					default:
						break;
				}
				que.push(x);
			}
		}
	}
	return cntB>cntW;
}

int main() {
	int i,j,k;
	scanf("%d",&n);
	rep(k,n-1){
		scanf("%d%d",&i,&j);
		adj[i-1].push_back(j-1);
		adj[j-1].push_back(i-1);
	}
	printf("%s\n",bfs()?"Fennec":"Snuke");
	return 0;
}