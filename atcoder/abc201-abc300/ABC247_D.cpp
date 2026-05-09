/*アルゴリズムと工夫点(Cylinder/CPU: 52 ms Memory: 7172 KB  Length: 1198 B)

*/
#include<iostream>
#include<deque>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct RLE{
    int x;
    ll c;

    RLE(int xx=0,ll cc=0):x(xx),c(cc){}
};

int q;

int main(){
    int i,j;
    scanf("%d",&q);
    deque<RLE> deq;
    RLE tmp;
    ll sum;
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d%d",&i,&j);
            if(deq.size()>0&&deq.back().x==i){
                tmp=deq.back();
                deq.pop_back();
                deq.push_back(RLE(tmp.x,tmp.c+j));
            }else deq.push_back(RLE(i,j));
        }else{
            sum=0;
            scanf("%d",&i);
            while(i>0){
                tmp=deq.front();
                deq.pop_front();
                if(i>=tmp.c){
                    sum+=tmp.x*tmp.c;
                    i-=tmp.c;
                }else{
                    sum+=(ll)tmp.x*i;
                    tmp.c-=i;
                    i=0;
                    deq.push_front(tmp);
                }
            }
            printf("%lld\n",sum);
        }
    }
    return 0;
}