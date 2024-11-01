package file1234567;

public class File implements Component {

    public String name;
    public Integer size;
    private Component parent = null;

    public File(String n, Integer s) {
        this.name = n;
        this.size = s;
    }

    public void setParent(Component c) {
        this.parent = c;
    }

    @Override
    public String getName() {
        return null;
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public int getCount() {
        return 1;
    }

    @Override
    public String display(String prefix) {
        return name + " (" + getSize() + ")";
    }

    @Override
    public Component search(String name) {
        return this.name.equals(name) ? parent : null;
    }
}