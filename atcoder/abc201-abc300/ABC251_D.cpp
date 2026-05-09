/*アルゴリズムと工夫点(At Most 3 (Contestant ver.)/CPU: 1 ms Memory: 3900 KB  Length: 519 B)
10進数の各桁に着目し，桁毎に3個以下の数を選択すれば，任意の値を作ることが可能になるような数を出力すればよい．
今回は，2桁ずつ分けて考えればよい．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int w;

int main(){
    int i,j;
    scanf("%d",&w);
    vector<int> ans;
    for(i=1;i<=99;i++)ans.push_back(i);
    for(i=100;i<=9900;i+=100)ans.push_back(i);
    for(i=10000;i<=990000;i+=10000)ans.push_back(i);
    printf("%ld\n",ans.size());
    rep(i,ans.size()-1)printf("%d ",ans[i]);printf("%d\n",ans[i]);
    return 0;
}