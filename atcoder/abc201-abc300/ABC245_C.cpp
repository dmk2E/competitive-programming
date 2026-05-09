/*アルゴリズムと工夫点(Choose Elements/CPU: 57 ms Memory: 18920 KB  Length: 1761 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,bool> P;//(整数値，Bの要素か否か)

int n,k;

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    vector<int> a(n),b(n);
    rep(i,n)scanf("%d",&a[i]);
    rep(i,n)scanf("%d",&b[i]);
    auto bfs=[&]()->bool{
        int i;
        P now;
        queue<P> que;
        vector<vector<bool> > vis(n,vector<bool>(2,false));
        que.push(P(0,false));
        que.push(P(0,true));
        vis[0][0]=true;
        vis[0][1]=true;
        while(que.size()){
            now=que.front();que.pop();
            if(now.first==n-1)return true;
            if(now.second){
                if(abs(b[now.first]-a[now.first+1])<=k&&vis[now.first+1][0]==false){
                    que.push(P(now.first+1,false));
                    vis[now.first+1][0]=true;
                }
                if(abs(b[now.first]-b[now.first+1])<=k&&vis[now.first+1][1]==false){
                    que.push(P(now.first+1,true));
                    vis[now.first+1][1]=true;
                }
            }else{
                if(abs(a[now.first]-a[now.first+1])<=k&&vis[now.first+1][0]==false){
                    que.push(P(now.first+1,false));
                    vis[now.first+1][0]=true;
                }
                if(abs(a[now.first]-b[now.first+1])<=k&&vis[now.first+1][1]==false){
                    que.push(P(now.first+1,true));
                    vis[now.first+1][1]=true;
                }
            }
        }
        return false;
    };
    printf("%s\n",bfs()?"Yes":"No");
    return 0;
}