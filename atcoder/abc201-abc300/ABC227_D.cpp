/*アルゴリズムと工夫点(Project Planning/CPU:  ms Memory:  KB  Length:  B)
x個のプロジェクトを作れる場合，x以下のプロジェクトは必ず作ることができるため，単調性が存在するから，二分探索を行う．
「x個以上のプロジェクトを作れるか」の判定は貪欲法で行うことができる．
従って最悪計算量はO(N*log2(N*max(Ai)))<10^7 より，高速。
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_A ((ll)(1e12)+1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i;
    ll left,right,mid;
    scanf("%d%d",&n,&k);
    vector<ll> a(n);
    rep(i,n)scanf("%lld",&a[i]);
    sort(a.rbegin(),a.rend());
    auto judge=[&](ll x)->bool{
        int i;
        ll sum=0;
        rep(i,n){
            sum+=min(a[i],x);
            if(k<=sum/x)return true;//オーバーフローを防ぐため，割り算の形に式変形
        }
        return false;
    };
    left=0,right=(ll)n*MAX_A+1;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))
            left=mid+1;
        else
            right=mid;
    }
    printf("%lld\n",left-1);
    return 0;
}