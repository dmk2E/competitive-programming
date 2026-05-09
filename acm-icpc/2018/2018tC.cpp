/*アルゴリズムと工夫点(知識の証明/CPU: 30 ms Memory: 3560 KB  Length: 1334 B)
ハッシュ関数は、'['と']'を無視して末端から訪問すれば、逆ポーランド記法と同様になり、計算自体の最悪計算量は O(|P|)となる。
1桁の値のとりうるパターン数は「10」通りであるから、4桁分の全探索は10^4通りとなる。したがって最悪計算量は、O(10^4*|P|)=8.0*10^5<10^6 となり、十分高速。
*/
#include<iostream>
#include<stack>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_D 4
using namespace std;

int n[MAX_D];
string s;

int solve(){
    int i,j,k;
    stack<int> sta;
    for(i=s.length()-1;i>=0;i--){
        if((int)'a'<=(int)s[i]&&(int)s[i]<=(int)'d'){
            sta.push(n[(int)s[i]-(int)'a']);
        }else if(s[i]=='+'){
            j=sta.top();sta.pop();
            k=sta.top();sta.pop();
            sta.push(j|k);
        }else if(s[i]=='*'){
            j=sta.top();sta.pop();
            k=sta.top();sta.pop();
            sta.push(j&k);
        }else if(s[i]=='^'){
            j=sta.top();sta.pop();
            k=sta.top();sta.pop();
            sta.push(j^k);
        }
    }
    return sta.top();
}

int main(){
    int i,j,k,l,cnt,ans;
    while(1){
        cin>>s;
        if(s[0]=='.')
            break;
        rep(i,MAX_D)
            scanf("%1d",&n[i]);
        ans=solve();
        cnt=0;
        rep(i,10){
            n[0]=i;
            rep(j,10){
                n[1]=j;
                rep(k,10){
                    n[2]=k;
                    rep(l,10){
                        n[3]=l;
                        if(solve()==ans)
                            cnt++;
                    }
                }
            }
        }
        printf("%d %d\n",ans,cnt);
    }
    return 0;
}