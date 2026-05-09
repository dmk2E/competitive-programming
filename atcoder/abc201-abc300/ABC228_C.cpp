/*アルゴリズムと工夫点(Final Day/CPU: 35 ms Memory: 4576 KB  Length: 864 B)
生徒毎に3日間の合計点数sumをもっておく．ある生徒iが上位k位に入れるかは，4日目のテストでその生徒が満点で，他の生徒が0点だった時の順位aを元に考えればよい．
sumを昇順に並べ替え，sum[i]+300より大きくなるsum上の添え字jは，二分探索で求めることができ，それを元にaは計算できる．
従って，最悪計算量は O(N*log2(N))≒10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,k;

int main(){
    int i,j,ii;
    scanf("%d%d",&n,&k);
    vector<int> sum(n);
    vector<p> d(n);
    rep(i,n){
        sum[i]=0;
        rep(j,3){
            scanf("%d",&ii);
            sum[i]+=ii;
        }
        d[i]=p(sum[i],i);
    }
    auto judge=[&](int id)->bool{
        int left=0,right=n,mid;
        while(left<right){
            mid=(left+right)/2;
            if(d[mid].first<=sum[id]+300)
                left=mid+1;
            else
                right=mid;
        }
        return n-left+1<=k;
    };
    sort(d.begin(),d.end());
    rep(i,n)printf("%s\n",judge(i)?"Yes":"No");
    return 0;
}