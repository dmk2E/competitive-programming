/*アルゴリズムと工夫点(Shift vs. CapsLock/CPU: 11 ms Memory: 4076 KB  Length: 967 B)
動的計画法で解く．
文字を消したり変更することはできないため、先頭から1文字ずつ決めていく必要がある．
決める際に重要なのが、「今CapsLockキーがONかOFFか」であるから、
dp[i][j]：i文字目を出力した際に、CapsLockキーがON（j=0）かOFF（j=1）か
最悪計算量は、O(|S|)<10^6 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int x,y,z;
string s;

int main(){
    int i,j;
    scanf("%d%d%d",&x,&y,&z);
    cin>>s;
    string state_to_str="aA";
    const ll INF=(ll)(1e15);
    vector<ll> dp(2,0);//CapsLockキーがONかOFFか
    dp[1]=INF;
    rep(i,s.size()){
        vector<ll> now(2,INF);
        rep(j,2){
            // CapsLockキーを押さない
            if(state_to_str[j]==s[i])now[j]=min(now[j],dp[j]+x);
            if(state_to_str[(j+1)%2]==s[i])now[j]=min(now[j],dp[j]+y);
            // CapsLockキーを押す
            if(state_to_str[(j+1)%2]==s[i])now[(j+1)%2]=min(now[(j+1)%2],dp[j]+x+z);
            if(state_to_str[j]==s[i])now[(j+1)%2]=min(now[(j+1)%2],dp[j]+y+z);
        }
        swap(now,dp);
    }
    printf("%lld\n",min(dp[0],dp[1]));
    return 0;
}