/*アルゴリズムと工夫点(Deck（★2）/CPU: 16 ms Memory: 4312 KB  Length: 535 B)
両端キューのdequeが便利．
※キーワードは「dequeを知っていますか．」
*/
#include<iostream>
#include<deque>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int q,t,x;
deque<int> card;

int main(){
    int i,j,k;
    scanf("%d",&q);
    rep(i,q){
        scanf("%d%d",&t,&x);
        switch(t){
            case 1:
                card.push_front(x);
                break;
            case 2:
                card.push_back(x);
                break;
            default:
                printf("%d\n",card[x-1]);
        }
    }
    return 0;
}