public class Main {

    public static void main(String[] args) {
        SList<Integer> s1 = new SList<Integer>();
        SList<Integer> s2 = new SList<Integer>();
        SList<Integer> s3 = new SList<Integer>();

        s1.insetFront(10);
        Node p = s1.head;
        s1.insertAfter(20, p);
        p = p.getNext();
        s1.insertAfter(30, p);
        p = p.getNext();
        s1.insertAfter(40, p);
        p = p.getNext();
        s1.insertAfter(50, p);

        System.out.print("Sorted List 1:\t");
        s1.print();

        s2.insetFront(15);
        p = s2.head;
        s2.insertAfter(18, p);
        p = p.getNext();
        s2.insertAfter(35, p);
        p = p.getNext();
        s2.insertAfter(37, p);
        p = p.getNext();
        s2.insertAfter(55, p);

        System.out.print("Sorted List 2:\t");
        s2.print();

        SList<Integer> mergedList = new SList<Integer>();
        mergedList.mergeLists(s1.head, s2.head);
        System.out.print("Merged List:\t");
        mergedList.print();
        System.out.println("--------------------\n");

        s3.insetFront(10);
        p = s3.head;
        s3.insertAfter(90, p);
        p = p.getNext();
        s3.insertAfter(15, p);
        p = p.getNext();
        s3.insertAfter(10, p);
        p = p.getNext();
        s3.insertAfter(35, p);
        p = p.getNext();
        s3.insertAfter(57, p);
        p = p.getNext();
        s3.insertAfter(50, p);
        p = p.getNext();
        s3.insertAfter(20, p);
        p = p.getNext();
        s3.insertAfter(17, p);
        p = p.getNext();
        s3.insertAfter(45, p);

        SList<Integer> l1 = new SList<Integer>();
        SList<Integer> l2 = new SList<Integer>();
        s3.splitList(s3.head, 20, l1, l2);

        System.out.print("Single List :\t");
        s3.print();
        System.out.println("k=20을 기준으로 두 개의 리스트로 분리:");
        System.out.print("List 1(<= 20):\t");
        l1.print();
        System.out.print("List 2(> 20):\t");
        l2.print();
    }
}
