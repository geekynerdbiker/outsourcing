"""
NAME: 
YID: 

Data Structures
doublylinkedlist.py

2D doubly linked list utils for HW1.
"""

import numpy as np

class Node:
    """ Node class
        
            up
             |
    left - data - right
             |
           down
    """

    def __init__(self, data):
        self.data = data
        self.right = None
        self.left = None
        self.up = None
        self.down = None
        
        
def dllToArray(dll_ptr):
    """ Converts a 2D doubly linked list into an array.
    
    input: 
        dll_ptr: the head (most upper left node) of a 2D dll.
        
    output:
        image: a multi-dimensional array of height x width x channel
            where channel is the dimension of dll.data.
            If dll is originally constructed from a color image, then channel = 3.
            If dll is originally constructed from a 2D array, then channel = 1.
    """
    
    # Height and width of the dll determines the size of the array
    height = getHeight(dll_ptr);
    width = getWidth(dll_ptr);
    
    # Check the dimension of the data
    channel = dll_ptr.data.size
    image = np.empty([height, width, channel])
    down_ptr = dll_ptr
    x = 0
    y = 0
    
    while down_ptr != None:
        right_ptr = down_ptr
        x = 0
        
        while right_ptr != None:
            # When image is stored in a 2D array, the (x,y) location of the image
            # has to be accessed by array[y][x]. This is because the first dimension
            # index of array is for the vertical index 
            # (y-direction, or row-direction) while the second dimension of array 
            # is for the horizontal index (x-direction, or column-direction)
            image[y][x] = right_ptr.data
            right_ptr = right_ptr.right
            x += 1
        down_ptr = down_ptr.down
        y += 1
        
    return image


def display(dll_ptr):
    """ Prints the 2D dll according to their positions similar to 
        printing a 2D array.
    
    input:
        dll_ptr: the head (most upper left node) of a 2D dll.
        
    output:
        None
    """
    right_ptr = None
    down_ptr = dll_ptr
    
    while down_ptr != None:
        right_ptr = down_ptr
        
        while right_ptr != None:
            print(right_ptr.data, end=' ')
            right_ptr = right_ptr.right
        print()
        down_ptr = down_ptr.down
        
        
def compareDLL(dll1, dll2):
    """ Compare two DLLs. This compares all four pointers of each node.
    
    input:
        dll1: the first DLL to compare
        dll2: the second DLL to compare
        
    output:
        true iff dll1 == dll2. false iff not.
    """
    right_dll1 = None
    down_dll1 = dll1
    right_dll2 = None
    down_dll2 = dll2
    
    try:
        while down_dll1 != None:
            right_dll1 = down_dll1
            right_dll2 = down_dll2

            while right_dll1 != None:
                assert(compareNodes(right_dll1, right_dll2))
                assert(compareNodes(right_dll1.left, right_dll2.left))
                assert(compareNodes(right_dll1.right, right_dll2.right))
                assert(compareNodes(right_dll1.up, right_dll2.up))
                assert(compareNodes(right_dll1.down, right_dll2.down))
                right_dll1 = right_dll1.right
                right_dll2 = right_dll2.right
            down_dll1 = down_dll1.down
            down_dll2 = down_dll2.down
            
        print("DLL Comparison: Two DLLs Match!")
    except AssertionError as e:
        print("DLL Comparison: Two DLLs Do NOT Match!")
        
        
def compareNodes(node1, node2):
    """ Simple comparison of two nodes.
    
    input:
        node1
        node2
        
    output:
        boolean: true iff node1 == node2, also handles None
    """
    if node1 is None or node2 is None:
        return node1 == node2
    else:
        return node1.data == node2.data
        

def findSeam(energy_map):
    """ Assigns negative infinity to the horizontal seam given an energy map.
    This is a greedy algorithm which starts from the right most column and
    iteratively picks the minimum entry from left, left.up, and left.down.
    The path is marked by changing the energy_map value along the path to be
    negative infinity.
    
    input:
        energy_map: The cumulative energy map to find the path.
        
    output:
        energy_map: The new cumulative energy map where the path has values
            with negative infinity.
    """
    y_ptr = energy_map
    
    while y_ptr.right != None:
        y_ptr = y_ptr.right
        
    min_ptr = y_ptr
    
    while y_ptr.down != None:
        y_ptr = y_ptr.down
        if y_ptr.data < min_ptr.data:
            min_ptr = y_ptr
            
    min_ptr.data = np.NINF
    while min_ptr.left != None:
        
        min_ptr_leftup = min_ptr.left.up
        min_ptr_left = min_ptr.left
        min_ptr_leftdown = min_ptr.left.down
        
        if(min_ptr_leftup.data <= min_ptr_left.data
           and min_ptr_leftup.data <= min_ptr_leftdown.data):
            min_ptr = min_ptr_leftup
        elif(min_ptr_left.data <= min_ptr_leftup.data
           and min_ptr_left.data <= min_ptr_leftdown.data):
            min_ptr = min_ptr_left
        else:
            min_ptr = min_ptr_leftdown
        
        min_ptr.data = np.NINF
        
    return energy_map


def constructDoublyLinkedListRecursion(arr):
    """ Converts a 2D array into a 2D doubly linked list by calling
    the recursee constructDLLRecursiveStep.
 
    input:
        arr: 2D array to turn into a 2D DLL
        
    output:
        head (top left node) of the 2D DLL of the input arr.
    """
    return constructDLLRecursiveStep(arr, 0, 0, None)
        
    
def getHeight(dll_ptr):
    """ Returns the height of a 2D dll. 
    
    input:
        dll_ptr: the head (most upper left node) of a 2D dll.
        
    output:
        height: the vertical length of the 2D dll.
    """
    height = 0
    while dll_ptr != None:
        dll_ptr = dll_ptr.down
        height += 1
    return height


def removeSeam(image, energy_map):
    """ 
    1. Finds the starting node of the recursive seam removal which is the
        node with -infinity value in the leftmost column of energy map (em_ptr).
        a. Note we also move the pointer to the same location in the image (im_ptr).
    2. Calls the recursive function removeNodeRecursive which starts
        from the node found in step 1, and moves towards the left
        to remove the nodes with -infinity values.
    
    input:
        image: The image in 2D DLL. The seam to remove is the path
            alont the nodes with -infinity values in energy_map.
        energy_map: The energy map in 2D DLL. This contains the seam
            which is the horizontal path of nodes with -infinity values.
                
    output:
        image: The image in 2D DLL after the seam has been removed.
        energy_map: The energy map in 2D DLL after teh seam has been removed.
    """
    em_ptr = energy_map
    im_ptr = image
    
    while em_ptr.down != None:
        em_ptr = em_ptr.down
        im_ptr = im_ptr.down
        if np.isneginf(em_ptr.data):
            min_em_ptr = em_ptr
            min_im_ptr = im_ptr
    
    removeNodeRecursive(min_em_ptr, min_im_ptr)
    
    return [image, energy_map]

# -------------------------- DO NOT CHANGE ABOVE CODES ------------------- #

# -------------------------- IMPLEMENT BELOW YOURSELF -------------------- #


def getWidth(dll_ptr):
    """ Returns the width of a 2D dll. 
    
    input:
        dll_ptr: the head (most upper left node) of a 2D dll.
        
    output:
        width: the horizontal length of the 2D dll.
    """
    width = 0
    while dll_ptr != None:
        dll_ptr = dll_ptr.right
        width += 1
    return width


def constructDoublyLinkedListLoop(arr):
    """ Converts a 2D array into a 2D doubly linked list with loops.
 
    input:
        arr: 2D array to turn into a 2D DLL
        
    output:
        top_left_ptr: head (top left node) of the 2D DLL of the input arr.
    """
    rows = np.shape(arr)[0]
    columns = np.shape(arr)[1]
    x = None
    for i in range(rows):
        if i > 0:
            z = y
        for j in range(columns):
            temp = Node(arr[i,j])
            if i == 0 and j == 0:
                top_left_ptr = temp
            if j == 0:
                y = temp
            if j > 0:
                x.right = temp
                temp.left = x
            x = temp
            if j == columns - 1:
                temp.right = None
            if i > 0:
                temp.up = z
                z.down = temp
                z = z.right
    return top_left_ptr


def constructDLLRecursiveStep(arr, y, x, curr):
    """ Recursively construct the 2D DLL from the given array.
    This is the "recursee" of constructDoublyLinkedListRecursion.
    
    input:
        arr: The 2D array to construct the 2D DLL from.
        y: y-coordinate of the array to get the value from.
        x: x-coordinate of the array to get the value from.
        curr: The current node to connect the new node from.
        
    output:
        new_node: The newly created node which connects to curr node.
    """
    
    rows = np.shape(arr)[0]
    columns = np.shape(arr)[1]
    if y >= rows or x >= columns:
        return None
    new_node = Node(arr[y][x])
    if y > 0:
        new_node.left = curr
    if x > 0:
        new_node.up = curr
    new_node.right = constructDLLRecursiveStep(arr, y, x+1, new_node)
    new_node.down = constructDLLRecursiveStep(arr, y+1, x, new_node)                                 
    return new_node
    
    
def removeNodeRecursive(em_ptr, im_ptr):
    """ Recursive seam removal function.
    Given the current node (em_ptr), suppose it has the
    following neighbor nodes:
    
    UL: Upper Left
    U: Up
    UR: Upper Right
    L: Left
    DL: Down Left
    D: Down
    DR: Down Right
        
    UL --   U    -- UR
    |       |       |
    L  -- em_ptr -- R
    |       |       |
    DL --   D    -- DR
    
    1. em_ptr should be removed because em_ptr.data has NINF.
        a. Do the same for the image 2D DLL using im_ptr.
    2. Only one of UR, R, or DR has -INF data.
        a. Example: if checking R, use np.isneginf(em_ptr.right.data)
    3. Recursively call the next node with NINF you found.
        a. Depending which one of UR, R, or DR you remove next, you need to
            carefully restructure the nodes. See Step 3 of the HW2 slides
            for an example.
           
    Note: You do not need to consider the corner case where
        the nodes to remove are along the image edges (e.g., nodes with up or down 
        nodes that are None). 
           
    input:
        em_ptr: pointer to the energy map node to remove.
        im_ptr: pointer to the image node to remove.
        
    output:
        none
    """
        