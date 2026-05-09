/*アルゴリズムと工夫点(Previous Permutation/CPU: 1 ms Memory: 3896 KB  Length: 414 B)
Pi<Pi+1 となる最大のiを見つける．
Pi<Pj(i<j)となる最大のjを見つける．
PiとPjを入れ替える．
Pi+1以降を逆順にする．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> p(n),pp;
    rep(i,n)scanf("%d",&p[i]);
    prev_permutation(p.begin(),p.end());
    rep(i,n-1)printf("%d ",p[i]);
    printf("%d\n",p[i]);
    return 0;
}