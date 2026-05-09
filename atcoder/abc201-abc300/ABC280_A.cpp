/*アルゴリズムと工夫点(/CPU:  ms Memory:  KB  Length:  B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j,cnt=0;
    scanf("%d%d",&h,&w);
    rep(i,h){
        getchar();
        rep(j,w)if(getchar()=='#')cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}