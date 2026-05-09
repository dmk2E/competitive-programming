/*アルゴリズムと工夫点(Palindromic in Both Bases/CPU: 742 ms Memory: 3956 KB  Length: 2014 B)
候補を全列挙して総和を求める．
まず10進数で回文になる整数値を全列挙する．
この実装は再帰で行う．
列挙したそれぞれの数について，A進数でも回文か否か判定し，総和を求める．
最悪計算量は，O(9^(ceil(log10(N))/2)*(logA(N)+log10(N)))<597861*50<10^8 となり，間に合う．
※計算量を正しく見積もれるか，重い実装がこなせるかを問われた問題
※バーチャル参加
*/
#include<iostream>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a;
string n;
const int DIGIT_MAX=10,MAX_DIGIT=12;

/// @brief 2つの整数の大小比較
/// @param a 1つ目の整数（文字列）
/// @param b 2つ目の整数（文字列）
/// @return a<=b であるか
bool smaller(const string& a,const string& b){//<=
    if(a.size()==b.size()){
        int i;
        rep(i,a.size())if(a[i]!=b[i])return a[i]<b[i];
        return true;
    }
    return a.size()<b.size();
}

/// @brief 文字列を整数に変換
/// @param str 文字列
/// @return 文字列を整数に変換した値
ll str2Int(string& str){
    int i;
    ll ans=0;
    rep(i,str.size()){
        ans*=10;
        ans+=str[i]-'0';
    }
    return ans;
}

/// @brief 値がA進数でも回文になるか否か
/// @param str 判定する値
/// @return A進数でも回文になるか否か
bool judge(string& str){
    int i;
    ll num=str2Int(str);
    string str_a="";
    while(num>0){
        str_a+=('0'+(num%a));
        num/=a;
    }
    reverse(str_a.begin(),str_a.end());
    rep(i,(str_a.size()+1)/2)if(str_a[i]!=str_a[str_a.size()-1-i])return false;
    return true;
}

/// @brief 再帰で回文の片側を全列挙
/// @param now 今何桁目か
/// @param digit 桁数
/// @param str 情報退避文字列
/// @return digit桁の条件を満たす値の総和
ll rec(int now,int digit,string& str){
    int i;
    if(now==digit){
        ll ans=0;
        string str_rev=str;
        reverse(str_rev.begin(),str_rev.end());
        if(digit>0){
            string num=str+str_rev;
            if(smaller(num,n) && judge(num))ans+=str2Int(num);
            num=str+'0'+str_rev;
            if(smaller(num,n) && judge(num))ans+=str2Int(num);
        }
        rep(i,DIGIT_MAX-1){
            string num=str+(char)('0'+i+1)+str_rev;
            if(smaller(num,n) && judge(num))ans+=str2Int(num);
        }
        return ans;
    }
    ll ans=0;
    rep(i,DIGIT_MAX-1){
        str+=(char)('0'+i+1);
        ans+=rec(now+1,digit,str);
        str.pop_back();
    }
    if(now>0){
        str+='0';
        ans+=rec(now+1,digit,str);
        str.pop_back();
    }
    return ans;
}

int main(){
    int i,j;
    ll ans=0;
    string tmp="";
    scanf("%d",&a);cin>>n;
    ans+=rec(0,0,tmp);
    for(i=1;2*i<=n.size();i++){
        string tmp="";
        ans+=rec(0,i,tmp);
    }
    printf("%lld\n",ans);
    return 0;
}