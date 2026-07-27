# 預先計算 0 到 300 的答案
answer = [1] * 301

for n in range(1, 301):
    answer[n] = (
        answer[n - 1]
        * (2 * n)
        * (2 * n - 1)
        // (n + 1)
)

# 一行一行讀取輸入
while True:
    n = int(input())

    if n == 0:
        break

    print(answer[n])

'''
題目:
給定 n 個彼此不同的元素，計算能建立多少棵不同的「有標號二元樹」

T_n = T_(n-1) * (2n) * (2n-1) / (n+1)
'''
