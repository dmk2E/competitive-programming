/*アルゴリズムと工夫点(Find Takahashi/CPU: 1 ms Memory: 3952 KB  Length: 378 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,h;

int main(){
    int i,j,maxH=-1,maxI;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&h);
        if(maxH<h){
            maxH=h;
            maxI=i;
        }
    }
    printf("%d\n",maxI+1);
    return 0;
}