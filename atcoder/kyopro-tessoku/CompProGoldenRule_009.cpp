/*アルゴリズムと工夫点(Winter in ALGO Kingdom/CPU: 72 ms Memory: 21624 KB  Length: 693 B)
二次元imos法の基本問題．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w,n;

int main(){
    int i,j,k,l;
    scanf("%d%d%d",&h,&w,&n);
    vector<vector<int> > snow(h+1,vector<int>(w+1,0));
    while(n--){
        scanf("%d%d%d%d",&i,&j,&k,&l);
        i--;j--;k--;l--;
        snow[i][j]++;
        snow[i][l+1]--;
        snow[k+1][j]--;
        snow[k+1][l+1]++;
    }
    rep(i,h)rep(j,w)snow[i][j+1]+=snow[i][j];
    rep(j,w)rep(i,h)snow[i+1][j]+=snow[i][j];
    rep(i,h){
        rep(j,w-1)printf("%d ",snow[i][j]);
        printf("%d\n",snow[i][j]);
    }
    return 0;
}