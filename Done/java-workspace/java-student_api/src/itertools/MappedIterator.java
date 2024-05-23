package itertools;

import java.util.Iterator;
import java.util.function.Function;

public class MappedIterator<T, R> implements Iterator<R> {
    private final Iterator<T> it;
    private final Function<T, R> f;

    public MappedIterator(Iterator<T> it, Function<T, R> f) {
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
}
