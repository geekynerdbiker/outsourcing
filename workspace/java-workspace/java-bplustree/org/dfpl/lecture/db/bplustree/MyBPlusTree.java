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
        while (!myBPlusTreeNode.isLeaf()) { // 리프가 아닌 동안
            int index = 0;
            while (index < myBPlusTreeNode.getKeyList().size() && key >= myBPlusTreeNode.getKeyList().get(index)) // 키 값을 비교하며 찾으려는 키 값이 작을 때 인덱스 증가
                index++;

            if (index < myBPlusTreeNode.getKeyList().size()) { // 키 리스트 순회 완료했을 때 인덱스가
                if (key < myBPlusTreeNode.getKeyList().get(index)) // 찾은 키가 작을 때
                    System.out.println("less than " + myBPlusTreeNode.getKeyList().get(index));
                else // 클 때
                    System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().get(index - 1));
            } else // 리스트 모든 값이 키 보다 작을 때
                System.out.println("larger than or equal to " + myBPlusTreeNode.getKeyList().get(index - 1));
            myBPlusTreeNode = myBPlusTreeNode.getChildren().get(index); // 자식노드 순회
        }

        int index = 0;
        while (index < myBPlusTreeNode.getKeyList().size() && key > myBPlusTreeNode.getKeyList().get(index)) // 같은 방식으로 순회
            index++;

        if (index < myBPlusTreeNode.getKeyList().size() && key.equals(myBPlusTreeNode.getKeyList().get(index))) { // 존재할 경우
            System.out.println(key + " found");
            return myBPlusTreeNode;
        } else { // 존재하지 않을 경우
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

        inorderTraverseHelper(root); // 노드 단위 재귀 호출을 위한 도움 함수
        System.out.println();
    }

    private void inorderTraverseHelper(MyBPlusTreeNode myBPlusTreeNode) {
        if (myBPlusTreeNode.isLeaf()) // 노드가 리프 노드이면 순회하면서 키 값 출력
            for (Integer key : myBPlusTreeNode.getKeyList())
                System.out.println(key);
        else
            for (int i = 0; i < myBPlusTreeNode.getChildren().size(); i++) // 리프 노드가 아니면 자식노드 순회
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

        return sizeHelper(root); // 노드 단위 재귀 호출을 위한 도움 함수
    }

    private int sizeHelper(MyBPlusTreeNode myBPlusTreeNode) {
        if (myBPlusTreeNode.isLeaf()) // 리프 노드 인경우 현재 노드의 키값 갯수 반환
            return myBPlusTreeNode.getKeyList().size();

        int size = 0; // 리프 노드가 아닌 경우
        for (MyBPlusTreeNode child : myBPlusTreeNode.getChildren()) // 모든 자식노드를 순회하며 자식 노드들의 크기 합산
            size += sizeHelper(child);

        return size; // 전체 크기 반환

    }

    @Override
    public boolean isEmpty() {
        // TODO Auto-generated method stub

        return root.getKeyList().isEmpty(); // 루트 노드의 키 값 존재 유무 반환
    }

    @Override
    public boolean contains(Object o) {
        // TODO Auto-generated method stub

        return containsHelper(root, (Integer) o); // 노드 단위 재귀 호출을 위한 도움 함수
    }

    private boolean containsHelper(MyBPlusTreeNode myBPlusTreeNode, Integer key) {
        int position = Collections.binarySearch(myBPlusTreeNode.getKeyList(), key); // 이진 탐색을 통한 키값 위치 탐색
        if (position >= 0) // 키 값이 존재하는 경우 참 반환
            return true;

        if (myBPlusTreeNode.isLeaf()) // 참을 반환하지 못했으나 리프 노드인 경우 -> 값이 존재하지 않으므로 거짓 반환
            return false;

        position = -(position + 1); // 키 값이 존재하지 않고 음수인 경우 다음 자식노드를 가리킴
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

        if (myBPlusTreeNode.getKeyList().size() == m - 1 && myBPlusTreeNode.getChildren().isEmpty()) { // 루트 노드가 꽉 찼으나 자식이 없는 경우
            MyBPlusTreeNode newNode = new MyBPlusTreeNode(false, m); // 새 노드 생성
            newNode.getChildren().add(myBPlusTreeNode); // 새 노드에 루트 노드 자식으로 추가
            root = newNode; // 새 노드를 루트로 변경
            newNode.split(myBPlusTreeNode, 0); // 새 노드 스플릿
            insert(newNode, e); // 키 삽입
        } else {
            insert(myBPlusTreeNode, e); // 루트에 키 삽입
            if (myBPlusTreeNode.getKeyList().size() == m) { // 삽입 후 노드가 꽉 찬 경우
                MyBPlusTreeNode newNode = new MyBPlusTreeNode(false, m);
                newNode.getChildren().add(myBPlusTreeNode);
                root = newNode;
                newNode.split(myBPlusTreeNode, 0);
            }
        }

        return false;
    }

    private void insert(MyBPlusTreeNode myBPlusTreeNode, int key) {
        int index = myBPlusTreeNode.getKeyList().size() - 1; // 맨 마지막 인덱스

        if (myBPlusTreeNode.isLeaf()) { // 노드가 리프 노드인 겨우
            myBPlusTreeNode.getKeyList().add(null); // 빈 값 추가

            while (index >= 0 && key < myBPlusTreeNode.getKeyList().get(index)) { // 노드가 비어있지 않고, 삽입할 키 값 위치 찾기
                myBPlusTreeNode.getKeyList().set(index + 1, myBPlusTreeNode.getKeyList().get(index)); // 기존 키 값 한칸씩 옮김
                index--;
            }

            myBPlusTreeNode.getKeyList().set(index + 1, key); // 찾은 위치에 추가
        } else { // 리프 노드가 아닌 경우
            while (index >= 0 && key < myBPlusTreeNode.getKeyList().get(index))
                index--;

            index++; // 찾은 위치의 다음 칸에 삽입하기 위해 1 증가
            MyBPlusTreeNode indexedNode = myBPlusTreeNode.getChildren().get(index);

            if (indexedNode.getKeyList().size() == m - 1) { // 노드가 가득 찬 경우
                myBPlusTreeNode.split(indexedNode, index); // 노드 스플릿

                if (key > myBPlusTreeNode.getKeyList().get(index)) // 위치 찾을 때 까지 인덱스 증가
                    index++;
            }
            insert(myBPlusTreeNode.getChildren().get(index), key); // 자식 노드에 삽입하기 위해 호출
        }
    }
    
    private int find(MyBPlusTreeNode myBPlusTreeNode, int key) {
        int index = 0;

        while (index < myBPlusTreeNode.getKeyList().size() && myBPlusTreeNode.getKeyList().get(index) < key) // 현재 노드 내에서 키 값 위치 찾기
            index++;

        return index; // 인덱스 반환
    }

    @Override
    public boolean remove(Object o) {
        // TODO Auto-generated method stub
        if (o == null)
            return false;

        removeHelper(root, (Integer) o); // 노드 단위 재귀 호출을 위한 도움 함수
        if (root.getKeyList().isEmpty()) { // 빈 노드인 경우
            if (!root.isLeaf()) { // 리프 노드가 아니면
                root = root.getChildren().getFirst(); // 첫번째 자식 노드를 루트 노드로 설정
                return true;
            } else {
                root = null; // 루트 없음
                return true;
            }
        }
        return false; // 실패
    }

    private void removeHelper(MyBPlusTreeNode myBPlusTreeNode, int key) {
        int index = find(myBPlusTreeNode, key); // 키 값 탐섹

        if (index < myBPlusTreeNode.getKeyList().size() && myBPlusTreeNode.getKeyList().get(index) == key) { // 찾은 경우
            if (myBPlusTreeNode.isLeaf()) { // 리프 노드이면
                for (int i = index + 1; i < myBPlusTreeNode.getKeyList().size(); i++) // 한 칸씩 이동
                    myBPlusTreeNode.getKeyList().set(i - 1, myBPlusTreeNode.getKeyList().get(i));

                myBPlusTreeNode.getKeyList().removeLast(); // 삭제
            } else {
                int tempKey = myBPlusTreeNode.getKeyList().get(index); // 키 값 저장

                if (myBPlusTreeNode.getChildren().get(index).getKeyList().size() >= (m + 1) / 2) {
                    MyBPlusTreeNode currentNode = myBPlusTreeNode.getChildren().get(index); // 현재 노드

                    while (!currentNode.isLeaf()) // 현재 노드가 리프 노드가 아닌 경우
                        currentNode = currentNode.getChildren().get(currentNode.getKeyList().size()); // 자식 노드 순회

                    int predecessor = currentNode.getKeyList().getLast(); // 프리디세서 선정
                    myBPlusTreeNode.getKeyList().set(index, predecessor);
                    removeHelper(myBPlusTreeNode.getChildren().get(index), predecessor); // 삭제
                } else if (myBPlusTreeNode.getChildren().get(index + 1).getKeyList().size() >= (m + 1) / 2) {
                    MyBPlusTreeNode currentNode = myBPlusTreeNode.getChildren().get(index + 1);

                    while (!currentNode.isLeaf())
                        currentNode = currentNode.getChildren().getFirst();

                    int successor = currentNode.getKeyList().getFirst(); // 석세서 선정
                    myBPlusTreeNode.getKeyList().set(index, successor);
                    removeHelper(myBPlusTreeNode.getChildren().get(index + 1), successor);
                } else {
                    merge(myBPlusTreeNode, index); // 병합
                    removeHelper(myBPlusTreeNode.getChildren().get(index), tempKey);
                }
            }
        } else { // 못찾은 경우
            if (myBPlusTreeNode.isLeaf()) { // 리프 노드인 경우 종료
                return;
            }

            boolean isLast = (index == myBPlusTreeNode.getKeyList().size()); // 마지막 인덱스인지 확인

            if (myBPlusTreeNode.getChildren().get(index).getKeyList().size() < (m + 1) / 2) { // 키 갯수가 모자란 경우
                if (index != 0 && myBPlusTreeNode.getChildren().get(index - 1).getKeyList().size() >= (m + 1) / 2) { // 자식 노드를 채움
                    MyBPlusTreeNode child = myBPlusTreeNode.getChildren().get(index);
                    MyBPlusTreeNode sibling = myBPlusTreeNode.getChildren().get(index - 1);
                    child.getKeyList().addFirst(myBPlusTreeNode.getKeyList().get(index - 1));

                    if (!child.isLeaf())
                        child.getChildren().addFirst(sibling.getChildren().removeLast());

                    myBPlusTreeNode.getKeyList().set(index - 1, sibling.getKeyList().removeLast());
                } else if (index != myBPlusTreeNode.getKeyList().size() && myBPlusTreeNode.getChildren().get(index + 1).getKeyList().size() >= (m + 1) / 2) {
                    MyBPlusTreeNode child = myBPlusTreeNode.getChildren().get(index); // 다시 채움
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

            if (isLast && index > myBPlusTreeNode.getKeyList().size()) { // 자식 노드 채운 이후 병합되어 인덱스가 변경된 경우
                removeHelper(myBPlusTreeNode.getChildren().get(index - 1), key); // 직전 노드 삭제
            } else { // 변화 없는 경우
                removeHelper(myBPlusTreeNode.getChildren().get(index), key); // 현재 인덱스 자식 노드 삭제
            }
        }
    }

    private void merge(MyBPlusTreeNode myBPlusTreeNode, int index) {
        MyBPlusTreeNode child = myBPlusTreeNode.getChildren().get(index);
        MyBPlusTreeNode sibling = myBPlusTreeNode.getChildren().get(index + 1);

        if (!child.isLeaf()) // 자식 노드가 리프 노드가 아닌 경우
            child.getKeyList().add(myBPlusTreeNode.getKeyList().get(index)); // 키 추가

        for (int i = 0; i < sibling.getKeyList().size(); i++) // 시블링 노드에서 순서대로 저장
            child.getKeyList().add(sibling.getKeyList().get(i));

        if (!child.isLeaf())
            for (int i = 0; i < sibling.getChildren().size(); i++) // 시블링의 자식 노드들 추가
                child.getChildren().add(sibling.getChildren().get(i));

        myBPlusTreeNode.getKeyList().remove(index);
        myBPlusTreeNode.getChildren().remove(index + 1);

        if (myBPlusTreeNode == root && myBPlusTreeNode.getKeyList().isEmpty()) // 현재 노드가 루트 노드이고 빈 노드인 경우
            root = child; // 루트를 자식 노드로 저장
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
            MyBPlusTreeNode currentNode = root; // 루트 노드를 현재 노드로 초기화
            int index = 0;

            {
                while (!currentNode.isLeaf()) // 리프가 아닌동안
                    currentNode = currentNode.getChildren().getFirst(); // 맨 왼쪽 노드로 이동
            }

            @Override
            public boolean hasNext() {
                return index < currentNode.getKeyList().size() || currentNode.getNext() != null; // 현재 노드를 순회중이거나, 다음 노드가 있는 경우 확인
            }

            @Override
            public Integer next() {
                if (index >= currentNode.getKeyList().size()) { // 현재 노드가 끝난 경우
                    currentNode = currentNode.getNext(); // 다음 노드 받아옴
                    index = 0; // 새 노드이므로 인덱스 0으로 초기화

                    if (currentNode == null) // 다음 노드가 없는 경우
                        throw new NoSuchElementException();
                }
                return currentNode.getKeyList().get(index++); // 현재 키 값을 반환함과 동시에 인덱스 증가
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
