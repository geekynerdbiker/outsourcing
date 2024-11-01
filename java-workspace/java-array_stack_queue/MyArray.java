import java.util.Arrays;

public class MyArray<E> {
    private Object[] elements;
    private int size;

    public MyArray() {
        this.elements = new Object[10];
        this.size = 0;
    }

    public Object get(int i) {

        return elements[i];
    }

    public Object set(int i, Object e) {

        Object oldEle = elements[i];
        elements[i] = e;
        return oldEle;
    }

    public void add(int i, Object e) {

        if (size == elements.length) {

            elements = Arrays.copyOf(elements, 2 * elements.length);
        }

        System.arraycopy(elements, i, elements, i + 1, size - i);
        elements[i] = e;
        size++;
    }

    public Object remove(int i) {

        Object removedEle = elements[i];

        System.arraycopy(elements, i + 1, elements, i, size - i - 1);
        elements[size - 1] = null;
        size--;

        return removedEle;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        if (size == 0) return true;
        else return false;
    }

}

