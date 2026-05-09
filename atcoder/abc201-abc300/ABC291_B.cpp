/*アルゴリズムと工夫点(Trimmed Mean/CPU: 1 ms Memory: 3796 KB  Length: 379 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n;

int main(){
    int i,sum=0;
    scanf("%d",&n);
    vector<int> x(5*n);
    rep(i,5*n)
        scanf("%d",&x[i]);
    sort(x.begin(),x.end());
    rep(i,3*n)
        sum+=x[i+n];
    printf("%.6f\n",(double)sum/(3*n));
    return 0;
}