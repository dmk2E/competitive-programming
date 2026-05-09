/*アルゴリズムと工夫点(Chinese Restaurant/CPU: 20 ms Memory: 4912 KB  Length: 633 B)
操作を行う回数は最大でN-1回と考えても良い．そこで，
pls[i]=(操作をi回行ったとき，喜ぶ人数)
を求め，max(pls)を出力することを考える．
plsは，人iを一人ずつ見ていき，料理iが，その人が喜ぶ位置に入っているための操作回数を算数で求めていけばよい．
最悪計算量は O(N)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> p2Id(n),pls(n,0);
    rep(i,n){
        scanf("%d",&j);
        p2Id[j]=i;
    }
    auto dist=[](int start,int end)->int{
        return start<=end?end-start:n-start+end;
    };
    rep(i,n){
        pls[dist(p2Id[i],(i-1+n)%n)]++;
        pls[dist(p2Id[i],i)]++;
        pls[dist(p2Id[i],(i+1)%n)]++;
    }
    j=0;
    rep(i,n)j=max(j,pls[i]);
    printf("%d\n",j);
    return 0;
}