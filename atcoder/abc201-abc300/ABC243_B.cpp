/*アルゴリズムと工夫点(Hit and Blow/CPU: 1 ms Memory: 3960 KB  Length: 578 B)

*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,ans1,ans2;
    scanf("%d",&n);
    set<int> sa;
    vector<int> a(n);
    rep(i,n){
        scanf("%d",&a[i]);
        sa.insert(a[i]);
    }
    ans1=ans2=0;
    rep(i,n){
        scanf("%d",&j);
        if(sa.find(j)!=sa.end()){
            ans1+=a[i]==j;
            ans2+=a[i]!=j;
        }
    }
    printf("%d\n%d\n",ans1,ans2);
    return 0;
}