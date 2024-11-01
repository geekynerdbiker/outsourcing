package org.dfpl.db.hash.m16013094;

//package 이름은 org.dfpl.db.hash.m학번 입니다.
//지키지 않을 시 반려합니다.

@SuppressWarnings("unused")
public class MyThreeWayBTreeNode {

    MyThreeWayBTreeNode parent;
    MyThreeWayBTreeNode leftChild;
    MyThreeWayBTreeNode middleChild;
    MyThreeWayBTreeNode rightChild;
    Integer leftElement;
    Integer rightElement;
    boolean twoNode;
    public static MyThreeWayBTreeNode newTwoNode(int element) { // 원소가 하나인 노드 추가
        MyThreeWayBTreeNode node = new MyThreeWayBTreeNode();
        node.leftElement = element;
        node.twoNode = true;
        return node;
    }

    public static MyThreeWayBTreeNode newThreeNode(int leftElement, int rightElement) { // 원소가 두개인 노드 추가
        MyThreeWayBTreeNode node = new MyThreeWayBTreeNode();
        if (leftElement > rightElement) { // 왼쪽이 작은 값이 되도록 함
            node.rightElement = leftElement;
            node.leftElement = rightElement;
        } else {
            node.leftElement = leftElement;
            node.rightElement = rightElement;
        }
        node.twoNode = false;
        return node;
    }


    public static HoleNode newHole() {
        return new HoleNode();
    } // 구멍 노드 추가


    public void setLeftChild(MyThreeWayBTreeNode leftChild) { // 왼쪽 자식 setter
        this.leftChild = leftChild;
        if (leftChild != null) { // 부모 노드로 지정
            leftChild.setParent(this);
        }
    }

    public void removeChildren() { // 자식 제거
        this.leftChild = null;
        this.rightChild = null;
    }


    public void setRightChild(MyThreeWayBTreeNode rightChild) { // 오른쪽 자식 setter
        this.rightChild = rightChild;
        if (rightChild != null) { // 부모 노드로 지정
            rightChild.setParent(this);
        }
    }

    public void setMiddleChild(MyThreeWayBTreeNode middleChild) { // 가운데 자식 setter
        assert isThreeNode(); // 노드 원소가 두개가 아니면 assert
        this.middleChild = middleChild;
        if (middleChild != null) { // 부모 노드로 지정
            middleChild.setParent(this);
        }
    }


    public final MyThreeWayBTreeNode parent() {
        return parent;
    } // 부모 노드 getter

    public final void setParent(MyThreeWayBTreeNode parent) {
        this.parent = parent;
    } // 부모 노드 setter


    public boolean isTerminal() {
        return leftChild == null && rightChild == null;
    } // 자식이 없는 노드인지 검사


    public Integer element() { // getter
        assert isTwoNode();
        return leftElement;
    }


    public Integer leftElement() { // getter
        assert isThreeNode();
        return leftElement;
    }

    public void setElement(Integer element) { // setter
        assert isTwoNode();
        leftElement = element;
    }


    public Integer rightElement() { // getter
        assert isThreeNode();
        return rightElement;
    }

    public void setLeftElement(Integer leftElement) { // setter
        assert isThreeNode();
        this.leftElement = leftElement;
    }

    public void setRightElement(Integer rightElement) { // setter
        assert isThreeNode();
        this.rightElement = rightElement;
    }

    public boolean isTwoNode() { // getter
        return twoNode;
    }

    public boolean isThreeNode() {
        return !isTwoNode();
    } // 원소가 두개인 노드인지 검사

    public MyThreeWayBTreeNode leftChild() {
        return leftChild;
    } // getter

    public MyThreeWayBTreeNode rightChild() {
        return rightChild;
    } // getter

    public MyThreeWayBTreeNode middleChild() { // getter
        assert isThreeNode(); // 원소 값이 두개가 아니면 assert
        return middleChild;
    }


    public void replaceChild(MyThreeWayBTreeNode currentChild, MyThreeWayBTreeNode newChild) { // 자식 교체 함수
        if (currentChild == leftChild) {
            leftChild = newChild;
        } else if (currentChild == rightChild) {
            rightChild = newChild;
        } else {
            assert middleChild == currentChild;
            middleChild = newChild;
        }
        newChild.setParent(this);
        currentChild.setParent(null);
    }
}

class HoleNode extends MyThreeWayBTreeNode { // 구멍 노드
    private MyThreeWayBTreeNode child;

    HoleNode() {
        super();
    }

    public boolean isTwoNode() {
        return false;
    }

    public MyThreeWayBTreeNode sibling() { // 자식 노드인지 검사
        if (parent() != null) {
            return parent().leftChild() == this ? parent().rightChild() : parent().leftChild();
        }
        return null;
    }

    @Override
    public void setLeftChild(MyThreeWayBTreeNode leftChild) {
    }

    @Override
    public void removeChildren() {
        child = null;
    } // 자식 삭제


    @Override
    public void setRightChild(MyThreeWayBTreeNode rightChild) {
    }

    public MyThreeWayBTreeNode child() {
        return child;
    } // getter

    public void setChild(MyThreeWayBTreeNode child) {
        this.child = child;
    } // setter
}