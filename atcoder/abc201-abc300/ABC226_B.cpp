/*アルゴリズムと工夫点(Counting Arrays/CPU: 123 ms Memory: 22396 KB  Length: 489 B)

*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,l;
set<vector<int> > v;

int main(){
    int i,j;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&l);
        vector<int> a;
        rep(i,l){
            scanf("%d",&j);
            a.push_back(j);
        }
        v.insert(a);
    }
    printf("%d\n",(int)v.size());
    return 0;
}