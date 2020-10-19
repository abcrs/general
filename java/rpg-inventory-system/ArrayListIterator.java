//Written by rosss001

import java.util.Iterator;
import java.util.NoSuchElementException;

public class ArrayListIterator<T> implements ListIterator<T>
{
  private int i = -1;
  private ArrayList<T> list;

  public ArrayListIterator(ArrayList<T> list)
  {
      this.list = list;
  }

  public boolean hasNext()
  {
      return i + 1 < list.size();
  }

  public T next()
  {
      if (!hasNext())
      {
          throw new NoSuchElementException();
      }
      i++;
      return list.get(i);
  }

  public void set(T element)
  {
      list.set(i, element);
  }

  public void add(T element)
  {
      i++;
      list.add(i, element);
  }

  public void remove()
  {
    if (i == -1)
    {
        throw new IllegalStateException(
            "Remove not allowed in the current state.");
    }

    list.remove(i);
    i--;
  }
}
