// 이진 탐색 트리 클래스
public class BST {
    protected Node root;

    public BST() {
        root = null;
    }

    // 노드 삽입 함수
    public boolean insert(Node n) {
        // 루트가 없으면
        if (root == null) {
            root = n;
            return true;
        } else {
            // 탐색용 노드
            Node p = root;

            // 루트부터 탐색
            while (p != null) {
                // 삽입 할 노드의 값이 현재 노드보다 작을 때
                if (n.value < p.value) {
                    // 왼쪽 자식이 없으면 삽입
                    if (p.left == null) {
                        p.left = n;
                        return true;
                    } else
                        // 왼쪽으로 이동
                        p = p.left;
                    // 삽입 할 노드의 값이 현재 노드보다 클 때
                } else if (n.value > p.value) {
                    // 오른쪽 자식이 없으면 삽입
                    if (p.right == null) {
                        p.right = n;
                        return true;
                    } else
                        // 오른쪽으로 이동
                        p = p.right;
                }
            }
        }
        return false;
    }

    // 노드 검색 함수
    public Node search(int value) {
        // 탐색용 노드
        Node p = root;

        // 루트가 없으면 null 반환
        if (root == null)
            return null;
        else {
            while (p != null) {
                // 현재 노드와 찾으려는 값이 같으면 현재 노드 반환
                if (p.value == value)
                    return p;
                else {
                    // 작으면 왼쪽, 크면 오른쪽으로 이동
                    if (value < p.value)
                        p = p.left;
                    else
                        p = p.right;
                }
            }
        }
        return null;
    }

    // 노드 삭제 함수
    public Node delete(int value) {
        // 탐색용 노드의 부모 노드, 탐색용 노드
        Node parent = null;
        Node p = root;

        // 노드 탐색
        while (p != null && p.value != value) {
            parent = p;
            if (value < p.value) {
                p = p.left;
            } else {
                p = p.right;
            }
        }

        // 존재하지 않으면 null 반환
        if (p == null)
            return null;

        // 자식이 없는 노드일 때
        if (p.left == null && p.right == null) {
            // 현재 노드가 루트가 아니면
            if (p != root) {
                // 부모의 왼쪽 자식이 현재 노드이면 왼쪽 삭제
                if (parent.left == p) {
                    parent.left = null;
                    // 부모의 오른쪽 자식이 현재 노드이면 오른쪽 삭제
                } else {
                    parent.right = null;
                }
                // 루트이면 루트 삭제
            } else {
                root = null;
            }
            // 양쪽 모두 자식이 있을 때
        } else if (p.left != null && p.right != null) {
            // 오른쪽 자식의 최솟값을 찾음
            Node temp = minimum(p.right);
            int tempValue = temp.value;

            // 최솟값 노드를 삭제하고 현재 노드를 최솟값 노드로 변경
            delete(temp.value);
            p.value = tempValue;
            // 한쪽만 자식이 있을 때
        } else {
            // 자식 노드
            Node child = (p.left != null) ? p.left : p.right;

            // 현재 노드가 루트가 아니면
            if (p != root) {
                // 부모의 왼쪽 자식이면 왼쪽에 자식노드 삽입
                if (p == parent.left) {
                    parent.left = child;
                    // 부모의 오른쪽 자식이면 오른쪽에 자식노드 삽입
                } else {
                    parent.right = child;
                }
                // 루트이면 루트에 자식노드 삽입
            } else {
                root = child;
            }
        }

        return root;
    }

    // 최솟값 찾는 함수
    public Node minimum(Node p) {
        // 맨 왼쪽으로 이동
        while (p.left != null)
            p = p.left;

        return p;
    }

    // 최댓값 찾는 함수
    public Node maximum(Node p) {
        // 맨 오른쪽으로 이동
        while (p.right != null)
            p = p.right;

        return p;
    }

    // 전위 순회
    public void inorder(Node p) {
        // 현재 노드가 null 이면 종료
        if (p == null)
            return;

        // 왼쪽 노드 전위 순회
        inorder(p.left);
        // 현재 노드 출력
        System.out.print(p.value + " ");
        // 오른쪽 노드 순회
        inorder(p.right);
    }

    // 루트 반환 함수
    public Node getRoot() {
        return root;
    }

    // successor 찾는 함수
    public Node successor(Node n) {
        // 노드가 없으면 null 반환
        if (n == null)
            return null;

        // 오른쪽 자식이 없으면 현재 노드 반환
        if (n.right == null) {
            return n;
        }

        // 탐색용 노드 (현재의 오른쪽 노드, 부모 노드)
        Node successor = n.right;
        Node parent = n;

        // 맨 왼쪽으로 이동
        while (successor.left != null) {
            parent = successor;
            successor = successor.left;
        }

        return successor;
    }

    // predecessor 찾는 함수
    public Node predecessor(Node n) {
        // 노드가 없으면 null 반환
        if (n == null)
            return null;

        // 왼쪽 자식이 없으면 현재 노드 반환
        if (n.left == null) {
            return n;
        }

        // 탐색용 노드 (현재의 왼쪽 노드, 부모 노드)
        Node predecessor = n.left;
        Node parent = n;

        // 맨 오른쪽으로 이동
        while (predecessor.right != null) {
            parent = predecessor;
            predecessor = predecessor.right;
        }

        return predecessor;
    }
}