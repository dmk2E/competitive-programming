/*アルゴリズムと工夫点(Destroyer Takahashi/CPU:  ms Memory:  KB  Length:  B)
同じ列を複数回パンチする必要はない．そこで，「座標sを始点にD列パンチするか」を 0<=s<=10^9-d+1 の範囲で順に判定していくことを考える．
この場合，sが破壊されていないの終端に到達した時，そこでパンチを打たないと，もうその壁を破壊することができなくため，その場所でD列パンチする必要がある．
その時，別の壁も破壊されている場合があり，その場合にも対処するようにすると，解ける．
これは貪欲法で，最悪計算量は O(N*log2(N))≒10^6 となり十分高速．
※初見AC出来た!
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,d;

int main(){
    int i,j,ans=0;
    scanf("%d%d",&n,&d);
    vector<p> ipt(n);
    rep(i,n)scanf("%d%d",&ipt[i].second,&ipt[i].first);
    sort(ipt.begin(),ipt.end());
    i=j=0;
    while(i<n){
        if(j<ipt[i].second){
            ans++;
            j=ipt[i].first+d-1;
        }
        i++;
    }
    printf("%d\n",ans);
    return 0;
}