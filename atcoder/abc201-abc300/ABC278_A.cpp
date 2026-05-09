/*アルゴリズムと工夫点(Shift/CPU: 1 ms Memory: 3924 KB  Length: 388 B)
k回だけ「0」を追加して，k個目以降を出力すれば，最悪計算量O(N+K)で解ける．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    rep(i,k)a.push_back(0);
    rep(i,n-1)printf("%d ",a[k+i]);
    printf("%d\n",a[k+i]);
    return 0;
}