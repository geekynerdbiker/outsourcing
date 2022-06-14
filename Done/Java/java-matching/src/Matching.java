import java.io.*;
import java.util.*;

public class Matching {
    public static AVLTree[] hashTable;
    private static LinkedList<String> stringList;

    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input.compareTo("QUIT") == 0)
                    break;

                command(input);
            } catch (IOException e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    private static void command(String input) throws IOException {
        // TODO : 아래 문장을 삭제하고 구현해라.

        String[] arr = input.split(" ", 2);

        if (arr[0].equals("<")) {inputData(arr[1]);}
        else if(arr[0].equals("@")) {printData(arr[1]);}
        else if(arr[0].equals("?")) {searchData(arr[1]);}
        else {throw new IOException();}
    }

    static void inputData(String content) throws IOException {
        hashTable = new AVLTree[100];
        stringList = new LinkedList<>();

        for (int i = 0; i <hashTable.length; i++) {
            hashTable[i] = new AVLTree();
        }

        try {
            File file = new File(content);
            BufferedReader br = new BufferedReader(new FileReader(file));

            String line;
            int k = 0;
            while ((line = br.readLine()) != null) {
                stringList.addLast(line);

                for (int i = 0; i < line.length() - 5; i++) {
                    String sub = line.substring(i, i+6);

                    Place p = new Place(k, i);

                    char[] inputArray = sub.toCharArray();
                    int sumAscii = 0;

                    for (int j = 0; j < inputArray.length; j++) {
                        sumAscii += inputArray[j];
                    }

                    hashTable[sumAscii % 100].insert(sub, p);
                }
                k++;
            }
            br.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    static void printData(String str) {
        String[] inputArray = str.split(" ");
        try {
            AVLNode node = hashTable[Integer.parseInt(inputArray[0])].getRoot();
            if (node.item == null)
                System.out.println("EMPTY");
            else {
                AVLTree.preOrderPrint(node, node);
                System.out.println();
            }
        } catch (Exception e) {
            System.out.println("EMPTY");
        }
    }

    static void searchData(String str) {
        String pattern = str;
        String searchingString = str.substring(0, 6);

        char[] inputArray = searchingString.toCharArray();
        int sumAscii = 0;

        for (int i = 0; i < inputArray.length; i++) {
            sumAscii += inputArray[i];
        }

        AVLNode node = hashTable[sumAscii % 100].search(searchingString);


        if (node == null)
            System.out.println("(0, 0)");
        else {
            LinkedList<Place> indexLinkedList = node.list;
            int cnt = 0;

            for (int k = 0; k < indexLinkedList.size(); k++) {

                String indexes = indexLinkedList.get(k).toString();
                String[] data = indexes.split(", ");
                int i = Integer.parseInt(data[0].split("\\(")[1]);
                int j = Integer.parseInt(data[1].split("\\)")[0]);

                String strings = stringList.get(i);

                if (j + pattern.length() > strings.length())
                    continue;

                String patternString = strings.substring(j, j + pattern.length());

                if (pattern.compareTo(patternString) == 0) {
                    if (cnt != 0)
                        System.out.print(" ");

                    System.out.print("(" + (i+1) + ", " + (j+1) + ")");
                    cnt++;
                }
            }
            if (cnt == 0)
                System.out.println("(0, 0)");
            else System.out.println();


        }
    }
}

class AVLTree<T extends Comparable<T>> {
    private AVLNode<T> root;
    public final static AVLNode NIL = new AVLNode(null, null, null, 0);

    public AVLTree() {
        root = NIL;
    }

    public AVLNode getRoot() {
        return root;
    }

    // 검색
    public AVLNode<T> search(T x) {
        return searchItem(root, x);
    }

    private AVLNode searchItem(AVLNode<T> tNode, T x) {
        if (tNode == NIL) return NIL;
        else if (x.compareTo(tNode.item) == 0) return tNode;
        else if (x.compareTo(tNode.item) < 0) {
            return searchItem(tNode.left, x);
        } else return searchItem(tNode.right, x);
    }

    // 삽입
    public void insert(T x, Place p) {
        root = insertItem(root, x, p);
    }

    // 같은경우도 체크해서 추가해주자
    private AVLNode insertItem(AVLNode<T> tNode, T x, Place p) {
        int type;
        if (tNode == NIL) {
            tNode = new AVLNode(x, p);
            return tNode;
        }
        if (x.compareTo(tNode.item) == 0) {
            tNode.list.add(p);
        } else if (x.compareTo(tNode.item) < 0) {
            tNode.left = insertItem(tNode.left, x, p);
            tNode.height = 1 + Math.max(tNode.right.height, tNode.left.height);
            type = needBalance(tNode);
            if (type != NO_NEED) {
                tNode = balanceAVL(tNode, type);
            }
        } else if (x.compareTo(tNode.item) > 0) {
            tNode.right = insertItem(tNode.right, x, p);
            tNode.height = 1 + Math.max(tNode.right.height, tNode.left.height);
            type = needBalance(tNode);
            if (type != NO_NEED) {
                tNode = balanceAVL(tNode, type);
            }
        }
        return tNode;
    }


    private AVLNode balanceAVL(AVLNode tNode, int type) {
        AVLNode returnNode = NIL;
        switch (type) {
            case LL:
                returnNode = rightRotate(tNode);
                break;
            case LR:
                tNode.left = leftRotate(tNode.left);
                returnNode = rightRotate(tNode);
                break;
            case RR:
                returnNode = leftRotate(tNode);
                break;
            case RL:
                tNode.right = rightRotate(tNode.right);
                returnNode = leftRotate(tNode);
                break;
            default:
                System.out.println("Impossible type! Should be one of LL, LR, RR, RL");
                break;
        }

        return returnNode;
    }

    private AVLNode leftRotate(AVLNode t) {
        AVLNode RChild = t.right;
        if (RChild == NIL) {
            System.out.println("left rotate - ERROR!");
        }
        AVLNode RLChild = RChild.left;
        RChild.left = t;
        t.right = RLChild;
        t.height = 1 + Math.max(t.left.height, t.right.height);
        RChild.height = 1 + Math.max(RChild.left.height, RChild.right.height);
        return RChild;
    }

    private AVLNode rightRotate(AVLNode t) {
        AVLNode LChild = t.left;
        if (LChild == NIL) {
            System.out.println("right rotate - ERROR!");
        }
        AVLNode LRChild = LChild.right;
        LChild.right = t;
        t.left = LRChild;
        t.height = 1 + Math.max(t.left.height, t.right.height);
        LChild.height = 1 + Math.max(LChild.left.height, LChild.right.height);
        return LChild;
    }

    // Balancing 작업
    private final int LL = 1, LR = 2, RR = 3, RL = 4, NO_NEED = 0, ILLEGAL = -1;

    private int needBalance(AVLNode t) {
        int type = ILLEGAL;
        if (t.left.height + 2 <= t.right.height) {
            if ((t.right.left.height) <= t.right.right.height) {
                type = RR;
            } else
                type = RL;
        } else if ((t.left.height) >= t.right.height + 2) {
            if ((t.left.left.height) >= t.left.right.height) {
                type = LL;
            } else
                type = LR;
        } else
            type = NO_NEED;
        return type;
    }

    // 전위순회 출력
    public static void preOrderPrint(AVLNode node, AVLNode root) {
        if (node == NIL) {
            return;
        }
        if (node == root) System.out.print(node.item);
        else System.out.print(" " + node.item);
        preOrderPrint(node.left, root);
        preOrderPrint(node.right, root);
    }
}

class AVLNode<T extends Comparable<T>> {
    public T item;
    public AVLNode left, right;
    public int height;
    public LinkedList<Place> list = new LinkedList<>();

    public AVLNode(T newItem) {
        item = newItem;
        left = AVLTree.NIL;
        right = AVLTree.NIL;
        height = 1;
    }

    public AVLNode(T newItem, Place p) {
        item = newItem;
        left = AVLTree.NIL;
        right = AVLTree.NIL;
        height = 1;
        list.add(p);
    }

    public AVLNode(T sub, AVLNode leftChild, AVLNode rightChild) {
        item = sub;
        this.left = leftChild;
        this.right = rightChild;
        height = 1;
    }

    public AVLNode(T newItem, AVLNode left, AVLNode right, int h) {
        item = newItem;
        this.left = left;
        this.right = right;
        this.height = h;
    }
}

class Place {
    int line;
    int start;

    public Place() {
        this.line = 0;
        this.start = 0;
    }

    public Place(int line, int start) {
        this.line = line;
        this.start = start;
    }

    public String toString() {
        return "(" + this.line + ", " + this.start + ")";
    }
}
//
//import java.io.*;
//import java.lang.Math;
//import java.lang.StringBuilder;
//
//public class Matching {
//    private static AVLTree[] hashTable;
//    private static CustomLinkedList textStrings;
//
//    public static void main(String args[]) {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//
//        while (true) {
//            try {
//                String input = br.readLine();
//                if (input.compareTo("QUIT") == 0)
//                    break;
//
//                command(input);
//            } catch (IOException e) {
//                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
//            }
//        }
//    }
//
//    private static void command(String input) {
//        if (input.charAt(0) == '<') {
//            // operator가 < 인 경우
//
//            hashTable = new AVLTree[100]; // 파일을 읽을때마다 hashTable 초기화.
//            textStrings = new CustomLinkedList(); // 파일을 읽을때마다 LinkedList 초기화.
//            String[] inputArray = input.split(" ");
//
//            // 먼저 hashTable의 각 slot의 AVLTree들을 생성해준다.
//            for (int i = 0; i < hashTable.length; i++) {
//                hashTable[i] = new AVLTree();
//            }
//
//            try {
//                // FileReader를 통해서 txt 파일을 읽어들인다.
//                // 파일이 없으면 exception 처리
//                BufferedReader reader = new BufferedReader(new FileReader(inputArray[1]));
//                String string; // string은 한줄 단위로 구분된다.
//                int i = 0;
//
//                while ((string = reader.readLine()) != null) {
//                    // 줄 단위로 string을 읽어낸다.
//                    // 읽어낸 string은 textStrings LinkedList에 저장한다.
//                    textStrings.addLast(string);
//
//                    for (int j = 0; j < string.length() - 5; j++) {
//                        String substring = string.substring(j, j + 6);
//
//                        int address = hashFunction(substring);
//
//                        hashTable[address].insert(substring, i, j);
//                    }
//
//                    i++;
//                }
//
//                reader.close();
//            } catch (IOException e) {
//                System.err.println(e); // FileReading에 에러가 있으면 에러메시지 출력
//                System.exit(1);
//            }
//
//        } else if (input.charAt(0) == '@') {
//            // operator가 @ 인 경우
//            // input으로 부터 hash 주소값을 알아내서 AVLTree preorder로 출력
//
//            String[] inputArray = input.split(" ");
//            int address = Integer.parseInt(inputArray[1]);
//
//            hashTable[address].print();
//
//        } else if (input.charAt(0) == '?') {
//            // operator가 ? 인 경우
//            // input으로 부터 앞 6자리 String을 추출해서 Hash, AVLTree에서 검색한다.
//
//            String patternString = input.substring(2);
//            String searchingString = input.substring(2, 8);
//            int address = hashFunction(searchingString);
//            AVLTreeNode node = hashTable[address].search(searchingString);
//
//            if (node == null)
//                // 검색 실패인 경우.
//                System.out.println("(0, 0)");
//            else {
//                // 해당 노드를 찾은 경우.
//                // 해당 노드로 부터 index i, j를 모두 꺼내온다.
//                CustomLinkedList indexLinkedList = node.getLinkedList();
//                int cnt = 0; // 찾은 패턴의 개수를 세준다.
//
//                for (int k = 0; k < indexLinkedList.size(); k++) {
//
//                    String indexes = indexLinkedList.get(k);
//                    int i = Integer.parseInt(indexes.split(", ")[0]);
//                    int j = Integer.parseInt(indexes.split(", ")[1]);
//
//                    // i, j를 꺼내고 나면, textFile을 줄단위로 저장한 LinkedList에서 patterString을 찾아 비교해본다.
//                    // 이런 과정을 거치는 이유는, hashing은 6개 단위로 하는데 patternString은 그것보다 길 수 있기 때문이다.
//                    String stringFromTXT = textStrings.get(i);
//
//                    // 그 이전에 j를 검사해준다. 해쉬는 6자 단위로 했는데 여기선 6자 이상의 patternString을 검사한다.
//                    if (j + patternString.length() > stringFromTXT.length())
//                        continue;
//
//                    String patternStringFromTXT = stringFromTXT.substring(j, j + patternString.length());
//
//                    if (patternString.compareTo(patternStringFromTXT) == 0) {
//                        // 찾고자 하는 patternString과 textFile에 있는 patternString이 실제로 동일한 경우
//                        // index를 출력해준다.
//                        if (cnt != 0)
//                            System.out.print(" ");
//
//                        System.out.print("(" + (i + 1) + ", " + (j + 1) + ")");
//                        cnt++;
//                    }
//                }
//
//                System.out.println();
//
//                if (cnt == 0)
//                    System.out.println("(0, 0)");
//            }
//        }
//    }
//
//    private static int hashFunction(String input) {
//        char[] inputArray = input.toCharArray();
//        int sumAscii = 0;
//
//        for (int i = 0; i < input.length(); i++) {
//            sumAscii += inputArray[i];
//        }
//
//        return sumAscii % 100;
//    }
//}
//
//class AVLTreeNode {
//    private String subString; // AVLTreeNode 에 저장되는 아이템은 길이 6의 subString
//    private CustomLinkedList linkedList; // AVLTreeNode는 LinkedList를 item으로 갖는다.
//    private AVLTreeNode leftChild; // 왼쪽 Child
//    private AVLTreeNode rightChild; // 오른쪽 Child
//    private int height; // 오른쪽 subTree의 Height
//
//    public AVLTreeNode(String subString) {
//        // constructor w subString
//
//        this.subString = subString;
//        linkedList = new CustomLinkedList();
//        leftChild = null;
//        rightChild = null;
//        height = 1;
//    }
//
//    // 이하 getter 및 setter
//    public String getSubString() {
//        return subString;
//    }
//
//    public void setSubString(String subString) {
//        this.subString = subString;
//    }
//
//    public AVLTreeNode getLeftChild() {
//        return leftChild;
//    }
//
//    public void setLeftChild(AVLTreeNode leftChild) {
//        this.leftChild = leftChild;
//    }
//
//    public AVLTreeNode getRightChild() {
//        return rightChild;
//    }
//
//    public void setRightChild(AVLTreeNode rightChild) {
//        this.rightChild = rightChild;
//    }
//
//    public int getHeight() {
//        return height;
//    }
//
//    public void setHeight(int height) {
//        this.height = height;
//    }
//
//    public CustomLinkedList getLinkedList() {
//        return linkedList;
//    }
//
//    public void addSubStringIndex(int i, int j) {
//        StringBuilder sb = new StringBuilder();
//        sb.append(i);
//        sb.append(", ");
//        sb.append(j);
//        linkedList.addLast(sb.toString());
//    }
//}
//
//class AVLTree {
//    private AVLTreeNode root;
//
//    public AVLTree() {
//        // constructor
//
//        root = null;
//    }
//
//    public boolean isEmpty() {
//        // AVLTree가 비어있는가
//        return root == null;
//    }
//
//    private int subTreeHeight(AVLTreeNode node) {
//        // subTree의 Height를 리턴
//        // node가 null 이면 0 리턴
//        if (node == null) return 0;
//
//        return node.getHeight();
//    }
//
//    public void insert(String subString, int i, int j) {
//        // AVLTree에 subString을 갖는 노드를 추가해준다.
//        root = insert(subString, root, i, j);
//    }
//
//    private AVLTreeNode insert(String newSubString, AVLTreeNode node, int i, int j) {
//        // subString 을 가진 node를 추가
//        if (node == null) {
//            // 만약 node가 null이면 (leaf거나 root가 empty tree) subString을 item으로 갖는 노드를 생성해준다.
//            node = new AVLTreeNode(newSubString);
//            node.addSubStringIndex(i, j);
//        } else {
//            // 만약 node가 null이 아닌경우
//            // 새로 추가할 노드의 subString과 현재의 subString을 비교.
//
//            if (newSubString.compareTo(node.getSubString()) > 0) {
//                // newSubString이 node의 subString보다 사전에서 뒤에 온다.
//                // rightNode에 recursive하게 추가 (leaf 노드까지 내려감)
//
//                node.setRightChild(insert(newSubString, node.getRightChild(), i, j));
//
//                if (subTreeHeight(node.getRightChild()) - subTreeHeight(node.getLeftChild()) == 2) {
//                    // insert 한 뒤 rightSubTree 높이가 leftSubTree 높이보다 2(이상) 큰 경우
//                    if (newSubString.compareTo(node.getRightChild().getSubString()) > 0)
//                        // insert 된 노드가 rightChild의 오른쪽 서브트리에 붙어있으면 single Rotation
//                        node = rotateWithRightChild(node);
//                    else
//                        // insert 된 노드가 rightChild의 왼쪽 서브트리에 붙어있으면 double Rotation
//                        node = doubleRotateWithRightChild(node);
//                }
//            } else if (newSubString.compareTo(node.getSubString()) < 0) {
//                // newSubString이 node의 subString보다 사전에서 앞에 온다.
//                // leftNode에 recursive하게 추가 (leaf 노드까지 내려감)
//
//                node.setLeftChild(insert(newSubString, node.getLeftChild(), i, j));
//
//                if (subTreeHeight(node.getLeftChild()) - subTreeHeight(node.getRightChild()) == 2) {
//                    // insert 한 뒤 leftSubTree 높이가 rightSubTree 높이보다 2(이상) 큰 경우
//                    if (newSubString.compareTo(node.getLeftChild().getSubString()) < 0)
//                        // insert 된 노드가 leftChild의 왼쪽 서브트리에 붙어있으면 single Rotation
//                        node = rotateWithLeftChild(node);
//                    else
//                        // insert 된 노드가 leftChild의 오른쪽 서브트리에 붙어있으면 double Rotation
//                        node = doubleRotateWithLeftChild(node);
//                }
//            } else {
//                // newSubString이 node의 subString과 같은 경우.
//                // node 추가하지 않고 해당 node의 linkedList에 subString index 추가.
//                node.addSubStringIndex(i, j);
//            }
//        }
//
//        // 새로운 node를 insertion한 뒤에 높이 값을 재설정. (기존의 높이보다 1 커졌다.)
//        node.setHeight(Math.max(subTreeHeight(node.getLeftChild()), subTreeHeight(node.getRightChild())) + 1);
//
//        return node;
//    }
//
//    private AVLTreeNode rotateWithRightChild(AVLTreeNode node) {
//        // 오른쪽 child를 중심으로 왼쪽으로 rotate
//
//        AVLTreeNode newParentNode = node.getRightChild();
//        node.setRightChild(newParentNode.getLeftChild());
//        newParentNode.setLeftChild(node);
//
//        node.setHeight(Math.max(subTreeHeight(node.getLeftChild()), subTreeHeight(node.getRightChild())) + 1);
//        newParentNode.setHeight(Math.max(subTreeHeight(newParentNode.getRightChild()), subTreeHeight(node)) + 1);
//
//        return newParentNode;
//    }
//
//    private AVLTreeNode doubleRotateWithRightChild(AVLTreeNode node) {
//        // 오른쪽 child를 중심으로 dubleRotate
//        // 오른쪽 child를 rotateWithLeftChild 해주고 node를 rotateWithRightChild 한다.
//        node.setRightChild(rotateWithLeftChild(node.getRightChild()));
//
//        return rotateWithRightChild(node);
//    }
//
//    private AVLTreeNode rotateWithLeftChild(AVLTreeNode node) {
//        // 왼쪽 child를 중심으로 왼쪽으로 rotate
//
//        AVLTreeNode newParentNode = node.getLeftChild();
//        node.setLeftChild(newParentNode.getRightChild());
//        newParentNode.setRightChild(node);
//
//        node.setHeight(Math.max(subTreeHeight(node.getRightChild()), subTreeHeight(node.getLeftChild())) + 1);
//        newParentNode.setHeight(Math.max(subTreeHeight(newParentNode.getLeftChild()), subTreeHeight(node)) + 1);
//
//        return newParentNode;
//    }
//
//    private AVLTreeNode doubleRotateWithLeftChild(AVLTreeNode node) {
//        // 왼쪽 child를 중심으로 dubleRotate
//        // 왼쪽 child를 rotateWithRightChild 해주고 node를 rotateWithLeftChild 한다.
//        node.setLeftChild(rotateWithRightChild(node.getLeftChild()));
//
//        return rotateWithLeftChild(node);
//    }
//
//    public void print() {
//        // preorder로 모든 노드를 출력
//        if (root == null) System.out.println("EMPTY");
//        else {
//            preorder(root);
//            System.out.println();
//        }
//    }
//
//    private void preorder(AVLTreeNode node) {
//        if (node != null) {
//            // node가 null 이 아니면 recursive하게 node 데이터 출력
//            System.out.print(node.getSubString() + " ");
//            preorder(node.getLeftChild());
//            preorder(node.getRightChild());
//        }
//    }
//
//    public AVLTreeNode search(String patternString) {
//        // patternString과 같은 node를 찾는다.
//        return search(patternString, root);
//    }
//
//    private AVLTreeNode search(String patternString, AVLTreeNode node) {
//        // Binary Search Tree의 검색 알고리즘과 유사
//        if (node == null)
//            // 검색실패
//            return null;
//        else if (patternString.compareTo(node.getSubString()) > 0)
//            // patternString이 현재 node의 subString 보다 사전상 뒤에 옴.
//            return search(patternString, node.getRightChild());
//        else if (patternString.compareTo(node.getSubString()) < 0)
//            // patternString이 현재 node의 subString 보다 사전상 앞에 옴.
//            return search(patternString, node.getLeftChild());
//        else
//            // patternString이 현재 node의 subString과 같음.
//            return node;
//    }
//}
//
//class LinkedListNode {
//    private String item;
//    private LinkedListNode next;
//
//    public LinkedListNode() {
//        // dummy constructor
//
//        this.item = null;
//        this.next = null;
//    }
//
//    public LinkedListNode(String item) {
//        // constructor
//
//        this.item = item;
//        this.next = null;
//    }
//
//    // getters & setters
//    public String getItem() {
//        return item;
//    }
//
//    public void setItem(String item) {
//        this.item = item;
//    }
//
//    public LinkedListNode getNext() {
//        return next;
//    }
//
//    public void setNext(LinkedListNode next) {
//        this.next = next;
//    }
//}
//
//class CustomLinkedList {
//    private int size;
//    private LinkedListNode head;
//
//    public CustomLinkedList() {
//        // constructor
//
//        size = 0;
//        head = null;
//    }
//
//    public void addLast(String item) {
//        // LinkedList의 맨 마지막에 item 추가
//        if (size == 0) {
//            LinkedListNode newNode = new LinkedListNode(item);
//            head = newNode;
//        } else {
//            LinkedListNode newNode = new LinkedListNode(item);
//            getNode(size - 1).setNext(newNode);
//        }
//
//        size++;
//    }
//
//    private LinkedListNode getNode(int index) {
//        LinkedListNode curr = head;
//
//        for (int i = 0; i < index; i++) {
//            curr = curr.getNext();
//        }
//
//        return curr;
//    }
//
//    public String get(int index) {
//        return getNode(index).getItem();
//    }
//
//    public int size() {
//        return size;
//    }
//}