'''アルゴリズムと工夫点(Coin Gacha/CPU: 66 ms Memory: 81388 KB  Length: 81 B)
期待値の線型性を利用する問題だが，どんな値を確率変数とするか決定するのがかなり難しい．
なので，分からなければ公式解説を参照すること
'''
n=int(input())
ans=0.0
for i in range(1,n+1):
    ans+=1/i
ans*=n
print(ans)