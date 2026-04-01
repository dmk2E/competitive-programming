'''アルゴリズムと工夫点(Tree Distance（★5）/CPU: 242 ms Memory: 122872 KB  Length: 810 B)
DFS で解く．
2頂点間の全ての経路において，各辺を通る回数を考えると，その総和が解となる．
各辺を通る回数は，その辺によってグラフが，頂点数A, B個に分割された時，A * B回となる．
従って，頂点1を根とし，DFS（オイラーツアー）を行うことで，各頂点の配下にいくつ頂点が存在するか求め，
その頂点を端点としてもつ辺を通る回数を加算していけばよい．
最悪計算量は，O(N) < 10 ^ 6 となり，十分高速．
※ 直接総和を求められない時，「足される回数を考えるテクニック」を試してみる
※ Python で提出する場合，最大再帰呼び出し回数を更新しておくこと
'''
import sys

MAX_N = 10**5

n = 0
adj: list[list[int]] = [[]]

sys.setrecursionlimit(MAX_N + 1)

def dfs(prev: int, now: int) -> tuple[int, int]: 
    global n, adj
    sum, sum_nodes = 0, 1
    for x in adj[now]: 
        if x != prev: 
            tmp_sum, tmp_sum_nodes = dfs(prev=now, now=x)
            sum += tmp_sum
            sum_nodes += tmp_sum_nodes
    return (sum + sum_nodes * (n - sum_nodes), sum_nodes)

def main(argv: list[str]):
    global n, adj
    n = int(input())
    adj = [[] for _ in range(n)]
    for _ in range(n - 1): 
        a, b = map(int, input().split())
        a -= 1;b -= 1
        adj[a].append(b)
        adj[b].append(a)
    NIL = -1
    ans, _ = dfs(prev=NIL, now=0)
    print(ans)

if __name__ == "__main__":
    main(argv=sys.argv[1:])