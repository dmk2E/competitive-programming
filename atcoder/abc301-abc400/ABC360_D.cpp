/*アルゴリズムと工夫点(Ghost Ants/CPU: 46 ms Memory: 5916 KB  Length: 1345 B)
左を向いている蟻がぶつかる可能性がある蟻群は，右を向いている蟻だけで，逆も同様．
従って，左を向いている蟻だけを順番に見ていき，数える．左を向いている蟻iを固定すると，蟻iとぶつかる右を向いている蟻jの数は，右を向いている蟻の座標を昇順に管理している配列と，二分探索で求めることができる．
従って，最悪計算量はO(N*log2(N))<10^7 で高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;
typedef long long ll;

int n,t;
vector<ll> l,r;
string s;

ll search(ll lx){
    int left=0,right=r.size(),mid;
    long long ans=0;
    while(left<right){
        mid=(left+right)/2;
        if(r[mid]-t<=lx+t)
            left=mid+1;
        else
            right=mid;
    }
    ans=left;
    left=0,right=r.size();
    //printf("%lld\n",ans);
    while(left<right){
        mid=(left+right)/2;
        if(r[mid]<lx)
            left=mid+1;
        else
            right=mid;
    }
    ans-=left;
    //printf("%lld\n",ans);
    return ans;
}

int main(){
    int i,j;
    ll temp;
    long long ans=0;
    scanf("%d%d",&n,&t);
    cin>>s;
    rep(i,n){
        scanf("%lld",&temp);
        if(s[i]=='0')
            r.push_back(temp);
        else
            l.push_back(temp);
    }
    sort(l.begin(),l.end());
    sort(r.begin(),r.end());
    // rep(i,l.size()){
    //     printf("%lld ",l[i]);
    // }
    // puts("");
    // rep(i,r.size()){
    //     printf("%lld ",r[i]);
    // }
    // puts("");
    rep(i,l.size()){
        //printf("i:%d\n",i);
        ans+=search(l[i]);
    }
    printf("%lld\n",ans);
    return 0;
}