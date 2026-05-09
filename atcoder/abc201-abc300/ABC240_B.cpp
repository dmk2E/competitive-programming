/*アルゴリズムと工夫点(Count Distinct Integers/CPU: 1 ms Memory: 3928 KB  Length: 352 B)

*/
#include<iostream>
#include<set>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    set<int> v;
    rep(i,n){
        scanf("%d",&j);
        v.insert(j);
    }
    printf("%d\n",(int)v.size());
    return 0;
}