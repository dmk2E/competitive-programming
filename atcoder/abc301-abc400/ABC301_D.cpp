/*アルゴリズムと工夫点(Bitmask/CPU: 7 ms Memory: 3892 KB  Length: 609 B)
現時点でのとり得る最小値を管理しながら，先頭ビットから見ていって?を「1」にするか「0」にするか貪欲に判定．
最悪計算量はO(|s|) となり十分高速．
※初見ACできた!
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;
ll n;

int main(){
    int i,j;
    ll ans=0;
    cin>>s;
    scanf("%lld",&n);
    rep(i,s.length()){
        if(s[i]=='1')ans+=((ll)1<<((int)s.length()-1-i));
    }
    if(n<ans){
        puts("-1");
        return 0;
    }
    rep(i,s.length()){
        if(s[i]=='?'){
            if(ans+((ll)1<<((int)s.length()-1-i))<=n)
                ans+=((ll)1<<((int)s.length()-1-i));
        }
    }
    printf("%lld\n",ans);
    return 0;
}