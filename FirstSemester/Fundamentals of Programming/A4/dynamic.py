def partition_minimal_difference(S):
    def recursive_partition(S, n, sum1, sum2):
        if n == 0:
            return abs(sum1 - sum2)
        else:
            # Include the nth element in S1
            diff1 = recursive_partition(S, n - 1, sum1 + S[n - 1], sum2)
            # Include the nth element in S2
            diff2 = recursive_partition(S, n - 1, sum1, sum2 + S[n - 1])
            return min(diff1, diff2)

    n = len(S)
    return recursive_partition(S, n, 0, 0)


def partition_minimal_difference_dynamic(S):
    total_sum = sum(S)
    n = len(S)
    dp = [[False for _ in range(total_sum + 1)] for _ in range(n + 1)]
    print(dp)
    for i in range(n + 1):
        dp[i][0] = True
    print(dp)
    for i in range(1, n + 1):
        for j in range(1, total_sum // 2 + 1):
            dp[i][j] = dp[i - 1][j]
            if S[i - 1] <= j:
                dp[i][j] = dp[i][j] or dp[i - 1][j - S[i - 1]]
        print(dp)
    j = total_sum // 2
    while not dp[n][j]:
        j -= 1

    S1, S2 = [], []
    i = n

    while i > 0 and j > 0:
        if dp[i - 1][j]:
            S2.append(S[i - 1])
        else:
            S1.append(S[i - 1])
            j -= S[i - 1]
        i -= 1

    return S1, S2
