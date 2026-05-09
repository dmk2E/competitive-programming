/*アルゴリズムと工夫点(部員の変遷/CPU: 0 ms Memory: 3572 KB  Length: 553 B)
連続した3年分の入部人数の最大値を求めればよい．
1テストケース当たりの最悪計算量は，O(n) となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,sum,ans;
    while(1){
        scanf("%d",&n);
        if(!n)break;
        vector<int> a(n);
        rep(i,n)scanf("%d",&a[i]);
        sum=0;
        rep(i,3)sum+=a[i];
        ans=sum;
        for(i=3;i<n;i++){
            sum-=a[i-3];
            sum+=a[i];
            ans=max(ans,sum);
        }
        printf("%d\n",ans);
    }
    return 0;
}