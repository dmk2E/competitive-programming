/*アルゴリズムと工夫点(I Hate Non-integer Number/CPU: 63 ms Memory: 3976 KB  Length: 881 B)
ii個選ぶと固定して，dp[i][j][k]:i個目までみてj個選んだ時，iiで割った余りがkとなる数
という動的計画法で解く．
最悪計算量は O(N^(4))=10^8 となるが，毎回(N+1)*(N+1)*Nの大きさのテーブルを考えるわけではないため計算量を削減できるため，実際は高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,k,ii,jj,ans=0;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    for(ii=1;ii<=n;ii++){//ii個選ぶとする
        vector<vector<int> > dp(ii+1,vector<int>(ii,0));//dp[i][j]:i個選んで，iiで割った余りがjの数
        dp[0][0]=1;
        rep(i,n){
            vector<vector<int> > now=dp;
            rep(j,min(i+1,ii))rep(k,ii){
                jj=(k+a[i])%ii;
                now[j+1][jj]=(now[j+1][jj]+dp[j][k])%MOD;
            }
            swap(dp,now);
        }
        //printf("%d\n",dp[ii][0]);
        ans=(ans+dp[ii][0])%MOD;
    }
    printf("%d\n",ans);
    return 0;
}