// 테스트용 메인 클래스
public class Main {
    public static void main(String[] args) {
        // 트리 생성
        BST tree = new BST();

        // 값 삽입
        tree.insert(new Node(15));
        tree.insert(new Node(25));
        tree.insert(new Node(5));
        tree.insert(new Node(45));
        tree.insert(new Node(51));
        tree.insert(new Node(29));

        // 전위 순회 수행
        System.out.print("Inorder: ");
        tree.inorder(tree.getRoot());
        System.out.println();

        // 노드 삭제
        tree.delete(16);
        tree.delete(25);
        tree.delete(45);

        // 삭제 후 전위 순회 재출력
        System.out.print("Inorder: ");
        tree.inorder(tree.getRoot());
        System.out.println();

        // root 기준 최대 최솟값 출력
        System.out.println("Maximum: " + tree.maximum(tree.getRoot()).value);
        System.out.println("Minimum: " + tree.minimum(tree.getRoot()).value);

        // 29 기준 successor predecessor 출력
        System.out.println("Successor of 29: "+tree.successor(tree.search(29)).value);
        System.out.println("Predecessor of 29: "+tree.predecessor(tree.search(29)).value);
    }
}
