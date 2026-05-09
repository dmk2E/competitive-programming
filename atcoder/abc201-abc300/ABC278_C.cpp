/*アルゴリズムと工夫点(FF/CPU: 98 ms Memory: 8776 KB  Length: 567 B)
「a->b」のフォローの情報と「b->a」のフォローの情報の参照・追加・削除が高速に行えればよいから，連想配列等を用いればよい．
最悪計算量はO(Q*log2(Q))<10^7 となり，高速．
*/
#include<iostream>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,q,t,a,b;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    set<p> v;
    while(q--){
        scanf("%d%d%d",&t,&a,&b);
        if(t==1){
            v.insert(p(a,b));
        }else if(t==2){
            v.erase(p(a,b));
        }else{
            printf("%s\n",(v.find(p(a,b))!=v.end()&&v.find(p(b,a))!=v.end())?"Yes":"No");
        }
    }
    return 0;
}