/*アルゴリズムと工夫点(Select 5（★2）/CPU: 280 ms Memory: 3888 KB  Length: 634 B)
N個の数列のそれぞれの値をpで割った余りで保持して置き，5個の値の積の余りがqとなる時を全探索する．
N個の中から5個選ぶ選び方は，NC5通り．単純に5重ループで実装すると，最悪計算量はO(NC5)=75287520<10^8 となり，間に合う．
※計算量の定数倍を見積もる．NC5=1/120*N^5と，定数倍がかなり小さいため，十分高速に動作する．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100
using namespace std;
typedef long long ll;

int n,p,q;
ll a[MAX_N];

int main(){
    int i,j,k,ii,jj,cnt=0;
    ll pdt;
    //printf("%lld\n",(ll)100*99*98*97*96/120);
    //printf("%d %d %d\n",100,23,5);rep(i,99)printf("%d ",i);printf("%d\n",i);return 0;
    scanf("%d%d%d",&n,&p,&q);
    rep(i,n){
        scanf("%lld",&a[i]);
        a[i]%=p;
    }
    rep(i,n)rep(j,i)rep(k,j)rep(ii,k)rep(jj,ii){
        pdt=(((((((a[i]*a[j])%p)*a[k])%p)*a[ii])%p)*a[jj])%p;
        if(pdt==q)cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}