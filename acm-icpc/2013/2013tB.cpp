/*アルゴリズムと工夫点(どうぶつの盛り2013/CPU: 290 ms Memory: 3936 KB  Length: 3136 B)
国語力の問題．時間を分に直して，各種条件を満たすか判定していけばよい．
開始時間の全パターン数は，7*24*60≒10^4 となり，全探索可能．
1テストケース当たりの最悪計算量は O(7*24*60*m)≒10^6 となり十分高速．
*/
#include<iostream>
#include<cmath>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define DAY_END (24*60)
#define MAX_WEEKDAY 7
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int s,n,t,p,m;
string str_weekday,str_time;

int weekday2Id(const string str){
    if(str=="Sun")return 0;
    else if(str=="Mon")return 1;
    else if(str=="Tue")return 2;
    else if(str=="Wed")return 3;
    else if(str=="Thu")return 4;
    else if(str=="Fri")return 5;
    else if(str=="Sat")return 6;
    return 7;
}

bool isValid(int start_time,int end_time,int time){
    if(start_time<=end_time)return start_time<=time&&time<end_time;
    return (start_time<=time&&time<DAY_END)||(0<=time&&time<end_time);
}

int main(){
    //printf("%.8f\n",1.0-pow(pow(1.0-1.0/150.0,37),1));return 0;
    int i,j,start_minute,end_minute,weekday_id;
    double ans;
    while(1){
        scanf("%d%d%d",&s,&n,&t);
        cin>>str_weekday>>str_time;
        scanf("%d%d",&p,&m);
        if(!s)break;
        if(str_time=="All"){
            start_minute=0;
            end_minute=24*60;
        }else if(str_time=="Day"){
            start_minute=6*60;
            end_minute=18*60;
        }else{
            start_minute=18*60;
            end_minute=6*60;
        }

        weekday_id=weekday2Id(str_weekday);
        auto isCommon=[&](int start_time,int end_time,int start_minute,int end_minute)->bool{
            end_time=(end_time+1)%DAY_END;
            if(start_minute<end_minute){
                if(start_time<end_time)return end_time-start_time==min(end_time,end_minute)-max(start_time,start_minute);
                else return false;
            }else{
                if(start_time<end_time)return min(end_time,start_minute)-max(start_time,end_minute)<=0;
                else return start_minute<=start_time&&end_time<=end_minute;
            }
        };
        auto calc=[&](int weekday,int time)->double{
            int mm=m;
            double tmp=1.0;
            while(mm--){
                // 日を跨いで良いのは，全ての曜日で突然変異する時のみ
                if((time+s<DAY_END&&weekday_id==weekday)||weekday_id==MAX_WEEKDAY){
                    if((str_time=="All"||isCommon(time,(time+s)%DAY_END,start_minute,end_minute)))tmp*=pow(1.0-1.0/p,n);
                }
                if(time+t>=DAY_END)weekday=(weekday+1)%MAX_WEEKDAY;
                time=(time+t)%DAY_END;
            }
            return 1.0-tmp;
        };
        ans=0.0;
        rep(i,MAX_WEEKDAY)rep(j,DAY_END)ans=max(ans,calc(i,j));
        printf("%.9f\n",ans);
    }
    return 0;
}