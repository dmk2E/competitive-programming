/*アルゴリズムと工夫点(Counting 2/CPU: 89 ms Memory: 4056 KB  Length: 467 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    while(q--){
        scanf("%d",&j);
        printf("%d\n",(int)(a.end()-lower_bound(a.begin(),a.end(),j)));
    }
    return 0;
}