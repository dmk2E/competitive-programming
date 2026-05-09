/*アルゴリズムと工夫点(Secret Number/CPU: 2 ms Memory: 3828 KB  Length: 1134 B)
合計枚数が4枚の中で、数値それぞれを何個使うかを確定させると、その場合のありうる暗証番号のパターン数はかぶりを省く順列の個数を求める式でO(1)で求めることができる。したがってそれぞれの数値の使う個数を再帰を用いて、全探索
する。最大4種類の数値をそれぞれ最大4個使うから、全パターン数は4^10≒10^6 通りより少なくなる。したがって、最悪計算量は 10^3 より小さくなり、十分高速。
※これを元ネタにしたオリジナル問題では、桁dの値を 1<=d<=15 で変化させて暗証番号としてあり得る全パターンを答えさせる。枝刈り条件をつけているため、d=15のテストケースでも考えるべき数値の数の組は1307504通りしかない。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_NUM 10
#define MAX_D 4
#define NIL -1
using namespace std;

int cnt[MAX_NUM]={0},kaijyo[MAX_NUM];
string s;

int res(int now,int cnt[MAX_NUM],int len,int sum){
    int i,ccnt=0;
    if(now==len-1){
        cnt[now]+=MAX_D-sum;
        ccnt=kaijyo[MAX_D];
        rep(i,MAX_NUM){
            if(cnt[i]>0)
                ccnt/=kaijyo[cnt[i]];
        }
        cnt[now]-=MAX_D-sum;
        return ccnt;
    }
    rep(i,MAX_D+1){
        if(sum+i<=MAX_D){
            cnt[now]+=i;
            ccnt+=res(now+1,cnt,len,sum+i);
            cnt[now]-=i;
        }else
            break;
    }
    return ccnt;
}

int main(){
    int i,sum=0,next=0;
    cin>>s;
    kaijyo[0]=1;
    rep(i,MAX_NUM-1)
        kaijyo[i+1]=kaijyo[i]*(i+1);
    rep(i,s.length()){
        if(s[i]=='o'){
            cnt[next++]=1;
            sum++;
        }else if(s[i]=='?')
            cnt[next++]=0;
    }
    if(sum>MAX_D||next==0)
        puts("0");
    else{
        printf("%d\n",res(0,cnt,next,sum));        
    }
    return 0;
}