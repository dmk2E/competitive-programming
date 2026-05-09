/*アルゴリズムと工夫点(恒等式/CPU: 380 ms Memory: 3388 KB  Length: 5648 B)
各々変数がとり得る値はTrueかFalseのみであり，出現する変数の種類数vは最大で11個しかないため，全パターン数は2^11<10^4となる．ここで，中間値法の長さ|S|の論理式Sの論理式解析にかかる計算量はO(|S|)となるから，
全体の最悪計算量はO((2^v)*|S|)<10^7 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_ALFA 11
using namespace std;

string str;
int af2I[MAX_ALFA];
bool i2Bool[MAX_ALFA];

bool analyze(int s,int e){//括弧で覆われた論理式の値を求める再帰関数 走査範囲:[s,e)
    int tmp,cnt;
    bool temp,deny;
    vector<bool> sta;
    //printf("start\n");
    for(;s<e;s++){
        if('a'<=str[s]&&str[s]<='z')
            sta.push_back(i2Bool[af2I[str[s]-'a']]);
        else if(str[s]=='T')
            sta.push_back(true);
        else if(str[s]=='F')
            sta.push_back(false);
        else{
            switch(str[s]){
                case '(':
                    tmp=s;
                    cnt=0;
                    for(;s<e;s++){if(str[s]=='(')cnt++;else if(str[s]==')')cnt--;if(cnt==0)break;}
                    sta.push_back(analyze(tmp+1,s));
                    break;
                case '+':
                    s++;
                    temp=sta.back();sta.pop_back();
                    deny=false;
                    if(str[s]=='-'){
                        deny=true;
                        s++;
                    }
                    if(str[s]=='('){
                        tmp=s;
                        cnt=0;
                        for(;s<e;s++){if(str[s]=='(')cnt++;else if(str[s]==')')cnt--;if(cnt==0)break;}
                        sta.push_back(temp||(deny^analyze(tmp+1,s)));
                    }else if(str[s]=='T')
                        sta.push_back(temp||(deny^true));
                    else if(str[s]=='F')
                        sta.push_back(temp||(deny^false));
                    else
                        sta.push_back(temp||(deny^i2Bool[af2I[str[s]-'a']]));
                    break;
                case '*':
                    s++;
                    temp=sta.back();sta.pop_back();
                    deny=false;
                    if(str[s]=='-'){
                        deny=true;
                        s++;
                    }
                    if(str[s]=='('){
                        tmp=s;
                        cnt=0;
                        for(;s<e;s++){if(str[s]=='(')cnt++;else if(str[s]==')')cnt--;if(cnt==0)break;}
                        sta.push_back(temp&&(deny^analyze(tmp+1,s)));
                    }else if(str[s]=='T')
                        sta.push_back(temp&&(deny^true));
                    else if(str[s]=='F')
                        sta.push_back(temp&&(deny^false));
                    else
                        sta.push_back(temp&&(deny^i2Bool[af2I[str[s]-'a']]));
                    break;
                default:
                    s++;
                    if(str[s]=='>'){
                        s++;
                        temp=sta.back();sta.pop_back();
                        deny=false;
                        if(str[s]=='-'){
                            deny=true;
                            s++;
                        }
                        if(str[s]=='('){
                            tmp=s;
                            cnt=0;
                            for(;s<e;s++){if(str[s]=='(')cnt++;else if(str[s]==')')cnt--;if(cnt==0)break;}
                            sta.push_back(temp==false||(deny^analyze(tmp+1,s)));
                        }else if(str[s]=='T')
                            sta.push_back(temp==false||(deny^true));
                        else if(str[s]=='F')
                            sta.push_back(temp==false||(deny^false));
                        else{
                            sta.push_back(temp==false||(deny^i2Bool[af2I[str[s]-'a']]));
                        }
                    }else if(str[s]=='('){
                        tmp=s;
                        cnt=0;
                        for(;s<e;s++){if(str[s]=='(')cnt++;else if(str[s]==')')cnt--;if(cnt==0)break;}
                        sta.push_back(!analyze(tmp+1,s));
                    }else if(str[s]=='T')
                        sta.push_back(!true);
                    else if(str[s]=='F')
                        sta.push_back(!false);
                    else
                        sta.push_back(!i2Bool[af2I[str[s]-'a']]);
                    break;
            }
        }
    }
    //printf("%d\n",s);printf("end:%d\n",sta.back()?1:0);
    return sta.back();
}

bool judge(int s,vector<char>& alfa,int mid){
    int i;
    //printf("judge:%d\n",s);
    rep(i,alfa.size())
        i2Bool[i]=s&(1<<(alfa.size()-1-i));
    return analyze(0,mid)==analyze(mid+1,str.length());
}

int main(){
    int i,j;
    string sstr;
    while(1){
        cin>>str;
        if(str[0]=='#')
            break;
        vector<char> alfa;
        bool flag[MAX_ALFA]={0};
        for(i=0;i<str.length();i++){
            if(str[i]=='-'){
                j=0;
                while(str[i]=='-'){
                    j++;
                    i++;
                }
                if(j%2==1)
                    sstr.push_back('-');
            }
            sstr.push_back(str[i]);
        }
        str=sstr;
        for(i=0;i<str.length();i++){
            if((int)'a'<=str[i]&&str[i]<=(int)'z'&&flag[(int)str[i]-(int)'a']==false){
                alfa.push_back(str[i]);
                flag[(int)str[i]-(int)'a']=true;
                af2I[(int)str[i]-(int)'a']=alfa.size()-1;
            }else if(str[i]=='=')
                j=i;
        }
        //rep(i,alfa.size()){printf("%d ",af2I[alfa[i]-'a']);}puts("");
        //rep(i,alfa.size()){printf("%c ",alfa[i]);}puts("");
        //printf("mid:%d\n",j);
        rep(i,1<<alfa.size()){
            if(judge(i,alfa,j)==false)
                break;
        }
        printf("%s\n",i==(1<<alfa.size())?"YES":"NO");
    }
    return 0;
}