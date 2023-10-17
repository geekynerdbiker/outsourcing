package org.dfpl.db.hash.m16013094;
// package 이름은 org.dfpl.db.hash.m학번 입니다. 
// 지키지 않을 시 반려합니다. 

import java.util.*;

public class MyHashSet<I extends Number> implements Set<Integer> {

    // 너무 어려운 학생은 LinkedList 등으로 작성하셔도 됩니다.
    // 최대 3점을 받을 수 있습니다.
    // 멤버 변수는 hashTable 이외의 것을 사용하지 않습니다. (예: size)
    private MyThreeWayBTree[] hashTable;
    // 예: private LinkedList<Integer>[] hashTable;

    public MyHashSet() {
        // 해시테이블 배열 크기는 3로 고정합니다.
        // hash function은 key를 3로 나눈 값이며,
        // 충돌시 3-way B-Tree에 저장됩니다.
        hashTable = new MyThreeWayBTree[3];
    }

    @Override
    public int size() { // 노드 갯수 반환
        int size = 0;

        for (MyThreeWayBTree t : hashTable) {
            if (t != null)
                size += t.size();
        }
        return size;
    }

    @Override
    public boolean isEmpty() { // 빈 노드인지 검사
        // TODO Auto-generated method stub
        return size() == 0;
    }

    @Override
    public boolean contains(Object o) { // 3개의 테이블에 대해서 원소가 있는지 검사
        // TODO Auto-generated method stub
        for (MyThreeWayBTree t : hashTable) {
            if (t == null)
                continue;
            if (t.contains((Integer) o))
                return true;
        }
        return false;
    }

    @Override
    public Iterator<Integer> iterator() { // 반복자
        // TODO Auto-generated method stub
        return new Iterator<Integer>() {
            private int pointer = -1;
            Iterator it0 = hashTable[0].iterator();
            Iterator it1 = hashTable[1].iterator();
            Iterator it2 = hashTable[2].iterator();
            List<Integer> list = new ArrayList<>();

            { // 인덱스 1, 0, 2 순서로 순회
                while (it1.hasNext())
                    list.add((Integer) it1.next());
                while (it0.hasNext())
                    list.add((Integer) it0.next());
                while (it2.hasNext())
                    list.add((Integer) it2.next());
            }

            @Override
            public boolean hasNext() {
                if (pointer < (list.size() - 1)) return true;
                return false;
            }

            @Override
            public Integer next() {
                pointer++;
                Integer element = null;

                try {
                    element = list.get(pointer);
                } catch (IndexOutOfBoundsException exception) {
                    throw new NoSuchElementException(exception.getMessage());
                }
                return element;
            }

            public void remove() {
                if (-1 < pointer && pointer < list.size()) {
                    MyHashSet.this.remove(list.get(pointer));
                    pointer--;
                    return;
                }
                throw new IllegalStateException();
            }
        };
    }

    @Override
    public Object[] toArray() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public <T> T[] toArray(T[] a) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public boolean add(Integer e) { // 3으로 나눈 나머지 해싱으로 노드 삽입
        // TODO Auto-generated method stub
        if (hashTable[e % 3] == null)
            hashTable[e % 3] = new MyThreeWayBTree();
        return hashTable[e % 3].add(e);
    }

    @Override
    public boolean remove(Object o) {
        // TODO Auto-generated method stub
        for (MyThreeWayBTree t : hashTable)
            t.remove(o);
        return false;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends Integer> c) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public void clear() {
        // TODO Auto-generated method stub

    }

}
