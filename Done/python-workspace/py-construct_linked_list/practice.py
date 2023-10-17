dim = 3
right = 0
down = 1
dList = []

# struct node of doubly linked
# list with four pointer
# next, prev, up, down
class Node:

    def __init__(self, data):
        self.data = data
        self.left = None
        self.up = None
        self.down = None
        self.right = None


# new node
def createNode(data):
    temp = Node(data)
    return temp


# function to construct the
# doubly linked list
def constructDoublyListUtil(mtrx, i, j, curr, dir):
    if i >= dim or j >= dim:
        return None

    temp = createNode(mtrx[i][j])

    for node in dList:
        if node.data == mtrx[i][j]:
            temp = node
    # Assign address of curr into
    # the prev pointer of temp
    if dir == right:
        temp.left = curr

    # Assign address of curr into
    # the up pointer of temp
    if dir == down:
        temp.up = curr
        # temp.left = curr.left.down.right

    # Recursive call for next
    # pointer
    temp.right = constructDoublyListUtil(mtrx, i, j + 1, temp, right)

    # Recursive call for down pointer
    temp.down = constructDoublyListUtil(mtrx, i + 1, j, temp, down)

    # Return newly constructed node
    # whose all four node connected
    # at it's appropriate position
    dList.append(temp)
    return temp


# Function to construct the
# doubly linked list
def constructDoublyList(mtrx):
    # function call for construct
    # the doubly linked list
    return constructDoublyListUtil(mtrx, 0, 0, None, None)


# function for displaying
# doubly linked list data
def display(head):
    # pointer to move right
    rPtr = None

    # pointer to move down
    dPtr = head

    # loop till node->down
    # is not NULL
    while (dPtr != None):

        rPtr = dPtr

        # loop till node->right
        # is not NULL
        while (rPtr != None):
            msg = f"{rPtr.data} | "
            for i, direction in enumerate([("top", rPtr.up), ("right", rPtr.right), ("down", rPtr.down),
                                           ("left", rPtr.left)]):
                direction_str, direction_ptr = direction
                if direction_ptr:
                    msg += f"{direction_str}: {direction_ptr.data}"
                else:
                    msg += f"{direction_str}: None"
                msg += ", "
            print(msg)
            rPtr = rPtr.right

        print()
        dPtr = dPtr.down


# Driver code
if __name__ == "__main__":
    # initialise matrix
    mtrx = [[1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]]

    list = constructDoublyList(mtrx)
    display(list)
