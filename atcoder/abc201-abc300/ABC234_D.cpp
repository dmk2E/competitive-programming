/*アルゴリズムと工夫点(Prefix K-th Max/CPU: 129 ms Memory: 5892 KB  Length: 1204 B)
BIT+二分探索 で解ける．
Pの先頭i項の値aiの数を，BIT上の添え字aiに入れておくことで，(値ai以下の要素の数)=sum(ai) として求めることができる．
最悪計算量は O((N-K-1)*log2(N))<10^7 より高速．
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
    BinaryIndexedTree(int size){
        bit=vector<int>(size+1,0);
    }

    void add(int i,int x){
        while(i<bit.size()){
            bit[i]+=x;
            i+=(i&(-i));
        }
    }

    int sum(int i){//sum[0,i]
        int ssum=0;
        while(i>0){
            ssum+=bit[i];
            i-=(i&(-i));
        }
        return ssum;
    }

    int search(int k){
        int left=0,right=bit.size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(sum(mid)<k)
                left=mid+1;
            else
                right=mid;
        }
        return left;
    }
}BIT;

int n,k,p;

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    BIT bit(n);
    rep(i,k){
        scanf("%d",&p);
        bit.add(p,1);
    }
    for(;i<n;i++){
        printf("%d\n",bit.search(i-k+1));
        scanf("%d",&p);
        bit.add(p,1);
    }
    printf("%d\n",bit.search(i-k+1));
    return 0;
}