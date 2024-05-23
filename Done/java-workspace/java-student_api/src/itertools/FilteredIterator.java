package itertools;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.function.Predicate;

public class FilteredIterator<T> implements Iterator<T> {
    private final Iterator<T> it;
    private final Predicate<T> pred;
    private final ArrayList<T> filteredList;
    private boolean callNext = true;
    private int index = 0;

    public FilteredIterator(Iterator<T> it, Predicate<T> pred) {
        this.it = it;
        this.pred = pred;
        filteredList = new ArrayList<>();
    }

    @Override
    public boolean hasNext() {
        if (!callNext)
            return true;

        T t = it.next();

        while (!pred.test(t)) {
            if (it.hasNext())
                t = it.next();
            else
                return false;
        }
        filteredList.add(t);

        callNext = false;

        return pred.test(t);
    }

    @Override
    public T next() {
        callNext = true;
        return filteredList.get(index++);
    }
}
