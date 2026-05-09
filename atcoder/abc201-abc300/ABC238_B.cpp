/*アルゴリズムと工夫点(Pizza/CPU: 1 ms Memory: 3820 KB  Length: 621 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,k;
    scanf("%d",&n);
    vector<int> args(n+1);
    const int MAX_ARG=360,MIN=-1;
    j=0;
    args[0]=j;
    rep(i,n){
        scanf("%d",&k);
        args[i+1]=(k+j)%MAX_ARG;
        j=args[i+1];
    }
    sort(args.begin(),args.end());
    j=MIN;
    rep(i,n)
        j=max(j,abs(args[i]-args[(i+1)%(n+1)]));
    j=max(j,MAX_ARG-args[i]+args[0]);
    printf("%d\n",j);
    return 0;
}