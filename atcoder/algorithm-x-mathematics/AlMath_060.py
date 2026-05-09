'''アルゴリズムと工夫点(Stones Game 1/CPU: 58 ms Memory: 76328 KB  Length: 58 B)
小さいテストケースを試して，規則性を見つけ出すのポイント．
1 <= N <= 12 の範囲で試してみると，Nが4の倍数の時のみ後手必勝となることが分かり，そのまま実装．
最悪計算量は，O(1)
'''
n = int(input())
print("Second" if n%4 == 0 else "First")