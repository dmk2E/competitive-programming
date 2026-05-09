/*アルゴリズムと工夫点(Mod Sigma Problem/CPU: 28 ms Memory: 4968 KB  Length: 1052 B)
方針は公式解説と同じ．
・0<= X mod M <=M-1 ということ
・「mod M の世界において負の数になったらMを足す」
この2点に注意して，累積和・時系列処理を用いた問題．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class BinaryIndexedTree{
    vector<int> bit;
public:
    BinaryIndexedTree(int n){
        bit=vector<int>(n+1,0);
    }

    void add(int id,int a){
        while(id<(int)bit.size()){
            bit[id]+=a;
            id+=id&(-id);
        }
    }

    int sum(int id){//sum[0,id]
        int ans=0;
        while(id>0){
            ans+=bit[id];
            id-=id&(-id);
        }
        return ans;
    }
}BIT;

int n,m;

int main(){
    int i;
    ll ans=0,sumL=0;
    scanf("%d%d",&n,&m);
    vector<int> sum(n+1);
    BIT bit(m);
    sum[0]=0;
    rep(i,n){
        scanf("%d",&sum[i+1]);
        sum[i+1]=((sum[i+1]%m)+(sum[i]%m))%m;
    }
    for(i=1;i<=n;i++){
        ans+=(ll)sum[i]*i-sumL+(ll)m*(bit.sum(m)-bit.sum(sum[i]+1));
        bit.add(sum[i]+1,1);
        sumL+=sum[i];
    }
    printf("%lld\n",ans);
    return 0;
}