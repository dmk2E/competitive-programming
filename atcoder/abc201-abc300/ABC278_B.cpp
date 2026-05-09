/*アルゴリズムと工夫点(Misjudge the Time/CPU: 1 ms Memory: 3932 KB  Length: 562 B)
全時刻のパターン数が大したことないから，1分毎進めて，「見間違えやすい時刻か」の判定にひっかかった時刻を出力．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 24
#define MAX_M 60
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,m;

bool judge(int h,int w){
    int hh=(h-(h%10))+w/10,ww=(h%10)*10+w%10;
    return 0<=hh&&hh<MAX_H&&0<=ww&&ww<MAX_M;
}

int main(){
    int i,j,hh,mm;
    scanf("%d%d",&h,&m);
    hh=h,mm=m;
    do{
        if(judge(hh,mm))break;
        mm=(mm+1)%MAX_M;
        if(mm==0)hh=(hh+1)%MAX_H;
    }while(hh!=h||mm!=m);
    printf("%d %d\n",hh,mm);
    return 0;
}