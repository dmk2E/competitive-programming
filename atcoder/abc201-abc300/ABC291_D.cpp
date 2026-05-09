/*アルゴリズムと工夫点(Flip Cards/CPU: 44 ms Memory: 3900 KB  Length: 580 B)
dp[i][j∈(0,1)]:1~i枚目までのカードの表裏を決めた状態で，i枚がj(j=0で表,j=1で裏)である場合のカードの状態の総数
という動的計画法で解ける．
※初見4完!嬉しい
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353
using namespace std;

int n,a,b;

int main(){
    int i,lA,lB;
    scanf("%d",&n);
    vector<int> dp(2,1);
    scanf("%d%d",&lA,&lB);
    rep(i,n-1){
        scanf("%d%d",&a,&b);
        vector<int> old(2,0);
        swap(old,dp);
        dp[0]=((a==lA?0:(long long)old[0])+(a==lB?0:old[1]))%MOD;
        dp[1]=((b==lA?0:(long long)old[0])+(b==lB?0:old[1]))%MOD;
        lA=a;lB=b;
    }
    printf("%d\n",(int)(((long long)dp[0]+dp[1])%MOD));
    return 0;
}