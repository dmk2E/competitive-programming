/*アルゴリズムと工夫点(Jumping Takahashi/CPU: 2 ms Memory: 3868 KB  Length: 651 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,a,b,x;

int main(){
    int i,j;
    scanf("%d%d",&n,&x);
    vector<bool> now(x+1,false);
    now[0]=true;
    rep(i,n){
        scanf("%d%d",&a,&b);
        vector<bool> tmp(x+1,false);
        rep(j,x+1){
            if(now[j]){
                if(j+a<=x)tmp[j+a]=true;
                if(j+b<=x)tmp[j+b]=true;
            }
        }
        swap(now,tmp);
    }
    printf("%s\n",now[x]?"Yes":"No");
    return 0;
}