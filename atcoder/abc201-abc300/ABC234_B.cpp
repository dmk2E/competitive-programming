/*アルゴリズムと工夫点(Longest Segment/CPU: 1 ms Memory: 3904 KB  Length: 485 B)

*/
#include<iostream>
#include<vector>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    double max=-1.0;
    scanf("%d",&n);
    vector<int> y(n),x(n);
    rep(i,n)scanf("%d%d",&x[i],&y[i]);
    rep(i,n)rep(j,i){
        if(max<hypot(y[i]-y[j],x[i]-x[j]))
            max=hypot(y[i]-y[j],x[i]-x[j]);
    }
    printf("%.7f\n",max);
    return 0;
}