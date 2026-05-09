'''アルゴリズムと工夫点(Bishop/CPU: 57 ms Memory: 79964 KB  Length: 164 B)
高さと幅が共に2以上ある場合は，到達可能なマスは市松模様のようになることを利用する．
そうでない場合に，解は1となることに注意．
'''
h, w = map(int, input().split())

first_col_cnt = (h + 1) // 2

print(first_col_cnt * ((w + 1) // 2) + (h - first_col_cnt) * (w // 2) if h > 1 and w > 1 else 1)