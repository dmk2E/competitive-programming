/*アルゴリズムと工夫点(1122 Substring/CPU: 19 ms Memory: 4892 KB  Length: 1087 B)
条件を満たすか常に管理しながら，尺取り法で解く．
最悪計算量は O(N)<10^6 となり十分高速．
※半開区間[l,r)を考えた時，lの値を固定した時のある条件を満たす半開区間の右端rの最大値f(l)とする．このlの値に対してf(l)の値が単調増加する時，尺取り法が使える．
*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,l,r,ans=0;
    scanf("%d",&n);
    vector<int> a(n),a2Cnt(n+1,0);
    rep(i,n)scanf("%d",&a[i]);
    r=0;
    j=n;//種類数
    rep(l,n){
        //printf("before l:%d r:%d j:%d\n",l,r,j);
        if(l+1>=n||r-l<=1||a[l]==a[l+1]){
            while(r<n){
                if(a2Cnt[a[r]]+1>2||((r-l)%2==1&&a[r-1]!=a[r]))break;
                if(a2Cnt[a[r]]==0)j--;
                else if(a2Cnt[a[r]]==1)j++;
                a2Cnt[a[r]]++;         
                r++;
                if((r-l)%2==0&&j==n){
                    ans=max(ans,r-l);
                    //printf("get l:%d r:%d j:%d\n",l,r,j);
                }
            }
        }
        //printf("after l:%d r:%d j:%d\n",l,r,j);
        if(l==r)r++;
        if(a2Cnt[a[l]]==2)j--;
        a2Cnt[a[l]]--;
        if(a2Cnt[a[l]]==0)j++;
    }
    printf("%d\n",ans);
    return 0;
}