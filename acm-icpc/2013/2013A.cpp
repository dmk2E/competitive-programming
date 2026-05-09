/*アルゴリズムと工夫点(整長方形/CPU: 0 ms Memory: 3552 KB  Length: 887 B)
二分探索を用いて解く．
横長整長方形の大小関係は対角線によって決まる．その対角線は高さhと幅wによって決まるため，求める最小横長整長方形は，(h,w)の組を全探索することで求める．
制約的に全探索しても良いが，高さhが固定されている時，横長整長方形の大小関係は，幅wが大きいほど大きくなる．
これを利用すると，「与えられた横長整長方形(h,w)より小さいか?」という判定条件に対して単調性を見つけることができる．
この単調性を利用すると，最悪計算量は O(MAX_H*log2(MAX_W))<10^4 となり十分高速．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 150
#define MAX_W 150
using namespace std;

int h,w;

int main(){
    int i,j,left,right,mid,ansH,ansW;
    auto smaller=[](int h,int w,int hh,int ww)->bool{//first<second
        int len1=h*h+w*w,len2=hh*hh+ww*ww;
        return len1<len2||(len1==len2&&h<hh);
    };
    while(1){
        scanf("%d%d",&h,&w);
        if(!(h|w))break;
        ansH=MAX_H+1;ansW=MAX_W+1;
        for(i=1;i<=MAX_H;i++){
            left=i+1,right=MAX_W;
            while(left<right){
                mid=(left+right)/2;
                if(smaller(h,w,i,mid))
                    right=mid;
                else
                    left=mid+1;
            }
            if(smaller(i,left,ansH,ansW)){
                ansH=i;
                ansW=left;
            }
        }
        printf("%d %d\n",ansH,ansW);
    }
    return 0;
}