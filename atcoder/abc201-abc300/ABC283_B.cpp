/*アルゴリズムと工夫点(First Query Problem/CPU: 32 ms Memory: 3820 KB  Length: 555 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;
vector<int> a;

int main(){
    int i,j;
    scanf("%d",&n);
    a=vector<int>(n);
    rep(i,n)
        scanf("%d",&a[i]);
    scanf("%d",&q);
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d%d",&i,&j);
            a[i-1]=j;
        }else{
            scanf("%d",&i);
            printf("%d\n",a[i-1]);
        }
    }
    return 0;
}