/*アルゴリズムと工夫点(Make Them Narrow/CPU: 34 ms Memory: 4144 KB  Length: 465 B)
配列aの最大値と最小値の差をdifとする．difの値は，aを昇順にソートした時の，(右端の値)-(左端の値)となる．
この時，k個消去しなければならないが，difの内，(左端の値)をaiに固定した時のdifの最小値は，a0~ai-1の値を消去し，その上で右端の値から消去できるだけ値を消去した時の右端の値ajとしたとき，dif_min=aj-aiとなる．
従って，固定する(左端の値)の値を順にみていった時のdifの最小値が求める答えとなる．
最悪計算量はO(N*log2(N)+k)
*/
#include<iostream>
#include<algorithm>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,k;

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    vector<int> a(n);
    rep(i,n)
        scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    j=0;
    for(i=0;i<=k;i++){
        if(a[n-1-k+i]-a[i]<a[n-1-k+j]-a[j])
            j=i;
    }
    printf("%d\n",a[n-1-k+j]-a[j]);
    return 0;
}