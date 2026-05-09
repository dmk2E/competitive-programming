/*アルゴリズムと工夫点(Many Segments/CPU: 12 ms Memory: 3896 KB  Length: 819 B)
nの数が小さいから、(i,j)の組み合わせを全列挙し、共通部分を持つか判定すればよい。共通部分を持つかの判定は定数時間で行えるから、最悪計算量はO(N^2)となる。
※公式解説によると、区間の両端が整数であることから、開区間を閉区間に変換することは楽に行うことができ、それにより判定の処理を簡単にしている。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 2000
using namespace std;

typedef struct data{
    int t,l,r;

    data(int tt=0,int ll=0,int rr=0):t(tt),l(ll),r(rr){}
}Data;

int n;
Data seg[MAX_N];

bool judge(int a,int b){
    int l,r,temp=min(seg[a].r,seg[b].r)-max(seg[a].l,seg[b].l);
    if(temp<0)
        return false;
    else if(temp>0)
        return true;
    l=seg[a].l<seg[b].l?b:a;r=seg[a].r<seg[b].r?a:b;
    return (seg[l].t==1||seg[l].t==2)&&(seg[r].t==1||seg[r].t==3);
}

int main(){
    int i,j,cnt=0;
    scanf("%d",&n);
    rep(i,n)
        scanf("%d%d%d",&seg[i].t,&seg[i].l,&seg[i].r);
    rep(i,n){
        for(j=i+1;j<n;j++){
            if(judge(i,j))
                cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}