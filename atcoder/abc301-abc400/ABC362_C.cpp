/*アルゴリズムと工夫点(Sum = 0/CPU: 56 ms Memory: 4948 KB  Length: 806 B)
一旦初期値をL[i]にしておいて，sum=0となるように必要な分だけ加算していくことで，O(n)で解を導出できる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;

int main(){
    int i;
    ll sumL=0,sumR=0;
    scanf("%d",&n);
    vector<int> l(n),r(n);
    rep(i,n){
        scanf("%d%d",&l[i],&r[i]);
        sumL+=l[i];
        sumR+=r[i];
    }
    if(sumL<=0&&sumR>=0){
        puts("Yes");
        rep(i,n){
            //printf("sumL:%lld\n",sumL);
            if(sumL==0)break;
            if(sumL+r[i]-l[i]<=0){
                sumL+=r[i]-l[i];
                l[i]=r[i];
            }else{
                l[i]+=-sumL;
                sumL=0;
            }
        }
        rep(i,n-1)
            printf("%d ",l[i]);
        printf("%d\n",l[i]);
    }else
        puts("No");
    return 0;
}