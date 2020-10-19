import java.util.Iterator;

public interface ReadonlyList<T> extends Iterable<T>
{
    T get(int index);
    int size();
}
