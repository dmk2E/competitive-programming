/*アルゴリズムと工夫点(Go Straight and Turn Right/CPU: 8 ms Memory: 3972 KB  Length: 509 B)

*/
#include<iostream>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    set<int> unused;
    rep(i,2*n+1)unused.insert(i+1);
    while(1){
        i=*unused.begin();
        printf("%d\n",i);
        cout<<flush;
        unused.erase(i);
        scanf("%d",&i);
        if(i==0)break;
        unused.erase(i);
    }
    return 0;
}