/*アルゴリズムと工夫点(Bowls and Beans/CPU: 3 ms Memory: 3940 KB  Length: 885 B)
ボールは一度に同じ場所に入れればよい．
また，右端から順番にボールを回収していくことを考える．
DAGであることを活かしたDPで解ける．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int solve(vector<int>& c){
    int i,j;
    const int INF=(int)(1e9);
    vector<int> dp(c.size()+1,INF);
    dp[0]=0;
    rep(i,c.size()){
        int now=INF;
        rep(j,c[i]){
            if(i-j<0)break;
            now=min(now,dp[i-j]);
        }
        dp[i+1]=now+1;
    }
    return dp.back();
}

int n;

int main(){
    int i,j,ans=0;
    scanf("%d",&n);
    vector<int> c(n,0),a(n,0);
    rep(i,n-1)scanf("%d",&c[i+1]);
    rep(i,n-1)scanf("%d",&a[i+1]);
    vector<int> cs;
    for(i=1;i<n;i++){
        cs.push_back(c[i]);
        if(a[i]==1){
            ans+=solve(cs);
            cs=vector<int>();
        }
    }
    printf("%d\n",ans);
    return 0;
}