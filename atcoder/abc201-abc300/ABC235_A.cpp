/*アルゴリズムと工夫点(Rotate/CPU: 1 ms Memory: 3904 KB  Length: 369 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;


int main(){
    int i,ans=0;
    vector<int> abc(3);
    rep(i,3)scanf("%1d",&abc[i]);
    rep(i,3){
        ans+=abc[i]*100+abc[(i+1)%3]*10+abc[(i+2)%3];
    }
    printf("%d\n",ans);
    return 0;
}