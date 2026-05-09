/*アルゴリズムと工夫点(Range Swap/CPU: 12 ms Memory: 3860 KB  Length: 582 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,p,q,r,s;

int main(){
    int i,j;
    scanf("%d%d%d%d%d",&n,&p,&q,&r,&s);
    p--;q--;r--;s--;
    vector<int> a(n),b;
    rep(i,n)
        scanf("%d",&a[i]);
    rep(i,n){
        if(p<=i&&i<=q)
            b.push_back(a[r+i-p]);
        else if(r<=i&&i<=s)
            b.push_back(a[i-r+p]);
        else
            b.push_back(a[i]);
    }
    rep(i,n-1)
        printf("%d ",b[i]);
    printf("%d\n",b[i]);
    return 0;
}