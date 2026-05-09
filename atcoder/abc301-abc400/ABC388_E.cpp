/*アルゴリズムと工夫点(Simultaneous Kagamimochi/CPU: 46 ms Memory: 5460 KB  Length: 607 B)
解に単調性が存在するから，二分探索を行う．
問題は判定関数についてで，k個作ると固定した時，適切なk個の選び方が実は貪欲で良いことに考察で気づけるかがカギだった．
左から昇順に並んでいる餅それぞれを，上下下上...のように選んだ時，上を左に詰め，下を右に詰めることができることから，2*k個選んだ時，上下を半分でに分割すればよい．
そして上に選ぶ餅の大きさは小さいほど，下に選ぶ餅は大きいほど良い．よって判定では，前のk個と後ろのk個を選べばよい．
最悪計算量は O(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,left,right,mid;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    auto judge=[&](int k)->bool{
        int i;
        rep(i,k)if(2*a[i]>a[n-k+i])return false;
        return true;
    };
    left=0,right=(n/2)+1;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))left=mid+1;
        else right=mid;
    }
    printf("%d\n",left-1);
    return 0;
}