/*アルゴリズムと工夫点(Mex/CPU: 1 ms Memory: 3900 KB  Length: 412 B)

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
    int i,j;
    scanf("%d",&n);
    vector<int> a2Cnt(n+1,0);
    rep(i,n){
        scanf("%d",&j);
        a2Cnt[j]++;
    }
    rep(i,n+1)if(a2Cnt[i]==0)break;
    printf("%d\n",i);
    return 0;
}