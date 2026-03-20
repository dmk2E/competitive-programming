'''アルゴリズムと工夫点(Parentheses Check/CPU: 68 ms Memory: 104652 KB  Length: 455 B)
スタックの考え方を利用して解く．
「Sが正しい括弧列である」とは，
・先頭から任意の地点までの部分文字列において，（'(' の数）>= （')'の数）を
・Sに含まれる'('と')'の数を等しい
を満たす．
これを純粋に判定すればよい．
最悪計算量は，O(|S|) < 10 ^ 7 となり間に合う．
※ 今回は必要ないが，問題によってはスタックというデータ構造を併用数場合もある
'''
import sys

n = 0
s = ""

def judge() -> bool:
    global n, s
    par_cnt = 0
    for c in s:
        if c == '(': 
            par_cnt += 1
        elif par_cnt > 0: 
            par_cnt -= 1
        else:
            return False
    return par_cnt == 0

def main(argv: list[str]):
    global n, s
    n = int(input())
    s = input()
    print("Yes" if judge() else "No")

if __name__ == "__main__":
    main(argv=sys.argv[1:])
