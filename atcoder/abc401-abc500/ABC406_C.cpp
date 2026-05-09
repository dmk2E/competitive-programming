/*アルゴリズムと工夫点(~/CPU: 30 ms Memory: 8596 KB  Length: 1228 B)
2つの条件それぞれを満たす添え字の位置の列rを先に求めておく．
その後，満たす条件が異なるr[i],r[i+1]が存在する時，それらを含むチルダ型を数え上げる．
チルダ型の左端を1ずつ増加させつつ固定し，その時にチルダ型となる数を順に数え上げても，慣らし計算量的には問題なく，最悪計算量は O(N)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MIN_LEN 4
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,bool> P;//(pos,cond)

int n;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d",&n);
    vector<int> a(n);
    vector<P> rle;
    rep(i,n)scanf("%d",&a[i]);
    for(i=1;i<n-1;i++){
        if(a[i-1]<a[i]&&a[i]>a[i+1])rle.push_back(P(i,false));
        if(a[i-1]>a[i]&&a[i]<a[i+1])rle.push_back(P(i,true));
    }
    int l,r;
    rep(i,rle.size()-1){
        if(rle[i].second!=rle[i+1].second){
            //printf("%d , %d\n",rle[i].first,rle[i+1].first);
            if(i-1>=0)l=rle[i-1].first;
            else l=0;
            if(i+2<rle.size())r=rle[i+2].first+1;
            else r=n;
            //printf("l:%d r:%d\n",l,r);
            while(l<rle[i].first){
                if(l+1<n&&a[l]<a[l+1]&&r-l>=MIN_LEN){
                    ans+=max(0,r-(max(rle[i+1].first+1,l+MIN_LEN-1)));
                    //printf("[%d,%d)\n",l,r);printf("ans:%lld\n",ans);
                }
                l++;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}