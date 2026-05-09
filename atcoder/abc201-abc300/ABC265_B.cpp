/*アルゴリズムと工夫点(Explore/CPU: 26 ms Memory: 4108 KB  Length: 616 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;
ll t;

int main(){
    int i,j;
    scanf("%d%d%lld",&n,&m,&t);
    vector<int> a(n-1),bonus(n-1,0);
    rep(i,n-1)scanf("%d",&a[i]);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;
        bonus[i]=j;
    }
    i=0;
    while(i<n-1){
        //printf("i:%d t:%lld\n",i,t);
        t+=bonus[i];
        if(t>a[i])t-=a[i];
        else break;
        i++;
    }
    printf("%s\n",i==n-1?"Yes":"No");
    return 0;
}