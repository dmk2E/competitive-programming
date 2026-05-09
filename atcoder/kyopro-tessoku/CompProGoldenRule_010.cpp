/*アルゴリズムと工夫点(Resort Hotel/CPU: 25 ms Memory: 4476 KB  Length: 590 B)
前後それぞれからの累積Maxを前処理で求めておけばよい．
最悪計算量O(N)<10^6 で十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,d;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n),tMax(n),rTMax(n);
    j=0;
    rep(i,n){
        scanf("%d",&a[i]);
        if(j<a[i])j=a[i];
        tMax[i]=j;
    }
    for(i=n-1,j=0;i>=0;i--){
        if(j<a[i])j=a[i];
        rTMax[i]=j;
    }
    scanf("%d",&d);
    while(d--){
        scanf("%d%d",&i,&j);
        printf("%d\n",max(tMax[i-2],rTMax[j]));
    }
    return 0;
}