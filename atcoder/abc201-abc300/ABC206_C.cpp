/*アルゴリズムと工夫点(Swappable/CPU: 62 ms Memory: 8060 KB  Length: 2330 B)
入力される最大N種類のAiの値それぞれについて、個数cnt[Ai]を保存しておく。そうすると求める値は、入れ替える対象の一つをAiと固定した時、cnt[Ai]*(cnt[Aj]+cnt[Aj+1]+...)(i<j)となる。ここで、cnt[Aj]+cnt[Aj+1]+...の部分は
前処理で累積和を計算しておくことで、高速化できる。ただし、Aiの値は最大10^9となるから、単純に0~max(Ai)の連続した区間の一次元配列として配列cntをとることはできない。そこで、座標圧縮を行う。
結果として、最悪計算量は O(N*log2(N))<10^7 となり、高速。
※C言語に書き直せるようなコーディングを久しぶりにやってみた。
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 300000
using namespace std;

class PriorityQueue{
    int h;
    vector<int> PQ;
public:
    PriorityQueue(int n=0):h(0){
        PQ.resize(n);
    }

    int size(){
        return h;
    }

    void insert(int x){
        int now;
        now=h;
        PQ[h++]=x;
        while(now>0&&PQ[now]<PQ[(now-1)/2]){
            swap(PQ[now],PQ[(now-1)/2]);
            now=(now-1)/2;
        }
    }

    int extractMin(){
        int min=PQ[0],now,smallest;
        PQ[now=0]=PQ[--h];
        while(1){
            if(2*now+1<h&&PQ[now]>PQ[2*now+1])
                smallest=2*now+1;
            else
                smallest=now;
            if(2*now+2<h&&PQ[smallest]>PQ[2*now+2])
                smallest=2*now+2;
            if(now==smallest)
                break;
            swap(PQ[now],PQ[smallest]);
            now=smallest;
        }
        return min;
    }
};

int n,a,i2A[3*MAX_N],i2Sum[3*MAX_N+1]={0},nxt=0,sset[MAX_N],nnxt=0;

int a2I(int a){
    int left=0,right=nxt,mid;
    while(left<right){
        mid=(left+right)/2;
        if(i2A[mid]<a)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i;
    long long sum=0;
    scanf("%d",&n);
    PriorityQueue PQ(n);
    while(n--){
        scanf("%d",&a);
        PQ.insert(a);
    }
    a=PQ.extractMin();
    i2A[nxt++]=a-1;
    i2A[nxt++]=a;
    i2A[nxt++]=a+1;
    i2Sum[a2I(a+1)]++;
    sset[nnxt++]=a;
    while(PQ.size()){
        a=PQ.extractMin();
        if(a-1>i2A[nxt-1])
            i2A[nxt++]=a-1;
        if(a>i2A[nxt-1]){
            i2A[nxt++]=a;
        }
        if(a+1>i2A[nxt-1])
            i2A[nxt++]=a+1;
        i2Sum[a2I(a+1)]++;
        if(sset[nnxt-1]<a)
            sset[nnxt++]=a;
    }
    rep(i,nxt)
        i2Sum[i+1]+=i2Sum[i];
    //rep(i,nxt-1)printf("%2d ",i2A[i]);printf("%2d\n",i2A[i]);
    //rep(i,nxt-1)printf("%2d ",i2Sum[i]);printf("%2d\n",i2Sum[i]);
    //rep(i,nnxt-1)printf("%2d ",sset[i]);printf("%2d\n",sset[i]);
    rep(i,nnxt)
        sum+=(long long)(i2Sum[a2I(sset[i])+1]-i2Sum[a2I(sset[i])])*(i2Sum[nxt]-i2Sum[a2I(sset[i])+1]);
    printf("%lld\n",sum);
    return 0;
}