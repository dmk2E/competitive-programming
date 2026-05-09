/*アルゴリズムと工夫点(How Many Guests?/CPU: 29 ms Memory: 3928 KB  Length: 475 B)
累積和の基本問題．C++だと，標準入力時に累積和作成の工夫ができる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<int> sum(n+1);
    sum[0]=0;
    rep(i,n){
        scanf("%d",&sum[i+1]);
        sum[i+1]+=sum[i];
    }
    while(q--){
        scanf("%d%d",&i,&j);
        i--;j--;
        printf("%d\n",sum[j+1]-sum[i]);
    }
    return 0;
}