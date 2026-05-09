/*アルゴリズムと工夫点(Printer/CPU: 10 ms Memory: 3904 KB  Length: 664 B)
「T秒後にK枚以上のチラシが印刷されているか」という判定条件を用いた二分探索で解ける．
最悪計算量はO(N*log2(MAX_T))≒10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_T (int)(1e9)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j,left,right,mid;
    scanf("%d%d",&n,&k);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    auto judge=[&](int t)->bool{
        int i;
        ll sum=0;
        rep(i,n)sum+=t/a[i];
        return sum>=k;
    };
    left=0,right=MAX_T;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))
            right=mid;
        else
            left=mid+1;
    }
    printf("%d\n",left);
    return 0;
}