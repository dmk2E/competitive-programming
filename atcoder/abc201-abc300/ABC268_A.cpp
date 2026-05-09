/*アルゴリズムと工夫点(Five Integers/CPU: 1 ms Memory: 3864 KB  Length: 333 B)

*/
#include<iostream>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int ipt;

int main(){
    int i;
    set<int> v;
    rep(i,5){
        scanf("%d",&ipt);
        v.insert(ipt);
    }
    printf("%d\n",(int)v.size());
    return 0;
}