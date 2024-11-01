import java.util.*;

public class AVLNode<T extends Comparable<T>> {
    public T item;
    public AVLNode left, right;
    public int height;
    public LinkedList<Place> list = new LinkedList<>();

    public AVLNode(T newItem) {
        item = newItem;
        left = AVLTree.NIL;
        right = AVLTree.NIL;
        height = 1;
    }
    public AVLNode(T newItem, Place p) {
        item = newItem;
        left = AVLTree.NIL;
        right = AVLTree.NIL;
        height = 1;
        list.add(p);
    }
    public AVLNode(T sub, AVLNode leftChild, AVLNode rightChild) {
        item = sub;
        this.left = leftChild;
        this.right = rightChild;
        height = 1;
    }
    public AVLNode(T newItem, AVLNode left, AVLNode right, int h) {
        item = newItem;
        this.left = left;
        this.right = right;
        this.height = h;
    }
}

class Place {
    int line;
    int start;

    public Place() {
        this.line = 0;
        this.start = 0;
    }
    public Place(int line, int start) {
        this.line = line;
        this.start = start;
    }
    public String toString(){
        return "(" + this.line + ", " + this.start + ")";
    }
}
