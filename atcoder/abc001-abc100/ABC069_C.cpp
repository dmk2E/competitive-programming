/*アルゴリズムと工夫点(4-adjacent/CPU: 12 ms  Memory: 3928 KB  Length: 1130 B)
ある整数を素因数分解したとき、2^xの項において、x=0の数Odd,x=1の数Two,x>=2の数Fourとして、それぞれの値をO(N)で求める。1<=i<=N-1 において、a(i)とa(i+1)の積が4の倍数になるためには、(Odd,Four),(Two,Two),(Two,Four),
(Four,Four)の組み合わせとなるように配列aを並び替える必要がある。したがって、Odd,Two,Fourそれぞれの数をあらかじめ数えて置き、配列aの先頭から条件を満たすように整数を置いていく。a(i)を置くとき、a(i-1)の値によって置く
整数の優先度が一意に定まることに注意(貪欲法)。このシミュレーションはO(N)で行える。したがって、全体の最悪計算量は O(N)=10^5 となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

typedef enum state{
	ALL=0,
	EVEN,
	FOUR,
	IMPOSSIBLE
}State;

int n,cntOdd,cnt2,cnt4;

int main() {
	int i,j;
	State now=ALL;
	scanf("%d",&n);
	cntOdd=cnt2=cnt4=0;
	rep(i,n){
		scanf("%d",&j);
		if(j%4==0)
			cnt4++;
		else{
			if(j%2==0)
				cnt2++;
			else
				cntOdd++;
		}
	}
	while(n--){
		//printf("now:%d\n",now);
		//printf("odd:%d even:%d four:%d\n",cntOdd,cnt2,cnt4);
		if(now==IMPOSSIBLE)
			break;
		switch(now){
			case ALL:
				if(cntOdd){
					cntOdd--;
					now=FOUR;
				}else if(cnt2){
					cnt2--;
					now=EVEN;
				}else{
					cnt4--;
					now=ALL;
				}
				//printf("%d\n",ALL);
				break;
			case EVEN:
				if(cnt2){
					cnt2--;
					now=EVEN;
				}else if(cnt4){
					cnt4--;
					now=ALL;
				}else
					now=IMPOSSIBLE;
				//printf("%d\n",EVEN);
				break;
			default:
				if(cnt4){
					cnt4--;
					now=ALL;
				}else
					now=IMPOSSIBLE;
				//printf("%d\n",FOUR);
				break;
		}
	}
	printf("%s\n",now==IMPOSSIBLE?"No":"Yes");
	return 0;
}