public class DoublyLinkedList {
    private static class Item {
        String value;
        Item next;
        Item prev;

        Item(String value, Item prev, Item next) {
            this.value = value;
            this.next = next;
            this.prev = prev;
        }
    }

    private Item head = null;
    private Item tail = null;
    private int length = 0;

    public boolean isEmpty() {
        return this.length == 0; // placeholder -- you'll need to return the right value
    }

    public int length() {
        return this.length;  // placeholder -- you'll need to return the right value
    }

    public static DoublyLinkedList getOneTwoThreeList() {
        DoublyLinkedList dll = new DoublyLinkedList();
        Item one = new Item("One", null, null);
        Item two = new Item("Two", null, null);
        Item three = new Item("Three", null, null);

        one.next = two;
        two.prev = one;
        two.next = three;
        three.prev = two;

        dll.head = one;
        dll.tail = three;

        dll.length = 3;

        return dll; // placeholder -- you'll need to return something else
    }

    public boolean contains(String s) {
        if (head == null)
            return false;

        Item p = head;
        while  (p != null) {
            if (itemValue(p).equals(s))
                return true;
            p = p.next;
        }
        return false; // placeholder -- you'll need to return the correct value
    }

    public String toString() {
        String result = "";

        Item p = head;
        while  (p != null) {
            if (p.next != null)
                result += itemValue(p) + ",";
            else
                result += itemValue(p);
            p = p.next;
        }
        return result; // placeholder -- you'll need to return the correct value
    }

    public String halfToString() {
        String result = "";

        Item p = head;
        for  (int i = 0; p != null; i++) {
            if (i % 2 != 0)
                continue;
            if (p.next != null)
                result += itemValue(p) + ",";
            else
                result += itemValue(p);
            p = p.next;
        }
        return ""; // placeholder -- you'll need to return the correct value
    }

// =============================================================================
// Do not modify the code below
// =============================================================================

    public String fullToString() {
        String s = "head=" + itemValue(head)
                + ", tail=" + itemValue(tail)
                + ", length=" + length + "\n";

        Item cur = head;
        int index = 0;
        while (cur != null) {
            s += index + ": " + cur.value + ", prev=" + itemValue(cur.prev)
                    + ", next=" + itemValue(cur.next) + "\n";
            cur = cur.next;
            index++;
        }
        return s;
    }

    private String itemValue(Item e) {
        return (e == null) ? "[null]" : e.value;
    }

    public static void main(String [] args) {
        System.out.println("Testing isEmpty() and length() on empty list.");
        DoublyLinkedList list = new DoublyLinkedList();
        System.out.println("Empty? " + list.isEmpty ());
        System.out.println("Length: " + list. length());

        System.out.println("Testing getOneTwoThreeList()");
        System.out.println(DoublyLinkedList.getOneTwoThreeList().fullToString());
    }
}