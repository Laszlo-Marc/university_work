def shell_sort(array,gaps):
    n = len(array)
    x=0
    for gap in gaps:
        for i in range(gap, n):
            temp = array[i]
            j = i
            while j >= gap and array[j - gap] > temp:
                array[j] = array[j - gap]
                j -= gap

            array[j] = temp
    return array