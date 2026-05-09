/*アルゴリズムと工夫点(We Need Both a and b（★5）/CPU: 65 ms Memory: 14456 KB  Length: 1630 B)
木DPに気づいていたが，状態の捉え方が難しかった...
※キーワード:「木DPに慣れよう」
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD (int)((1e9)+7)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n;
vector<bool> color;

int main(){
    int i,j,k;
    scanf("%d",&n);
    rep(i,n){
        getchar();
        color.push_back(getchar()=='a');
    }
    vector<vector<int> > adj(n,vector<int>(0));
    rep(i,n-1){
        scanf("%d%d",&j,&k);
        j--;k--;
        adj[j].push_back(k);
        adj[k].push_back(j);
    }
    vector<vector<int> > dp(n,vector<int>(3,0));
    auto dfs=[&](auto& f,int now,int prev)->void{
        int i,j;
        ll val1=1,val2=1;
        rep(i,adj[now].size()){
            if(adj[now][i]!=prev){
                f(f,adj[now][i],now);
                if(color[now]){
                    val1*=((ll)dp[adj[now][i]][0]+dp[adj[now][i]][2]);
                    val2*=((ll)dp[adj[now][i]][0]+dp[adj[now][i]][1]+2*(ll)dp[adj[now][i]][2]);
                }else{
                    val1*=((ll)dp[adj[now][i]][1]+dp[adj[now][i]][2]);
                    val2*=((ll)dp[adj[now][i]][0]+dp[adj[now][i]][1]+2*(ll)dp[adj[now][i]][2]);
                }
                val1%=MOD;
                val2%=MOD;
            }
        }
        if(color[now]){
            dp[now][0]=val1;
            dp[now][2]=(val2-val1+MOD)%MOD;
        }else{
            dp[now][1]=val1;
            dp[now][2]=(val2-val1+MOD)%MOD;
        }
        return ;
    };
    const int NIL=-1;
    dfs(dfs,0,NIL);
    printf("%d\n",dp[0][2]);
    return 0;
}