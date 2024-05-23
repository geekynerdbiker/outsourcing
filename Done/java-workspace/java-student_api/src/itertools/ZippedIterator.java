package itertools;

import java.util.Iterator;
import java.util.function.BiFunction;

public class ZippedIterator<T, U, R> implements Iterator<R> {
    private final Iterator<T> lit;
    private final Iterator<U> rit;
    private final BiFunction<T, U, R> f;

    public ZippedIterator(Iterator<T> lit, Iterator<U> rit, BiFunction<T, U, R> f) {
        this.lit = lit;
        this.rit = rit;
        this.f = f;
    }

    @Override
    public boolean hasNext() {
        return lit.hasNext() && rit.hasNext();
    }

    @Override
    public R next() {
        return (R) f.apply(lit.next(), rit.next());
    }
}
