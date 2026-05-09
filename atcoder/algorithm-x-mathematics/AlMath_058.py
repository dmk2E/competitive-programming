'''アルゴリズムと工夫点(Move on Squares 1/CPU: 57 ms Memory: 76540 KB  Length: 106 B)
(X,Y)への移動に必要な最小の移動回数は X+Y である．
そのため，N >= X+Y である必要があり，N-(X+Y)が偶数であれば，残りの移動回数を消化しつつ，N回目に特定の(X,Y)に到達可能である．
最悪計算量は，O(1) となり十分高速．
'''
n,x,y = map(int,input().split())
x=abs(x);y=abs(y)
print("Yes" if (n >= x+y and (n-x-y)%2==0) else "No")