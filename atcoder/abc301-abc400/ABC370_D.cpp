/*アルゴリズムと工夫点(Cross Explosion/CPU: 347 ms Memory: 59448 KB  Length: 1734 B)

*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w,q,r,c;

int main(){
    int i,j,cnt=0;
    set<int>::iterator it,iit;
    scanf("%d%d%d",&h,&w,&q);
    vector<set<int> > row(h),col(w);
    rep(i,h)rep(j,w)row[i].insert(j);
    rep(j,w)rep(i,h)col[j].insert(i);
    const int NIL=-1;
    while(q--){
        scanf("%d%d",&r,&c);
        r--;c--;
        it=row[r].lower_bound(c);
        iit=col[c].lower_bound(r);
        if((it!=row[r].end())&&(iit!=col[c].end())&&*it==c&&*iit==r){
            cnt++;
            row[r].erase(*it);
            col[c].erase(*iit);
        }else{
            i=it!=row[r].end()?*it:NIL;
            j=NIL;
            if(it!=row[r].begin()){
                it--;
                j=*it;
            }
            //printf("i:%d j:%d\n",i,j);
            if(i!=NIL){
                row[r].erase(i);
                col[i].erase(r);
                cnt++;
            }
            if(j!=NIL){
                row[r].erase(j);
                col[j].erase(r);
                cnt++;
            }
            i=iit!=col[c].end()?*iit:NIL;
            j=NIL;
            if(iit!=col[c].begin()){
                iit--;
                j=*iit;
            }
            //printf("i:%d j:%d\n",i,j);
            if(i!=NIL){
                col[c].erase(i);
                row[i].erase(c);
                cnt++;
            }
            if(j!=NIL){
                col[c].erase(j);
                row[j].erase(c);
                cnt++;
            }
        }
    }
    printf("%d\n",h*w-cnt);
    return 0;
}