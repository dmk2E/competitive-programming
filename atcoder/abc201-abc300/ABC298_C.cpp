/*アルゴリズムと工夫点(Cards Query Problem/CPU: 531 ms  Memory: 57412 KB  Length: 911 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n,q;
map<int,set<int> > box;
map<int,map<int,int> > cnt;
map<int,set<int> > card;

int main() {
	int i,j;
	set<int>::iterator it;
	scanf("%d%d",&n,&q);
	while(q--){
		scanf("%d",&i);
		if(i==1){
			scanf("%d%d",&i,&j);
			box[j].insert(i);
			cnt[j][i]++;
			card[i].insert(j);
		}else if(i==2){
			scanf("%d",&i);
			for(it=box[i].begin();;it++){
				it++;
				if(it==box[i].end())
					break;
				it--;
				j=cnt[i][*it];
				while(j--){
					printf("%d ",*it);
				}
			}
			it--;
			j=cnt[i][*it]-1;
			rep(i,j){
				printf("%d ",*it);
			}
			printf("%d\n",*it);
		}else{
			scanf("%d",&i);
			for(it=card[i].begin();;it++){
				it++;
				if(it==card[i].end())
					break;
				it--;
				printf("%d ",*it);
			}
			it--;
			printf("%d\n",*it);
		}
	}
	return 0;
}