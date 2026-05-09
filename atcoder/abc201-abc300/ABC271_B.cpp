/*アルゴリズムと工夫点(Maintain Multiple Sequences/CPU: 90 ms Memory: 14344 KB  Length: 509 B)

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
    vector<vector<int> > ipt(n);
    rep(i,n){
        scanf("%d",&j);
        ipt[i]=vector<int>(j);
        while(j--)scanf("%d",&ipt[i][(int)ipt[i].size()-j-1]);
    }
    while(q--){
        scanf("%d%d",&i,&j);
        printf("%d\n",ipt[i-1][j-1]);
    }
    return 0;
}