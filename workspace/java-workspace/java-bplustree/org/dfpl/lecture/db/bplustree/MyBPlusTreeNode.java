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

        if (myBPlusTreeNode.isLeaf) { // 리프 노드인 경우
            middleIndex = (m % 2 == 0) ? ((m - 1) / 2) + 1 : (m - 1) / 2; // m이 홀수일 때와 짝수 일 때 구분
            middleValue = myBPlusTreeNode.keyList.get(middleIndex);

            for (int j = middleIndex; j < myBPlusTreeNode.keyList.size(); j++) // 왼쪽 스플릿 노드를 위한 키값 복사
                newNode.keyList.add(myBPlusTreeNode.keyList.get(j));

            myBPlusTreeNode.keyList.subList(middleIndex, myBPlusTreeNode.keyList.size()).clear(); // 기존 노드의 왼쪽을 비움

            newNode.next = myBPlusTreeNode.next; // 노드 연결
            myBPlusTreeNode.next = newNode;
        } else { // 리프 노드가 아닌 경우
            middleIndex = (m - 1) / 2;
            middleValue = myBPlusTreeNode.keyList.get(middleIndex);

            for (int j = middleIndex + 1; j < myBPlusTreeNode.keyList.size(); j++) // 리프 노드일 때와 동일하게 복사
                newNode.keyList.add(myBPlusTreeNode.keyList.get(j));

            myBPlusTreeNode.keyList.subList(middleIndex, myBPlusTreeNode.keyList.size()).clear();

            for (int j = middleIndex + 1; j < myBPlusTreeNode.children.size(); j++) // 자식 데이터도 마찬가지로 복사
                newNode.children.add(myBPlusTreeNode.children.get(j));

            myBPlusTreeNode.children.subList(middleIndex + 1, myBPlusTreeNode.children.size()).clear(); // 기존 노드의 자식 비움
        }

        children.add(index + 1, newNode); // 자식에 새 노드 추가
        keyList.add(index, middleValue); // 키 리스트에 새 노드 추가
    }


}