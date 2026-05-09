/*アルゴリズムと工夫点(Circular Playlist/CPU: 11 ms Memory: 4092 KB  Length: 673 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll t,a;
vector<ll> sum;

int search(){
    int left=0,right=n+1,mid;
    while(left<right){
        mid=(left+right)/2;
        if(sum[mid]<=t)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i;
    scanf("%d%lld",&n,&t);
    sum=vector<ll>(n+1);
    sum[0]=0;
    rep(i,n){
        scanf("%lld",&a);
        sum[i+1]=a+sum[i];
    }
    t%=sum[n];
    t-=sum[(i=search())-1];
    printf("%d %lld\n",i,t);
    return 0;
}