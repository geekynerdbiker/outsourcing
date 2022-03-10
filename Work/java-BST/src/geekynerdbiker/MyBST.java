import java.util.ArrayList;
import java.util.Stack;


public class MyBST<K extends Comparable<K>, V> {
    MyBSTNode<K, V> root = null;
    int size = 0;

    public int size() {
        return size;
    }

    public V insert(K key, V value) {
        // TODO
        MyBSTNode<K, V> node = this.root;

        if (key == null) {
            throw new NullPointerException();
        }
        if (node == null) {
            this.root = new MyBSTNode<>(key, value, null);
            this.size++;
        } else {
            while (true) {
                if (node.getKey().compareTo(key) > 0) {
                    if (node.getLeft() == null) {
                        node.setLeft(new MyBSTNode<>(key, value, node));
                        this.size++;
                        return value;
                    } else node = node.getLeft();
                } else if (node.getKey().compareTo(key) < 0) {
                    if (node.getRight() == null) {
                        node.setRight(new MyBSTNode<>(key, value, node));
                        this.size++;
                        return value;
                    } else node = node.getRight();
                } else {
                    node.setValue(value);
                    return value;
                }
            }
        }
        return null;
    }

    public V search(K key) {
        MyBSTNode<K, V> n = this.root;

        while (n != null) {
            int cmp = key.compareTo(n.getKey());
            if (cmp < 0) {
                n = n.getLeft();
            } else if (cmp > 0) {
                n = n.getRight();
            } else {
                return n.getValue();
            }
        }
        return null;
    }

    public V remove(K key) {
        // TODO
        MyBSTNode<K, V> parent = null;
        MyBSTNode<K, V> curr = root;

        while (curr != null) {
            if (curr.getKey().equals(key)) {
                V oldValue = curr.getValue();
                if (curr.getLeft() == null && curr.getRight() == null) {
                    if (parent == null) {
                        root = null;
                    } else if (parent.getLeft() == curr) {
                        parent.setLeft(null);
                    } else {
                        parent.setRight(null);
                    }
                } else if (curr.getRight() == null) {
                    if (parent == null) {
                        root = curr.getLeft();
                    } else if (parent.getLeft() == curr) {
                        parent.setLeft(curr.getLeft());
                    } else {
                        parent.setRight(curr.getLeft());
                    }
                } else if (curr.getLeft() == null) {
                    if (parent == null) {
                        root = curr.getRight();
                    } else if (parent.getLeft() == curr) {
                        parent.setLeft(curr.getRight());
                    } else {
                        parent.setRight(curr.getRight());
                    }
                } else {
                    MyBSTNode<K, V> succ = curr.successor();
                    while (succ.left != null) {
                        succ = succ.getLeft();
                    }
                    K succKey = succ.getKey();
                    V succValue = succ.getValue();

                    remove(succ.getKey());
                    curr.setValue(succValue);
                    curr.setKey(succKey);
                    size--;
                }
                return oldValue;
            } else if (curr.key.compareTo(key) < 0) {
                parent = curr;
                curr = curr.right;
            } else {
                parent = curr;
                curr = curr.left;
            }
        }
        return null;
    }

    public ArrayList<MyBSTNode<K, V>> inorder() {
        // TODO
        ArrayList<MyBSTNode<K, V>> result = new ArrayList<>();

        if (this.root == null)
            return result;

        Stack<MyBSTNode<K, V>> s = new Stack<>();
        MyBSTNode<K, V> curr = this.root;

        while (curr != null || s.size() > 0) {
            while (curr != null) {
                s.push(curr);
                curr = curr.getLeft();
            }
            curr = s.pop();
            result.add(curr);
            curr = curr.getRight();
        }

        return result;
    }

    static class MyBSTNode<K, V> {
        private static final String TEMPLATE = "Key: %s, Value: %s";
        private static final String NULL_STR = "null";

        private K key;
        private V value;
        private MyBSTNode<K, V> parent;
        private MyBSTNode<K, V> left = null;
        private MyBSTNode<K, V> right = null;

        /**
         * Creates a MyBSTNode<K,V> storing specified data
         *
         * @param key    the key the MyBSTNode<K,V> will
         * @param value  the data the MyBSTNode<K,V> will store
         * @param parent the parent of this node
         */
        public MyBSTNode(K key, V value, MyBSTNode<K, V> parent) {
            this.key = key;
            this.value = value;
            this.parent = parent;
        }

        /**
         * Return the key stored in the the MyBSTNode<K,V>
         *
         * @return the key stored in the MyBSTNode<K,V>
         */
        public K getKey() {
            return key;
        }

        /**
         * Return data stored in the MyBSTNode<K,V>
         *
         * @return the data stored in the MyBSTNode<K,V>
         */
        public V getValue() {
            return value;
        }

        /**
         * Return the parent
         *
         * @return the parent
         */
        public MyBSTNode<K, V> getParent() {
            return parent;
        }

        /**
         * Return the left child
         *
         * @return left child
         */
        public MyBSTNode<K, V> getLeft() {
            return left;
        }

        /**
         * Return the right child
         *
         * @return right child
         */
        public MyBSTNode<K, V> getRight() {
            return right;
        }

        /**
         * Set the key stored in the MyBSTNode<K,V>
         *
         * @param newKey the key to be stored
         */
        public void setKey(K newKey) {
            this.key = newKey;
        }

        /**
         * Set the data stored in the MyBSTNode<K,V>
         *
         * @param newValue the data to be stored
         */
        public void setValue(V newValue) {
            this.value = newValue;
        }

        /**
         * Set the parent
         *
         * @param newParent the parent
         */
        public void setParent(MyBSTNode<K, V> newParent) {
            this.parent = newParent;
        }

        /**
         * Set the left child
         *
         * @param newLeft the new left child
         */
        public void setLeft(MyBSTNode<K, V> newLeft) {
            this.left = newLeft;
        }

        /**
         * Set the right child
         *
         * @param newRight the new right child
         */
        public void setRight(MyBSTNode<K, V> newRight) {
            this.right = newRight;
        }

        /**
         * TODO: add inline comments for this method to demonstrate your
         * understanding of this method. The predecessor can be implemented
         * in a similar way.
         * <p>
         * This method returns the in order successor of current node object.
         * It can be served as a helper method when implementing inorder().
         *
         * @return the successor of current node object
         */
        public MyBSTNode<K, V> successor() {
            if (this.getRight() != null) {
                MyBSTNode<K, V> curr = this.getRight();
                while (curr.getLeft() != null) {
                    curr = curr.getLeft();
                }
                return curr;
            } else {
                MyBSTNode<K, V> parent = this.getParent();
                MyBSTNode<K, V> curr = this;
                while (parent != null && curr == parent.getRight()) {
                    curr = parent;
                    parent = parent.getParent();
                }
                return parent;
            }
        }

        public MyBSTNode<K, V> predecessor() {
            // TODO
            if (this.getLeft() != null) {
                MyBSTNode<K, V> curr = this.getLeft();
                while (curr.getRight() != null) {
                    curr = curr.getRight();
                }
                return curr;
            } else {
                MyBSTNode<K, V> parent = this.getParent();
                MyBSTNode<K, V> curr = this;
                while (parent != null && curr == parent.getLeft()) {
                    curr = parent;
                    parent = parent.getParent();
                }
                return parent;
            }
        }

        /**
         * This method compares if two node objects are equal.
         *
         * @param obj The target object that the currect object compares to.
         * @return Boolean value indicates if two node objects are equal
         */
        public boolean equals(Object obj) {
            if (!(obj instanceof MyBSTNode))
                return false;

            MyBSTNode<K, V> comp = (MyBSTNode<K, V>) obj;

            return ((this.getKey() == null ? comp.getKey() == null :
                    this.getKey().equals(comp.getKey()))
                    && (this.getValue() == null ? comp.getValue() == null :
                    this.getValue().equals(comp.getValue())));
        }

        /**
         * This method gives a string representation of node object.
         *
         * @return "Key:Value" that represents the node object
         */
        public String toString() {
            return String.format(
                    TEMPLATE,
                    this.getKey() == null ? NULL_STR : this.getKey(),
                    this.getValue() == null ? NULL_STR : this.getValue());
        }
    }

}