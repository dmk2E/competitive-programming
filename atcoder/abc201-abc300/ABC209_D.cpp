/*アルゴリズムと工夫点(Collision/CPU: 50 ms Memory: 9340 KB  Length: 909 B)
ある頂点を始点として,他の2つの頂点の関係を調べたいとき,二部グラフの考えを用いると解けることがある.
また,閉路を持たないグラフ,つまり木構造は実際に絵に描いて,頂点の深さ等も考えながら,アルゴリズムを考案するようにしよう.
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define NIL -1
using namespace std;

int n,q;

void bfs(vector<vector<int> >& adj,vector<int>& color){
    int now;
    queue<int> que;
    color[0]=1;
    que.push(0);
    while(que.size()){
        now=que.front();que.pop();
        for(int x:adj[now]){
            if(color[x]==NIL){
                color[x]=(color[now]+1)%2;
                que.push(x);
            }
        }
    }
}

int main(){
    int i,j,k;
    scanf("%d%d",&n,&q);
    vector<vector<int> > adj(n);
    vector<int> color(n,NIL);
    rep(i,n-1){
        scanf("%d%d",&j,&k);
        j--;k--;
        adj[j].push_back(k);
        adj[k].push_back(j);
    }
    bfs(adj,color);
    while(q--){
        scanf("%d%d",&i,&j);
        i--;j--;
        printf("%s\n",color[i]==color[j]?"Town":"Road");
    }
    return 0;
}