'''アルゴリズムと工夫点(We Used to Sing a Song Together（★3）/CPU: 106 ms Memory: 137724 KB  Length: 187 B)
貪欲法で解く．
家と小学校それぞれについて，位置の昇順にソートし，前から順番にマッチングすればよい．
最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
'''
n = int(input())

a = list(map(int, input().split()))
b = list(map(int, input().split()))

a.sort();b.sort()

ans = 0
for i in range(n):
    ans += abs(a[i] - b[i])

print(ans)