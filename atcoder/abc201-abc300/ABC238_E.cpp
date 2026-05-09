/*アルゴリズムと工夫点(Range Sums/CPU: 134 ms Memory: 14916 KB  Length: 1000 B)
区間の和は「累積和」で考える．
半開区間[l,r)の和がXである時，s[r+1]-s[l]=Xとなる．ここで，s[0]=0であり，s[l],s[r+1]のどちらかが既知であれば，もう片方も特定することができる．
従って，sの一つ一つの要素それぞれを頂点とみなし，頂点0から頂点Nに到達可能か判定すればよい．
最悪計算量は O(N+Q)<10^7 となり高速．
※2変数の方程式が絡む問題では，一方の変数の値が決まるともう片方の値が決まることから，変数それぞれを頂点とみなし，「値が既知の頂点」から「求めたい値の頂点」まで連結か判定する典型パターンらしい
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<vector<int> > adj(n+1);
    while(q--){
        scanf("%d%d",&i,&j);
        i--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    const int NIL=-1;
    vector<int> color(n+1,NIL);
    auto bfs=[&](int now,int c)->void{
        int i;
        queue<int> que;
        que.push(now);
        color[now]=c;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size()){
                if(color[adj[now][i]]==NIL){
                    que.push(adj[now][i]);
                    color[adj[now][i]]=c;
                }
            }
        }
    };
    j=0;
    rep(i,n+1)if(color[i]==NIL)bfs(i,j++);
    printf("%s\n",color[0]==color[n]?"Yes":"No");
    return 0;
}