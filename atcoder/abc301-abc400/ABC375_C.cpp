/*アルゴリズムと工夫点(Spiral Rotation/CPU: 138 ms Memory: 29816 KB  Length: 575 B)
正方形単位で回転させる操作を，正方形の1辺の長さを2ずつ減らして行っていくイメージ．
なので，正方形の隅1周ずつで，0~3回回転させればよい．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,k,ii,jj;
    scanf("%d",&n);
    vector<string> mmap(n),ans;
    rep(i,n)cin>>mmap[i];
    ans=mmap;
    rep(i,n)rep(j,n){
        ii=i;jj=j;
        k=min(min(ii+1,jj+1),min(n-ii,n-jj));
        k%=4;
        while(k--){
            swap(ii,jj);
            jj=n-1-jj;
        }
        ans[ii][jj]=mmap[i][j];
    }
    rep(i,n)cout<<ans[i]<<'\n';
    return 0;
}