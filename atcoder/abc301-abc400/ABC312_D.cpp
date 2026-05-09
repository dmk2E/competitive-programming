/*アルゴリズムと工夫点(Count Bracket Sequences/CPU: 26 ms Memory: 3848 KB  Length: 969 B)
動的計画法で解く．
f(i)=S[0,i)における（'('の数）-（')'の数）
とする．正しい括弧列であるためには，1<=i<=|S|の任意のiについて，f(i)>=0 かつ f(|S|+1)=0 である必要がある．
従って，以下のDPを解けばよい．
dp[i][j]：f(i)=j である時のSの置き換え方の数
よって最悪計算量は，O(|S|^2)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i,j;
    cin>>s;
    vector<int> dp(s.length()+1,0);
    dp[0]=1;
    rep(i,s.length()){
        vector<int> nxt(s.length()+1,0);
        switch(s[i]){
            case '(':
                rep(j,s.length())if(j+1<s.length()+1)nxt[j+1]=(nxt[j+1]+dp[j])%MOD;
                break;
            case ')':
                rep(j,s.length())if(j-1>=0)nxt[j-1]=(nxt[j-1]+dp[j])%MOD;
                break;
            default:
                rep(j,s.length()){
                    if(j-1>=0)nxt[j-1]=(nxt[j-1]+dp[j])%MOD;
                    if(j+1<s.length()+1)nxt[j+1]=(nxt[j+1]+dp[j])%MOD;
                }
                break;
        }
        swap(dp,nxt);
    }
    printf("%d\n",dp[0]);
    return 0;
}