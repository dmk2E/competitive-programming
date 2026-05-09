/*アルゴリズムと工夫点(Takahashi's Solitaire/CPU: 38 ms Memory: 6216 KB  Length: 1108 B)
配列Aを昇順にソートし，同じ値はまとめて(値，個数)の形にランレングス圧縮を行ったものをrlとする．
rlを用いてゲームのシミュレーションを行ってみると，「この問題は(x->(x+1)%mの順で)連続する「値」を，好きな位置から出来なくなるまで除去した時の，残っているAiの総和の最小値を求めよ」という問題に帰着できる．
よって，始める位置を全て試してシミュレーションをし，解を出せばよい．この時，一度でも除去したことがある「値」からは始めないようにすること．
最悪計算量はO(N*log2(N))≒10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,m;

int main(){
    int i,j,now;
    ll sum=0,ans,tmp;
    scanf("%d%d",&n,&m);
    vector<int> a(n);
    rep(i,n){scanf("%d",&a[i]);sum+=a[i];}
    sort(a.begin(),a.end());
    vector<p> rl;
    i=0;
    while(i<n){
        rl.push_back(p(a[i],0));
        while(i<n&&rl[rl.size()-1].first==a[i]){
            rl[rl.size()-1].second++;
            i++;
        }
    }
    ans=sum;
    i=0;
    while(i<rl.size()){
        tmp=0;
        j=i;
        now=rl[j].first;
        do{
            tmp+=(ll)rl[j].first*rl[j].second;
            j=(j+1)%rl.size();
            now=(now+1)%m;
        }while(i!=j&&now==rl[j].first);
        if(ans>sum-tmp)ans=sum-tmp;
        //printf("%d->%d\n",i,j);
        if(i<j)i=j;
        else break;
    }
    //rep(i,rl.size())printf("(%d,%d)",rl[i].first,rl[i].second);puts("");
    printf("%lld\n",ans);
    return 0;
}