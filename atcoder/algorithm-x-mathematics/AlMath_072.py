'''アルゴリズムと工夫点(Max GCD 2/CPU: 73 ms Memory: 86420 KB  Length: 146 B)
最大公約数系の問題は，「倍数」に着目して全探索する．
今回の場合，「kの倍数か？」という条件を満たすか全探索すれば解ける．
最悪計算量は，O(B) < 10 ^ 6 となり十分高速．
※ ([a, b] に含まれるkの倍数の数) = (floor(b / k) - floor((a - 1) / k))
'''
a, b = map(int, input().split())
ans = 0

for i in range(1, b + 1): 
    if b // i - (a - 1) // i >= 2:
        ans = max(ans, i)
print(ans)