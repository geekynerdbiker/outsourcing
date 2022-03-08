/**
 * This is a simplified implementation of Java TreeMap data structure.
 * Name: Jianwei Gong
 * Email: jig184@ucsd.edu
 * Sources used: OpenJDK
 * 
 * This is a helper file offered to CSE 12 students, it contains the methods 
 * needed to implement the calendar application problem. For more infomation
 * about TreeMap, refer to the Javadoc official website.
 */
public class MyTreeMap<K extends Comparable<K>,V> extends MyBST<K, V>{
    /**
     * Returns a key-value mapping associated with the least key greater 
     * than or equal to the given key, or null if there is no such key.
     * @param key The key to locate in the map
     * @return The key that is greater or equal to the input key
     */
    public K ceilingKey(K key){
        MyBSTNode<K,V> curr = super.root;
        while (curr != null) {
            int cmp = key.compareTo(curr.getKey());
            // if input key is smaller than current node's key
            if (cmp < 0) {
                if (curr.getLeft() != null){
                    //continue to go to left subtree to find the target key
                    curr = curr.getLeft();
                }
                else{
                    //no left subtree, current key is the ceiling
                    return curr.getKey();
                }
            } else if (cmp > 0) {
                // if input key is greater than current node's key
                if (curr.getRight() != null) {
                    //continue to go to left subtree to find the target key
                    curr = curr.getRight();
                } else {
                    // right child is null, find the in order successor
                    // Does the following code look familiar to you?
                    MyBSTNode<K,V> parent = curr.getParent();
                    MyBSTNode<K,V> ch = curr;
                    while (parent != null && ch == parent.getRight()) {
                        ch = parent;
                        parent = parent.getParent();
                    }
                    return parent == null ? null : parent.getKey();
                }
            } else
                return curr == null ? null : curr.getKey();// key is found
        }
        return null;
    }

    /**
     * Returns a key-value mapping associated with the greatest key less than 
     * or equal to the given key, or null if there is no such key.
     * @param key The key to locate in the map
     * @return The key that is smaller or equal to the input key
     */
    public K floorKey(K key){
        MyBSTNode<K,V> curr = super.root;
        while (curr != null) {
            int cmp = key.compareTo(curr.getKey());
            if (cmp > 0) {
                if (curr.getRight() != null)
                    curr = curr.getRight();
                else
                    return curr.getKey();
            } else if (cmp < 0) {
                if (curr.getLeft() != null) {
                    curr = curr.getLeft();
                } else {
                    MyBSTNode<K,V> parent = curr.getParent();
                    MyBSTNode<K,V> ch = curr;
                    while (parent != null && ch == parent.getLeft()) {
                        ch = parent;
                        parent = parent.getParent();
                    }
                    return parent == null ? null : parent.getKey();
                }
            } else
                return curr == null ? null : curr.getKey();
        }
        return null;
    }

    /**
     * Put a new key value pair into the treemap or replace existing one.
     * @param key   The key in the pair
     * @param value The value in the pair
     * @return Return null if no repalcement happen. Otherwise, return the 
     * value replaced by the new value
     */
    public V put(K key, V value){  
        return super.insert(key, value);
    }

    /**
     * Get the value from the treemap based on the key
     * @param key The key to access value
     * @return The value
     */
    public V get(K key){  
        return super.search(key);
    }

}
