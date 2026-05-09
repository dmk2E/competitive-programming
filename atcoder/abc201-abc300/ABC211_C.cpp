/*アルゴリズムと工夫点(chokudai/CPU: 4 ms Memory: 3920 KB  Length: 524 B)
愚直に全探索しようとすると，2^|s|通りの部分文字列が存在してしまう．そこで，動的計画法で解く．
dp[i][j]:S[0,i]の範囲で存在するT[0,j)の部分文字列の数．とすると，更新漸化式は，dp[i][j+1]=dp[i-1][j+1]+dp[i-1][j] となり，O(|S|*|T|)で解ける．
今回，|T|=8より，O(|S|)<10^6 となり，十分高速．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_T 8
#define NIL -1
#define MOD ((int)(1e9)+7)
using namespace std;

int dp[MAX_T+1]={0};
string s,t="chokudai";

int main(){
    int i,j,now=0,k;
    cin>>s;
    dp[0]=1;
    rep(i,s.length()){
        for(j=t.length()-1;j>=0;j--)
            if(s[i]==t[j])
                dp[j+1]=(int)(((long long)dp[j+1]+dp[j])%MOD);
    }
    //rep(i,t.length()+1)printf("%d ",dp[i]);puts("");
    printf("%d\n",dp[t.length()]);
    return 0;
}