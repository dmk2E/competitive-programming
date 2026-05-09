/*アルゴリズムと工夫点(Matrix Transposition/CPU: 21 ms Memory: 8796 KB  Length: 426 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<vector<int> > a(h,vector<int>(w));
    rep(i,h)rep(j,w)scanf("%d",&a[i][j]);
    rep(i,w){
        rep(j,h-1)printf("%d ",a[j][i]);
        printf("%d\n",a[j][i]);
    }
    return 0;
}