/*アルゴリズムと工夫点(6÷2(1+2)/CPU: 300 ms Memory: 3540 KB  Length: 4366 B)
演算子の個数が最大で10個しかないから,演算の順序の全パターン数は10!しかないから,全探索する.ただし,括弧内の値は,その括弧内の式がとり得る全ての値を列挙してから,演算子の順序を全列挙して計算するようにする.そのため,再帰で
の実装が楽.
※実装やバグとりに3~4時間かかった....
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX 1000000000
#define MAX_S 200
#define PLUS MAX+1
#define MINUS MAX+2
#define MULT MAX+3
#define DIVI MAX+4
#define START MAX+5
using namespace std;

string str;

void dfs(int now,bool flag[MAX_S],const vector<int> temp,const vector<int>& e,set<int>& llog,vector<int> memo[MAX_S]){
    int i,j,k,l,r,rlt;
    bool fflag;
    //printf("now:%d→",now);rep(i,temp.size())printf("%d ",temp[i]);puts("");
    if(now==e.size()){//e:temp上の演算子が存在する添え字
        if(temp[0]>=START){
            rep(i,memo[temp[0]-START].size())
                llog.insert(memo[temp[0]-START][i]);
        }else
            llog.insert(temp[0]);
        return ;
    }
    rep(i,e.size()){
        if(flag[i]==false){
            flag[i]=true;
            vector<int> nnew;
            for(j=0;j<(temp[e[i]-1]>=START?memo[temp[e[i]-1]-START].size():1);j++){
                for(k=0;k<(temp[e[i]+1]>=START?memo[temp[e[i]+1]-START].size():1);k++){
                    fflag=false;
                    l=temp[e[i]-1]>=START?memo[temp[e[i]-1]-START][j]:temp[e[i]-1];
                    r=temp[e[i]+1]>=START?memo[temp[e[i]+1]-START][k]:temp[e[i]+1];
                    nnew=temp;
                    switch(temp[e[i]]){
                        case PLUS:
                            rlt=l+r;
                            break;
                        case MINUS:
                            rlt=l-r;
                            break;
                        case MULT:
                            rlt=l*r;
                            break;
                        default:
                            if(r==0){
                                fflag=true;
                                break;
                            }
                            rlt=l/r;
                    }
                    if(fflag)
                        continue;
                    l=e[i]-1;
                    r=e[i]+1;
                    while(l>=0&&temp[e[i]-1]==temp[l])
                        l--;
                    while(r<temp.size()&&temp[e[i]+1]==temp[r])
                        r++;
                    for(l++;l<r;l++)
                        nnew[l]=rlt;
                    dfs(now+1,flag,nnew,e,llog,memo);        
                }
            }
            flag[i]=false;
        }
    }
}

int counter(int l,int r,int& now,vector<int> memo[MAX_S]){
    int i,sum,nnow=now,j;
    bool flag[MAX_S]={0};
    vector<int> temp,e;
    for(i=l;i<r;i++){//一旦文字列を整数に変換する.この時,演算子も上で定義した整数で表す.
        if((int)'0'<=(int)str[i]&&(int)str[i]<=(int)'9'){
            sum=0;
            while((int)'0'<=(int)str[i]&&(int)str[i]<=(int)'9'){
                sum*=10;
                sum+=(int)str[i]-(int)'0';
                i++;
            }
            temp.push_back(sum);
            i--;
        }else{
            switch(str[i]){
                case '+':
                    temp.push_back(PLUS);
                    e.push_back(temp.size()-1);
                    break;
                case '-':
                    temp.push_back(MINUS);
                    e.push_back(temp.size()-1);
                    break;
                case '*':
                    temp.push_back(MULT);
                    e.push_back(temp.size()-1);
                    break;
                case '/':
                    temp.push_back(DIVI);
                    e.push_back(temp.size()-1);
                    break;
                default :
                    sum=1;
                    j=i+1;
                    i++;
                    while(sum>0){
                        if(str[i]=='(')
                            sum++;
                        else if(str[i]==')')
                            sum--;
                        i++;
                    }
                    now++;
                    temp.push_back(now);
                    i--;
                    counter(j,i,now,memo);
            }
        }
    }
    //rep(i,temp.size())printf("%d ",temp[i]);puts("");
    set<int> llog;
    dfs(0,flag,temp,e,llog,memo);
    for(int x:llog)
        memo[nnow-START].push_back(x);
    return llog.size();
}

int main(){
    int now;
    while(1){
        getline(cin,str);
        if(str[0]=='#')
            break;
        vector<int> memo[MAX_S];
        now=START;
        printf("%d\n",counter(0,(int)str.length(),now,memo));
    }
    return 0;
}