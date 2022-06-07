import java.util.ArrayDeque;
import java.util.Deque;


public class Heap {
	
	class Node{
		char key;
		Node left;
		Node right;
		Node parent;
		
		public Node(char v, Node l, Node r, Node p) {
			key = v;
			left = l;
			right = r;
			parent = p;
		}
		
		public String toString() {
			return " " + key;
		}	
	}
	
	Node heap, last;
	
	public Heap() {
		heap = null;
		last = null;
	}
	
	public void insert(char x) {
		Node pNext; // parent of new node
		if(heap == null) {
			heap = new Node(x, null, null, null);
			last = heap;
			pNext = null;
		}
		else if(heap == last) {
			heap.left = new Node(x, null, null, heap);
			last = heap.left;
			pNext = heap;
		}
		else if(last == last.parent.left) {
			last.parent.right = new Node(x, null, null, last.parent);
			last = last.parent.right;
			pNext = last.parent;
		}
		else {
			pNext = last;			
//			while() {
//				pNext = pNext.parent;
//				if(... != null) {
//					pNext = pNext.parent.right;
//				}	
//				while() {
//					pNext = pNext.left;
//				}
//				pNext.left = new Node();
//				last = ;
//			}
		}
		heapifyUpward(last);
		showHeap();
	}

	private void heapifyUpward(Node node) {
		if(node == null || node.parent == null)
			return;
		
		if(node.key > node.parent.key) {
			swap(node, node.parent);
			heapifyUpward(node.parent);
		}
	}
	
	private void swap(Node a, Node b) {
		char temp = a.key;
		a.key = b.key;
		b.key = temp;
	}
	
	public void showHeap() {
		System.out.println(levelOrderTraverse(heap));
	}
	
	private String levelOrderTraverse(Node node) {
		if(node == null)
			return null;
		Deque<Node> q = new ArrayDeque<Node>();
		q.addLast(heap);
		return levelOrderTraverse(q, "");
	}

	private String levelOrderTraverse(Deque<Node> q, String string) {
		if(q.isEmpty())
			return string;
		Node node = q.poll();
		string = string+node.toString();
		if(node.left != null) {
			q.add(node.left);
			if(node.right != null)
				q.add(node.right);
		}
		return levelOrderTraverse(q, string);
	}

	public Character delete() {
		return null;
	}
	
	private void heapifyDownward(Node node) {
		if(node == null || node.left == null)
			return;
		Node bigger = node.left;
		if(node.right != null && node.right.key > node.left.key) {
			bigger = node.right;
		}
		if(bigger.key > node.key) {
			swap(bigger, node);
			heapifyDownward(bigger);
		}
	}
	
	
	public static void main(String[] args) {
		Heap heap = new Heap();
		
		for (int i = 0; i < 26; i++) {
			heap.insert((char)((int)'A' + i));
		}	
				
		System.out.println("\nHeap Created:  ");
		heap.showHeap();

		System.out.println("\nSort [Max Heap]:  ");

		Character c;
		while((c = heap.delete()) != null) {
			System.out.print(c+ " ");
			heap.showHeap();
		}
	}

}
