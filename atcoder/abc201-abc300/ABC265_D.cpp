/*アルゴリズムと工夫点(Iroha and Haiku (New ABC Edition)/CPU: 27 ms Memory: 6512 KB  Length: 980 B)
前処理で尺取り法を用いて，P,Q,Rの値を取る(l,r)の値を予め求めておく．
その後，条件を満たす(x,y,z,w)が存在するか判定する．
最悪計算量は O(N)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
const int MAX=3;
ll pqr[3];

int main(){
    int i,j;
    scanf("%d%lld%lld%lld",&n,&pqr[0],&pqr[1],&pqr[2]);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    vector<vector<int> > l2R(MAX);
    const int NIL=-1;
    auto tpa=[&](ll x)->vector<int>{
        int l,r;
        ll sum=0;
        vector<int> ans(n,NIL);
        for(l=r=0;l<n;l++){
            while(r<n&&sum<x){
                sum+=a[r];
                r++;
            }
            if(sum==x)ans[l]=r;
            if(l==r)r++;
            else sum-=a[l];
        }
        return ans;
    };
    rep(i,MAX)l2R[i]=tpa(pqr[i]);
    rep(j,n)if(l2R[0][j]!=NIL&&(l2R[0][j]<n&&l2R[1][l2R[0][j]]!=NIL)&&(l2R[1][l2R[0][j]]<n&&l2R[2][l2R[1][l2R[0][j]]]!=NIL))break;
    printf("%s\n",j==n?"No":"Yes");
    return 0;
}