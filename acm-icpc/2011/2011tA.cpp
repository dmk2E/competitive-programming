/*アルゴリズムと工夫点(koukyoukoukokukikou/CPU: 0 ms Memory: 3488 KB  Length: 597 B)
その文字が左手で打つものか、右手で打つものかをbool値で保持する配列を用意し、一つ一つの文字列を先頭から走査することで数え上げる。最悪計算量はO(|s|)<10^2となり、十分高速。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_ALFA 26
using namespace std;

string s,rright="yuiophjklnm";
bool keyboard[MAX_ALFA]={0};

int count(string s){
    int i,cnt=0;
    bool now=keyboard[s[0]-'a'];
    rep(i,s.length())
        if(keyboard[s[i]-'a']!=now){
            now=keyboard[s[i]-'a'];
            cnt++;
        }
    return cnt;
}

int main(){
    int i;
    rep(i,rright.length())
        keyboard[(int)rright[i]-(int)'a']=true;
    while(1){
        cin>>s;
        if(s[0]=='#')
            break;
        printf("%d\n",count(s));
    }
    return 0;
}