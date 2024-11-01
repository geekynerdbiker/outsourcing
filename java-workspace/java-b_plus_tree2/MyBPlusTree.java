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
        return getNodeHelper(root, key); // 재귀 탐색
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
            return getNodeHelper(myBPlusTreeNode.getChildren().getFirst(), key); // 첫번째 자식 순회
        }

        for (int i = 1; i < myBPlusTreeNode.getKeyList().size(); i++) // 중간 key들 사이에 있는 경우
            if (key < myBPlusTreeNode.getKeyList().get(i)) {
                System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().get(i - 1));
                return getNodeHelper(myBPlusTreeNode.getChildren().get(i), key); // i번째 자식 순회
            }

        System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().getLast()); // 마지막 key보다 큰 경우
        return getNodeHelper(myBPlusTreeNode.getChildren().getLast(), key); // 마지막 자식 순회
    }

    private MyBPlusTreeNode find(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        if (myBPlusTreeNode.getChildren() == null || myBPlusTreeNode.getChildren().isEmpty()) // 리프 노드에 도달한 경우
            return myBPlusTreeNode;

        // 리프 노드가 아닌 경우
        for (int i = 0; i < myBPlusTreeNode.getKeyList().size(); i++)
            if (key < myBPlusTreeNode.getKeyList().get(i))  // 키가 현재 키보다 작은 경우
                return find(myBPlusTreeNode.getChildren().get(i), key); // i번째 자식 순회


        // 키가 해당 노드 keyList의 마지막 값보다 큰 경우
        return find(myBPlusTreeNode.getChildren().getLast(), key); // 마지막 자식 순회
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
        inorderTraverseHelper(root); // 재귀 탐색
    }

    private void inorderTraverseHelper(MyBPlusTreeNode myBPlusTreeNode) {
        if (myBPlusTreeNode == null)
            return;

        if (myBPlusTreeNode.isLeaf()) { // 리프 노드인 경우 출력
            for (Integer key : myBPlusTreeNode.getKeyList())
                System.out.println(key);
            return;
        }

        for (int i = 0; i < myBPlusTreeNode.getChildren().size(); i++) // 아닌 경우 재귀 탐색
            inorderTraverseHelper(myBPlusTreeNode.getChildren().get(i)); // 재귀 실행
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

        for (MyBPlusTreeNode myBPlusTreeNode : leafList) // 리프 노드를 순회
            size += myBPlusTreeNode.getKeyList().size(); // 노드의 키 리스트 사이즈 합산

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
            MyBPlusTreeNode newNode = new MyBPlusTreeNode(); // 새 노드 생성
            newNode.setKeyList(new ArrayList<>(Collections.singletonList(e)));

            root = newNode; // 루트로 지정
            leafList.add(newNode);

            return true;
        }

        MyBPlusTreeNode leafNode = find(root, e); // 키가 존재하는 리프 노드 찾기
        if (leafNode.getKeyList().contains(e)) // 중복 검사
            return false;

        int position = 0; // 순서대로 추가
        for (; position < leafNode.getKeyList().size(); position++)
            if (e < leafNode.getKeyList().get(position)) { // 키 비교하며 자리 탐색
                leafNode.getKeyList().add(position, e); // 찾은 자리에 추가
                break;
            }


        if (position == leafNode.getKeyList().size()) // 맨 마지막에 추가하는 경우
            leafNode.getKeyList().add(e); // 맨 뒤에 추가

        if (leafNode.getKeyList().size() >= max) // 크기가 가득 찬 경우
            split(leafNode, true); // 분할 실행
        return true;
    }

    private void split(MyBPlusTreeNode myBPlusTreeNode, boolean isLeaf) {
        if (isLeaf) { // 리프 노드를 스플릿 하는 경우
            int mid = myBPlusTreeNode.getKeyList().size() / 2; // 중간 값

            MyBPlusTreeNode rightNode = new MyBPlusTreeNode(); // 오른쪽 노드 생성
            rightNode.setKeyList(new ArrayList<>(myBPlusTreeNode.getKeyList().subList(mid, myBPlusTreeNode.getKeyList().size()))); // 중간부터 끝까지 키값 추가

            myBPlusTreeNode.setKeyList(new ArrayList<>(myBPlusTreeNode.getKeyList().subList(0, mid))); // 기존 노드를 왼쪽 노드로 변경 (처음부터 중간값 전까지)

            leafList.add(leafList.indexOf(myBPlusTreeNode) + 1, rightNode); // 오른쪽 노드를 leafList에 추가
            rightNode.setParent(myBPlusTreeNode.getParent()); // 오른쪽 노드의 부모 노드 설정
            insert(myBPlusTreeNode, rightNode.getKeyList().getFirst(), rightNode); // 왼쪽 노드와 오른쪽 노드를 가운드 노드의 자식 노드로 연결
        } else {
            int mid = (myBPlusTreeNode.getKeyList().size() - 1) / 2; // 중간 값
            int midKey = myBPlusTreeNode.getKeyList().get(mid); // 중간 키값

            // 오른쪽 노드 생성
            MyBPlusTreeNode rightNode = new MyBPlusTreeNode();
            rightNode.setKeyList(new ArrayList<>(myBPlusTreeNode.getKeyList().subList(mid + 1, myBPlusTreeNode.getKeyList().size()))); // 중간부터 끝까지 키값 추가
            rightNode.setChildren(new ArrayList<>(myBPlusTreeNode.getChildren().subList(mid + 1, myBPlusTreeNode.getChildren().size()))); // 중간부터 끝까지 자식 추가
            rightNode.setParent(myBPlusTreeNode.getParent()); // 부모 노드 지정

            // 현재 노드를 왼쪽 노드로
            myBPlusTreeNode.setKeyList(myBPlusTreeNode.getKeyList().subList(0, mid)); // 처음부터 중간까지 키값 추가
            myBPlusTreeNode.setChildren(new ArrayList<>(myBPlusTreeNode.getChildren().subList(0, mid + 1))); // 처음부터 중간까지 자식 추가

            // 부모 노드를 다시 설정
            for (MyBPlusTreeNode child : rightNode.getChildren())
                child.setParent(rightNode); // 부모 노드 지정

            insert(myBPlusTreeNode, midKey, rightNode); // 왼쪽 노드와 오른쪽 노드를 가운데 노드의 자식 노드로 연결
        }
    }

    private void insert(MyBPlusTreeNode leftNode, Integer midKey, MyBPlusTreeNode rightNode) {
        MyBPlusTreeNode parentNode = leftNode.getParent();

        if (parentNode == null) { // 부모 노드가 존재하지 않으면 root 노드로 설정
            MyBPlusTreeNode newRootNode = new MyBPlusTreeNode();
            newRootNode.setKeyList(new ArrayList<>(Collections.singletonList(midKey))); // 중간 키값 추가
            newRootNode.setChildren(new ArrayList<>(Arrays.asList(leftNode, rightNode))); // 왼쪽 오른쪽 모두 자식으로 추가

            leftNode.setParent(newRootNode); // 왼쪽 노드 부모 지정
            rightNode.setParent(newRootNode); // 오른쪽 노드 부모 지정
            root = newRootNode;
        } else { // 부모 노드가 존재하는 경우
            int index = parentNode.getChildren().indexOf(leftNode); // 왼쪽 노드의 인덱스 가져옴
            parentNode.getKeyList().add(index, midKey); // 부모 노드에 중간값 추가
            parentNode.getChildren().add(index + 1, rightNode); // 부모 노드에 오른쪽 자식 노드 추가

            if (parentNode.getKeyList().size() >= max) // 최대값을 초과한 경우
                split(parentNode, false); // 노드 분할
        }
    }

    @Override
    public boolean remove(Object o) {
        MyBPlusTreeNode leafNode = find(root, (Integer) o); // 노드 찾음

        if (!find(root, (Integer) o).getKeyList().contains((Integer) o)) // 존재 여부 확인
            return false; // 존재하지 않는 경우 거짓 반환

        removeHelper(leafNode, (Integer) o); // 재귀 호출

        return true;
    }

    private void removeHelper(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        if (myBPlusTreeNode == null) // 노드가 null 이면 종료
            return;

        int index = myBPlusTreeNode.getKeyList().indexOf(key); // 키값 위치 탐색

        if (index != -1)
            myBPlusTreeNode.getKeyList().remove(key); // 존재하면 삭제

        if (myBPlusTreeNode == root) // 루트 노드인 경우 종료
            return;

        if (index == 0 && leafList.indexOf(myBPlusTreeNode) > 0)  // 맨 왼쪽인 경우
            update(myBPlusTreeNode, myBPlusTreeNode.getKeyList().getFirst()); // 부모 노드 키 값 재설정

        if (myBPlusTreeNode.getKeyList().size() < min) // 최소 키 사이즈보다 작은 경우
            reorganize(myBPlusTreeNode); // 재배치 실행

        
        removeHelper(myBPlusTreeNode.getParent(), key); // 없으면 부모 노드로 이동
    }

    private void update(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        if (myBPlusTreeNode == root)
            return;

        MyBPlusTreeNode parentNode = myBPlusTreeNode.getParent(); // 부모 노드를 찾아
        int index = parentNode.getChildren().indexOf(myBPlusTreeNode); // 현재 노드의 인덱스 가져옴

        if (index > 0) parentNode.getKeyList().set(index - 1, key); // 첫번째가 아닌 경우 키값 이동
        else update(parentNode, key); // 첫번째인 경우
    }

    private void reorganize(MyBPlusTreeNode myBPlusTreeNode) {
        MyBPlusTreeNode parentNode = myBPlusTreeNode.getParent(); // 부모 노드를 찾아
        int index = parentNode.getChildren().indexOf(myBPlusTreeNode); // 현재 노드의 인덱스 가져옴

        MyBPlusTreeNode leftNode = null;
        MyBPlusTreeNode rightNode = null;

        if (index > 0) leftNode = parentNode.getChildren().get(index - 1); // 왼쪽 노드가 있는 경우
        if (index < parentNode.getChildren().size() - 1) rightNode = parentNode.getChildren().get(index + 1); // 오른쪽 노드가 있는 경우

        if (leftNode != null) { // 왼쪽 형제 노드가 존재하는 경우
            if (leftNode.getKeyList().size() > min) // 최소보다 큰 경우
                redistribute(parentNode, leftNode, myBPlusTreeNode, index - 1); // 노드 키 재분배
            else merge(parentNode, leftNode, myBPlusTreeNode, index - 1); // 노드 병합
        } else if (rightNode != null) { // 오른쪽 형제 노드가 존재하는 경우
            if (rightNode.getKeyList().size() > min) // 최소보다 큰 경우
                redistribute(parentNode, myBPlusTreeNode, rightNode, index); // 노드 키 재분배
            else merge(parentNode, myBPlusTreeNode, rightNode, index); // 노드 병합
        }
    }

    private void redistribute(MyBPlusTreeNode parentNode, MyBPlusTreeNode leftNode, MyBPlusTreeNode rightNode, int index) {
        if (leftNode.getKeyList().size() > min) { // 키를 가져올 노드가 왼쪽일 때
            if (leftNode.isLeaf()) { // 리프 노드일 때
                rightNode.getKeyList().addFirst(leftNode.getKeyList().removeLast()); // 왼쪽 노드 마지막 키를 오른쪽 노드로
                parentNode.getKeyList().set(index, rightNode.getKeyList().getFirst()); // 부모 노드 업데이트
            } else {
                rightNode.getKeyList().addFirst(parentNode.getKeyList().get(index)); // 해당 인덱스의 키 값을 오른쪽 노드에 추가
                parentNode.getKeyList().set(index, leftNode.getKeyList().removeLast()); // 왼쪽 노드의 마지막 키 값을 부모 노드에 추가
                rightNode.getChildren().addFirst(leftNode.getChildren().removeLast()); // 자식 노드로 이동
            }
        } else {
            if (leftNode.isLeaf()) {
                leftNode.getKeyList().add(rightNode.getKeyList().removeFirst()); // 오른쪽 노드 첫번째 키를 왼쪽 노드로
                parentNode.getKeyList().set(index, rightNode.getKeyList().getFirst());  // 부모 노드 업데이트
            } else {
                leftNode.getKeyList().add(parentNode.getKeyList().get(index)); // 해당 인덱스의 키 값을 왼쪽 노드에 추가
                parentNode.getKeyList().set(index, rightNode.getKeyList().removeFirst()); // 오른쪽 노드의 첫번째 키 값을 부모 노드에 추가
                leftNode.getChildren().add(rightNode.getChildren().removeFirst());  // 자식 노드로 이동
            }
        }
    }

    private void merge(MyBPlusTreeNode parentNode, MyBPlusTreeNode leftNode, MyBPlusTreeNode rightNode, int index) {
        if (leftNode.getKeyList().size() > min) { // 왼쪽 노드의 키 값의 갯수가 최소 보다 많은 경우
            if (leftNode.isLeaf()) { // 리프 노드일 때
                rightNode.getKeyList().addAll(0, leftNode.getKeyList()); // 오른쪽 노드에 전부 추가
                leafList.remove(leftNode); // 왼쪽 노드 삭제
            } else {
                rightNode.getKeyList().addFirst(parentNode.getKeyList().get(index)); // 왼쪽 노드의 키를 병합
                rightNode.getKeyList().addAll(0, leftNode.getKeyList()); // 오른쪽 노드에 키 전부 추가
                rightNode.getChildren().addAll(0, leftNode.getChildren()); // 오른쪽 노드에 자식 전부 추가
            }

            parentNode.getKeyList().remove(index); // 병합 이후 키 제거
            parentNode.getChildren().remove(leftNode); // 자식 제거


            if (parentNode == root && parentNode.getKeyList().isEmpty()) { // 부모가 루트이거나, 키값이 없는 경우
                rightNode.setParent(null); // 부모 삭제
                root = rightNode;// 루트 노드로 조정
            }
        } else { // 왼쪽 노드의 키 값의 갯수가 최소 보다 적은 경우
            if (leftNode.isLeaf()) { // 리프 노드일 때
                leftNode.getKeyList().addAll(rightNode.getKeyList()); // 왼쪽 노드에 전부 추가
                leafList.remove(rightNode); // 오른쪽 노드 삭제
            } else {
                leftNode.getKeyList().add(parentNode.getKeyList().get(index)); // 오른쪽 노드의 키를 병합
                leftNode.getKeyList().addAll(rightNode.getKeyList()); // 왼쪽 노드에 키 전부 추가
                leftNode.getChildren().addAll(rightNode.getChildren()); // 왼쪽 노드에 자식 전부 추가
            }

            parentNode.getKeyList().remove(index); // 병합 이후 키 제거
            parentNode.getChildren().remove(rightNode); // 자식 제거

            if (parentNode == root && parentNode.getKeyList().isEmpty()) { // 부모가 루트이거나, 키값이 없는 경우
                leftNode.setParent(null); // 부모 삭제
                root = leftNode; // 루트 노드로 조정
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
            private MyBPlusTreeNode currentNode = leafList.getFirst(); // 맨 왼쪽 리프 노드부터 순회
            private int index = 0;

            @Override
            public boolean hasNext() {
                return currentNode != null && index < currentNode.getKeyList().size(); // 노드가 존재하고 키를 순회하는 동안 참 반환
            }

            @Override
            public Integer next() {
                Integer nextKey = currentNode.getKeyList().get(index++); // 다음 키값

                if (index == currentNode.getKeyList().size()) { // 마지막 키값일 때
                    if (currentNode == leafList.getLast()) { // 마지막 노드일 때
                        currentNode = null; // 반복자 끝
                        return nextKey;
                    }

                    currentNode = leafList.get(leafList.indexOf(currentNode) + 1); // 다음 노드로 이동
                    index = 0; // 인덱스 초기화
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
