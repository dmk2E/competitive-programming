/*アルゴリズムと工夫点(Range Count Query/CPU: 119 ms Memory: 11976 KB  Length: 621 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q,l,r,x;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<vector<int> > a2Ids(n);
    rep(i,n){
        scanf("%d",&j);
        a2Ids[j-1].push_back(i);
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d",&l,&r,&x);
        l--;r--;x--;
        printf("%ld\n",upper_bound(a2Ids[x].begin(),a2Ids[x].end(),r)-lower_bound(a2Ids[x].begin(),a2Ids[x].end(),l));
    }
    return 0;
}