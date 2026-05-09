/*アルゴリズムと工夫点(Flip and Adjust/CPU: 4 ms Memory: 7220 KB  Length: 968 B)
dp[i][j]:1~i+1枚目までを表か裏にするか決めた時，その時点での総和がjとなる場合，i+1枚目を選ぶ前の総和の値
とする動的計画法で解くことができ，経路復元も可能．
最悪計算量は，O(N*S)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,s;

int main(){
    int i,j;
    scanf("%d%d",&n,&s);
    vector<int> a(n),b(n);
    rep(i,n)scanf("%d%d",&a[i],&b[i]);
    const int NIL=-1;
    vector<vector<int> > dp(n+1,vector<int>(s+1,NIL));
    dp[0][0]=0;
    rep(i,n){
        rep(j,s+1){
            if(dp[i][j]!=NIL){
                if(j+a[i]<=s)
                    dp[i+1][j+a[i]]=j;
                if(j+b[i]<=s)
                    dp[i+1][j+b[i]]=j;
            }
        }
    }
    if(dp[n][s]==NIL){
        puts("No");
        return 0;
    }
    puts("Yes");
    string ans;
    i=n;
    j=s;
    while(i>0){
        ans+=(a[i-1]==j-dp[i][j]?'H':'T');
        j=dp[i][j];
        i--;
    }
    rep(i,n-1)printf("%c",ans[n-1-i]);
    printf("%c\n",ans[n-1-i]);
    return 0;
}