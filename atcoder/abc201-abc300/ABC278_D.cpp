/*アルゴリズムと工夫点(All Assign Point Add/CPU: 67 ms Memory: 5652 KB  Length: 808 B)
Aiそれぞれと，「Aiそれぞれの値がいつ更新されたものであるか(when)」を別で保持して置き，「1」の命令がされた時刻nowと更新する値valも別で保持して置けば，高速で処理を行える．
最悪計算量はO(N+Q)<10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q,t;

int main(){
    int i,j,now,val;
    scanf("%d",&n);
    vector<ll> a(n);
    vector<int> when(n,0);
    rep(i,n)scanf("%lld",&a[i]);
    scanf("%d",&q);
    now=val=-1;
    rep(i,q){
        scanf("%d",&t);
        if(t==1){
            now=i+1;
            scanf("%d",&val);
        }else if(t==2){
            scanf("%d%d",&t,&j);
            t--;
            if(when[t]<now){
                a[t]=val+j;
                when[t]=i+1;
            }else
                a[t]+=j;
        }else{
            scanf("%d",&t);t--;
            printf("%lld\n",when[t]<now?val:a[t]);
        }
    }
    return 0;
}