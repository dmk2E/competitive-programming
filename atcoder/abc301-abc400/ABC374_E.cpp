/*アルゴリズムと工夫点(Sensor Optimization Dilemma 2/CPU: 2 ms Memory: 3936 KB  Length: 1398 B)
「それぞれの工程で，製造能力を「W」にするための最小の金額の合計がX以下になるか」という判定条件Pで二分探索．
機械Sの方がTよりも効率が良いとする．この時，TをA個以上買うとすると，Tの方で製造能力はA*B個以上プラスされる．
その内，Aの倍数個分の製造能力を，Sの方が肩代わりすることができ，より少ない金額で購入することができる．
最悪計算量はO(N*max(Ai,Bi)log2(INF))<10^6 となり十分高速．
※(効率)=(1円当たりの製造能力)
※二分探索で解けることは気づいていたが，判定条件をDPでしか考えることができなかった...
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct machine{
    int mer,mny;

    machine(int mmer=0,int mmny=0):mer(mmer),mny(mmny){}
}Machine;

typedef pair<Machine,Machine> p;

int n,x;

int main(){
    int i,j,left,right,mid;
    scanf("%d%d",&n,&x);
    vector<p> ipt(n);
    rep(i,n){
        scanf("%d%d%d%d",&ipt[i].first.mer,&ipt[i].first.mny,&ipt[i].second.mer,&ipt[i].second.mny);
        if(ipt[i].first.mny*ipt[i].second.mer>ipt[i].first.mer*ipt[i].second.mny)swap(ipt[i].first,ipt[i].second);
    }
    const int INF=(int)(1e9)+1;
    auto judge=[&](int w)->bool{
        int i,j,k;
        ll sum=0,tmp,mmin;
        rep(i,n){
            mmin=(ll)1e18;
            rep(j,ipt[i].first.mer){
                k=max(0,w-ipt[i].second.mer*j);
                k=(k+ipt[i].first.mer-1)/ipt[i].first.mer;
                if((tmp=j*ipt[i].second.mny+(ll)k*ipt[i].first.mny)<mmin)
                    mmin=tmp;
            }
            sum+=mmin;
            if(sum>x)return false;
        }
        return true;
    };
    left=0,right=INF;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))
            left=mid+1;
        else
            right=mid;
    }
    printf("%d\n",left-1);
    return 0;
}
/*
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x;

int main(){
    int i,j,ii;
    scanf("%d%d",&n,&x);
    vector<int> a(n),p(n),b(n),q(n);
    rep(i,n)scanf("%d%d%d%d",&a[i],&p[i],&b[i],&q[i]);
    const int MAX_W=(int)(1e9),INF=(int)(1e7)+1;
    vector<vector<int> > dp(n,vector<int>(INF+1,MAX_W));
    rep(i,n){
        dp[i][0]=0;
        rep(j,INF+1){
            if(dp[i][j]!=MAX_W){
                if(dp[i][j]+p[i]<dp[i][j+a[i]]){
                    dp[i][j+a[i]<INF?j+a[i]:INF]=dp[i][j]+p[i];
                }
                if(dp[i][j]+q[i]<dp[i][j+b[i]]){
                    dp[i][j+b[i]<INF?j+b[i]:INF]=dp[i][j]+q[i];
                }
            }
        }
        for(j=INF,ii=dp[i][INF];j>=0;j--){
            if(dp[i][j]<ii)ii=dp[i][j];
            dp[i][j]=ii;
        }
        //if(i==0)rep(j,INF)printf("%d ",dp[i][j]);puts("");
    }
    auto judge=[&](int w)->bool{
        int i,sum=0;
        rep(i,n){
            sum+=dp[i][w];
            if(sum>x)return false;
        }
        return true;
    };
    int left=0,right=INF,mid;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))
            left=mid+1;
        else
            right=mid;
    }
    printf("%d\n",left-1);
    return 0;
}
*/