/*アルゴリズムと工夫点(Who is missing?/CPU: 32 ms Memory: 3860 KB  Length: 395 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> x2Cnt(n,0);
    rep(i,4*n-1){
        scanf("%d",&j);
        x2Cnt[j-1]++;
    }
    rep(i,n)if(x2Cnt[i]!=4)break;
    printf("%d\n",i+1);
    return 0;
}