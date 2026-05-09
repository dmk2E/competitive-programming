/*アルゴリズムと工夫点(Subset Sum/CPU: 2 ms Memory: 3852 KB  Length: 492 B)
部分和問題．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,s;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&s);
    vector<bool> last(s+1,false);
    last[0]=true;
    rep(i,n){
        scanf("%d",&j);
        vector<bool> now=last;
        rep(k,s+1)if(last[k]&&k+j<=s)now[k+j]=true;
        swap(now,last);
    }
    printf("%s\n",last[s]?"Yes":"No");
    return 0;
}