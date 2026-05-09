/*アルゴリズムと工夫点(1D Pawn/CPU: 1 ms Memory: 3884 KB  Length: 662 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k,q;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&k,&q);
    vector<int> a(k);
    vector<bool> mmap(n,false);
    rep(i,k){
        scanf("%d",&a[i]);
        a[i]--;
        mmap[a[i]]=true;
    }
    while(q--){
        scanf("%d",&i);
        i--;
        if(a[i]==n-1||mmap[a[i]+1])continue;
        mmap[a[i]]=false;
        mmap[a[i]+1]=true;
        a[i]++;
    }
    rep(i,k-1)printf("%d ",a[i]+1);
    printf("%d\n",a[i]+1);
    return 0;
}