import sys
import random

match = int(sys.argv[1])
mismatch = int(sys.argv[2])
gapos = int(sys.argv[3])
gapes = int(sys.argv[4])
seq1 = sys.argv[5]
seq2 = sys.argv[6]

# print(match, mismatch, gapos, gapes, seq1, seq2)

# DP matrices
M, IX, IY = {}, {}, {}
for i in range(len(seq1) + 1):
    M[i], IX[i], IY[i] = {}, {}, {}

# print(M)
# print(IX)
# print(IY)

# Init
M[0][0] = [0, '']
IX[0][0] = [0, '']
IY[0][0] = [0, '']

# Columns
for i in range(1, len(seq1) + 1):
    M[i][0] = [float('-inf'), '']
    IX[i][0] = [gapos + (i - 1) * gapes, 'u']
    IY[i][0] = [float('-inf'), '']
    IY[i][1] = [float('-inf'), '']

# Rows
for j in range(1, len(seq2) + 1):
    M[0][j] = [float('-inf'), '']
    IX[0][j] = [float('-inf'), '']
    IX[1][j] = [float('-inf'), '']
    IY[0][j] = [gapos + (j - 1) * gapes, 'l']

# print(M)
# print(IX)
# print(IY)

# For other cells
for i in range(1, len(seq1) + 1):
    nt1 = seq1[i - 1]
    for j in range(1, len(seq2) + 1):
        nt2 = seq2[j - 1]

        # print(nt1, nt2)

        # Your code here
        match_score = match if nt1 == nt2 else mismatch

        ## Updating M
        M[i][j] = max(
            [M[i - 1][j - 1][0] + match_score, 'd'],
            [IX[i][j - 1][0] + match_score, 'l'],
            [IY[i - 1][j][0] + match_score, 'u']
        )

        ## Updating IX
        IX[i][j] = max(
            [M[i - 1][j - 1][0] + gapos - gapes, 'd'],
            [IX[i][j - 1][0] + gapes, 'l']
        )

        ## Updating IY
        IY[i][j] = max(
            [M[i - 1][j - 1][0] + gapos - gapes, 'd'],
            [IY[i - 1][j][0] + gapes, 'u']
        )

        if i == len(seq1) and j == len(seq2):
            M[i][j][0] -= 1
            IX[i][j][0] -= 1
            IY[i][j][0] -= 1

final_score = max(M[len(seq1)][len(seq2)][0], IX[len(seq1)][len(seq2)][0], IY[len(seq1)][len(seq2)][0])
print("Optimal alignment score =", final_score)

# Trace back
aseq1 = ''
aseq2 = ''

i = len(seq1)
j = len(seq2)

max_mat = ''
if final_score == M[len(seq1)][len(seq2)][0]: max_mat += 'm'
if final_score == IX[len(seq1)][len(seq2)][0]: max_mat += 'x'
if final_score == IY[len(seq1)][len(seq2)][0]: max_mat += 'y'

##
curr_mat = random.choice(max_mat)

while i != 0 or j != 0:
    dirs = ''
    if curr_mat == 'm':
        dirs = M[i][j][1]
    elif curr_mat == 'x':
        dirs = IX[i][j][1]
    else:
        dirs = IY[i][j][1]

    ##
    next_dir = random.choice(dirs)

    # Your code here
    if next_dir == 'd':
        aseq1 += seq1[len(seq1) - i]
        aseq2 += seq2[len(seq2) - j]
        i -= 1
        j -= 1
    elif next_dir == 'l':
        aseq1 += '-'
        aseq2 += seq2[len(seq2) - j]
        j -= 1
    else:
        aseq1 += seq1[len(seq1) - i]
        aseq2 += '-'
        i -= 1

print(aseq1)
print(aseq2)
