/*アルゴリズムと工夫点(ICPCの順位付け/CPU: 0 ms Memory: 3516 KB  Length: 1963 B)
問題文の規則に従って，順位付けするための情報を，チーム毎に構造体等でまとめて保持し，各ログの内容を反映後，ソートして出力する．
出力形式がかなり面倒だった...
最悪計算量は O(R+T*log2(T))<10^4 となり十分高速．
※ブロックスコープに注意．C言語もC++も，関数やif文等のブロック内で宣言した変数はそのブロック内でのみ有効．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

typedef struct TeamInfo{
    int id,ac,sumT;
    vector<int> wAC;

    TeamInfo(int iid=0,int m=0,int aac=0,int ssumT=0):id(iid),ac(aac),sumT(ssumT){
        wAC=vector<int>(m,0);
    }

    bool operator==(const TeamInfo& k)const{
        return ac==k.ac&&sumT==k.sumT;
    }

    bool operator<(const TeamInfo& k)const{
        return ac>k.ac||(ac==k.ac&&sumT<k.sumT);
    }
}TI;

int m,t,p,r;

int main(){
    int i,j,k,l;
    bool flag;
    while(1){
        scanf("%d%d%d%d",&m,&t,&p,&r);
        if(!(m||t||p||r))break;
        vector<TI> team,tteam;
        rep(i,t)team.push_back(TI(i,p));
        while(r--){
            scanf("%d%d%d%d",&i,&j,&k,&l);
            j--;k--;
            if(l==0){
                team[j].ac++;
                team[j].sumT+=i+team[j].wAC[k]*20;
            }else{
                team[j].wAC[k]++;
            }
        }
        tteam=team;
        sort(tteam.begin(),tteam.end());
        //rep(i,t)printf("%d ",tteam[i].id+1);puts("");
        flag=true;
        priority_queue<int> PQ;
        i=0;
        PQ.push(tteam[i].id);
        i++;
        while(i<t){
            if(team[PQ.top()]==tteam[i]){PQ.push(tteam[i].id);}
            else{
                if(flag){printf("%d",PQ.top()+1);PQ.pop();flag=false;}
                else{printf(",%d",PQ.top()+1);PQ.pop();}
                while(PQ.size()){
                    printf("=%d",PQ.top()+1);PQ.pop();
                }
                //priority_queue<int> PQ;//ここで宣言したPQはelse文を抜けると使えなくなる
                PQ.push(tteam[i].id);
            }
            i++;
        }
        if(PQ.size()){
            if(flag){printf("%d",PQ.top()+1);PQ.pop();flag=false;}
            else{printf(",%d",PQ.top()+1);PQ.pop();}
            while(PQ.size()){
                printf("=%d",PQ.top()+1);PQ.pop();
            }
        }
        puts("");
    }
    return 0;
}