/*アルゴリズムと工夫点(The Kth Time Query/CPU: 274 ms Memory: 41264 KB  Length: 474 B)

*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    map<int,vector<int> > v;
    rep(i,n){
        scanf("%d",&j);
        v[j].push_back(i);
    }
    while(q--){
        scanf("%d%d",&i,&j);
        printf("%d\n",j-1<(int)v[i].size()?v[i][j-1]+1:-1);
    }
    return 0;
}