/*アルゴリズムと工夫点(Circumferences/CPU: 15 ms Memory: 3980 KB  Length: 1437 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll s_x,s_y,t_x,t_y;

int main(){
    int i,j;
    scanf("%d%lld%lld%lld%lld",&n,&s_x,&s_y,&t_x,&t_y);
    vector<ll> x(n),y(n),r(n);
    rep(i,n)scanf("%lld%lld%lld",&x[i],&y[i],&r[i]);
    const int NIL=-1;
    vector<int> color(n,NIL);
    auto judge=[&](int a,int b)->bool{
        return ((r[a]-r[b])*(r[a]-r[b])<=(x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]))&&((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])<=(r[a]+r[b])*(r[a]+r[b]));
    };
    auto bfs=[&](int now,int c)->void{
        int i;
        queue<int> que;
        color[now]=c;
        que.push(now);
        while(que.size()){
            now=que.front();que.pop();
            rep(i,n){
                if(color[i]==NIL&&judge(i,now)){
                    color[i]=color[now];
                    que.push(i);
                }
            }
        }
    };
    j=0;
    rep(i,n)if(color[i]==NIL)bfs(i,j++);
    rep(i,n){
        if((s_x-x[i])*(s_x-x[i])+(s_y-y[i])*(s_y-y[i])==r[i]*r[i]){
            rep(j,n)if((t_x-x[j])*(t_x-x[j])+(t_y-y[j])*(t_y-y[j])==r[j]*r[j]&&color[i]==color[j]){
                    puts("Yes");
                    return 0;
                }
        }
    }
    puts("No");
    return 0;
}