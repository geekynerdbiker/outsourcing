import java.util.NoSuchElementException;

public class SList<E extends Comparable<E>> {

    protected Node head;
    private int size;

    public SList() {
        head = null;
        size = 0;
    }

    public int search(E target) {
        Node p = head;
        for (int k = 0; k < size; k++) {
            if (target == p.getItem()) return k;
            p = p.getNext();
        }
        return -1;
    }

    public void insetFront(E newItem) {
        head = new Node(newItem, head);
        size++; // 강의자료에서 없는 부분인데 제가 임의로 수정했습니다. 노드를 삽입하고 사이즈 증가
    }

    public void insertAfter(E newItem, Node p) {
        p.setNext(new Node(newItem, p.getNext()));
        size++;
    }

    public void deleteFront() {
        if (size == 0) throw new NoSuchElementException();
        head = head.getNext();
        size--;
    }

    public void deleteAfter(Node p) {
        if (p == null) throw new NoSuchElementException();
        Node t = p.getNext();
        p.setNext(t.getNext());
        t.setNext(null);
        size--;
    }

    public void print() {
        Node p = head;

        for (int i = 0; i < size; i++) {
            System.out.print(p.getItem() + "\t");
            p = p.getNext();
        }
        System.out.println();
    }

    public int size() {
        return size;
    }

    public void mergeLists(Node<Integer> p1, Node<Integer> p2) {
        SList<Integer> merged = new SList<Integer>(); // 합칠 리스트 생성
        Node p = null; // 위에서 만든 리스트를 순회할 노드 선언

        while (p1 != null && p2 != null) { // 두 리스트 중 하나라도 탐색을 마치면 종료
            if (merged.size() == 0) { // 처음 리스트가 비어있을 때
                if (p1.getItem() < p2.getItem()) { // 두 리스트의 헤드부터 원소 대소 비교, p1이 작을 때
                    merged.insetFront(p1.getItem()); // 처음이므로 맨 앞에 삽입
                    p1 = p1.getNext(); // 다음 노드를 가리키도록 이동
                } else {
                    merged.insetFront(p2.getItem()); // p2가 작을 때
                    p2 = p2.getNext(); // 다음 노드를 가리키도록 이동
                }
                p = merged.head; // 노드가 하나 추가 되었으므로 헤드를 가리키도록 설정
            } else { // merged 리스트가 비어있지 않을 때 (처음 제외 나머지 모든 경우)
                if (p1.getItem() < p2.getItem()) { // p1이 작을 때
                    merged.insertAfter(p1.getItem(), p); // p 뒤에 노드 삽입. 첫 실행 일 경우에, 위에서 빈 리스트에 하나를 추가하고 헤드를 가리키므로 헤드 뒤에 삽입.
                    p1 = p1.getNext(); // 다음 노드를 가리키도록 이동
                } else {
                    merged.insertAfter(p2.getItem(), p);// p 뒤에 노드 삽입.
                    p2 = p2.getNext(); // 다음 노드를 가리키도록 이동
                }
                p = p.getNext(); // 노드가 하나 추가 되었으므로 추가된 노드를 가리키도록 설정
            }
        }

        // while 문이 끝나면 두 리스트 중 하나는 탐색 완료
        if (p1 == null) { // 탐색을 완료하지 못한 리스트가 p1 일때, ex) p1: null(탐색 끝) / p2: 1, 2
            while (p2 != null) { // p2의 탐색을 완료할때 까지
                merged.insertAfter(p2.getItem(), p); // p 다음에 노드 추가
                p2 = p2.getNext(); // 다음 노드로 이동
            }
        } else if (p2 == null) { // 탐색을 완료하지 못한 리스트가 p2 일때,
            while (p1 != null) { // p1의 탐색을 완료할때 까지
                merged.insertAfter(p1.getItem(), p);  // p 다음에 노드 추가
                p1 = p1.getNext();  // 다음 노드로 이동
            }
        }
        head = merged.head; // 메소드를 호출한 리스트의 head가 새로 생성한 merged의 head를 가리키도록 설정
        size = merged.size; // 메소드를 호출한 리스트의 size 새로 생성한 merged의 size가 되도록 설정
    }

    public void splitList(Node p, int k, SList l1, SList l2) {
        Node<Integer> q = p; // 탐색할 리스트의 헤드노드
        Node pl1 = null, pl2 = null; // 쪼개질 두 리스트의 위치를 가르킬 노드 각각 생성

        while (q != null) { // 탐색할 리스트가 null이 아닐때. 즉 빈 리스트가 아니거나 탐색을 마치기 전까지 반복
            if (q.getItem() > k) { // k보다 원소가 큰 경우
                if (pl2 == null) { // 쪼갤 리스트의 크기가 0일 때
                    l2.insetFront(q.getItem()); // 리스트의 처음에 노드 삽입
                    pl2 = l2.head; // 빈 리스트에 노드가 삽입되었으므로 이 리스트의 head는 null이 아니기에 헤드를 가리킴
                } else {
                    l2.insertAfter(q.getItem(), pl2); // 리스트가 비어있지 않으므로 pl2 뒤에 삽입 (위 함수와 동일한 구조)
                    pl2 = pl2.getNext(); // 다음 원소를 가리키도록 이동
                }
            } else {
                if (pl1 == null) { // 쪼갤 리스트의 크기가 0일 때
                    l1.insetFront(q.getItem()); // 리스트의 처음에 노드 삽입
                    pl1 = l1.head; // 빈 리스트에 노드가 삽입되었으므로 이 리스트의 head는 null이 아니기에 헤드를 가리킴
                } else {
                    l1.insertAfter(q.getItem(), pl1); // 리스트가 비어있지 않으므로 pl2 뒤에 삽입 (위 함수와 동일한 구조)
                    pl1 = pl1.getNext(); // 다음 원소를 가리키도록 이동
                }
            }
            q = q.getNext(); // 탐색할 리스트의 다음 노드를 가리키도록 함.
        }
    }
}
