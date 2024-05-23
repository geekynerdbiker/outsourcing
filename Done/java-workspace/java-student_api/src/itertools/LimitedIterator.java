package itertools;

import java.util.Iterator;

public class LimitedIterator<T> implements Iterator<T> {
    private final Iterator<T> it;
    private int index = 0;
    private final int limit;

    public LimitedIterator(Iterator<T> it, int limit) {
        this.it = it;
        this.limit = limit;
    }

    @Override
    public boolean hasNext() {
        return it.hasNext() && index < limit;
    }

    @Override
    public T next() {
        index++;
        return it.next();
    }
}
