/*アルゴリズムと工夫点(Divide Interval/CPU: 1 ms Memory: 3872 KB  Length: 1153 B)
できるだけ広く半開区間をとっていく貪欲法。繰り返し二乗法や二分探索を用いて所々高速化した。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_M 1000
using namespace std;

typedef pair<unsigned long long,unsigned long long> p;

p ans[MAX_M];
unsigned long long l,r;

unsigned long long power(unsigned long long x,int a){
    if(a==0)
        return 1;
    unsigned long long res=power(x*x,a/2);
    if(a%2==1)
        res*=x;
    return res;
}

int count2(unsigned long long x){
    int left=0,right=61,mid;
    while(left<right){
        mid=(left+right)/2;
        if(x%power(2,mid)==0)
            left=mid+1;
        else
            right=mid;
    }
    return left-1;
}

int main(){
    int i,next=0,k;
    unsigned long long j,left,right,mid;
    scanf("%llu%llu",&l,&r);
    while(l<r){
        if(l%2==0)
            i=count2(l);
        else
            i=0;
        ans[next].first=l;
        do{
            j=l/power(2,i);
            i--;
        }while(power(2,i+1)*(j+1)>r);
        l=ans[next].second=power(2,i+1)*(j+1);
        next++;
    }
    printf("%d\n",next);
    rep(i,next)
        printf("%llu %llu\n",ans[i].first,ans[i].second);
    return 0;
}