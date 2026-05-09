/*アルゴリズムと工夫点(世界の天秤/CPU: 0 ms  Memory: 3348 KB  Length: 906 B)
バランスが取れているための必要条件として、文字列strを先頭から巡回していく時、('('の数)>=(')'の数) と ('['の数)>=(']'の数) は必ず満たす。これを、'('なら+1,')'なら-1する変数cnt1,'['と']'についても同様の動きをする変数
cnt2を用いて判定する。つまり、cnt1=cnt2=0からスタートして、「初めてcnt1>0またはcnt2>0になった時のstr[s]の括弧」と「cnt1=0かつcnt2=0に再びなった時のstr[e]の括弧」は対応する括弧となっている必要がある。また途中でcnt1,
cnt2のどちらが負の数になってはいけない。この時、条件を満たすなら、[s,e)のstrの部分列について、同様の判定を行えばよい。この実装は再帰を用いて行う。
str上の全ての文字を最大2,3回だけ巡回するから、最悪計算量は O(|s|)<10^3 となり、十分高速。
※一発AC出来なかった泣 cnt1,cnt2のいずれかが負になった時点でバランスではないから、その時点でfalseを返すようにした。
※スタックを用いた実装の方が楽かつ高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NIL -1
using namespace std;

string str;

bool isBalanced(int s,int e){//文字列strにおける[s,e)の部分がバランスしているか判定する。
	//printf("f(%d,%d) ",s,e);
	int i,ss=NIL,ee=NIL,cnt1=0,cnt2=0;
	for(i=s;i<e;i++){
		switch(str[i]){
			case '(':
				if(ss==NIL)
					ss=i;
				cnt1++;
				break;
			case '[':
				if(ss==NIL)
					ss=i;
				cnt2++;
				break;
			case ')':
				ee=i;
				cnt1--;
				break;
			case ']':
				ee=i;
				cnt2--;
				break;
			default:
				break;
		}
		if(cnt1<0||cnt2<0)
			return false;
		if(ss!=NIL){
			if(cnt1==0&&cnt2==0){
				//printf("judge(%d,%d)",ss,ee);
				if(((str[ss]=='('&&str[ee]==')')||(str[ss]=='['&&str[ee]==']'))&&isBalanced(ss+1,ee)){
					i=ee;
					ss=ee=NIL;
					cnt1=cnt2=0;
					//printf("true ");
				}else{
					//printf("false ");
					return false;
				}
			}
		}
	}
	//printf("finished ");
	return (ss==NIL)&&(ee==NIL);
}

int main() {
	while(1){
		getline(cin,str);
		if(str[0]=='.')
			break;
		printf("%s\n",isBalanced(0,(int)str.length())?"yes":"no");
	}
	return 0;
}