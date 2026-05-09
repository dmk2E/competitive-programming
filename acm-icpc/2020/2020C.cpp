/*アルゴリズムと工夫点(荷物/CPU: 5280 ms Memory: 45384 KB  Length: 3267 B)
<i>まず,使う素数を全列挙しておく.
<ii>pを素数の積に変換し,ccount配列に保持.
<iii>ccount配列を元に部分積をDPで求め,productに保持しておく.
<iv>productの中で,p^(1/3)に近い値を中心に100個選択し,その中の一つでhと固定し,今度はp/hに対し,<ii>～<iii>と同様の処理をする.
<v>pproductの中でp^(1/3)に近い値を中心に100個数選択し,dを固定すると,(w,d,h)の3つ全てが定まる.
※素因数分解して,(w,d)それぞれの素数の累乗の数について全探索する方が早い.
*/
#include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_PRIME 31622778
#define MAX_C 51
using namespace std;

long long p,ccount[MAX_C],cccount[MAX_C];
bool isPrime[MAX_PRIME+1];
vector<int> prime;

void init(){
    int i,j;
    rep(i,MAX_PRIME+1)
        isPrime[i]=true;
    isPrime[0]=isPrime[1]=false;
    for(i=2;i<MAX_PRIME+1;i++){
        if(isPrime[i]){
            prime.push_back(i);
            j=2*i;
            while(j<MAX_PRIME+1){
                isPrime[j]=false;
                j+=i;
            }
        }
    }
}

int setCount(long long p,long long ccount[MAX_C]){
    int i,now=0;
    //int max=(int)sqrt(p)+1;
    long long pp=p;
    ccount[now++]=1;
    rep(i,prime.size()){
        if((long long)prime[i]>pp)
            break;
        while((pp%prime[i])==0){
            ccount[now++]=prime[i];
            pp/=prime[i];
        }
    }
    if(now==1&&pp!=1)
        ccount[now++]=pp;
    return now;
}

int search(long long x,const vector<long long>& product){
    int left=0,right=product.size(),mid;
    double y=pow(x,1.0/3);
    while(left<right){
        mid=(left+right)/2;
        if((double)product[mid]<y)//product[mid]^3<x
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i,maxC,j,k,l,maxCC;
    long long pp,min,ccnt;
    init();
    //pp=1;i=0;while(pp<1000000000000000){pp*=prime[i];i++;}printf("%lld\n",pp/prime[i-1]);return 0;
    while(1){
        scanf("%lld",&p);
        if(p==0)
            break;
        map<long long,bool> prev;
        maxC=setCount(p,ccount);
        vector<long long> product;
        //rep(i,maxC)printf("%lld ",ccount[i]);puts("");
        prev[ccount[0]]=true;
        for(i=1;i<maxC;i++){
            map<long long,bool> now;
            for(pair<long long,bool> x:prev){
                now[x.first]=true;
                now[x.first*ccount[i]]=true;
            }
            swap(prev,now);
        }
        for(pair<long long,bool> x:prev)
            product.push_back(x.first);
        //printf("size:%d\n",(int)prev.size());for(pair<long long,bool> x:prev)printf("%lld\n",x.first);puts("");
        i=search(p,product);
        for(min=LLONG_MAX,j=0,i=i-50>=0?i-50:0;i<product.size()&&j<100;j++,i++){
            pp=p/product[i];
            maxCC=setCount(pp,cccount);
            vector<long long> pproduct;
            map<long long,bool> prev;
            prev[cccount[0]]=true;
            for(k=1;k<maxCC;k++){
                map<long long,bool> now;
                for(pair<long long,bool> x:prev){
                    now[x.first]=true;
                    now[x.first*cccount[k]]=true;
                }
                swap(prev,now);
            }
            for(pair<long long,bool> x:prev)
                pproduct.push_back(x.first);
            k=search(p,pproduct);
            //printf("h=%lld ",product[i]);printf("size:%d\n",(int)prev.size());for(pair<long long,bool> x:prev)printf("%lld\n",x.first);puts("");continue;
            for(l=0,k=k-50>=0?k-50:0;k<pproduct.size()&&l<100;l++,k++){
                if(min>product[i]+pproduct[k]+pp/pproduct[k])
                    min=product[i]+pproduct[k]+pp/pproduct[k];
            }
        }
        printf("%lld\n",min);
    }
    return 0;
}