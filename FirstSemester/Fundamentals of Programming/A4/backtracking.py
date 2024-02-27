def has_common_digit(x, y):
    while x!=0:
        digit= x%10
        cop =y
        while cop!=0:
            if digit == cop%10:
                return True
            else:
                cop=cop//10
        x=x//10
    return False


def find_subsequences_rec(seq):
    def backtrack(start,sub):
        if len(sub) >= 2:
            subsequences.append(sub[:])
        for i in range(start,len(seq)):
            if not sub or has_common_digit(sub[-1],seq[i]) and sub[-1]<=seq[i]:
                sub.append(seq[i])
                backtrack(i+1,sub)
                sub.pop()

    subsequences = []
    backtrack(0,[])
    return subsequences


def find_subsequences_iterative(seq):
        subsequences = []
        stack = []

        for i in range(len(seq)):
            stack.append(([seq[i]], i))

        while stack:
            current, index = stack.pop()
            if len(current) >= 2:
                subsequences.append(current[:])

            for i in range(index + 1, len(seq)):
                if has_common_digit(current[-1], seq[i]) and current[-1] <= seq[i]:
                    new_seq = current + [seq[i]]
                    stack.append((new_seq, i))

        return subsequences