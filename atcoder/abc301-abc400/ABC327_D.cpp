/*アルゴリズムと工夫点(Good Tuple Problem/CPU: 133 ms  Memory: 50560 KB  Length: 3519 B)
複数のオブジェクト間の関係をまとめるのにはグラフが適しており、条件を満たすかの判定にdfsやbfsを使うようにする。
頂点を訪問する度に、その頂点と1つの辺で繋がっている全ての頂点Niに対して次の操作を行う。もし頂点Niが未訪問ならそこからdfsを開始し、訪問済みなら与えた値が同じでないか確かめ、もし同じだったら条件を満たさず「No」と出力する。
最悪計算量は、O(n+2*m)=O(n+m) となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define swap(a,b,t){t=a,a=b,b=c}
#define MAX_N 200000
#define MAX_M 200000
using namespace std;

enum hasher {
	MAX=2000003,
	NIL=-1
};

typedef enum color {
	BLACK=-1,
	FALSE,
	TRUE
}Color;

typedef struct node {
	int id;
	Color color;
	struct node* prev, * next;
}Node;

typedef struct data {
	int a, b;
}Data;

int n, m,p[MAX_M];
Node *adj[MAX_N];
Color color[MAX_N];
Data table[MAX];

//ハッシュ法の実装(ダブルハッシュ)
void initHash() {
	int i;
	rep(i, MAX)
		table[i].a = NIL;
}

int toKey(int a,int b) {
	return (int)(((long long)a * b) % MAX + (100 * a) % MAX + (1000 * b) % MAX);
}

int h1(int key) {
	return key % MAX;
}

int h2(int key) {
	return 1 + key % (MAX-1);
}

int h(int key, int i) {
	return (int)((h1(key) + ((long long)h2(key) * i )% MAX) % MAX);
}

int insert(int a,int b) {
	int key = toKey(a,b),i=0;
	Data z;
	z.a = a;
	z.b = b;
	while (1) {
		if (table[h(key, i)].a == NIL) {
			table[h(key, i)] = z;
			return h(key,i);
		}else if (i >= MAX)
			break;
		i++;
	}
	return NIL;
}

int search(int a,int b) {
	int key = toKey(a, b), i = 0;
	while (1) {
		if (table[h(key, i)].a == a&& table[h(key, i)].b == b) 
			return h(key, i);
		else if (table[h(key, i)].a == NIL ||i >= MAX)
			break;
		i++;
	}
	return NIL;
}

//双方向リストの実装
void initList() {
	int i;
	rep(i, n) {
		adj[i] = new Node;
		adj[i]->prev = adj[i]->next = adj[i];
		color[i] = BLACK;
	}
}

void addNode(int a,int b) {
	Node* z = new Node;
	z->id = b;
	z->prev = adj[a];
	z->next = adj[a]->next;
	adj[a]->next->prev = z;
	adj[a]->next = z;
}

void deleteNode() {
	int i;
	Node* cur,*temp;
	rep(i, n) {
		cur = adj[i]->next;
		while (cur != adj[i]) {
			cur->next->prev = cur->prev;
			cur->prev->next = cur->next;
			temp = cur;
			cur = cur->next;
			delete temp;
		}
	}
}

void showList() {
	int i;
	Node* cur;
	rep(i, n) {
		printf("%d:", i);
		cur = adj[i]->next;
		if (adj[i] == cur) {
			cout << endl;
			continue;
		}
		while (cur->next != adj[i]) {
			printf("%d->", cur->id);
			cur = cur->next;
		}
		printf("%d\n",cur->id);
	}
}

//深さ優先探索の実装
bool dfs(int id,Color c) {
	Node* cur=adj[id]->next;
	color[id] = c;
	while(cur!=adj[id]) {
		if (color[cur->id] == BLACK)
			switch (c) {
			case TRUE:
				if(dfs(cur->id,FALSE)==false)
					return false;
				break;
			default:
				if(dfs(cur->id, TRUE)==false)
					return false;
				break;
			}
		else if (color[cur->id] == color[id])
			return false;
		cur = cur->next;
	}
	return true;
}

void showColor() {
	int i;
	rep(i, n)
		printf("%d:%d\n",i,color[i]);
}

int main() {
	int i,j;
	bool flag;
	scanf_s("%d%d",&n,&m);
	//scanf("%d%d", &n, &m);   //ソースコード提出用
	initList();
	initHash();
	rep(i, m) {
		scanf_s("%d", &p[i]);
		//scanf("%d", &p[i]);
	}
	rep(i, m) {   //同じ(a,b)の組を登録しないように、ハッシュ法で管理する。
		scanf_s("%d", &j);
		//scanf("%d", &j);
		p[i]--;
		j--;
		flag = false;
		if (p[i] < j) {
			if (search(p[i], j) == NIL) {
				insert(p[i], j);
				flag = true;
				//printf("new:%d %d\n", p[i], j);
			}else {
				//printf("exist:%d %d\n", p[i], j);
			}
		}
		else {
			if (search(j, p[i]) == NIL) {
				insert(j, p[i]);
				flag = true;
				//printf("new:%d %d\n",  j,p[i]);
			}
			else {
				//printf("exist:%d %d\n",j,p[i]);
			}
		}
		if (flag){
			addNode(p[i], j);
			addNode(j, p[i]);
		}
	}
	//showList();
	rep(i, n)
		if (color[i]==BLACK && dfs(i, FALSE) == false)
			break;
	if (i==n)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	//showColor();
	deleteNode();
	return 0;
}