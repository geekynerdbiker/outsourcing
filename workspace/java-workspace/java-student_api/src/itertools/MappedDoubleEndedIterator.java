package itertools;

import java.util.NoSuchElementException;
import java.util.function.Function;

public class MappedDoubleEndedIterator<T, R> implements DoubleEndedIterator<R> {
    private final DoubleEndedIterator<T> it;
    private final Function<T, R> f;

    public MappedDoubleEndedIterator(DoubleEndedIterator<T> it, Function<T, R> f) {
        this.it = it;
        this.f = f;
    }

    @Override
    public boolean hasNext() {
        return it.hasNext();
    }

    @Override
    public R next() {
        return (R) f.apply(it.next());
    }

    @Override
    public R reverseNext() throws NoSuchElementException {
        return (R) f.apply(it.reverseNext());
    }
}
