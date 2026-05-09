/*アルゴリズムと工夫点(Sum of All Substrings/CPU: 14 ms Memory: 6992 KB  Length: 762 B)
Sの前からi(0-indexed)文字の数は，10^(0)~10^(N-1-i)の位の数で加算される．
これに気づけば，後はimos法と10進数の繰り上がりの処理の問題になる．
最悪計算量は O(|S|)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;

int main(){
    int i,j;
    scanf("%d",&n);
    cin>>s;
    vector<ll> ans(n,0);
    rep(i,n){
        ans[0]+=(i+1)*((int)s[i]-'0');
        if(n-i<n)
            ans[n-i]-=(i+1)*((int)s[i]-'0');
    }
    rep(i,n)
        ans[i+1]+=ans[i];
    rep(i,n-1){
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
    }
    while(ans[ans.size()-1]>=10){
        ans.push_back(ans[ans.size()-1]/10);
        ans[ans.size()-2]%=10;
    }
    rep(i,ans.size()){
        printf("%lld",ans[(int)ans.size()-1-i]);
    }
    puts("");
    return 0;
}