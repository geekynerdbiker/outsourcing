def wfa(ga, gaScore):
    matrix = [[0 for i in range(gaScore * 2 + 1)] for j in range(ga+1)]  # create matrix

    # dia = row - col  # anti = row + col  # row = (anti + dia) / 2  # col = (anti - dia) / 2
    # (score, dia) = anti

def globalAlignment(seq1, seq2):
    matrix = [[0 for i in range(cols)] for j in range(rows)]  # create matrix
    ctr = 0
    # setting first row and column with gap penalties
    for j in range(cols):
        matrix[0][j] = ctr
        ctr += gap

    ctr = 0
    for i in range(rows):
        matrix[i][0] = ctr
        ctr += gap

    # computing dynamic programming matrix
    for i in range(rows):
        for j in range(cols):
            if i > 0 and j > 0:
                top = matrix[i - 1][j] + gap  # gap in sequence 1
                left = matrix[i][j - 1] + gap  # gap in sequence 2
                if seq1[j - 1] == seq2[i - 1]:  # match
                    diag = matrix[i - 1][j - 1] + match
                else:  # mismatch
                    diag = matrix[i - 1][j - 1] + mismatch

                # taking max of 3 possibilities
                matrix[i][j] = max(top, left, diag)

    for row in matrix:
        print(row)

    print('\nOptimal score: ')
    print(matrix[rows - 1][cols - 1])
    print('\nAligned sequences: ')

    # backtrack from last element in matrix to find aligned sequences
    reconstruct(matrix, rows - 1, cols - 1, '', '', '')

    return matrix


def reconstruct(matrix, rowpos, colpos, a1, a2, a3):  # generates optimal aligments
    if rowpos == 0 and colpos == 0:  # base case
        print(a1)
        print(a2)
        print(a3)
        return

    if rowpos == 0 and colpos != 0:
        if matrix[rowpos][colpos - 1] == matrix[rowpos][colpos] - gap:
            reconstruct(matrix, rowpos, colpos - 1, seq1[colpos - 1] + a1, ' ' + a2, '_' + a3)
            return

    if rowpos != 0 and colpos == 0:
        if matrix[rowpos - 1][colpos] == matrix[rowpos][colpos] - gap:
            reconstruct(matrix, rowpos - 1, colpos, '_' + a1, ' ' + a2, seq2[rowpos - 1] + a3)
            return

    if seq1[colpos - 1] == seq2[rowpos - 1]:
        if matrix[rowpos - 1][colpos - 1] == matrix[rowpos][colpos] - match:
            reconstruct(matrix, rowpos - 1, colpos - 1, seq1[colpos - 1] + a1, '|' + a2, seq2[rowpos - 1] + a3)

    if seq1[colpos - 1] != seq2[rowpos - 1]:
        if matrix[rowpos - 1][colpos - 1] == matrix[rowpos][colpos] - mismatch:
            reconstruct(matrix, rowpos - 1, colpos - 1, seq1[colpos - 1] + a1, ' ' + a2, seq2[rowpos - 1] + a3)

    if matrix[rowpos - 1][colpos] == matrix[rowpos][colpos] - gap:
        reconstruct(matrix, rowpos - 1, colpos, '_' + a1, ' ' + a2, seq2[rowpos - 1] + a3)

    if matrix[rowpos][colpos - 1] == matrix[rowpos][colpos] - gap:
        reconstruct(matrix, rowpos, colpos - 1, seq1[colpos - 1] + a1, ' ' + a2, '_' + a3)


def reconstructLocal(matrix, rowpos, colpos, a1, a2, a3):  # generates optimal aligments
    if matrix[rowpos][colpos] == 0:  # base case

        print(a1)
        print(a2)
        print(a3)
        return

    if seq1[colpos - 1] == seq2[rowpos - 1]:
        if matrix[rowpos - 1][colpos - 1] == matrix[rowpos][colpos] - match:
            reconstructLocal(matrix, rowpos - 1, colpos - 1, seq1[colpos - 1] + a1, '|' + a2, seq2[rowpos - 1] + a3)

    if seq1[colpos - 1] != seq2[rowpos - 1]:
        if matrix[rowpos - 1][colpos - 1] == matrix[rowpos][colpos] - mismatch:
            reconstructLocal(matrix, rowpos - 1, colpos - 1, seq1[colpos - 1] + a1, ' ' + a2, seq2[rowpos - 1] + a3)

    if matrix[rowpos - 1][colpos] == matrix[rowpos][colpos] - gap:
        reconstructLocal(matrix, rowpos - 1, colpos, '_' + a1, ' ' + a2, seq2[rowpos - 1] + a3)

    if matrix[rowpos][colpos - 1] == matrix[rowpos][colpos] - gap:
        reconstructLocal(matrix, rowpos, colpos - 1, seq1[colpos - 1] + a1, ' ' + a2, '_' + a3)


# seq1 = list(input('Sequence 1: '))  # input sequence 1
# seq2 = list(input('Sequence 2: '))  # input sequence 2
# match = int(input('Enter scoring function.\nMatch: '))  # input scoring function
# mismatch = int(input('Mismatch: '))
# gap = int(input('Gap: '))

seq1, seq2 = "ACACACTA", "AGCACACA"
match, mismatch, gap = 1, 0, -1
cols = len(seq1) + 1
rows = len(seq2) + 1

print('\nGlobal Alignment:\n')

# compute global alignment using dynamic programming
ga = globalAlignment(seq1, seq2)
wfa(ga, ga[rows - 1][cols - 1])
