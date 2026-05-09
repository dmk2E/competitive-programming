'''アルゴリズムと工夫点(Print 2N+3/CPU: 55 ms Memory: 76816 KB  Length: 28 B)
今更だが，input()は，標準入力を「文字列」として受け取るから，int関数で整数型に直して利用する．
'''
n=int(input())
print(2*n+3)