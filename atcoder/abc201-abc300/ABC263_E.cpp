/*アルゴリズムと工夫点(Sugoroku 3/CPU: 79 ms Memory: 4896 KB  Length: 1361 B)
期待値問題では双六のモデルに当てはめて言い換えることが多く，その時に考えるのは，
f(x):状態xから始めた時，条件を満たす状態になるまでに必要な試行回数の期待値
となる．
この考えと，BITを用いて今回の問題は解ける．
最悪計算量は O(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct BinaryIndexedTree{
    vector<int> bit;
public:
    BinaryIndexedTree(int n=1){
        bit=vector<int>(n+1,0);
    }

    void add(int k,int dx){
        assert(1<=k&&k<(int)bit.size());
        while(k<(int)bit.size()){
            bit[k]=(bit[k]+dx)%MOD;
            k+=(k&-k);
        }
    }

    int sum(int k){
        int ans=0;
        while(k>0){
            ans=(bit[k]+ans)%MOD;
            k-=(k&-k);
        }
        return ans;
    }

    int ssum(int l,int r){
        assert(1<=l&&l<bit.size());
        assert(1<=r&&r<bit.size());
        assert(l<=r);
        return sum(r)-sum(l-1);
    }
}BIT;

int n;

int power(int x,int a){
    if(a==0)return 1;
    int res=power((((long long)x%MOD)*(x%MOD))%MOD,a/2)%MOD;
    if(a%2==1)res=((long long)res*(x%MOD))%MOD;
    return res;
}

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n-1);
    BIT tree(n);
    rep(i,n-1)scanf("%d",&a[i]);
    tree.add(n,0);
    for(i=n-2;i>=0;i--)tree.add(i+1,(((tree.ssum(i+2,i+1+a[i])+a[i]+1)%MOD)*(ll)power(a[i],MOD-2))%MOD);
    printf("%d\n",tree.ssum(1,1));
    return 0;
}