'''アルゴリズムと工夫点(Number of Multiples 2/CPU: 74 ms Memory: 98000 KB  Length: 500 B)
包除原理 + bit全探索で解く．
k 個の条件それぞれを満たす要素の集合，c1, c2, ..., ck が存在する時，
c1 から ck の和集合の要素数は包除原理により求められる．
このとき，1個の集合の要素数は加算し，
2個の集合の共通部分は減算し，
3個の集合の共通部分は加算するという操作を，k 個の集合の共通部分まで繰り返す．
今回の場合，各条件は「Vの特定の要素で割り切れる数」であり，
複数の条件を満たす集合の数は，Vの複数要素の最小公倍数である．
最悪計算量は，O(2 ^ K * K) < 10 ^ 5 となり十分高速．
'''
def gcd(a: int, b: int) -> int:
    return a if b == 0 else gcd(b, a % b)

def lcm(a: int, b: int) -> int:
    return a // gcd(a, b) * b

n, k = map(int, input().split())
v = list(map(int, input().split()))

ans = 0
for s in range(1, 1 << k):
    cnt = 0
    now_lcm = 1
    for i in range(k):
        if (s >> i) & 1:
            cnt += 1
            now_lcm = lcm(now_lcm, v[i])
    if cnt % 2 == 1:
        ans += n // now_lcm
    else :
        ans -= n // now_lcm
print(ans)