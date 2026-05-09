/*アルゴリズムと工夫点(Lucky Bag（★5）/CPU: 46 ms Memory: 83248 KB  Length: 1161 B)
dp[i][j]:1~i+1日目まで，福袋AまたはBを購入した時，最後に買った福袋
とする動的計画法で解ける．最悪計算量はO(NS)≒10^7 となり，高速．
※キーワードDP復元
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

typedef enum state{
    NIL=-1,
    A,
    B
}State;

typedef pair<int,State> p;

int n,s,a,b;

int main(){
    int i,j;
    scanf("%d%d",&n,&s);
    vector<vector<p>> dp(n+1,vector<p>(s+1,p(NIL,NIL)));
    dp[0][0]=p(0,NIL);
    rep(j,n){
        scanf("%d%d",&a,&b);
        rep(i,s+1){
            if(dp[j][i].first!=NIL){
                if(i+a<=s)
                    dp[j+1][i+a]=p(i,A);
                if(i+b<=s)
                    dp[j+1][i+b]=p(i,B);
            }
        }
        //rep(i,s+1)printf("%d ",i);puts("");rep(i,s+1){if(i>=10)putchar(' ');printf("%c ",dp[j+1][i].first==NIL?'F':(dp[j][i].second==A?'A':'B'));}puts("");
    }
    if(dp[n][s].first==NIL)puts("Impossible");
    else{
        string ans;
        i=n;
        j=s;
        while(i>0){
            ans.push_back(dp[i][j].second==A?'A':'B');
            j=dp[i][j].first;
            i--;
        }
        for(i=ans.length()-1;i>=0;i--)
            putchar(ans[i]);
        puts("");
    }
    return 0;
}