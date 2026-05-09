/*アルゴリズムと工夫点(Long Bricks/CPU: 309 ms  Memory: 11556 KB  Length: 1835 B)
単純なシミュレーションで解く場合、与えられた区間の中で現時点での最大の高さを探索し、その値に1加算した値にその区間の要素を更新すれ場良いから、最悪計算量はO(NW) となる。
ただしこのアルゴリズムだと、Wの値が大きい場合に対応できない。そこで、保持しなければならない高さhの値に着目する。hの値は、与えられる区間の両端でしか値が変化しない。このことを考えると、保持する座標を区間の両端の座標
のみ絞ることができる。これを「座標圧縮」という。
ある一次元配列上の区間に関する処理を高速で行うには、セグメント木が有効で、これは一つの値の更新と、ある区間の情報を高速に取り出せるのが特徴。しかし、一度に複数の値の更新を行う場合、その値が必要になるまで更新をさぼる
遅延評価セグメント木が有効となる。遅延評価ではqueryと同じように上から辿って、求めたい範囲内に、頂点が示す範囲がきちんと収まったら、その頂点の遅延情報を更新して、遅延評価を行うeval関数を呼び出す。ここでeval関数では
、呼び出した頂点の値更新と、子供への遅延情報の伝搬を行う。updateと同じように、mappingでも、子に対するmapping処理が終わったら親の情報を更新する。
*/
#include <iostream>
#include <vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_W 500000
#define NIL 0
using namespace std;

typedef struct data{
	int max,delay;

	data(int mmax=NIL,int ddelay=0):max(mmax),delay(ddelay){}
}Data;

int w,n,l,r;
vector<Data> segT;

void init(int n){
	int nn=1;
	while(nn<n)nn*=2;
	segT.resize(2*nn-1,Data());
}

void update(int k,int a){
	k+=(segT.size()+1)/2-1;
	segT[k].max=a;
	while(k>0){
		k=(k-1)/2;
		segT[k]=max(segT[2*k+1].max,segT[2*k+2].max);
	}
}

void eval(int k,int l,int r){
	if(segT[k].delay!=0){
		//遅延情報による値の更新
		segT[k].max=segT[k].delay;
		if(r-l>1){   //葉でなければ、親から子に遅延情報を伝搬させる。値の更新はしない
			segT[2*k+1].delay=segT[k].delay;
			segT[2*k+2].delay=segT[k].delay;
		}
		segT[k].delay=0;
	}
}

void mapping(int a,int b,int k,int l,int r,int udt){
	eval(k,l,r);
	if(b<=l||r<=a)return ;
	if(a<=l&&r<=b){
		segT[k].delay=udt;
		eval(k,l,r);
		//printf("k:%d [%d,%d) max:%d\n",k,l,r,segT[k].max);
		return ;
	}
	mapping(a,b,2*k+1,l,(l+r)/2,udt);mapping(a,b,2*k+2,(l+r)/2,r,udt);
	segT[k].max=max(segT[2*k+1].max,segT[2*k+2].max);
}

int query(int a,int b,int k,int l,int r){
	if(b<=l||r<=a)return NIL;
	eval(k,l,r);
	if(a<=l&&r<=b)return segT[k].max;
	int ll=query(a,b,2*k+1,l,(l+r)/2),rr=query(a,b,2*k+2,(l+r)/2,r);
	return max(ll,rr);
}

int main() {
	int i,j;
	scanf("%d%d",&w,&n);
	init(w);
	rep(i,w)
		update(i,0);
	rep(i,n){
		scanf("%d%d",&l,&r);
		printf("%d\n",j=(query(l-1,r,0,0,(segT.size()+1)/2)+1));
		//printf("[%d,%d):\n",l-1,r);
		mapping(l-1,r,0,0,(segT.size()+1)/2,j);
		//puts("");rep(j,w)printf("(%d,%d,%d)",j,segT[j+(segT.size()+1)/2-1].max,segT[j+(segT.size()+1)/2-1].delay);puts("");
	}
	return 0;
}