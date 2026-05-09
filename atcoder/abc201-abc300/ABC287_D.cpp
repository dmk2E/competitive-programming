/*アルゴリズムと工夫点(Match or Not/CPU: 14 ms Memory: 4332 KB  Length: 757 B)
sと一致するか見るtの部分文字列をtopとtailの2つ用意する．先頭部分と一致するかはtop,末端部分と一致するかはtailで管理する．
この時，top,tailそれぞれで何文字と一致していたかはtopT,tailTそれぞれで保持して置く．
x=0,1,...とxの値が変化するごとに，tailの先頭文字がtopの末尾に加えられるため，そのたび，topT,tailTの値を更新し，条件を満たすかその都度判定すればよい．
最悪計算量はO(|S|+|T|)<10^7 となり，高速．
※初見4完!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

string s,t;
vector<bool> top,tail;

int main(){
    int i,j,topT=0,tailT=0;
    cin>>s>>t;
    rep(i,t.length()){
        if(t[i]=='?'||s[i+s.length()-t.length()]=='?'||t[i]==s[i+s.length()-t.length()]){
            tail.push_back(true);
            tailT++;
        }else
            tail.push_back(false);
    }
    rep(i,t.length()+1){
        printf("%s\n",topT==top.size()&&tailT==(tail.size()-i)?"Yes":"No");
        tailT-=tail[i];
        if(t[i]=='?'||s[i]=='?'||t[i]==s[i]){
            top.push_back(true);
            topT++;
        }else
            top.push_back(false);
    }
    return 0;
}