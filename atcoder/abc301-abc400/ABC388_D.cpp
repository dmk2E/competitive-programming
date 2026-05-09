/*アルゴリズムと工夫点(Coming of Age Celebration/CPU: 107 ms Memory: 19472 KB  Length: 1397 B)
時系列処理+BITで解く．
B[i]=(値が整数iとなる数) とする．
配列Bを時系列的に更新し，i年後のi人目の宇宙人が持つ石の数を求め，最後に各宇宙人から，渡すことになる数だけ石の個数を引くことで解く．
i人目の人は，i-1人目までの人から石を1つ貰うが，この処理は「1」とみなすB[i]のiの値を適切に変化させればよい．
・指定範囲の配列Aの合計
・指定したB[i]の更新
が高速に行うことができればよく，これはBITで良い．

最悪計算量は O(N*log2(N+2*max(Ai)))<10^7 となり高速．
※BITに追加する値がとり得る範囲を見誤って2WA...悔しい
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A 1000000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class BinaryIndexedTree{
    vector<ll> bit;
public:
    BinaryIndexedTree(int n=0){
        bit=vector<ll>(n+1,0);
    }

    void init(int n){
        bit=vector<ll>(n+1,0);
    }

    void add(int k,long long dx){
        while(k<=bit.size()){
            bit[k]=bit[k]+dx;
            k+=(k&(-k));
        }
    }

    ll sum(int k)const{
        ll s=0;
        while(k>0){
            s=(s+bit[k]);
            k-=(k&(-k));
        }
        return s;
    }

    int size(){
        return (int)bit.size();
    }

    void show(){
        int i;
        rep(i,bit.size()-2)
            printf("%lld ",sum(i+1)-sum(i));
        printf("%lld\n",sum(i+1)-sum(i));
    }
}BIT;

int n,a;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<ll> ans(n);
    BIT bit(n+MAX_A);
    scanf("%d",&a);
    ans[0]=a;
    if(ans[0]>0)bit.add(ans[0],1);
    for(i=1;i<n;i++){
        //bit.show();
        scanf("%d",&a);
        ans[i]=a+bit.sum(n+MAX_A)-bit.sum(i-1);
        bit.add((int)ans[i]+i,1);
        //bit.show();
    }
    rep(i,n-1)printf("%lld ",max((ll)0,ans[i]-(n-1-i)));
    printf("%lld\n",max((ll)0,ans[i]-(n-1-i)));
    return 0;
}