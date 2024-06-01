package org.dfpl.lecture.db.bplustree;

import java.util.ArrayList;
import java.util.List;

public class MyBPlusTreeNode {
    // Data Abstraction은 예시일 뿐 자유롭게 B+ Tree의 범주 안에서 어느정도 수정가능
    private List<Integer> keyList;
    private List<MyBPlusTreeNode> children;
    private boolean isLeaf;
    private int m;
    private MyBPlusTreeNode next;

    public List<Integer> getKeyList() {
        return keyList;
    }

    public List<MyBPlusTreeNode> getChildren() {
        return children;
    }

    public boolean isLeaf() {
        return isLeaf;
    }

    public MyBPlusTreeNode getNext() {
        return next;
    }


    public MyBPlusTreeNode(boolean isLeaf, int m) {
        this.keyList = new ArrayList<>();
        this.children = new ArrayList<>();
        this.next = null;
        this.isLeaf = isLeaf;
        this.m = m;
    }

    public void split(MyBPlusTreeNode myBPlusTreeNode, int index) {
        MyBPlusTreeNode newNode = new MyBPlusTreeNode(myBPlusTreeNode.isLeaf, m);

        int middleIndex;
        int middleValue;

        if (myBPlusTreeNode.isLeaf) {
            middleIndex = (m % 2 == 0) ? ((m - 1) / 2) + 1 : (m - 1) / 2;
            middleValue = myBPlusTreeNode.keyList.get(middleIndex);

            for (int j = middleIndex; j < myBPlusTreeNode.keyList.size(); j++)
                newNode.keyList.add(myBPlusTreeNode.keyList.get(j));

            myBPlusTreeNode.keyList.subList(middleIndex, myBPlusTreeNode.keyList.size()).clear();

            newNode.next = myBPlusTreeNode.next;
            myBPlusTreeNode.next = newNode;
        } else {
            middleIndex = (m - 1) / 2;
            middleValue = myBPlusTreeNode.keyList.get(middleIndex);

            for (int j = middleIndex + 1; j < myBPlusTreeNode.keyList.size(); j++)
                newNode.keyList.add(myBPlusTreeNode.keyList.get(j));

            myBPlusTreeNode.keyList.subList(middleIndex, myBPlusTreeNode.keyList.size()).clear();

            for (int j = middleIndex + 1; j < myBPlusTreeNode.children.size(); j++)
                newNode.children.add(myBPlusTreeNode.children.get(j));

            myBPlusTreeNode.children.subList(middleIndex + 1, myBPlusTreeNode.children.size()).clear();
        }

        children.add(index + 1, newNode);
        keyList.add(index, middleValue);
    }


}