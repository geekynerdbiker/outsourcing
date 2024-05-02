package file1234567;

import java.util.ArrayList;
import java.util.List;

public class Directory implements Component {

    public String dir;
    public List<Component> children;

    public Directory(String d) {
        this.dir = d;
        this.children = new ArrayList<>();
    }

    public void add(Component c) {
        children.add(c);
        if (c instanceof File) {
            ((File) c).setParent(this);
        }
    }

    public void remove(Component c) {
        children.remove(c);
    }

    @Override
    public String getName() {
        return dir;
    }

    @Override
    public int getSize() {
        int size = 0;

        for (Component child : this.children) {
            size += child.getSize();
        }
        return size;
    }

    @Override
    public int getCount() {
        int count = 0;

        for (Component child : children) {
            count += child.getCount();
        }
        return count;
    }

    public String display(String prefix) {
        StringBuilder root = new StringBuilder(dir + ": (count=" + getCount() + ", size=" + getSize() + ")");

        prefix += "\t\t";
        for (Component child : children) {
            root.append("\n").append(prefix).append(child.display(prefix));
        }
        return root.toString();
    }

    public Component search(String name) {
        Component c;

        for (Component child : children) {
            c = child.search(name);
            if (c != null) {
                return c;
            }
        }
        return null;
    }
}