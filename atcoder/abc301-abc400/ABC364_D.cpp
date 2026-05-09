/*アルゴリズムと工夫点(K-th Nearest/CPU: 354 ms Memory: 3904 KB  Length: 1123 B)
ある点bjとの距離がk番目に近い点Xを求めたいとき，ある点bjとの距離Lの範囲内に存在する点Aの数cntとした時，cnt>=kとなる最小のLを求めればよい．
二分探索を2重に行うから，最悪計算量はO(N*log2(N)+Q*log2(MAX_A)*log2(N))≒10^7となり，高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A (int)(1e8)
using namespace std;
typedef long long ll;

int n,q,b,k;
vector<int> a;

int count(int b,int x){
    int left,right,mid,l;
    left=0;right=a.size();
    while(left<right){
        mid=(left+right)/2;
        if(a[mid]<b-x)
            left=mid+1;
        else
            right=mid;
    }
    l=left;
    left=0;right=a.size();
    while(left<right){
        mid=(left+right)/2;
        if(a[mid]<=b+x)
            left=mid+1;
        else
            right=mid;
    }
    return right-l;
}

int main(){
    int i,j,left,right,mid;
    scanf("%d%d",&n,&q);
    a=vector<int>(n);
    rep(i,n)
        scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    while(q--){
        scanf("%d%d",&b,&k);
        left=0;right=2*MAX_A+1;
        while(left<right){
            mid=(left+right)/2;
            if(count(b,mid)<k)
                left=mid+1;
            else
                right=mid;
        }
        printf("%d\n",left);
    }
    return 0;
}