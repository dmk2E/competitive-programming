/*アルゴリズムと工夫点(短歌数/CPU: 0 ms Memory: 3404 KB  Length: 2595 B)
先頭の桁から値を、パターン数に基づいて順次決めていく方針で解ける。
※power関数を用いて高速化しておく。
※long long型で耐えられるか定かではない時、unsigned long long型で計算するようにする。
※アルゴリズム自体はあっていたが、デバッグで時間をかけすぎてしまった。
*/
#include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_D 54
#define MAX_N (1e18)
using namespace std;

unsigned long long n,cnt[MAX_D+1];//cnt[i]:i桁ある数字で条件を満たすパターン数

unsigned long long power(unsigned long long x,int a){
    if(a==0)
        return 1;
    unsigned long long temp=power(x*x,a/2);
    if(a%2==1)
        temp*=x;
    return temp;
}

int init(){
    int i;
    unsigned long long sum;
    cnt[0]=cnt[1]=0;sum=cnt[2]=81;
    for(i=3;i<MAX_D+1;i++){
        cnt[i]=81*(power(2,i-2)+power(2,i-2)-1);
        sum+=cnt[i];
        if(sum>=MAX_N)
            break;
    }
    return i;
}

void search(int d,unsigned long long now){//now+1番目からi桁の数字
    //printf("now:%llu\n",now);
    int i,j,small,large;
    unsigned long long sum=0;
    bool flag=true;
    vector<int> ans(d);
    rep(i,9){//先頭の桁の数字がi+1かどうか判定
        sum+=9*(power(2,d-1)-1);
        if(now+sum>=n)
            break;
    }
    ans[0]=i+1;
    sum-=9*(power(2,d-1)-1);
    now+=sum;sum=0;
    for(j=1;j<d;j++){
        //printf("now:%llu\n",now);
        if(flag){   //使う数字の種類が1つしか決まってない時
            rep(i,10){
                if(i==ans[0])
                    sum+=d-1-j>0?9*(power(2,d-1-j)-1):0;
                else
                    sum+=d-1-j>0?(power(2,d-1-j)):1;
                if(now+sum>=n)
                    break;
            }
            ans[j]=i;
            flag=ans[j]==ans[0];
            sum-=i==ans[0]?d-1-j>0?9*(power(2,d-1-j)-1):0:d-1-j>0?(power(2,d-1-j)):1;
            now+=sum;sum=0;
            if(flag==false){
                if(ans[0]<ans[j]){
                    small=ans[0];
                    large=ans[j];
                }else{
                    large=ans[0];
                    small=ans[j];
                }
            }
        }else{
            rep(i,2){
                sum+=d-1-j>=0?power(2,d-1-j):1;
                if(now+sum>=n)
                    break;
            }
            ans[j]=i==0?small:large;
            sum-=d-1-j>=0?power(2,d-1-j):1;
            now+=sum;sum=0;
        }
    }
    rep(i,ans.size()){
        printf("%d",ans[i]);
    }
    puts("");
    return ;
}

int main(){
    int i,len;
    unsigned long long sum=0;
    len=init();
    len++;
    //rep(i,len){sum+=cnt[i];printf("%d桁:%llu sum:%llu\n",i,cnt[i],sum);}return 0;
    while(1){
        scanf("%llu",&n);
        if(!n)
            break;
        sum=0;
        for(i=2;i<MAX_D+1;i++){//i桁あると探索する。
            sum+=cnt[i];
            if(n<=sum)
                break;
        }
        //printf("%d\n",i);
        search(i,sum-cnt[i]);
    }
    return 0;
}