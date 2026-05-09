/*アルゴリズムと工夫点(審判は君だ！/CPU: 0 ms Memory: 3580 KB  Length: 1448 B)
構造体で大小関係を定義して，入力に応じて値を反映させていくと楽．
計算量は，O(R+T*log2(T))<10^3 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_P 10
using namespace std;

typedef struct team{
    int id,cntWA[MAX_P],cntAC;
    long long pelty;

    team(int iid=0):id(iid),cntAC(0),pelty(0){
        int i;
        rep(i,MAX_P)cntWA[i]=0;
    }

    bool operator<(const team& k)const{
        if(cntAC<k.cntAC)
            return true;
        else if(cntAC>k.cntAC)
            return false;
        else if(cntAC==k.cntAC){
            if(pelty>k.pelty)
                return true;
            else if(pelty<k.pelty)
                return false;
        }
        return id>k.id;
        //return (cntAC<k.cntAC||(cntAC==k.cntAC&&pelty>k.pelty)||(pelty==k.pelty&&id>k.id));//今回はこれで上手くいく.
    }
}Team;

int t,p,r,tt,ttime;
string msge;

int main(){
    int i,j;
    while(1){
        scanf("%d%d%d",&t,&p,&r);
        if(!(t||p||r))
            break;
        vector<Team> ddata;
        rep(i,t)
            ddata.push_back(Team(i));
        while(r--){
            scanf("%d%d%d",&tt,&p,&ttime);cin>>msge;
            tt--;p--;
            if(msge[0]=='C'){
                ddata[tt].cntAC++;
                ddata[tt].pelty+=ddata[tt].cntWA[p]*1200+ttime;
            }else
                ddata[tt].cntWA[p]++;
        }
        sort(ddata.begin(),ddata.end());
        rep(i,t)
            printf("%d %d %lld\n",ddata[t-1-i].id+1,ddata[t-1-i].cntAC,ddata[t-1-i].pelty);
    }
    return 0;
}