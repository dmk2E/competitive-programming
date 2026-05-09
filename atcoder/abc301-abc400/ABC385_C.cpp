/*アルゴリズムと工夫点(Illuminate Buildings/CPU: 26 ms Memory: 5312 KB  Length: 1553 B)
高さ，幅，最小の添え字を固定して全探索する．
同じ探索をしないように工夫して高速化すれば，O(H*N+N^2)<10^7 に抑えることができる．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 3000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,left,right,mid;
    scanf("%d",&n);
    vector<vector<int> > h2Id(MAX_H+1,vector<int>(0));
    vector<vector<bool> > h2Ids(MAX_H+1,vector<bool>(n,false));
    rep(i,n){
        scanf("%d",&j);
        h2Id[j].push_back(i);
        h2Ids[j][i]=true;
    }
    const int NIL=-1;
    auto answer=[&]()->int{
        int i,j,l,lNow,cnt,diff,mmax=NIL;
        for(i=1;i<=MAX_H;i++){
            vector<int> flag(n,NIL);
            for(diff=1;diff<=n;diff++){
                for(l=0;l<h2Id[i].size();l++){
                    lNow=h2Id[i][l];
                    if(flag[lNow]==diff)continue;
                    flag[lNow]=diff;
                    cnt=1;
                    //printf("lNow:%d\n",lNow);
                    while(lNow+diff<n&&(flag[lNow+diff]!=diff||false)&&h2Ids[i][lNow+diff]){
                        cnt++;
                        lNow+=diff;
                        // printf("lNow:%d\n",lNow);
                        // printf("lNow+diff:%d\n",lNow+diff);
                        flag[lNow]=diff;
                    }
                    mmax=max(mmax,cnt);
                    //printf("h:%d l:%d lNow:%d diff:%d cnt:%d\n",i,l,lNow,diff,cnt);
                }
            }
        }
        return mmax;
    };
    printf("%d\n",answer());
    return 0;
}