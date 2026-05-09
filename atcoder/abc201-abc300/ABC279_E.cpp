/*アルゴリズムと工夫点(Cheating Amidakuji/CPU: 26 ms Memory: 6408 KB  Length: 633 B)
「先頭からの累積和的なもの+末尾からの累積和的なもの」を求めておくことで，経路の途中で何らかの処理が入る場合の解を高速で求めることが可能になる．
もしメモリ的に許されないなら，解自体を先に求めるようにすることで，その時に必要な分のメモリだけ用意するだけでよくなる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    vector<int> a(m),s(m);
    rep(i,m){
        scanf("%d",&a[i]);
        a[i]--;
    }
    j=0;
    rep(i,m){
        s[i]=j;
        if(a[i]+1==j)j--;
        else if(a[i]==j)j++;
    }
    vector<int> ans(m),now(n);
    rep(i,n)now[i]=i;
    for(j=m-1;j>=0;j--){
        ans[j]=now[s[j]];
        swap(now[a[j]],now[a[j]+1]);
    }
    rep(i,m)printf("%d\n",ans[i]+1);
    return 0;
}