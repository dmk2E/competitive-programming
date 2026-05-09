/*アルゴリズムと工夫点(Squares in Circle/CPU: 58 ms Memory: 3872 KB  Length: 1010 B)
円の中心(0,0) とし，(x,y) (x>0,y>0)の範囲の座標を頂点に持つ正方形の数を数え上げ，4倍するなどして数を合わせる．
(y+1/2,?) (1<=y<r)を正方形の右上と固定した時の，円内の正方形の数は二分探索で求めることができる．
最悪計算量は O(r*log2(r))<10^7 となり高速．
※もっといい方法があるのか...?
※式変形ミスって大幅時間ロス...悔
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll r;

int main(){
    int i,j,left,right,mid;
    ll ans=0;
    scanf("%lld",&r);
    auto judge=[&](ll y,ll k)->int{
        return ((2*y+1)*(2*y+1)+(2*k+1)*(2*k+1)<=4*r*r)&&((2*(y-1)+1)*(2*(y-1)+1)+(2*k+1)*(2*k+1)<=4*r*r)&&((2*y+1)*(2*y+1)+(2*(k-1)+1)*(2*(k-1)+1)<=4*r*r);
    };
    for(i=1;i<r;i++){
        left=i+1;
        right=r;
        while(left<right){
            mid=(left+right)/2;
            if(judge(i,mid))
                left=mid+1;
            else
                right=mid;
        }
        ans+=max(left-i-1,0);
    }
    ans*=2;
    left=1;
    right=r;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid,mid))
            left=mid+1;
        else
            right=mid;
    }
    ans+=max(left-1,0);
    ans*=4;
    printf("%lld\n",ans+(r-1)*4+1);
    return 0;
}