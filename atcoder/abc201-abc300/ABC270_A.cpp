/*アルゴリズムと工夫点(1-2-4 Test/CPU: 1 ms Memory: 3900 KB  Length: 571 B)
高橋君と青木君がそれぞれどの問題を解けたかビット全探索で求め，一方が解けた問題の点数の総和を出力すればよい．
※点数が2の累乗となっていることに気づければ，(x|y)が答えとなることを思いつけたかも．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int point[3]={1,2,4};
int a,b;

int main(){
    int i,ans=0,j=0;
    scanf("%d%d",&a,&b);
    auto judge=[](int s)->int{
        int i,j,p;
        for(i=0;i<(1<<3);i++){
            p=0;
            rep(j,3)p+=(1&(i>>j))*point[j];
            if(p==s)break;
        }
        return i;
    };
    j|=judge(a);
    j|=judge(b);
    rep(i,3)ans+=(1&(j>>i))*point[i];
    printf("%d\n",ans);
    return 0;
}