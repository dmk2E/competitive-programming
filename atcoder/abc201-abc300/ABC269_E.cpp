/*アルゴリズムと工夫点(Last Rook/CPU: 4 ms Memory: 3892 KB  Length: 814 B)
N*Nのマス目に条件を満たしてルークがおかれている場合，最後のルークを置くことができるのが上からrow行だったとすると，sum[1,x][1,N]==x(1<=x<row),sum[1,x][1,N]!=x(row<=x<=N) となる．
つまり，xは「sum[1,x][1,N]==x」の条件に対して単調性があり，条件を満たさなくなる分かれ目が求めるrowとなる．これは二分探索で求めることができる．
列についても同様．
よってクエリの回数は，2*log2(N)<20 となり間に合う．
最悪計算量は O(log2(N))<10^2 となり十分高速．
※初見5完!
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,row,left,right,mid;
    scanf("%d",&n);
    //phase4SearchingRow
    left=1,right=n;
    while(left<right){
        mid=(left+right)/2;
        printf("? %d %d %d %d\n",1,mid,1,n);
        cout<<flush;
        scanf("%d",&i);
        if(mid==i)left=mid+1;
        else right=mid;
    }
    row=left;
    //phase4SearchingColumn
    left=1,right=n;
    while(left<right){
        mid=(left+right)/2;
        printf("? %d %d %d %d\n",1,n,1,mid);
        cout<<flush;
        scanf("%d",&i);
        if(mid==i)left=mid+1;
        else right=mid;
    }
    printf("! %d %d\n",row,left);
    cout<<flush;
    return 0;
}