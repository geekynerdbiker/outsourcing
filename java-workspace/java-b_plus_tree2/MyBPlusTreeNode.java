package org.dfpl.lecture.db.bplustree;

import java.util.List;

@SuppressWarnings("unused")
public class MyBPlusTreeNode {

    // Data Abstraction은 예시일 뿐 자유롭게 B+ Tree의 범주 안에서 어느정도 수정가능
    private MyBPlusTreeNode parent;
    private List<Integer> keyList;
    private List<MyBPlusTreeNode> children;


    public MyBPlusTreeNode getParent() {
        return parent;
    }

    public void setParent(MyBPlusTreeNode parent) {
        this.parent = parent;
    }

    public List<Integer> getKeyList() {
        return keyList;
    }

    public void setKeyList(List<Integer> keyList) {
        this.keyList = keyList;
    }


    public List<MyBPlusTreeNode> getChildren() {
        return children;
    }

    public void setChildren(List<MyBPlusTreeNode> children) {
        this.children = children;
    }

    public void setKey(int index, int key) { // 키 리스트에서 특정 키 값만 변경
        keyList.set(index, key);
    }
    
    public boolean isLeaf() { // 리프 노드인지 검사
        return getChildren() == null || getChildren().isEmpty();
    }
}