/*アルゴリズムと工夫点(Sigma Problem/CPU: 60 ms Memory: 5104 KB  Length: 674 B)
与えられた式の値は,aの並びを変えても変化しない.また,問題の制約から,x+y>=10^8の時,x+y-10^8,x+y<10^8 の時,x+yとなることから,一旦余りの操作を無視して総和を求める.その後,必要な分だけ総和から10^8を引けばよい.
a[i]を固定した時,a[i]+a[j]>=MODとなる最小のjは,ソート後のa上で二分探索を行うことで求めることができる.したがって,最悪計算量はO(N*log2(N))<10^7 となり,十分高速.
※「元の配列をソートしても式の値が変わらない」というのは重要な性質.考察できちんと見つけられるようにしたい.
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 300000
#define MOD 100000000
using namespace std;

int n,a[MAX_N];

int main(){
    int i,left,right,mid;
    long long ans=0,sum=0;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&a[i]);
        ans+=a[i];
    }
    ans*=n-1;
    sort(a,a+n);
    rep(i,n-1){
        left=i+1;right=n;
        while(left<right){
            mid=(left+right)/2;
            if(a[i]+a[mid]<MOD)
                left=mid+1;
            else
                right=mid;
        }
        printf("%d\n",n-left);
        ans-=MOD*((long long)n-left);
    }
    printf("%lld\n",ans);
    return 0;
}