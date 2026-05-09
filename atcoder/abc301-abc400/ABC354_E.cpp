/*アルゴリズムと工夫点(Remove Pairs/CPU: 129 ms Memory: 4144 KB  Length: 662 B)
ゲームの勝敗判定:ゲームの各状態sとして,「sの状態から先手がゲームを始めた時の勝敗」をf(s)とすると,遷移先の状態s'とし,f(s')のいずれかが敗北していれば,f(s)は勝利と判定できることを利用した,メモ化再帰or集合DPで解ける.
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 18
using namespace std;

typedef pair<int,int> Card;

int n;
bool dp[1<<MAX_N]={0};
Card c[MAX_N];

int main(){
    int i,j,k,max;
    bool flag;
    scanf("%d",&n);
    rep(i,n)
        scanf("%d%d",&c[i].first,&c[i].second);
    max=1<<n;
    rep(k,max){
        flag=false;
        rep(i,n)rep(j,i){
            if(((k>>i)&1)&&((k>>j)&1)&&(c[i].first==c[j].first||c[i].second==c[j].second)&&!dp[k^(1<<i)^(1<<j)]){
                flag=true;
            }
        }
        dp[k]=flag;
    }
    printf("%s\n",dp[(1<<n)-1]?"Takahashi":"Aoki");
    return 0;
}
/*再帰を用いた勝敗判定ver 26AC/30 4TLE/30 
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 18
using namespace std;

typedef pair<int,int> Card;

int n,colorA[MAX_N]={0},colorB[MAX_N]={0};
bool flag[MAX_N]={0};
Card c[MAX_N];

bool judge(int t){
    //printf("called\n");
    int i,j,k,l;
    bool fA[MAX_N+1]={0},fB[MAX_N+1]={0};
    bool f;
    //rep(i,n)printf("%d ",flag[i]?1:0);puts("");
    if(t%2==1){//Takahashi
        rep(i,n){
            if(flag[i]==false&&fA[colorA[i]]==false){
                vector<int> sta;
                //printf("%d:",t);
                fA[j=colorA[i]]=true;
                //printf("Takahashi:%d\n",j);
                rep(k,n){
                    if(flag[k]==false&&colorA[k]==j)
                        sta.push_back(k);
                }
                //printf("%d\n",sta.size());
                rep(k,sta.size()){
                    flag[sta[k]]=true;
                    for(l=k+1;l<sta.size();l++){
                        flag[sta[l]]=true;
                        if(judge(t+1)){
                            flag[sta[k]]=flag[sta[l]]=false;
                            return true;
                        }
                        flag[sta[l]]=false;
                    }
                    flag[sta[k]]=false;
                }
            }
        }
        rep(i,n){
            if(flag[i]==false&&fB[colorB[i]]==false){
                vector<int> sta;
                //printf("%d:",t);
                fB[j=colorB[i]]=true;
                //printf("Takahashii:%d\n",j);
                rep(k,n){
                    if(flag[k]==false&&colorB[k]==j)
                        sta.push_back(k);
                }
                //printf("%d\n",sta.size());
                rep(k,sta.size()){
                    flag[sta[k]]=true;
                    for(l=k+1;l<sta.size();l++){
                        flag[sta[l]]=true;
                        if(judge(t+1)){
                            flag[sta[k]]=flag[sta[l]]=false;
                            return true;
                        }
                        flag[sta[l]]=false;
                    }
                    flag[sta[k]]=false;
                }
            }
        }
        //printf("Aoki win\n");
        return false;
    }else{
        rep(i,n){
            if(flag[i]==false&&fA[colorA[i]]==false){
                vector<int> sta;
                //printf("%d:",t);
                fA[j=colorA[i]]=true;
                //printf("Aoki:%d\n",j);
                rep(k,n){
                    if(flag[k]==false&&colorA[k]==j)
                        sta.push_back(k);
                }
                //printf("%d\n",sta.size());
                rep(k,sta.size()){
                    flag[sta[k]]=true;
                    for(l=k+1;l<sta.size();l++){
                        flag[sta[l]]=true;
                        if(judge(t+1)==false){
                            flag[sta[k]]=flag[sta[l]]=false;
                            return false;
                        }
                        flag[sta[l]]=false;
                    }
                    flag[sta[k]]=false;
                }
            }
        }
        rep(i,n){
            if(flag[i]==false&&fB[colorB[i]]==false){
                vector<int> sta;
                //printf("%d:",t);
                fB[j=colorB[i]]=true;
                //printf("Aokii:%d\n",j);
                rep(k,n){
                    if(flag[k]==false&&colorB[k]==j)
                        sta.push_back(k);
                }
                //printf("%d\n",sta.size());
                rep(k,sta.size()){
                    flag[sta[k]]=true;
                    for(l=k+1;l<sta.size();l++){
                        flag[sta[l]]=true;
                        if(judge(t+1)==false){
                            flag[sta[k]]=flag[sta[l]]=false;
                            return false;
                        }
                        flag[sta[l]]=false;
                    }
                    flag[sta[k]]=false;
                }
            }
        }
        //printf("Aoki win\n");
        return true;
    }
}

int main(){
    int i,j,cnt=1;
    scanf("%d",&n);
    rep(i,n)
        scanf("%d%d",&c[i].first,&c[i].second);
    rep(i,n){
        if(colorA[i]==0){
            colorA[i]=cnt;
            for(j=i+1;j<n;j++){
                if(c[i].first==c[j].first)
                    colorA[j]=cnt;
            }
            cnt++;
        }
    }
    cnt=1;
    rep(i,n){
        if(colorB[i]==0){
            colorB[i]=cnt;
            for(j=i+1;j<n;j++){
                if(c[i].second==c[j].second)
                    colorB[j]=cnt;
            }
            cnt++;
        }
    }
    //rep(i,n)printf("%d ",colorA[i]);puts("");rep(i,n)printf("%d ",colorB[i]);puts("");
    printf("%s\n",judge(1)?"Takahashi":"Aoki");
    return 0;
}
*/