/*アルゴリズムと工夫点(Souvenirs/CPU: 76 ms Memory: 7344 KB  Length: 1561 B)
A,Bの二つともソートするだけで解けるらしい...．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define NIL -1
using namespace std;

int n,m;

int search(int b,vector<int>& a,vector<bool>& flag){
    int left=0,right=n,mid;
    while(left<right){
        mid=(left+right)/2;
        if(b>a[mid])
            left=mid+1;
        else
            right=mid;
    }
    if(left==n)
        return NIL;
    return left;
}

int main(){
    int i,j;
    long long ans=0;
    scanf("%d%d",&n,&m);
    vector<int> a(n),b(m),cnt(n,0);
    vector<long long> sum(n+1);
    vector<bool> flag(n,false);
    rep(i,n){
        scanf("%d",&a[i]);
    }
    rep(i,m){
        scanf("%d",&b[i]);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    ans=0;
    rep(i,m){
        if((j=search(b[i],a,flag))!=NIL)
            cnt[j]++;
        else{
            printf("%d\n",NIL);
            return 0;
        }
    }
    sum[0]=0;
    rep(i,n)
        sum[i+1]=sum[i]+a[i];
    j=0;
    //rep(i,n+1)printf("%lld ",sum[i]);puts("");
    rep(i,n){
        //printf("%d ",cnt[i]);
        if(cnt[i]>0){
            if(j<=i){
                if(i+cnt[i]>n)
                    break;
                ans+=sum[i+cnt[i]]-sum[i];
                j=i+cnt[i];
            }else{
                if(j+cnt[i]>n)
                    break;
                ans+=sum[j+cnt[i]]-sum[j];
                j=j+cnt[i];
            }
        }
    }
    //puts("");
    printf("%lld\n",i==n?ans:NIL);
    return 0;
}