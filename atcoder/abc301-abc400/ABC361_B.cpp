/*アルゴリズムと工夫点(Intesection of Cuboids/CPU: 2 ms Memory: 3736 KB  Length: 488 B)
共通範囲の出し方を覚えていれば，x,y,zそれぞれの軸上で見た時の共通範囲の大きさが1以上であれば，条件を満たす．
最悪計算量はO(1).
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int a,b,c,d,e,f,g,h,i,j,k,l;

bool judge(int a,int b,int c,int d){
    //printf("%d\n",min(b,d)-max(a,c));
    return (min(b,d)-max(a,c))>0;
}

int main(){
    int i,j;
    scanf("%d%d%d%d%d%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l);
    if(judge(a,d,g,j)&&judge(b,e,h,k)&&judge(c,f,i,l))
        puts("Yes");
    else
        puts("No");
    return 0;
}