package org.dfpl.lecture.db.bplustree;

import java.util.*;

@SuppressWarnings("unused")
public class MyBPlusTree implements NavigableSet<Integer> {

    // Data Abstraction은 예시일 뿐 자유롭게 B+ Tree의 범주 안에서 어느정도 수정가능
    private MyBPlusTreeNode root;
    private final int m;

    public MyBPlusTree(int m) {
        this.root = new MyBPlusTreeNode(true, m);
        this.m = m;
    }

    /**
     * 과제 Assignment4를 위한 메소드:
     * <p>
     * key로 검색하면 root부터 시작하여, key를 포함할 수 있는 leaf node를 찾고 key가 실제로 존재하면 해당 Node를
     * 반환하고, 그렇지 않다면 null을 반환한다. 중간과정을 System.out.println(String) 으로 출력해야 함. 6 way
     * B+ tree에서 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 이 순서대로
     * add되었다고 했을 때,
     * <p>
     * 예: getNode(11)을 수행하였을 때
     * > less than 13
     * > larger than or equal to 10
     * > 11 found
     * 위의 3 문장을
     * 콘솔에 출력하고 11을 포함한 SixWayBPlusTreeNode를 반환함
     * <p>
     * 예: getNode(22)를 수행하였을 때
     * > larger than or equal to 13
     * > larger than or equal to 19
     * > 22 not found
     * 위의 3
     * 문장을 콘솔에 출력하고 null을 반환함.
     *
     * @param key
     * @return
     */
    public MyBPlusTreeNode getNode(Integer key) {
        // TODO Auto-generated method stub

        MyBPlusTreeNode myBPlusTreeNode = root;
        while (!myBPlusTreeNode.isLeaf()) {
            int index = 0;
            while (index < myBPlusTreeNode.getKeyList().size() && key >= myBPlusTreeNode.getKeyList().get(index))
                index++;

            if (index < myBPlusTreeNode.getKeyList().size()) {
                if (key < myBPlusTreeNode.getKeyList().get(index))
                    System.out.println("less than " + myBPlusTreeNode.getKeyList().get(index));
                else
                    System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().get(index - 1));
            } else
                System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().get(index - 1));
            myBPlusTreeNode = myBPlusTreeNode.getChildren().get(index);
        }

        int index = 0;
        while (index < myBPlusTreeNode.getKeyList().size() && key > myBPlusTreeNode.getKeyList().get(index))
            index++;

        if (index < myBPlusTreeNode.getKeyList().size() && key.equals(myBPlusTreeNode.getKeyList().get(index))) {
            System.out.println(key + " found");
            return myBPlusTreeNode;
        } else {
            System.out.println(key + " not found");
            return null;
        }
    }

    /**
     * 과제 Assignment4를 위한 메소드:
     * <p>
     * 재귀적으로 inorder traversal을 수행하여, 값을 오름차순으로 출력한다.
     * 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 이 순서대로
     * add되었다고 했을 때,
     * 1
     * 2
     * 3
     * 4
     * 5
     * 6
     * 7
     * 8
     * 9
     * 10
     * 11
     * 12
     * 13
     * 14
     * 15
     * 16
     * 17
     * 18
     * 19
     * 20
     * 21
     * 위와 같이 출력되어야 함.
     */
    public void inorderTraverse() {
        // TODO Auto-generated method stub

        inorderTraverseHelper(root);
        System.out.println();
    }

    private void inorderTraverseHelper(MyBPlusTreeNode myBPlusTreeNode) {
        if (myBPlusTreeNode.isLeaf())
            for (Integer key : myBPlusTreeNode.getKeyList())
                System.out.println(key);
        else
            for (int i = 0; i < myBPlusTreeNode.getChildren().size(); i++)
                inorderTraverseHelper(myBPlusTreeNode.getChildren().get(i));
    }

    @Override
    public Comparator<? super Integer> comparator() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer first() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer last() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public int size() {
        // TODO Auto-generated method stub

        return sizeHelper(root);
    }

    private int sizeHelper(MyBPlusTreeNode myBPlusTreeNode) {
        if (myBPlusTreeNode.isLeaf())
            return myBPlusTreeNode.getKeyList().size();

        int size = 0;
        for (MyBPlusTreeNode child : myBPlusTreeNode.getChildren())
            size += sizeHelper(child);

        return size;

    }

    @Override
    public boolean isEmpty() {
        // TODO Auto-generated method stub

        return root.getKeyList().isEmpty();
    }

    @Override
    public boolean contains(Object o) {
        // TODO Auto-generated method stub

        return containsHelper(root, (Integer) o);
    }

    private boolean containsHelper(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        int position = Collections.binarySearch(myBPlusTreeNode.getKeyList(), key);
        if (position >= 0)
            return true;

        if (myBPlusTreeNode.isLeaf())
            return false;

        position = -(position + 1);
        return containsHelper(myBPlusTreeNode.getChildren().get(position), key);
    }

    @Override
    public Object[] toArray() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public <T> T[] toArray(T[] a) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean add(Integer e) {
        // TODO Auto-generated method stub
        MyBPlusTreeNode myBPlusTreeNode = root;

        if (myBPlusTreeNode.getKeyList().size() == m - 1 && myBPlusTreeNode.getChildren().isEmpty()) {
            MyBPlusTreeNode newNode = new MyBPlusTreeNode(false, m);
            newNode.getChildren().add(myBPlusTreeNode);
            root = newNode;
            newNode.split(myBPlusTreeNode, 0);
            insert(newNode, e);
        } else {
            insert(myBPlusTreeNode, e);
            if (myBPlusTreeNode.getKeyList().size() == m) {
                MyBPlusTreeNode s = new MyBPlusTreeNode(false, m);
                s.getChildren().add(myBPlusTreeNode);
                root = s;
                s.split(myBPlusTreeNode, 0);
            }
        }

        return false;
    }

    private void insert(MyBPlusTreeNode myBPlusTreeNode, int key) {
        int index = myBPlusTreeNode.getKeyList().size() - 1;

        if (myBPlusTreeNode.isLeaf()) {
            myBPlusTreeNode.getKeyList().add(null);

            while (index >= 0 && key < myBPlusTreeNode.getKeyList().get(index)) {
                myBPlusTreeNode.getKeyList().set(index + 1, myBPlusTreeNode.getKeyList().get(index));
                index--;
            }

            myBPlusTreeNode.getKeyList().set(index + 1, key);
        } else {
            while (index >= 0 && key < myBPlusTreeNode.getKeyList().get(index))
                index--;

            index++;
            MyBPlusTreeNode indexedNode = myBPlusTreeNode.getChildren().get(index);

            if (indexedNode.getKeyList().size() == m - 1) {
                myBPlusTreeNode.split(indexedNode, index);

                if (key > myBPlusTreeNode.getKeyList().get(index))
                    index++;
            }
            insert(myBPlusTreeNode.getChildren().get(index), key);
        }
    }
    
    private int find(MyBPlusTreeNode myBPlusTreeNode, int key) {
        int index = 0;

        while (index < myBPlusTreeNode.getKeyList().size() && myBPlusTreeNode.getKeyList().get(index) < key)
            index++;

        return index;
    }

    @Override
    public boolean remove(Object o) {
        // TODO Auto-generated method stub

        removeHelper(root, (Integer) o);
        if (root.getKeyList().isEmpty()) {
            if (!root.isLeaf())
                root = root.getChildren().getFirst();
            else
                root = null;
        }
        return true;
    }

    private void removeHelper(MyBPlusTreeNode myBPlusTreeNode, int key) {
        int index = find(myBPlusTreeNode, key);

        if (index < myBPlusTreeNode.getKeyList().size() && myBPlusTreeNode.getKeyList().get(index) == key) {
            if (myBPlusTreeNode.isLeaf()) {
                for (int i = index + 1; i < myBPlusTreeNode.getKeyList().size(); i++)
                    myBPlusTreeNode.getKeyList().set(i - 1, myBPlusTreeNode.getKeyList().get(i));

                myBPlusTreeNode.getKeyList().removeLast();
            } else {
                int tempKey = myBPlusTreeNode.getKeyList().get(index);

                if (myBPlusTreeNode.getChildren().get(index).getKeyList().size() >= (m + 1) / 2) {
                    MyBPlusTreeNode currentNode = myBPlusTreeNode.getChildren().get(index);

                    while (!currentNode.isLeaf())
                        currentNode = currentNode.getChildren().get(currentNode.getKeyList().size());

                    int predecessor = currentNode.getKeyList().getLast();
                    myBPlusTreeNode.getKeyList().set(index, predecessor);
                    removeHelper(myBPlusTreeNode.getChildren().get(index), predecessor);
                } else if (myBPlusTreeNode.getChildren().get(index + 1).getKeyList().size() >= (m + 1) / 2) {
                    MyBPlusTreeNode currendNode = myBPlusTreeNode.getChildren().get(index + 1);

                    while (!currendNode.isLeaf())
                        currendNode = currendNode.getChildren().getFirst();

                    int successor = currendNode.getKeyList().getFirst();
                    myBPlusTreeNode.getKeyList().set(index, successor);
                    removeHelper(myBPlusTreeNode.getChildren().get(index + 1), successor);
                } else {
                    merge(myBPlusTreeNode, index);
                    removeHelper(myBPlusTreeNode.getChildren().get(index), tempKey);
                }
            }
        } else {
            if (myBPlusTreeNode.isLeaf()) {
                return;
            }

            boolean isSizeEqualsIndex = (index == myBPlusTreeNode.getKeyList().size());

            if (myBPlusTreeNode.getChildren().get(index).getKeyList().size() < (m + 1) / 2) {
                if (index != 0 && myBPlusTreeNode.getChildren().get(index - 1).getKeyList().size() >= (m + 1) / 2) {
                    MyBPlusTreeNode child = myBPlusTreeNode.getChildren().get(index);
                    MyBPlusTreeNode sibling = myBPlusTreeNode.getChildren().get(index - 1);
                    child.getKeyList().addFirst(myBPlusTreeNode.getKeyList().get(index - 1));

                    if (!child.isLeaf())
                        child.getChildren().addFirst(sibling.getChildren().removeLast());

                    myBPlusTreeNode.getKeyList().set(index - 1, sibling.getKeyList().removeLast());
                } else if (index != myBPlusTreeNode.getKeyList().size() && myBPlusTreeNode.getChildren().get(index + 1).getKeyList().size() >= (m + 1) / 2) {
                    MyBPlusTreeNode child = myBPlusTreeNode.getChildren().get(index);
                    MyBPlusTreeNode sibling = myBPlusTreeNode.getChildren().get(index + 1);

                    child.getKeyList().add(myBPlusTreeNode.getKeyList().get(index));
                    if (!child.isLeaf())
                        child.getChildren().add(sibling.getChildren().removeFirst());

                    myBPlusTreeNode.getKeyList().set(index, sibling.getKeyList().removeFirst());
                } else {
                    if (index != myBPlusTreeNode.getKeyList().size())
                        merge(myBPlusTreeNode, index);
                    else
                        merge(myBPlusTreeNode, index - 1);
                }
            }

            if (isSizeEqualsIndex && index > myBPlusTreeNode.getKeyList().size()) {
                removeHelper(myBPlusTreeNode.getChildren().get(index - 1), key);
            } else {
                removeHelper(myBPlusTreeNode.getChildren().get(index), key);
            }
        }
    }

    private void merge(MyBPlusTreeNode myBPlusTreeNode, int index) {
        MyBPlusTreeNode child = myBPlusTreeNode.getChildren().get(index);
        MyBPlusTreeNode sibling = myBPlusTreeNode.getChildren().get(index + 1);

        if (!child.isLeaf())
            child.getKeyList().add(myBPlusTreeNode.getKeyList().get(index));

        for (int i = 0; i < sibling.getKeyList().size(); i++)
            child.getKeyList().add(sibling.getKeyList().get(i));

        if (!child.isLeaf())
            for (int i = 0; i < sibling.getChildren().size(); i++)
                child.getChildren().add(sibling.getChildren().get(i));

        myBPlusTreeNode.getKeyList().remove(index);
        myBPlusTreeNode.getChildren().remove(index + 1);

        if (myBPlusTreeNode == root && myBPlusTreeNode.getKeyList().isEmpty())
            root = child;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean addAll(Collection<? extends Integer> c) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public void clear() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer lower(Integer e) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer floor(Integer e) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer ceiling(Integer e) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer higher(Integer e) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer pollFirst() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer pollLast() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterator<Integer> iterator() {
        // TODO Auto-generated method stub

        return new Iterator<>() {
            MyBPlusTreeNode currentNode = root;
            int index = 0;

            {
                while (!currentNode.isLeaf())
                    currentNode = currentNode.getChildren().getFirst();
            }

            @Override
            public boolean hasNext() {
                return index < currentNode.getKeyList().size() || currentNode.getNext() != null;
            }

            @Override
            public Integer next() {
                if (index >= currentNode.getKeyList().size()) {
                    currentNode = currentNode.getNext();
                    index = 0;

                    if (currentNode == null)
                        throw new NoSuchElementException();
                }
                return currentNode.getKeyList().get(index++);
            }
        };
    }

    @Override
    public NavigableSet<Integer> descendingSet() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterator<Integer> descendingIterator() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<Integer> subSet(Integer fromElement, boolean fromInclusive, Integer toElement,
                                        boolean toInclusive) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<Integer> headSet(Integer toElement, boolean inclusive) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<Integer> tailSet(Integer fromElement, boolean inclusive) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public SortedSet<Integer> subSet(Integer fromElement, Integer toElement) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public SortedSet<Integer> headSet(Integer toElement) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

    @Override
    public SortedSet<Integer> tailSet(Integer fromElement) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException();
    }

}
