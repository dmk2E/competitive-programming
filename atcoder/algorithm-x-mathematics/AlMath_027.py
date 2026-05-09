'''アルゴリズムと工夫点(Sorting/CPU: 207 ms Memory: 123964 KB  Length: 493 B)
マージソート自体の説明は参考書に任せる．
ポイントは，左半分と右区間それぞれの数列が昇順に並んでいる時，それらを元に昇順の数列を合成するのにかかる最悪計算量はO(N)で抑えられること．
この時，最も大きい値を番兵として末尾に追加しておくと，処理しやすくなる．
区間がどんどん半分になっていくから，再帰呼び出しの深さは最大でも log2(N) 程になる．
それぞれの深さでの区間合成の計算量はO(N) となるから最悪計算量は O(N*log2(N)) 
※おまけ
マージソート
・長所:安定なソートなる
・短所:メモリ消費量が大きいこと
クイックソート
・長所:元の配列以上のメモリを使用しない
・短所:真ん中の値の選定方法によっては，最悪計算量がO(N^2)
※再帰関数は，再帰呼び出しをせずに終了する条件を先に書いておくと良い．
'''
MAX_A=int(1e9)+1
def merge(l,r)->list:
    #再帰の終了条件を先に書く
    if r-l==1:
        return [a[l]]
    left=merge(l,(l+r)//2)
    right=merge((l+r)//2,r)
    #番兵をセットしておく
    left.append(MAX_A)
    right.append(MAX_A)
    rgt=[]
    i,j=0,0
    while i<len(left)-1 or j<len(right)-1:
        if left[i]<right[j]:
            rgt.append(left[i])
            i+=1
        else :
            rgt.append(right[j])
            j+=1
    return rgt
n=int(input())
a=list(map(int,input().split()))
a=merge(0,n)
print(*a)