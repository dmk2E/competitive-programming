/*アルゴリズムと工夫点(Defect-free Squares/CPU: 263 ms Memory: 38764 KB  Length: 903 B)
二次元累積和+二分探索で解く．
最悪計算量は，O(N+H*W*log2(max(H,W)))<10^8 となり間に合う．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w,n;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d%d",&h,&w,&n);
    vector<vector<int> > sum(h+1,vector<int>(w+1,0));
    while(n--){
        scanf("%d%d",&i,&j);
        sum[i][j]++;
    }
    rep(i,h)rep(j,w)sum[i+1][j+1]+=sum[i+1][j]+sum[i][j+1]-sum[i][j];
    auto f=[&](int sy,int sx,int gy,int gx)->int{
        return sum[gy+1][gx+1]-sum[gy+1][sx]-sum[sy][gx+1]+sum[sy][sx];
    };
    rep(i,h)rep(j,w){
        int left=0,right=min(h-i,w-j)+1;
        while(left<right){
            int mid=(left+right)/2;
            if(f(i,j,i+mid-1,j+mid-1)==0)left=mid+1;
            else right=mid;
        }
        ans+=max(0,left-1);
    }
    printf("%lld\n",ans);
    return 0;
}