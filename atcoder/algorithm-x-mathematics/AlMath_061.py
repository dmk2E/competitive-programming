'''アルゴリズムと工夫点(Stones Game 2/CPU: 56 ms Memory: 76880 KB  Length: 94 B)
規則性を利用する．
小さいテストケースについての解を順に求めてみると，N = 2^(k)-1 である時のみ後手必勝である．
そこで，N+1 = 2^(k) であるかを判定すればよく，最悪計算量は，O(log2(N)) < 10^2 となり高速．
'''
n = int(input())
n += 1
while n%2 == 0:
    n //= 2
print("Second" if n == 1 else "First")