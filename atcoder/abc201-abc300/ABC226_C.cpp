/*アルゴリズムと工夫点(Martial artist/CPU: 59 ms Memory: 15160 KB  Length: 964 B)
1回のBFSで解けることに気づくのに時間がかかってしまった...
むやみにトポロジカルソートするものではないね...
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,t;

int main(){
    int i,j,k;
    scanf("%d",&n);
    vector<vector<int> > adj(n,vector<int>(0));//(id,dist)
    vector<int> tt(n);
    vector<bool> flag(n,false);
    ll ans=0;
    rep(i,n){
        scanf("%d%d",&t,&j);
        tt[i]=t;
        if(j==0)continue;
        while(j--){
            scanf("%d",&k);
            adj[i].push_back(k-1);
        }
    }
    queue<int> que;
    que.push(n-1);
    flag[n-1]=true;
    ans+=tt[n-1];
    while(que.size()){
        i=que.front();que.pop();
        rep(j,adj[i].size()){
            if(flag[adj[i][j]]==false){
                flag[adj[i][j]]=true;
                que.push(adj[i][j]);
                ans+=tt[adj[i][j]];
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}