'''アルゴリズムと工夫点(Sum of 3 Integers/CPU: 58 ms Memory: 75740 KB  Length: 44 B)
要素が複数並んだデータ構造である「タプル」や「リスト」は，以下の式の様に，一つの式で複数の変数に代入する処理，「アンパック」することができる．
'''
a,b,c=map(int,input().split())
print(a+b+c)