package org.dfpl.db.hash.m16013094;
//package 이름은 org.dfpl.db.hash.m학번 입니다. 

//지키지 않을 시 반려합니다. 

import java.util.*;

@SuppressWarnings("unused")
public class MyThreeWayBTree implements NavigableSet<Integer> {
    private MyThreeWayBTreeNode root;
    private int size;

    public boolean add(Integer value) { // 노드 추가
        if (root == null) { // 루트가 null 일 때
            root = MyThreeWayBTreeNode.newTwoNode(value);
        } else { // 아닐 때
            try {
                MyThreeWayBTreeNode result = insert(value, root); // 노드 삽입 함수 호출
                if (result != null) {
                    root = result;
                }
            } catch (DuplicateException e) {
                return false;
            }
        }
        size++;
        return true;
    }

    @Override
    public boolean remove(Object o) { // 노드 삭제
        return remove((Integer) o);
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends Integer> c) {
        return false;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public boolean contains(Object o) {
        return findNode(root, (Integer) o) != null;
    }

    private MyThreeWayBTreeNode findNode(MyThreeWayBTreeNode node, Integer value) { // 노드 탐색
        if (node == null) { // 탐색 시작 노드가 null 일 때
            return null;
        }

        if (node.isThreeNode()) { // 원소가 두개이면
            int leftComp = value.compareTo((Integer) node.leftElement()); // 왼쪽 원소와 비교
            int rightComp = value.compareTo((Integer) node.rightElement()); // 오른쪽 원소와 비교
            if (leftComp == 0 || rightComp == 0) { // 둘 중 한쪽과 일치할 때
                return node;
            }
            if (leftComp < 0) { // 왼쪽 원소보다 작으면 왼쪽 자식으로 이동 (재귀)
                return findNode(node.leftChild(), value);
            } else if (rightComp < 0) { // 왼쪽 원소보다 크나, 오른쪽 보다 작으면 가운데 자식으로 이동 (재귀)
                return findNode(node.middleChild(), value);
            } else { // 오른쪽 원소보다 크면 오른쪽 자식으로 이동 (재귀)
                return findNode(node.rightChild(), value);
            }
        } else { // 원소가 하나인 노드일 때
            int comp = value.compareTo((Integer) node.element()); // 단일 원소와 비교
            if (comp == 0) { // 같으면 해당 노드 반환
                return node;
            }
            if (comp < 0) { // 작으면 왼쪽 탐색
                return findNode(node.leftChild(), value);
            } else { // 크면 오른쪽 탐색
                return findNode(node.rightChild(), value);
            }
        }
    }


    public String next(int x) { // 다음 노드
        int n = nextNode(x);
        return (n == Integer.MAX_VALUE) ? "none" : String.valueOf(n);
    }

    private Integer nextNode(Integer x) { // 다음 노드 실질적 함수
        if (root == null) { // 빈 트리일 때
            return Integer.MAX_VALUE; // int형 최댓값 반환
        } else if (size == 1) { // 루트가 노드 뿐일 때
            if (x >= last()) { // 마지막 원소보다 클 경우
                return Integer.MAX_VALUE;
            } else { // 작을 경우
                return root.leftElement();
            }
        } else if (size == 2) { // 루트가 노드뿐이면서 원소가 두개일 때
            if (x >= last()) { // 마지막 원소보다 클 경우
                return Integer.MAX_VALUE;
            } else {
                if (root.leftElement() > x) { // 왼쪽보다 작을 경우
                    return root.leftElement();
                } else { // 왼쪽보다 클 경우
                    return root.rightElement();
                }
            }
        } else { // 노드가 여러개일 때
            MyThreeWayBTreeNode currentNode = root; // 루트부터 탐색
            int nextValue = Integer.MAX_VALUE;
            while (!currentNode.isTerminal()) { // 자식이 존재하는 노드
                if (currentNode.isTwoNode()) { // 원소가 하나인 경우 (탐색 방식은 트리의 기본 방식. 위와 동일)
                    if (x < currentNode.leftElement()) {
                        nextValue = currentNode.leftElement();
                        currentNode = currentNode.leftChild();
                    } else {
                        currentNode = currentNode.rightChild();
                    }
                } else if (currentNode.isThreeNode()) { // 원소가 두개인 경우
                    if (x < currentNode.leftElement()) {
                        nextValue = currentNode.leftElement();
                        currentNode = currentNode.leftChild();
                    } else if (x < currentNode.rightElement()) {
                        nextValue = currentNode.rightElement();
                        currentNode = currentNode.middleChild();
                    } else {
                        currentNode = currentNode.rightChild();
                    }
                }
            }
            if (currentNode.isTwoNode()) { // 원소가 하나인 노드일 때
                if (currentNode.leftElement() > x) {
                    return currentNode.leftElement();
                } else {
                    return nextValue;
                }
            } else { // 원소가 둘인 노드일 때
                if (currentNode.leftElement() > x) {
                    return currentNode.leftElement();
                } else if (currentNode.rightElement() > x) {
                    return currentNode.rightElement();
                } else return nextValue;
            }
        }
    }

    public String prev(int x) { // 이전 노드
        int n = prevNode(x);
        return (n == Integer.MIN_VALUE) ? "none" : String.valueOf(n);
    }

    private int prevNode(int x) { // 이전 노드 실질적 함수. 방식은 동일하나 반대로 검사
        if (root == null) {
            return Integer.MIN_VALUE;
        } else if (size == 1) {
            if (x <= first()) {
                return Integer.MIN_VALUE;
            } else {
                return root.leftElement();
            }
        } else if (size == 2) {
            if (x <= first()) {
                return Integer.MIN_VALUE;
            } else {
                if (root.rightElement() < x) {
                    return root.rightElement();
                } else {
                    return root.leftElement();
                }
            }
        } else {
            MyThreeWayBTreeNode currentNode = root;
            int prevValue = Integer.MIN_VALUE;
            while (!currentNode.isTerminal()) {
                if (currentNode.isTwoNode()) {
                    if (x > currentNode.leftElement()) {
                        prevValue = currentNode.leftElement();
                        currentNode = currentNode.rightChild();
                    } else {
                        currentNode = currentNode.leftChild();
                    }
                } else if (currentNode.isThreeNode()) {
                    if (x > currentNode.rightElement()) {
                        prevValue = currentNode.rightElement();
                        currentNode = currentNode.rightChild();
                    } else if (x > currentNode.leftElement()) {
                        prevValue = currentNode.leftElement();
                        currentNode = currentNode.middleChild();
                    } else {
                        currentNode = currentNode.leftChild();
                    }
                }
            }
            if (currentNode.isTwoNode()) {
                if (currentNode.leftElement() < x) {
                    return currentNode.leftElement();
                } else {
                    return prevValue;
                }
            } else {
                if (currentNode.rightElement() < x) {
                    return currentNode.rightElement();
                } else if (currentNode.leftElement() < x) {
                    return currentNode.leftElement();
                } else return prevValue;
            }
        }
    }

    private static final class DuplicateException extends RuntimeException {
    }

    ;
    private static final DuplicateException DUPLICATE = new DuplicateException(); // 복사 예외 검사 처리용

    private MyThreeWayBTreeNode insert(Integer value, MyThreeWayBTreeNode node) throws DuplicateException { // 노드 삽입
        MyThreeWayBTreeNode returnValue = null;
        if (node.isTwoNode()) { // 원소가 하나인 경우
            int comp = value.compareTo(node.element()); // 현재 원소와 비교

            if (node.isTerminal()) { // 자식이 없을 때
                if (comp == 0) { // 같으면 동일한 값이므로 예외 throw
                    throw DUPLICATE;
                }
                MyThreeWayBTreeNode thnode = MyThreeWayBTreeNode.newThreeNode(value, node.element()); // 새로운 원소 두개 노드
                MyThreeWayBTreeNode parent = node.parent(); // 부모 노드
                if (parent != null) { // 부모가 있는 경우
                    parent.replaceChild(node, thnode); // 자식 교체
                } else { // null인 경우 -> 루트가 없을 때
                    root = thnode;
                }
            } else { // 자식이 있을 때
                if (comp < 0) { // 비교 값이 더 클 때
                    MyThreeWayBTreeNode result = insert(value, node.leftChild());
                    if (result != null) {
                        MyThreeWayBTreeNode threeNode = MyThreeWayBTreeNode.newThreeNode(result.element(), node.element());
                        threeNode.setRightChild(node.rightChild());
                        threeNode.setMiddleChild(result.rightChild());
                        threeNode.setLeftChild(result.leftChild());
                        if (node.parent() != null) {
                            node.parent().replaceChild(node, threeNode);
                        } else {
                            root = threeNode;
                        }
                        unlinkNode(node);
                    }
                } else if (comp > 0) { // 비교 값이 더 작을 때
                    MyThreeWayBTreeNode result = insert(value, node.rightChild());
                    if (result != null) {
                        MyThreeWayBTreeNode threeNode = MyThreeWayBTreeNode.newThreeNode(result.element(), node.element());
                        threeNode.setLeftChild(node.leftChild());
                        threeNode.setMiddleChild(result.leftChild());
                        threeNode.setRightChild(result.rightChild());
                        if (node.parent() != null) {
                            node.parent().replaceChild(node, threeNode);
                        } else {
                            root = threeNode;
                        }
                        unlinkNode(node);
                    }
                } else {
                    throw DUPLICATE;
                }
            }

        } else { // three node
            MyThreeWayBTreeNode threeNode = node;

            int leftComp = value.compareTo(threeNode.leftElement());
            int rightComp = value.compareTo(threeNode.rightElement());
            if (leftComp == 0 || rightComp == 0) {
                throw DUPLICATE;
            }

            if (threeNode.isTerminal()) {

                returnValue = splitNode(threeNode, value);

            } else {
                if (leftComp < 0) {
                    MyThreeWayBTreeNode result = insert(value, threeNode.leftChild());
                    if (result != null) {
                        returnValue = splitNode(threeNode, result.element());
                        returnValue.leftChild().setLeftChild(result.leftChild());
                        returnValue.leftChild().setRightChild(result.rightChild());
                        returnValue.rightChild().setLeftChild(threeNode.middleChild());
                        returnValue.rightChild().setRightChild((threeNode.rightChild()));
                        unlinkNode(threeNode);
                    }
                } else if (rightComp < 0) {
                    MyThreeWayBTreeNode result = insert(value, threeNode.middleChild());
                    if (result != null) {
                        returnValue = splitNode(threeNode, result.element());
                        returnValue.leftChild().setLeftChild(threeNode.leftChild());
                        returnValue.leftChild().setRightChild(result.leftChild());
                        returnValue.rightChild().setLeftChild(result.rightChild());
                        returnValue.rightChild().setRightChild(threeNode.rightChild());
                        unlinkNode(threeNode);
                    }
                } else {
                    MyThreeWayBTreeNode result = insert(value, threeNode.rightChild());
                    if (result != null) {
                        returnValue = splitNode(threeNode, result.element());
                        returnValue.leftChild().setLeftChild(threeNode.leftChild());
                        returnValue.leftChild().setRightChild(threeNode.middleChild());
                        returnValue.rightChild().setLeftChild(result.leftChild());
                        returnValue.rightChild().setRightChild(result.rightChild());
                        unlinkNode(threeNode);
                    }
                }
            }
        }
        return returnValue;
    }

    public boolean remove(Integer value) { // 삭제 함수
        if (value == null) {
            return false;
        }

        MyThreeWayBTreeNode node = findNode(root, value);
        if (node == null) {
            return false;
        }

        HoleNode hole = null;
        MyThreeWayBTreeNode terminalNode;
        Integer holeValue;
        if (node.isTerminal()) {
            terminalNode = node;
            holeValue = value;
        } else {
            // successor에 의한 교체
            if (node.isThreeNode()) {
                if (node.leftElement() == value) {
                    MyThreeWayBTreeNode pred = predecessor(node, value);
                    holeValue = pred.isThreeNode() ? pred.rightElement() : pred.element();
                    node.setLeftElement(holeValue);
                    terminalNode = pred;
                } else {
                    MyThreeWayBTreeNode succ = successor(node, value);
                    holeValue = succ.isThreeNode() ? succ.leftElement() : succ.element();
                    node.setRightElement(holeValue);
                    terminalNode = succ;
                }
            } else {
                MyThreeWayBTreeNode succ = successor(node, value);
                holeValue = succ.isThreeNode() ? succ.leftElement() : succ.element();
                node.setElement(holeValue);
                terminalNode = succ;
            }
        }

        assert terminalNode.isTerminal();

        if (terminalNode.isThreeNode()) {
            // 원소가 두개인 노드를 하나인 노드로 교체
            Integer val = terminalNode.leftElement() == holeValue ? terminalNode.rightElement() :
                    terminalNode.leftElement();
            MyThreeWayBTreeNode twoNode = MyThreeWayBTreeNode.newTwoNode(val);
            if (terminalNode.parent() != null) {
                terminalNode.parent().replaceChild(terminalNode, twoNode);
            } else {
                root = twoNode;
            }
        } else {
            if (terminalNode.parent() != null) {
                hole = MyThreeWayBTreeNode.newHole();
                terminalNode.parent().replaceChild(terminalNode, hole);
            } else {
                root = null;
            }
        }

        while (hole != null) {
            // 구멍이 있고, 구멍 노드에 자식이 있는 경우 (자식이 원소가 하나)
            if (hole.parent().isTwoNode() && hole.sibling().isTwoNode()) {
                MyThreeWayBTreeNode parent = hole.parent();
                MyThreeWayBTreeNode sibling = hole.sibling();

                MyThreeWayBTreeNode threeNode = MyThreeWayBTreeNode.newThreeNode(parent.element(), sibling.element());
                if (parent.leftChild() == hole) {
                    threeNode.setLeftChild(hole.child());
                    threeNode.setMiddleChild(sibling.leftChild());
                    threeNode.setRightChild(sibling.rightChild());
                } else {
                    threeNode.setLeftChild(sibling.leftChild());
                    threeNode.setMiddleChild(sibling.rightChild());
                    threeNode.setRightChild(hole.child());
                }

                if (parent.parent() == null) {
                    unlinkNode(hole);
                    root = threeNode;
                    hole = null;
                } else {
                    hole.setChild(threeNode);
                    parent.parent().replaceChild(parent, hole);
                }
                unlinkNode(parent);
                unlinkNode(sibling);

            }
            // 구멍이 있고, 구멍 노드에 자식이 있는 경우 (자식이 원소가 두개)
            else if (hole.parent().isTwoNode() && hole.sibling().isThreeNode()) {
                MyThreeWayBTreeNode parent = hole.parent();
                MyThreeWayBTreeNode sibling = hole.sibling();

                if (parent.leftChild() == hole) {
                    MyThreeWayBTreeNode leftChild = MyThreeWayBTreeNode.newTwoNode(parent.element());
                    MyThreeWayBTreeNode rightChild = MyThreeWayBTreeNode.newTwoNode(sibling.rightElement());
                    parent.setElement(sibling.leftElement());
                    parent.replaceChild(hole, leftChild);
                    parent.replaceChild(sibling, rightChild);
                    leftChild.setLeftChild(hole.child());
                    leftChild.setRightChild(sibling.leftChild());
                    rightChild.setLeftChild(sibling.middleChild());
                    rightChild.setRightChild(sibling.rightChild());
                } else {
                    MyThreeWayBTreeNode leftChild = MyThreeWayBTreeNode.newTwoNode(sibling.leftElement());
                    MyThreeWayBTreeNode rightChild = MyThreeWayBTreeNode.newTwoNode(parent.element());
                    parent.setElement(sibling.rightElement());
                    parent.replaceChild(sibling, leftChild);
                    parent.replaceChild(hole, rightChild);
                    leftChild.setLeftChild(sibling.leftChild());
                    leftChild.setRightChild(sibling.middleChild());
                    rightChild.setLeftChild(sibling.rightChild());
                    rightChild.setRightChild(hole.child());
                }
                unlinkNode(hole);
                unlinkNode(sibling);
                hole = null;
            }

            // 부모 노드의 원소가 두개
            else if (hole.parent().isThreeNode()) {
                MyThreeWayBTreeNode parent = hole.parent();

                // 구멍이 가운데 자식 노드일 경우 1
                if (parent.middleChild() == hole && parent.leftChild().isTwoNode()) {
                    MyThreeWayBTreeNode leftChild = parent.leftChild();
                    MyThreeWayBTreeNode newParent = MyThreeWayBTreeNode.newTwoNode(parent.rightElement());
                    MyThreeWayBTreeNode newLeftChild = MyThreeWayBTreeNode.newThreeNode(leftChild.element(), parent.leftElement());
                    newParent.setLeftChild(newLeftChild);
                    newParent.setRightChild(parent.rightChild());
                    if (parent != root) {
                        parent.parent().replaceChild(parent, newParent);
                    } else {
                        root = newParent;
                    }

                    newLeftChild.setLeftChild(leftChild.leftChild());
                    newLeftChild.setMiddleChild(leftChild.rightChild());
                    newLeftChild.setRightChild(hole.child());

                    unlinkNode(parent);
                    unlinkNode(leftChild);
                    unlinkNode(hole);
                    hole = null;
                }
                // 구멍이 가운데 자식 노드일 경우 2
                else if (parent.middleChild() == hole && parent.rightChild().isTwoNode()) {
                    MyThreeWayBTreeNode rightChild = parent.rightChild();
                    MyThreeWayBTreeNode newParent = MyThreeWayBTreeNode.newTwoNode(parent.leftElement());
                    MyThreeWayBTreeNode newRightChild = MyThreeWayBTreeNode.newThreeNode(parent.rightElement(), rightChild.element());
                    newParent.setLeftChild(parent.leftChild());
                    newParent.setRightChild(newRightChild);
                    if (parent != root) {
                        parent.parent().replaceChild(parent, newParent);
                    } else {
                        root = newParent;
                    }
                    newRightChild.setLeftChild(hole.child());
                    newRightChild.setMiddleChild(rightChild.leftChild());
                    newRightChild.setRightChild(rightChild.rightChild());
                    unlinkNode(parent);
                    unlinkNode(rightChild);
                    unlinkNode(hole);
                    hole = null;
                } else if (parent.middleChild().isTwoNode()) {
                    MyThreeWayBTreeNode middleChild = parent.middleChild();

                    // 구멍이 왼쪽 자식 노드일 경우
                    if (parent.leftChild() == hole) {
                        MyThreeWayBTreeNode newParent = MyThreeWayBTreeNode.newTwoNode(parent.rightElement());
                        MyThreeWayBTreeNode leftChild = MyThreeWayBTreeNode.newThreeNode(parent.leftElement(), middleChild.element());
                        newParent.setLeftChild(leftChild);
                        newParent.setRightChild(parent.rightChild());
                        if (parent != root) {
                            parent.parent().replaceChild(parent, newParent);
                        } else {
                            root = newParent;
                        }

                        leftChild.setLeftChild(hole.child());
                        leftChild.setMiddleChild(middleChild.leftChild());
                        leftChild.setRightChild(middleChild.rightChild());

                        unlinkNode(parent);
                        unlinkNode(hole);
                        unlinkNode(middleChild);
                        hole = null;
                    }
                    // 구멍이 오른쪽 자식 노드일 경우
                    else if (parent.rightChild() == hole) {
                        MyThreeWayBTreeNode newParent = MyThreeWayBTreeNode.newTwoNode(parent.leftElement());
                        MyThreeWayBTreeNode rightChild = MyThreeWayBTreeNode.newThreeNode(middleChild.element(), parent.rightElement());
                        newParent.setRightChild(rightChild);
                        newParent.setLeftChild(parent.leftChild());
                        if (parent != root) {
                            parent.parent().replaceChild(parent, newParent);
                        } else {
                            root = newParent;
                        }

                        rightChild.setLeftChild(middleChild.leftChild());
                        rightChild.setMiddleChild(middleChild.rightChild());
                        rightChild.setRightChild(hole.child());

                        unlinkNode(parent);
                        unlinkNode(hole);
                        unlinkNode(middleChild);
                        hole = null;
                    }
                }

                // 구멍 노드가 원소가 두개인 노드이면서 부모 노드도 원소가 두개인 경우
                else if (parent.middleChild().isThreeNode()) {
                    MyThreeWayBTreeNode middleChild = parent.middleChild();
                    // 구멍이 왼쪽 자식 노드일 경우
                    if (hole == parent.leftChild()) {
                        MyThreeWayBTreeNode newLeftChild = MyThreeWayBTreeNode.newTwoNode(parent.leftElement());
                        MyThreeWayBTreeNode newMiddleChild = MyThreeWayBTreeNode.newTwoNode(middleChild.rightElement());
                        parent.setLeftElement(middleChild.leftElement());
                        parent.setLeftChild(newLeftChild);
                        parent.setMiddleChild(newMiddleChild);
                        newLeftChild.setLeftChild(hole.child());
                        newLeftChild.setRightChild(middleChild.leftChild());
                        newMiddleChild.setLeftChild(middleChild.middleChild());
                        newMiddleChild.setRightChild(middleChild.rightChild());

                        unlinkNode(hole);
                        unlinkNode(middleChild);
                        hole = null;
                    }
                    // 구멍이 오른쪽 자식 노드일 경우
                    else if (hole == parent.rightChild()) {
                        MyThreeWayBTreeNode newMiddleChild = MyThreeWayBTreeNode.newTwoNode(middleChild.leftElement());
                        MyThreeWayBTreeNode newRightChild = MyThreeWayBTreeNode.newTwoNode(parent.rightElement());
                        parent.setRightElement(middleChild.rightElement());
                        parent.setMiddleChild(newMiddleChild);
                        parent.setRightChild(newRightChild);
                        newMiddleChild.setLeftChild(middleChild.leftChild());
                        newMiddleChild.setRightChild(middleChild.middleChild());

                        newRightChild.setLeftChild(middleChild.rightChild());
                        newRightChild.setRightChild(hole.child());

                        unlinkNode(hole);
                        unlinkNode(middleChild);
                        hole = null;

                    } else if (hole == parent.middleChild() && parent.leftChild().isThreeNode()) {
                        MyThreeWayBTreeNode leftChild = parent.leftChild();
                        MyThreeWayBTreeNode newLeftChild = MyThreeWayBTreeNode.newTwoNode(leftChild.leftElement());
                        MyThreeWayBTreeNode newMiddleChild = MyThreeWayBTreeNode.newTwoNode(parent.leftElement());
                        parent.setLeftElement(leftChild.rightElement());
                        parent.setLeftChild(newLeftChild);
                        parent.setMiddleChild(newMiddleChild);
                        newLeftChild.setLeftChild(leftChild.leftChild());
                        newLeftChild.setRightChild(leftChild.middleChild());
                        newMiddleChild.setLeftChild(leftChild.rightChild());
                        newMiddleChild.setRightChild(hole.child());

                        unlinkNode(hole);
                        unlinkNode(leftChild);
                        hole = null;
                    } else {
                        assert (hole == parent.middleChild() && parent.rightChild().isThreeNode());
                        MyThreeWayBTreeNode rightChild = parent.rightChild();
                        MyThreeWayBTreeNode newRightChild = MyThreeWayBTreeNode.newTwoNode(rightChild.rightElement());
                        MyThreeWayBTreeNode newMiddleChild = MyThreeWayBTreeNode.newTwoNode(parent.rightElement());
                        parent.setRightElement(rightChild.leftElement());
                        parent.setMiddleChild(newMiddleChild);
                        parent.setRightChild(newRightChild);
                        newRightChild.setRightChild(rightChild.rightChild());
                        newRightChild.setLeftChild(rightChild.middleChild());
                        newMiddleChild.setRightChild(rightChild.leftChild());
                        newMiddleChild.setLeftChild(hole.child());

                        unlinkNode(hole);
                        unlinkNode(rightChild);
                        hole = null;
                    }
                }

            }
        }

        size--;
        return true;
    }

    private void unlinkNode(MyThreeWayBTreeNode node) { // 노드 연결 해제
        node.removeChildren();
        node.setParent(null);
    }

    private MyThreeWayBTreeNode successor(MyThreeWayBTreeNode node, Integer value) { // successor
        if (node == null) {
            return null;
        }

        if (!node.isTerminal()) {
            MyThreeWayBTreeNode p;
            if (node.isThreeNode() && node.leftElement() == (value)) {
                p = node.middleChild();
            } else {
                p = node.rightChild();
            }
            while (p.leftChild() != null) {
                p = p.leftChild();
            }
            return p;
        } else {
            MyThreeWayBTreeNode p = node.parent();
            if (p == null) {
                return null;
            }

            MyThreeWayBTreeNode ch = node;
            while (p != null && ch == p.rightChild()) {
                ch = p;
                p = p.parent();
            }
            return p != null ? p : null;
        }
    }

    private MyThreeWayBTreeNode predecessor(MyThreeWayBTreeNode node, Integer value) { // predecessor
        if (node == null) {
            return null;
        }

        MyThreeWayBTreeNode p;
        if (!node.isTerminal()) {
            if (node.isThreeNode() && node.rightElement() == (value)) {
                p = node.middleChild();
            } else {
                p = node.leftChild();
            }

            while (p.rightChild() != null) {
                p = p.rightChild();
            }
            return p;
        } else {
            throw new UnsupportedOperationException(
                    "Implement predecessor parent is not terminal node");
        }

    }

    private MyThreeWayBTreeNode splitNode(MyThreeWayBTreeNode threeNode, Integer value) { // 노드 스플릿
        Integer min;
        Integer max;
        Integer middle;
        if (value.compareTo(threeNode.leftElement()) < 0) {
            min = value;
            middle = threeNode.leftElement();
            max = threeNode.rightElement();
        } else if (value.compareTo(threeNode.rightElement()) < 0) {
            min = threeNode.leftElement();
            middle = value;
            max = threeNode.rightElement();
        } else {
            min = threeNode.leftElement();
            max = value;
            middle = threeNode.rightElement();
        }

        MyThreeWayBTreeNode parent = MyThreeWayBTreeNode.newTwoNode(middle);
        parent.setLeftChild(MyThreeWayBTreeNode.newTwoNode(min));
        parent.setRightChild(MyThreeWayBTreeNode.newTwoNode(max));
        return parent;
    }

    public interface Function { // 적용 함수 인터페이스
        public void apply(Integer t);
    }

    public void preOrder(MyThreeWayBTreeNode node, Function f) { // 전위 순회
        if (node.isThreeNode()) {
            f.apply(node.leftElement());
            f.apply(node.rightElement());
        }
        if (node.isTerminal()) {
            return;
        }


        preOrder(node.leftChild(), f);
        if (node.isThreeNode()) {
            assert node.middleChild() != null;
            preOrder(node.middleChild(), f);
        }
        preOrder(node.rightChild(), f);
    }

    public void inorderSearch(MyThreeWayBTreeNode node, Function func) { // 중위 검색
        if (node == null) {
            return;
        }
        inorderSearch(node.leftChild(), func);
        if (node.isThreeNode()) {
            MyThreeWayBTreeNode threeNode = node;
            func.apply(threeNode.leftElement());
            inorderSearch(threeNode.middleChild(), func);
            func.apply(threeNode.rightElement());
        } else {
            func.apply(node.element());
        }
        inorderSearch(node.rightChild(), func);
    }

    @Override
    public Integer lower(Integer integer) {
        return null;
    }

    @Override
    public Integer floor(Integer integer) {
        return null;
    }

    @Override
    public Integer ceiling(Integer integer) {
        return null;
    }

    @Override
    public Integer higher(Integer integer) {
        return null;
    }

    @Override
    public Integer pollFirst() {
        return null;
    }

    @Override
    public Integer pollLast() {
        return null;
    }

    public Iterator iterator() {

        return new Iterator() {
            MyThreeWayBTreeNode nextNode;

            // Stack to keep three nodes
            Deque<MyThreeWayBTreeNode> threeNodes = new ArrayDeque<MyThreeWayBTreeNode>();
            Integer next;

            {
                MyThreeWayBTreeNode node = root;
                while (node != null && node.leftChild() != null) {
                    node = node.leftChild();
                }
                nextNode = node;
            }

            public boolean hasNext() {
                return next != null || nextNode != null;
            }

            public Integer next() {
                Integer prev;
                if (next != null) {
                    prev = next;
                    next = null;
                    nextNode = successor(nextNode, prev);
                    return prev;
                }
                if (nextNode.isThreeNode()) {
                    if (nextNode.isTerminal()) {
                        next = nextNode.rightElement();
                        prev = nextNode.leftElement();
                    } else {
                        if (threeNodes.peekFirst() == nextNode) {
                            threeNodes.pollFirst();
                            assert nextNode != null;
                            prev = nextNode.rightElement();
                        } else {
                            prev = nextNode.leftElement();
                            threeNodes.addFirst(nextNode);
                        }
                        nextNode = successor(nextNode, prev);
                    }
                } else {
                    prev = nextNode.element();
                    nextNode = successor(nextNode, prev);
                }
                return prev;
            }
        };

    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

    @Override
    public <T> T[] toArray(T[] a) {
        return null;
    }

    @Override
    public NavigableSet<Integer> descendingSet() {
        return null;
    }

    @Override
    public Iterator<Integer> descendingIterator() {
        return null;
    }

    @Override
    public NavigableSet<Integer> subSet(Integer fromElement, boolean fromInclusive, Integer toElement, boolean toInclusive) {
        return null;
    }

    @Override
    public NavigableSet<Integer> headSet(Integer toElement, boolean inclusive) {
        return null;
    }

    @Override
    public NavigableSet<Integer> tailSet(Integer fromElement, boolean inclusive) {
        return null;
    }

    @Override
    public Comparator<? super Integer> comparator() {
        return null;
    }

    @Override
    public SortedSet<Integer> subSet(Integer fromElement, Integer toElement) {
        return null;
    }

    @Override
    public SortedSet<Integer> headSet(Integer toElement) {
        return null;
    }

    @Override
    public SortedSet<Integer> tailSet(Integer fromElement) {
        return null;
    }

    public Integer first() { // 맨 왼쪽 첫번째 노드
        MyThreeWayBTreeNode node = root;
        while (node.leftChild() != null) {
            node = node.leftChild();
        }
        return node.isThreeNode() ? node.leftElement() : node.element();
    }

    public Integer last() { // 맨 오른쪽 마지막 노드
        MyThreeWayBTreeNode node = root;
        while (node.rightChild() != null) {
            node = node.rightChild();
        }
        return node.isThreeNode() ? node.rightElement() : node.element();
    }

    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }
}

