package itertools;

import java.util.NoSuchElementException;

public class ReversedDoubleEndedIterator<T> implements DoubleEndedIterator<T> {
    private final DoubleEndedIterator<T> it;

    public ReversedDoubleEndedIterator(DoubleEndedIterator<T> it) {
        this.it = it;
    }

    @Override
    public boolean hasNext() {
        return it.hasNext();
    }

    @Override
    public T next() {
        return it.reverseNext();
    }

    @Override
    public T reverseNext() throws NoSuchElementException {
        return it.next();
    }
}
