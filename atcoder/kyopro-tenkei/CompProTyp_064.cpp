/*アルゴリズムと工夫点(Uplift（★3）/CPU: 38 ms Memory: 5304 KB  Length: 749 B)
階差を考えると，変化するのは両端付近の値のみであることを利用する．
※階差を考える:絶対値が絡む問題では，とりあえず「片方-片方」の形に直し，計算した結果を観察してみる．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N (int)(1e5)
using namespace std;
typedef long long ll;

int n,q;
ll a[MAX_N]={0},da[MAX_N]={0},ans=0;

int main(){
    int i,j,k;
    ll last,now;
    scanf("%d%d",&n,&q);
    rep(i,n){
        scanf("%lld",&a[i]);
        if(0<=i-1){
            da[i-1]+=a[i];
            ans+=abs(da[i-1]);
        }
        if(i<n-1)
            da[i]-=a[i];
    }
    while(q--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        last=now=0;
        if(i-1>=0){last+=abs(da[i-1]);da[i-1]+=k;now+=abs(da[i-1]);}
        if(j<n-1){last+=abs(da[j]);da[j]-=k;now+=abs(da[j]);}
        ans+=now-last;
        printf("%lld\n",ans);
    }
    return 0;
}