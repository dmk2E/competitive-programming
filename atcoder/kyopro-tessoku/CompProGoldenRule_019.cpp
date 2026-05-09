/*アルゴリズムと工夫点(A19 - Knapsack 1/CPU: 13 ms Memory: 5476 KB  Length: 569 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,w;

int main(){
    int i,j,ww,v;
    scanf("%d%d",&n,&w);
    const int NIL=0;
    vector<ll> last(w+1,NIL);
    rep(i,n){
        vector<ll> now=last;
        scanf("%d%d",&ww,&v);
        rep(j,w+1){
            if(j+ww<w+1&&now[j+ww]<last[j]+v){
                now[j+ww]=last[j]+v;
            }
        }
        swap(last,now);
    }
    printf("%lld\n",last[w]);
    return 0;
}