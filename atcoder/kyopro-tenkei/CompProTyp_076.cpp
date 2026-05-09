/*アルゴリズムと工夫点(Cake Cut（★3）/CPU: 17 ms Memory: 4100 KB  Length: 1066 B)
円形に並んだN個の要素は，N個の要素をもつ一次元配列Aで表現されることが多い．この時，連続する要素の選び方は，始点A[s]とすると，
<i>終点が A[s]~A[N-1]の場合 <ii>A[N-1]をまたいで，A[0]~A[s-1]の場合
の二つに場合分けして考える．<ii>の場合は，不変量のsum(A)を用いれば，sum(A)-(範囲外のAの要素の総和ssumA) とすることができる．
ssumAは，A上で連続した要素A[1,s)を指定すればよく，考えやすくなる．
今回はAの累積和をとり，連続する要素の先頭を固定すると，二分探索で，<i>または<ii>の場合それぞれで条件を満たすか高速に判定可能．
最悪計算量はO(N*log2(N))≒10^6 となり，十分高速．
※キーワード:「円環を列にして二倍する」
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i;
    scanf("%d",&n);
    vector<ll> sum(n+1);
    sum[0]=0;
    rep(i,n){
        scanf("%lld",&sum[i+1]);
        sum[i+1]+=sum[i];
    }
    auto search=[&](int x)->bool{
        int left=x+1,right=sum.size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(10*(sum[mid]-sum[x])<sum[n])
                left=mid+1;
            else
                right=mid;
        }
        if(left<sum.size()&&10*(sum[left]-sum[x])==sum[n])return true;
        left=1,right=x;
        while(left<right){
            mid=(left+right)/2;
            if(10*(sum[n]-sum[x]+sum[mid])<sum[n])
                left=mid+1;
            else
                right=mid;   
        }
        return left<x&&10*(sum[n]-sum[x]+sum[left])==sum[n];
    };
    rep(i,n)if(search(i))break;
    printf("%s\n",i==n?"No":"Yes");
    return 0;
}