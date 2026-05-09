/*アルゴリズムと工夫点(繰り返す10進数/CPU: 20 ms Memory: 7152 KB  Length: 1295 B)
数値の小さい順に各桁を並び替えると,最も小さい数になる.数値の大きい順に各桁を並べ替えると最も大きな値になる.これらの事実を元にシミュレーションすればよい.
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_A 1000000
#define MAX_L 6
#define NIL -1
using namespace std;

char a[MAX_L+1];
int l,a2I[MAX_A];

int c2I(){
    int i,sum=0;
    for(i=0;i<l;i++){
        sum*=10;
        sum+=(int)a[i]-(int)'0';
    }
    return sum;
}

int c2IR(){
    int i,sum=0;
    for(i=l-1;i>=0;i--){
        sum*=10;
        sum+=(int)a[i]-(int)'0';
    }
    return sum;
}

void setA(int x){
    int i;
    for(i=l-1;i>=0;i--){
        if(x>0){
            a[i]=(char)((int)'0'+x%10);
            x/=10;
        }else
            a[i]='0';
    }
}

int main(){
    int i,j,nxt,cnt;
    while(1){
        scanf("%s%d",a,&l);
        if(l==0)
            break;
        cnt=0;
        rep(i,MAX_A)
            a2I[i]=NIL;
        for(i=0;a[i]!='\0';i++);
        if(l-i>0){
            for(j=i-1;j>=0;j--)
                a[j+l-i]=a[j];
            for(j=0;j<l-i;j++)
                a[j]='0';
        }
        a[l]='\0';
        while(1){
            a2I[c2I()]=cnt;
            sort(a,a+l);
            nxt=c2IR()-c2I();
            cnt++;
            if(a2I[nxt]!=NIL){
                printf("%d %d %d\n",a2I[nxt],nxt,cnt-a2I[nxt]);
                break;
            }
            setA(nxt);
        }
    }
    return 0;
}