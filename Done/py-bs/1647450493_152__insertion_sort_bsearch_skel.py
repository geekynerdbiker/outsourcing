import random

global binary_tn
# parameters:
#   - @arr is the array on which the binary search shall be run
#   - @l is the lower index of @arr
#   - @h is the higher index of @arr
#   - @key : the key value
# return: 
#   - the index where the @key value shall be placed in
def binary_search(arr, l, h, key):
    global binary_tn

    binary_tn += 1
    if h > l:  # base case
        binary_tn += 1
        # compute the middle index of array

        m = (h + l) // 2
        binary_tn += 1

        # if middle element is key, return mid
        binary_tn += 1
        if arr[m] == key:
            binary_tn += 1
            return m

        # if m > key, element is in the left half
        elif arr[m] > key:
            binary_tn += 1
            return binary_search(arr, l, m, key)  #### HERE ####

        # else element is in the right half

        else:
            binary_tn += 1
            return binary_search(arr, m + 1, h, key)  #### HERE ####

    else:
        binary_tn += 1
        return h  #### HERE ####


# the insertion sort algorithm
def insertion_sort(A):
    # T(n) counter
    tn = 0

    tn += 1  # for loop's exit case
    for j in range(1, len(A)):
        tn += 1  # for loop cost

        key = A[j]
        tn += 1

        # i = j - 1
        # tn += 1
        #
        # tn += 2  # for the while loop's exit case. (two comparisons, so cost=2 for each iteration)
        # while i >= 0 and A[i] > key:
        #     tn += 2  # for the while loop
        #
        #     A[i + 1] = A[i]
        #     tn += 1
        #
        #     i = i - 1
        #     tn += 1
        #
        # A[i + 1] = key
        tn += 1

        #### HERE - START ####
        #
        # find the correct index for @key
        # comment out ln 65
        global binary_tn

        binary_tn = 0
        i = binary_search(A[:j], 0, len(A[:j]) - 1, key)

        k = j - 1
        tn += 1

        tn += 1
        while k >= i:
            tn += 1

            A[k + 1] = A[k]
            tn += 1
            k = k - 1
            tn += 1

        A[i] = key
        tn += 1
        #
        # line 65 is not enough, some more code is required to
        # complete the binary search applied insertion sort
        # hint: about 5 more lines of code needed

        #### HERE - END ####

    tn += 1  # the return cost = 1
    return tn


# generate a list of random integers in range of @
n = 1000
max_val = n * 10
random.seed(1234) # seed number for the random generator
A = random.sample(range(0, max_val), n)

# print input
print("Input: n=%d" % (n))
print(A)

# run insertion sort
tn = insertion_sort(A)

# print output
print("Output:")
print(A)

# print T(n)
print("T(n):", tn)
print("Bianry T(n):", binary_tn)
