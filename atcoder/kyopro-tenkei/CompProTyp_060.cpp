/*アルゴリズムと工夫点(Chimera（★5）/CPU: 60 ms Memory: 8576 KB  Length: 1186 B)
dp[i]:配列aの先頭から考えて，a[i]が最後の項となるLIS(最長増加部分列)
revDp[i]:配列aの末尾から考えて，a[i]が最後の項となるLIS(最長増加部分列)
を前処理でLISのアルゴリズムでO(N*log2(N))で求める．その後，a[i]がBkとなるときの，Mの最大値を全探索する．この時の最悪計算量はO(N)
従って，全体の最悪計算量はO(N*log2(N))<10^7となり高速．
LISは，LIS[i]:長さがiとなるLISで，末尾の値が最も小さいものを保持 LISは単調性を持つため，ある値が末尾となるLISは，配列LISを用いた二分探索で求められる．
※キーワードは「両側から考える/最長増加部分列」
※初見AC嬉しい!
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N (int)(3e5)
using namespace std;
typedef long long ll;

int n,a[MAX_N],dp[MAX_N+1],revDp[MAX_N+1],LIS[MAX_N+1];

int main(){
    int i,left,right,mid;
    scanf("%d\n",&n);
    rep(i,n){
        scanf("%d",&a[i]);
        LIS[i]=MAX_N+1;
    }
    LIS[i]=MAX_N+1;
    for(i=0;i<n;i++){
        left=1;right=n+1;
        while(left<right){
            mid=(left+right)/2;
            if(LIS[mid]<a[i])
                left=mid+1;
            else
                right=mid;
        }
        dp[i]=left;
        if(a[i]<LIS[left])
            LIS[left]=a[i];
    }
    rep(i,n+1)LIS[i]=MAX_N+1;
    for(i=n-1;i>=0;i--){
        left=1;right=n+1;
        while(left<right){
            mid=(left+right)/2;
            if(LIS[mid]<a[i])
                left=mid+1;
            else
                right=mid;
        }
        revDp[i]=left;
        if(a[i]<LIS[left])
            LIS[left]=a[i];
    }
    left=-1;
    rep(i,n){
        if(left<dp[i]+revDp[i]-1)
            left=dp[i]+revDp[i]-1;
    }
    printf("%d\n",left);
    return 0;
}