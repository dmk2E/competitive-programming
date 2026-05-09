/*ƒAƒ‹ƒSƒŠƒYƒ€‚ÆH•v“_(˜AŒ‹/CPU: 166 ms  Memory: 40224 KB  Length: 2118 B)
Union-Find–Ø‰^“](“ss‚Æ“S“¹‚ÌƒZƒbƒg)B•’Ê‚Émap‚ÅŠÇ—‚µ‚½•û‚ª‘‚¢B
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 200000
#define NIL -1
using namespace std;

int n, k, l, road[MAX_N], train[MAX_N], ranks[MAX_N], par[MAX_N], cnt[MAX_N];
list<int> adjR[MAX_N], adjT[MAX_N];

//Union-Find–Ø
void init() {
	int i;
	rep(i, n) {
		ranks[i] = 0;
		par[i] = i;
		cnt[i] = 1;
	}
}

int find(int x) {
	if (par[x] == x)
		return x;
	return par[x] = find(par[x]);
}

void unite(int x,int y) {
	x = find(x);
	y = find(y);
	if (x == y)
		return;
	if (ranks[x] < ranks[y]) {
		par[x] = y;
		cnt[y] += cnt[x];
	}
	else {
		par[y] = x;
		if (ranks[x] == ranks[y])
			ranks[x]++;
		cnt[x] += cnt[y];
	}
}

int same(int x,int y) {
	return find(x) == find(y);
}

//˜AŒ‹¬•ª’Tõ
void bfsR(int now,int color) {
	int i;
	queue<int> que;
	road[now] = color;
	que.push(now);
	while (!que.empty()) {
		now = que.front(); que.pop();
		for (int next : adjR[now]) {
			if (road[next] == NIL) {
				road[next] = color;
				que.push(next);
			}
		}
	}
}

void bfsT(int now, int color) {
	int i;
	queue<int> que;
	train[now] = color;
	que.push(now);
	while (!que.empty()) {
		now = que.front(); que.pop();
		for (int next : adjT[now]) {
			if (train[next] == NIL) {
				train[next] = color;
				que.push(next);
			}
		}
	}
}

int main() {
	int i, j;
	map<pair<int, int>, int> v;
	scanf("%d%d%d",&n,&k,&l);
	while (k--) {
		scanf("%d%d",&i,&j);
		adjR[--i].push_back(--j);
		adjR[j].push_back(i);
	}
	while (l--) {
		scanf("%d%d", &i, &j);
		adjT[--i].push_back(--j);
		adjT[j].push_back(i);
	}
	rep(i, n)
		road[i] = train[i] = NIL;
	j = 0;
	rep(i,n)
		if (road[i] == NIL)
			bfsR(i,j++);
	j = 0;
	rep(i, n)
		if (train[i] == NIL)
			bfsT(i, j++);
	/*
	rep(i, n)
		printf("%d:(%d,%d)\n",i,road[i],train[i]);
	*/
	init();
	rep(i, n) {
		if (v[make_pair(road[i], train[i])] == 0)
			v[make_pair(road[i], train[i])] = i + 1;
		else
			unite(v[make_pair(road[i], train[i])]-1,i);
	}
	rep(i, n - 1)
		printf("%d ",cnt[find(i)]);
	printf("%d\n",cnt[find(i)]);
	return 0;
}