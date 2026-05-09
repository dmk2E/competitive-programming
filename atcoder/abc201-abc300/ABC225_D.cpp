/*アルゴリズムと工夫点(Play Train/CPU: 89 ms Memory: 7624 KB  Length: 1301 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int NIL=-1;

typedef struct train{
    int prev,nxt;

    train(int pprev=NIL,int nnxt=NIL):prev(pprev),nxt(nnxt){}
}Train;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<Train> train(n);
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d%d",&i,&j);
            i--;j--;
            train[i].nxt=j;
            train[j].prev=i;
        }else if(i==2){
            scanf("%d%d",&i,&j);
            i--;j--;
            train[i].nxt=NIL;
            train[j].prev=NIL;
        }else{
            vector<int> tmp;
            scanf("%d",&i);i--;
            j=train[i].nxt;
            do{
                tmp.push_back(i);
                i=train[i].prev;
            }while(i!=NIL);
            reverse(tmp.begin(),tmp.end());
            while(j!=NIL){
                tmp.push_back(j);
                j=train[j].nxt;
            }
            printf("%d ",(int)tmp.size());
            rep(i,tmp.size()-1)
                printf("%d ",tmp[i]+1);
            printf("%d\n",tmp[i]+1);
        }
    }
    return 0;
}