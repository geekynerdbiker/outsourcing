public class Tree {
    private Node root;
    private boolean isValid;
    private int size = 0;

    public Tree() {
        this.root = null;
        isValid = true;
    }

    public Node getRoot() {
        return root;
    }

    public void addNode(String parent, String child) {
        if (root == null) {
            root = new Node(parent);
            root.addChild(new Node(child));
            size++;
        } else {
            if (findNode(root, parent) == null) {
                isValid = false;
                return;
            } if (findNode(root, child) != null) {
                isValid = false;
                return;
            }
            Node src = findNode(root, parent);
            src.addChild(new Node(child));
            size++;
        }
    }
    public Node findNode(Node src, String name) {
        if (src.getName().equals(name))
            return src;
        if (src.getSize() == 0)
            return null;

        Node[] children = src.getChildren();
        for (int i = 0; i <src.getSize(); i++) {
            if (children[i].getName().equals(name))
                return children[i];
            else {
                if (findNode(children[i], name) == null)
                    continue;
                else
                    return findNode(children[i], name);
            }
        }
        return null;
    }

    public boolean validation() {
        return isValid;
    }

    public ArrayQueue levelOrder() {
        if (root == null)
            return null;

        ArrayQueue result = new ArrayQueue(size+1);
        ArrayQueue queue = new ArrayQueue(size+1);

        queue.enqueue(root);

        while (!queue.isEmpty()) {
            Node currentNode = queue.dequeue();
            result.enqueue(currentNode);

            Node [] children = currentNode.getChildren();
            for (int i = 0; i < currentNode.getSize(); i++) {
                queue.enqueue(children[i]);
            }
        }

        return result;
    }
}