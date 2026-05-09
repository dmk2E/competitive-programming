/*アルゴリズムと工夫点(Writing a Numeral/CPU: 72 ms  Memory: 8584 KB  Length: 591 B)
Qの数だけ静的確保した配列と、sを表す配列上の添え字の範囲[top,tail)で、Sを表現し、各操作を行う毎にSが表す値をMODで割った余りsumを更新していけばよい。この時、前処理として、modTen[x]=(10^x)%MOD となるmodTenを用意して
おく。こうすることで、「2項演算である和・差・積の値をMODで割った余り」は、「2つの項の値それぞれを「MODで割った余り」として計算した結果」と等しいことを利用して解くことができる。
最悪計算量は O(Q) となり、十分高速。
*/
#include <iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_Q 600000
#define MOD 998244353
using namespace std;

int q,modTen[MAX_Q+1],s[MAX_Q+1],top=0,tail=0;

int main() {
	int i;
	long long sum=1;
	rep(i,MAX_Q+1){
		modTen[i]=(int)(sum%=MOD);
		sum*=10;
	}
	scanf("%d",&q);
	sum=1;
	s[tail++]=1;
	while(q--){
		scanf("%d",&i);
		if(i==1){
			scanf("%d",&i);
			s[tail++]=i;
			sum=(sum*10+i)%MOD;
		}else if(i==2){
			sum=(MOD+sum-((long long)s[top]*modTen[tail-top-1])%MOD)%MOD;//合同式の差は、差を行う2つの値それぞれがMODで割ったものでなければならない。
			top++;
		}else{
			printf("%lld\n",sum);
		}
	}
	return 0;
}