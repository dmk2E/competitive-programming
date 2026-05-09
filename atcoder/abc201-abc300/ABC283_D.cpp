/*アルゴリズムと工夫点(Scope/CPU: 28 ms Memory: 34332 KB  Length: 1083 B)
「)」がくると，それと対応する「(」で囲まれた範囲に存在するアルファベットが復活する．
従って，前処理で各アルファベットが何文字目までに何回登場したかの累積和alfaSumをあらかじめとっておき，
26種類のアルファベットそれぞれが，()で囲まれた範囲に存在するかをalfaSumでO(1)で判定し，存在すれば「復活する」という処理を行えばよい．
従って，各文字を先頭から順番にシミュレーションして解くことができる．
最悪計算量はO(26*|S|)≒10^6 となり，十分高速．
※初見4完!嬉しい!
※スタックを使って楽に解くこともできるらしい
※再帰降下構文解析とかでも解けるらしい
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ALFA 26
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

bool isExist[MAX_ALFA];
vector<vector<int> > alfaSum;
string s;

int main(){
    int i,j,cnt=0;
    cin>>s;
    rep(i,MAX_ALFA)isExist[i]=true;
    alfaSum=vector<vector<int> >(MAX_ALFA,vector<int>(s.length()+1,0));
    vector<int> cnt2Id(s.length()+1,0);
    rep(i,MAX_ALFA)
        rep(j,s.length())
            alfaSum[i][j+1]=((char)((int)'a'+i)==s[j])+alfaSum[i][j];
    rep(i,s.length()){
        if((int)'a'<=(int)s[i]&&(int)s[i]<=(int)'z'){
            if(isExist[s[i]-'a'])isExist[s[i]-'a']=false;
            else break;
        }else if(s[i]=='('){
            cnt++;
            cnt2Id[cnt]=i;
        }else if(s[i]==')'){
            rep(j,MAX_ALFA){
                if(alfaSum[j][i+1]-alfaSum[j][cnt2Id[cnt]]>0)
                    isExist[j]=true;
            }
            cnt--;
        }
    }
    printf("%s\n",i==s.length()?"Yes":"No");
    return 0;
}