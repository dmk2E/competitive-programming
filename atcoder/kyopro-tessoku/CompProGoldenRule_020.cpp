/*アルゴリズムと工夫点(A20 - LCS/CPU: 10 ms Memory: 3808 KB  Length: 655 B)
dp[i][j]:S[0,i)とT[0,j)のLCS とする動的計画法で解ける．
最悪計算量はO(|S|*|T|)<10^7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s,t;

int main(){
    int i,j,maxL,k;
    cin>>s>>t;
    const int NIL=0;
    maxL=0;
    vector<int> last(t.length()+1,NIL);
    rep(i,s.length()){
        vector<int> now=last;
        rep(j,t.length()){
            if(s[i]==t[j]){
                now[j+1]=max(now[j+1],last[j]+1);
            }
            now[j+1]=max(now[j],now[j+1]);
            maxL=now[j+1];
        }
        swap(last,now);
    }
    printf("%d\n",maxL);
    return 0;
}