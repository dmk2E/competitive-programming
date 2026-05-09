/*アルゴリズムと工夫点(Typical Shop（★5）/CPU: 216 ms Memory: 23656 KB  Length: 1624 B)
「半分全列挙」というアルゴリズムを知っていたため，初見ACできた．個数ごとに値段の合計を保持しておき，昇順にソートして，片方の(個数,値段)を固定した時，合計の値段がP以下となる個数を二分探索する．
最悪計算量はO(n/2*2^(n/2)+2^(n/2)*log2(2^n))=O(n*2^(n/2))≒10^7<10^8 となり，高速．
※オーバーフローに気づかず，3回WAorREとなってしまった．気を付けたい．
*/
#include<iostream>
#include<algorithm>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_K 40
using namespace std;

typedef long long ll;

int k,n;
ll p;
vector<ll> first[MAX_K+1],second[MAX_K+1];

void bitBruteForce(vector<ll>& tmp,vector<ll> saving[MAX_K+1]){
    int i,j,cnt;
    long long sum;
    rep(i,1<<tmp.size()){
        sum=cnt=0;
        j=0;
        while((1<<j)<=i){
            if((1<<j)&i){
                cnt++;
                sum+=tmp[j];
            }
            j++;
        }
        saving[cnt].push_back(sum);
    }
}

long long search(ll value,int cnt){
    int left=0,right=second[k-cnt].size(),mid;
    while(left<right){
        mid=(left+right)/2;
        if(second[k-cnt][mid]+value<=p)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i,j;
    ll ans=0;
    vector<ll> tmp;
    scanf("%d%d%lld",&n,&k,&p);
    tmp=vector<ll>((n+1)/2);
    rep(i,(n+1)/2){
        scanf("%lld",&tmp[i]);
    }
    bitBruteForce(tmp,first);
    tmp=vector<ll>(n/2);
    rep(i,n/2){
        scanf("%lld",&tmp[i]);
    }
    bitBruteForce(tmp,second);
    rep(i,k+1)//n/2+1
        sort(second[i].begin(),second[i].end());
    //rep(i,(n+1)/2+2){printf("%d:",i);rep(j,first[i].size())printf("%lld ",first[i][j]);puts("");}
    //rep(i,n/2+2){printf("%d:",i);rep(j,second[i].size())printf("%lld ",second[i][j]);puts("");}
    rep(i,k+1){
        rep(j,first[i].size()){
            ans+=search(first[i][j],i);
        }
    }
    printf("%lld\n",ans);
    return 0;
}