package org.dfpl.lecture.db.bplustree;

import java.util.*;

@SuppressWarnings("unused")
public class MyBPlusTree implements NavigableSet<Integer> {

    // Data Abstraction은 예시일 뿐 자유롭게 B+ Tree의 범주 안에서 어느정도 수정가능
    private MyBPlusTreeNode root;
    private LinkedList<MyBPlusTreeNode> leafList;
    private final int max;
    private final int min;

    public MyBPlusTree(int m) {
        root = null;
        leafList = new LinkedList<>();
        max = m;
        min = (m + 1) / 2 - 1;
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
        return getNodeHelper(root, key);
    }

    private MyBPlusTreeNode getNodeHelper(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        if (myBPlusTreeNode == null)
            return null;

        if (myBPlusTreeNode.getChildren() == null || myBPlusTreeNode.getChildren().isEmpty()) {
            if (myBPlusTreeNode.getKeyList().contains(key)) { // key가 존재하는 경우
                System.out.println(key + " found");
                return myBPlusTreeNode;
            }


            System.out.println(key + " not found"); // key가 존재하지 않는 경우
            return null;

        }


        if (key < myBPlusTreeNode.getKeyList().getFirst()) { // 첫 번째 key보다 작은 경우
            System.out.println("less than " + myBPlusTreeNode.getKeyList().getFirst());
            return getNodeHelper(myBPlusTreeNode.getChildren().getFirst(), key);
        }

        for (int i = 1; i < myBPlusTreeNode.getKeyList().size(); i++) // 중간 key들 사이에 있는 경우
            if (key < myBPlusTreeNode.getKeyList().get(i)) {
                System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().get(i - 1));
                return getNodeHelper(myBPlusTreeNode.getChildren().get(i), key);
            }

        System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().getLast()); // 마지막 key보다 큰 경우
        return getNodeHelper(myBPlusTreeNode.getChildren().getLast(), key);
    }

    private MyBPlusTreeNode find(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        if (myBPlusTreeNode.getChildren() == null || myBPlusTreeNode.getChildren().isEmpty()) // 리프 노드에 도달한 경우
            return myBPlusTreeNode;

        // 리프 노드가 아닌 경우
        for (int i = 0; i < myBPlusTreeNode.getKeyList().size(); i++)
            if (key < myBPlusTreeNode.getKeyList().get(i))  // 키가 현재 키보다 작은 경우
                return find(myBPlusTreeNode.getChildren().get(i), key);


        // 키가 해당 노드 keyList의 마지막 값보다 큰 경우
        return find(myBPlusTreeNode.getChildren().getLast(), key);
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
        inorderTraverseHelper(root);
    }

    private void inorderTraverseHelper(MyBPlusTreeNode myBPlusTreeNode) {
        if (myBPlusTreeNode == null)
            return;

        if (myBPlusTreeNode.isLeaf()) { // 리프 노드인 경우 출력
            for (Integer key : myBPlusTreeNode.getKeyList())
                System.out.println(key);
            return;
        }

        for (int i = 0; i < myBPlusTreeNode.getChildren().size(); i++)
            inorderTraverseHelper(myBPlusTreeNode.getChildren().get(i));

    }

    @Override
    public Comparator<? super Integer> comparator() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer first() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer last() {
        throw new UnsupportedOperationException();
    }

    @Override
    public int size() {
        int size = 0;

        for (MyBPlusTreeNode myBPlusTreeNode : leafList)
            size += myBPlusTreeNode.getKeyList().size();

        return size;
    }

    @Override
    public boolean isEmpty() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean contains(Object o) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Object[] toArray() {
        throw new UnsupportedOperationException();
    }

    @Override
    public <T> T[] toArray(T[] a) {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean add(Integer e) {
        if (root == null) { // root가 null인 경우
            MyBPlusTreeNode newNode = new MyBPlusTreeNode();
            newNode.setKeyList(new ArrayList<>(Collections.singletonList(e)));

            root = newNode;
            leafList.add(newNode);

            return true;
        }

        MyBPlusTreeNode leafNode = find(root, e); // 키가 존재하는 리프 노드 찾기
        if (leafNode.getKeyList().contains(e)) // 중복 검사
            return false;

        int position = 0; // 순서대로 추가
        for (; position < leafNode.getKeyList().size(); position++)
            if (e < leafNode.getKeyList().get(position)) {
                leafNode.getKeyList().add(position, e);
                break;
            }


        if (position == leafNode.getKeyList().size()) // 맨 마지막에 추가하는 경우
            leafNode.getKeyList().add(e);

        if (leafNode.getKeyList().size() >= max) // 크기가 가득 찬 경우
            split(leafNode, true);
        return true;
    }

    private void split(MyBPlusTreeNode myBPlusTreeNode, boolean isLeaf) {
        if (isLeaf) {
            int mid = myBPlusTreeNode.getKeyList().size() / 2;

            MyBPlusTreeNode rightNode = new MyBPlusTreeNode(); // 오른쪽 노드 생성
            rightNode.setKeyList(new ArrayList<>(myBPlusTreeNode.getKeyList().subList(mid, myBPlusTreeNode.getKeyList().size())));

            myBPlusTreeNode.setKeyList(new ArrayList<>(myBPlusTreeNode.getKeyList().subList(0, mid))); // 기존 노드를 왼쪽 노드로 변경 (처음부터 중간값 전까지)

            leafList.add(leafList.indexOf(myBPlusTreeNode) + 1, rightNode); // 오른쪽 노드를 leafList에 추가
            rightNode.setParent(myBPlusTreeNode.getParent()); // 오른쪽 노드의 부모 노드 설정
            insert(myBPlusTreeNode, rightNode.getKeyList().getFirst(), rightNode); // 왼쪽 노드와 오른쪽 노드를 가운드 노드의 자식 노드로 연결
        } else {
            int mid = (myBPlusTreeNode.getKeyList().size() - 1) / 2;
            int midKey = myBPlusTreeNode.getKeyList().get(mid);

            // 오른쪽 노드 생성
            MyBPlusTreeNode rightNode = new MyBPlusTreeNode();
            rightNode.setKeyList(new ArrayList<>(myBPlusTreeNode.getKeyList().subList(mid + 1, myBPlusTreeNode.getKeyList().size())));
            rightNode.setChildren(new ArrayList<>(myBPlusTreeNode.getChildren().subList(mid + 1, myBPlusTreeNode.getChildren().size())));
            rightNode.setParent(myBPlusTreeNode.getParent());

            // 노드를 왼쪽 노드로
            myBPlusTreeNode.setKeyList(myBPlusTreeNode.getKeyList().subList(0, mid));
            myBPlusTreeNode.setChildren(new ArrayList<>(myBPlusTreeNode.getChildren().subList(0, mid + 1)));

            // 부모 노드를 다시 설정
            for (MyBPlusTreeNode child : rightNode.getChildren())
                child.setParent(rightNode);

            // 왼쪽 노드와 오른쪽 노드를 가운데 노드의 자식 노드로 연결
            insert(myBPlusTreeNode, midKey, rightNode);
        }
    }

    private void insert(MyBPlusTreeNode leftNode, Integer midKey, MyBPlusTreeNode rightNode) {
        MyBPlusTreeNode parentNode = leftNode.getParent();

        if (parentNode == null) { // 부모 노드가 존재하지 않으면 root 노드로 설정
            MyBPlusTreeNode newRootNode = new MyBPlusTreeNode();
            newRootNode.setKeyList(new ArrayList<>(Collections.singletonList(midKey)));
            newRootNode.setChildren(new ArrayList<>(Arrays.asList(leftNode, rightNode)));

            leftNode.setParent(newRootNode);
            rightNode.setParent(newRootNode);
            root = newRootNode;
        } else { // 부모 노드가 존재하는 경우
            int index = parentNode.getChildren().indexOf(leftNode);
            parentNode.getKeyList().add(index, midKey); // 부모 노드에 중간값 추가
            parentNode.getChildren().add(index + 1, rightNode); // 부모 노드에 오른쪽 자식 노드 추가

            if (parentNode.getKeyList().size() >= max)
                split(parentNode, false);
        }
    }

    @Override
    public boolean remove(Object o) {
        MyBPlusTreeNode leafNode = find(root, (Integer) o);

        if (!find(root, (Integer) o).getKeyList().contains((Integer) o)) // 존재 여부 확인
            return false;

        removeHelper(leafNode, (Integer) o);

        return true;
    }

    private void removeHelper(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        if (myBPlusTreeNode == null)
            return;

        int index = myBPlusTreeNode.getKeyList().indexOf(key);

        if (index != -1)
            myBPlusTreeNode.getKeyList().remove(key); // 존재하면 삭제

        // 루트 노드인 경우 종료
        if (myBPlusTreeNode == root)
            return;

        if (index == 0 && leafList.indexOf(myBPlusTreeNode) > 0)  // 맨 왼쪽인 경우
            update(myBPlusTreeNode, myBPlusTreeNode.getKeyList().getFirst()); // 부모 노드 키 값 재설정

        // 최소 키 사이즈보다 작은 경우
        if (myBPlusTreeNode.getKeyList().size() < min)
            reorganize(myBPlusTreeNode); // 재배치

        // 부모 노드로 이동
        removeHelper(myBPlusTreeNode.getParent(), key);
    }

    private void update(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        if (myBPlusTreeNode == root)
            return;

        MyBPlusTreeNode parentNode = myBPlusTreeNode.getParent();
        int index = parentNode.getChildren().indexOf(myBPlusTreeNode);

        if (index > 0) parentNode.getKeyList().set(index - 1, key); // 첫번째가 아닌 경우
        else update(parentNode, key); // 첫번째인 경우
    }

    private void reorganize(MyBPlusTreeNode myBPlusTreeNode) {
        MyBPlusTreeNode parentNode = myBPlusTreeNode.getParent();
        int index = parentNode.getChildren().indexOf(myBPlusTreeNode);

        MyBPlusTreeNode leftNode = null;
        MyBPlusTreeNode rightNode = null;

        if (index > 0) leftNode = parentNode.getChildren().get(index - 1);
        if (index < parentNode.getChildren().size() - 1) rightNode = parentNode.getChildren().get(index + 1);

        // 왼쪽 형제 노드가 존재하는 경우
        if (leftNode != null) {
            if (leftNode.getKeyList().size() > min) // 최소보다 큰 경우
                redistribute(parentNode, leftNode, myBPlusTreeNode, index - 1);
            else merge(parentNode, leftNode, myBPlusTreeNode, index - 1);
        }
        // 오른쪽 형제 노드가 존재하는 경우
        else if (rightNode != null) {
            if (rightNode.getKeyList().size() > min)
                redistribute(parentNode, myBPlusTreeNode, rightNode, index);
            else merge(parentNode, myBPlusTreeNode, rightNode, index);
        }
    }

    private void redistribute(MyBPlusTreeNode parentNode, MyBPlusTreeNode leftNode, MyBPlusTreeNode rightNode, int index) {
        if (leftNode.getKeyList().size() > min) { // 키를 가져올 노드가 왼쪽일 때
            if (leftNode.isLeaf()) { // 리프 노드일 때
                rightNode.getKeyList().addFirst(leftNode.getKeyList().removeLast());
                parentNode.getKeyList().set(index, rightNode.getKeyList().getFirst());
            } else {
                rightNode.getKeyList().addFirst(parentNode.getKeyList().get(index));
                parentNode.getKeyList().set(index, leftNode.getKeyList().removeLast());
                rightNode.getChildren().addFirst(leftNode.getChildren().removeLast());
            }
        } else { // 키를 가져올 노드가 오른쪽일 때
            if (leftNode.isLeaf()) {
                leftNode.getKeyList().add(rightNode.getKeyList().removeFirst());
                parentNode.getKeyList().set(index, rightNode.getKeyList().getFirst()); // 부모 노드 업데이트
            } else {
                leftNode.getKeyList().add(parentNode.getKeyList().get(index));
                parentNode.getKeyList().set(index, rightNode.getKeyList().removeFirst());
                leftNode.getChildren().add(rightNode.getChildren().removeFirst()); // 오른쪽 노드의 키를 가져옴
            }
        }
    }

    private void merge(MyBPlusTreeNode parentNode, MyBPlusTreeNode leftNode, MyBPlusTreeNode rightNode, int index) {
        if (leftNode.getKeyList().size() > min) {
            if (leftNode.isLeaf()) { // 리프 노드일 때
                rightNode.getKeyList().addAll(0, leftNode.getKeyList());
                leafList.remove(leftNode);
            } else {
                rightNode.getKeyList().addFirst(parentNode.getKeyList().get(index)); // 왼쪽 노드의 키를 병합
                rightNode.getKeyList().addAll(0, leftNode.getKeyList());
                rightNode.getChildren().addAll(0, leftNode.getChildren());
            }

            parentNode.getKeyList().remove(index); // 병합 이후 키와 자식 제거
            parentNode.getChildren().remove(leftNode);


            if (parentNode == root && parentNode.getKeyList().isEmpty()) {
                rightNode.setParent(null); // 루트 노드로 조정
                root = rightNode;
            }
        } else {
            if (leftNode.getChildren() == null) {
                leftNode.getKeyList().addAll(rightNode.getKeyList());
                leafList.remove(rightNode);
            } else {
                leftNode.getKeyList().add(parentNode.getKeyList().get(index));
                leftNode.getKeyList().addAll(rightNode.getKeyList());
                leftNode.getChildren().addAll(rightNode.getChildren());
            }

            parentNode.getKeyList().remove(index);
            parentNode.getChildren().remove(rightNode);

            if (parentNode == root && parentNode.getKeyList().isEmpty()) {
                leftNode.setParent(null);
                root = leftNode;
            }
        }
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean addAll(Collection<? extends Integer> c) {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void clear() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer lower(Integer e) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer floor(Integer e) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer ceiling(Integer e) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer higher(Integer e) {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer pollFirst() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Integer pollLast() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterator<Integer> iterator() {
        return new Iterator<>() {
            private MyBPlusTreeNode currentNode = leafList.getFirst();
            private int index = 0;

            @Override
            public boolean hasNext() {
                return currentNode != null && index < currentNode.getKeyList().size();
            }

            @Override
            public Integer next() {
                Integer nextKey = currentNode.getKeyList().get(index++);

                if (index == currentNode.getKeyList().size()) {
                    if (currentNode == leafList.getLast()) {
                        currentNode = null;
                        return nextKey;
                    }

                    currentNode = leafList.get(leafList.indexOf(currentNode) + 1);
                    index = 0;
                }

                return nextKey;
            }
        };
    }

    @Override
    public NavigableSet<Integer> descendingSet() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterator<Integer> descendingIterator() {
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<Integer> subSet(Integer fromElement, boolean fromInclusive, Integer toElement, boolean toInclusive) {
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<Integer> headSet(Integer toElement, boolean inclusive) {
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<Integer> tailSet(Integer fromElement, boolean inclusive) {
        throw new UnsupportedOperationException();
    }

    @Override
    public SortedSet<Integer> subSet(Integer fromElement, Integer toElement) {
        throw new UnsupportedOperationException();
    }

    @Override
    public SortedSet<Integer> headSet(Integer toElement) {
        throw new UnsupportedOperationException();
    }

    @Override
    public SortedSet<Integer> tailSet(Integer fromElement) {
        throw new UnsupportedOperationException();
    }

}
