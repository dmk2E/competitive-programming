/*アルゴリズムと工夫点(LIS/CPU: 12 ms Memory: 3916 KB  Length: 574 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_A (int)(5e5)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,a;

int main(){
    int i,j,ans;
    scanf("%d",&n);
    vector<int> len(n+1,MAX_A+1);
    len[0]=0;
    ans=0;
    rep(i,n){
        scanf("%d",&a);
        j=lower_bound(len.begin(),len.begin()+ans+1,a)-len.begin();
        if(a<len[j]){
            len[j]=a;
            ans=max(j,ans);
        }
    }
    printf("%d\n",ans);
    return 0;
}