package itertools;

import java.util.Iterator;
import java.util.function.BiFunction;

public class ReducedIterator<T, R> implements Iterator<R> {
    private final Iterator<T> it;
    private final R init;
    private final BiFunction<R, T, R> f;
    private R rst;
    private boolean isFirst = true;

    public ReducedIterator(Iterator<T> it, R init, BiFunction<R, T, R> f) {
        this.it = it;
        this.init = init;
        this.f = f;
    }

    @Override
    public boolean hasNext() {
        return it.hasNext();
    }

    @Override
    public R next() {
        if (isFirst)
            rst = f.apply(init, it.next());
        else if (it.hasNext())
            rst = f.apply(rst, it.next());
        isFirst = false;
        return rst;
    }
}
