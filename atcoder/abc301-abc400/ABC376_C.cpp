/*アルゴリズムと工夫点(Prepare Another Box/CPU: 94 ms Memory: 6724 KB  Length: 1195 B)
貪欲法 + 二分探索 で解ける．
もし，大きさxの箱を用意して操作2を実行できるなら，xより大きい箱を用意しても操作2を実行することができる．
つまり大きさxを境目にして，「操作2を実行できる」か否かが2分される．これを「単調性」という．
大きさxに関して単調性があるので，二分探索によりxの最小値を求めることができる．
問題は「操作2を実行できるか否か」の判定条件だが，
全てのiについて，sorted(A)[i]<=sorted(xを加えたB)[i]
となる(∵小さいAiから小さいBiに入れていって，もし一つでも入らなければ，条件を満たさなくなるから)．
最悪計算量はO(N*log2(N)+N*log2(INF))<10^(7) となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n),b(n-1);
    rep(i,n)scanf("%d",&a[i]);
    rep(i,n-1)scanf("%d",&b[i]);
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    auto judge=[&](int x)->bool{
        int i;
        bool flag=true;
        vector<int> bb;
        rep(i,n-1){
            if(flag&&x<b[i]){
                bb.push_back(x);
                bb.push_back(b[i]);
                flag=false;
            }else{
                bb.push_back(b[i]);
            }
        }
        if(flag)bb.push_back(x);
        //printf("%d:",x);rep(i,n)printf("%d ",bb[i]);puts("");
        rep(i,n){
            if(a[i]>bb[i])return false;
        }
        return true;
    };
    const int INF=(int)(1e9)+5;
    int left=0,right=INF,mid;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))
            right=mid;
        else
            left=mid+1; 
    }
    printf("%d\n",left==INF?-1:left);
    return 0;
}