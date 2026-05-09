/*アルゴリズムと工夫点(Not Equal/CPU: 34 ms Memory: 4588 KB  Length: 568 B)
ソート済みであれば解ける問題->ソートしても値が変わらない問題かどうか判定するとよい.
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
#define MOD 1000000007
using namespace std;

int n,c[MAX_N];

int main(){
    int i,nowI,now;
    long long ans=1;
    scanf("%d",&n);
    rep(i,n)
        scanf("%d",&c[i]);
    sort(c,c+n);
    nowI=0;now=c[0];
    rep(i,n){
        if(c[nowI]<c[i]){
            now+=c[i]-c[nowI];
            nowI=i;
        }
        ans=(ans*now)%MOD;
        now--;
        if(now<0)
            break;
    }
    printf("%lld\n",ans);
    return 0;
}