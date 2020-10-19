//Written by rosss001

import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class ArrayList<T> implements List<T>
{
  private Object[] array;
  private int size=0;

  public ArrayList(int capacity)
  {
      array = new Object[capacity];
  }

  public int size()
  {
      return size;
  }

  @SuppressWarnings("unchecked")
  public T get(int index)
  {
      if (index >= size)
      {
          throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
      }
      else
      {
          return (T) array[index];
      }
  }

  public void set(int index, T element)
  {
      if (index >= size)
      {
          throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
      }
      else
      {
          array[index] = element;
      }
  }

  public void clear()
  {
      size = 0;
  }

  private void resize(int newCapacity)
  {
      Object[] original = array;
      array = new Object[newCapacity];

      for (int i = 0; i < size; i++)
      {
          array[i] = original[i];
      }
  }

  public void add(T element)
  {
    if (size == array.length)
    {
        resize(size * 2);
    }
    array[size] = element;
    size++;
  }

  @SuppressWarnings("unchecked")
  public void add(T element, Comparator c)
  {
    boolean sorted=false;
    if (size == array.length)
    {
        resize(size * 2);
    }
    for (int i=0; i<size && !sorted; i++)
    {
      if(c.compare(element,array[i])>0)
      {
        sorted=true;
        shiftRight(i,1);
      }
      if(sorted)
      {
        array[i]=element;
      }
    }
    if(!sorted)
    {
      array[size]=element;
    }
    size++;
  }

  public void addAll(T[] elements)
  {
      for (T v : elements)
      {
          add(v);
      }
  }

  public void addAll(T[] elements, Comparator c)
  {
    for (T v : elements)
    {
      add(v,c);
    }
  }

  private void shiftRight(int index, int amount)
  {
      for (int k = size - 1; k >= index; k--)
      {
          array[k + amount] = array[k];
      }
  }

  public void add(int index, T element)
  {
      if (index > size)
      {
          throw new IndexOutOfBoundsException(
              "Index: " + index + ", Size: " + size);
      }

      if (size == array.length)
      {
          resize(size * 2);
      }

      shiftRight(index, 1);
      array[index] = element;
      size++;
  }

  public void addFirst(T element)
  {
      add(0, element);
  }

  public void addLast(T element)
  {
      add(element);
  }

  public void addAll(int index, T[] elements)
  {
      if (index > size)
      {
          throw new IndexOutOfBoundsException(
              "Index: " + index + ", Size: " + size);
      }

      if (size + elements.length > array.length)
      {
          resize((size + elements.length) * 2);
      }

      shiftRight(index, elements.length);

      for (int k = 0; k < elements.length; k++)
      {
          array[index + k] = elements[k];
      }

      size += elements.length;
  }

  public void remove()
  {
      if (size <= 0)
      {
          throw new EmptyListException();
      }
      else
      {
          size--;
      }
  }

  private void shiftLeft(int index, int amount)
  {
      for (int k = index; k + amount < size; k++)
      {
          array[k] = array[k + amount];
      }
  }

  public void remove(int index, int count)
  {
    if (index + count > size)
    {
      throw new IndexOutOfBoundsException(
        "Index: " + size + ", Size: " + size);
    }
    else
    {
      shiftLeft(index, count);
      size -= count;
    }
  }

  public void remove(int index)
  {
      remove(index, 1);
  }

  public void removeFirst()
  {
    remove(0);
  }

  public void removeLast()
  {
    remove();
  }

  @SuppressWarnings("unchecked")
  public String findItem(Object element, Comparator iComp, Comparator aComp, Comparator wComp)
  //Searches Inventory for instance of passed in Item, Armor, or Weapon
  //Removes it if found (used for dropItem method)
  {
    boolean found=false;
    for (int i=0; i<size && !found; i++)
    {
      if(array[i] instanceof ArmorEquipment && element instanceof ArmorEquipment)
      {
        if(aComp.compare(array[i],element)==0)
        {
          found=true;
          remove(i);
          return "";
        }
      }
      else if(array[i] instanceof WeaponEquipment && element instanceof WeaponEquipment)
      {
        if(wComp.compare(array[i],element)==0)
        {
          found=true;
          remove(i);
          return "";
        }
      }
      else
      {
        if(iComp.compare(array[i],element)==0)
        {
          found=true;
          remove(i);
          return "";
        }
      }
    }
    return null;
  }

  @SuppressWarnings("unchecked")
  public int findArmor(Armor armor, Comparator c)
  //Look for instance of Armor in Inventory
  {
    for(int i=0; i<size; i++)
    {
      if(array[i] instanceof ArmorEquipment)
      {
        if(c.compare(array[i],armor)==0)
        {
          remove(i);
          return armor.getSlot();
        }
      }
    }
    return -1;
  }

  @SuppressWarnings("unchecked")
  public Armor findBestArmor(Armor current, Comparator c)
  //Compares passed in Armor to Armor in Inventory
  //If any have better rating (and have same slot)
  //Return the better Armor and remove it from Inventory
  {
    Armor betterArmor=null;
    int index=-1;
    for(int i=0; i<size; i++)
    {
      if(array[i] instanceof ArmorEquipment)
      {
        if(c.compare(current,array[i])<0)
        {
          current=(Armor)array[i];
          betterArmor=current;
          index=i;
        }
      }
    }
    if(betterArmor!=null)
    {
      remove(index);
      return betterArmor;
    }
    return null;
  }

  @SuppressWarnings("unchecked")
  public Weapon findWeapon(Weapon weapon, Comparator c)
  //Looks for instance of passed in Weapon in Inventory
  {
    for(int i=0; i<size; i++)
    {
      if(array[i] instanceof WeaponEquipment)
      {
        if(c.compare(weapon,array[i])==0)
        {
          remove(i);
          return weapon;
        }
      }
    }
    return null;
  }

  @SuppressWarnings("unchecked")
  public Weapon findBestWeapon(Weapon current, Comparator c)
  //Takes passed in Weapon and looks through Inventory for better one
  {
    Weapon betterWeapon=null;
    int index=-1;
    for(int i=0; i<size; i++)
    {
      if(array[i] instanceof WeaponEquipment)
      {
        if(c.compare(current,array[i])<0)
        //When a better Weapon is found, hold it and the index it is at
        {
          current=(Weapon)array[i];
          betterWeapon=current;
          index=i;
        }
      }
    }
    if(betterWeapon!=null)
    //If a better Weapon is found, return it and remove it from Inventory
    {
      remove(index);
      return betterWeapon;
    }
    return null;
  }

  @SuppressWarnings("unchecked")
  public Item removeLowest(Item nothing, Comparator c)
  //Find the lowest value item that has weight>0, and remove it
  {
    for(int i=size-1; i>0; i--)
    {
      if(c.compare(array[i],nothing)==0)
      {
        System.out.println(array[i].toString());
        remove(i);
        return (Item)array[i];
      }
    }
    return null;
  }

  @SuppressWarnings("unchecked")
  public void removeAll(Item nothing, Comparator c)
  //Removes everything with weight
  {
    for(int i=size-1; i>=0; i--)
    {
      if(c.compare(array[i],nothing)==0)
      {
        System.out.println(array[i].toString());
        remove(i);
      }
    }
  }

  public void sort(Comparator<T> c)
  //Sort swapped to create list of descending order
  {
    for (int i = 1; i < size; i++)
    {
        T n = get(i);

        for (int j = i - 1;
             j >= 0 && c.compare(n, get(j)) > 0;
             j--)
        {
            array[j + 1] = get(j);
            array[j] = n;
        }
    }
  }

  public String print()
  {
    if (size==0)
    {
      return "";
    }
    StringBuilder output=new StringBuilder();
    for(int i=0; i<size; i++)
    {
      output.append(array[i].toString());
      output.append("\n");
    }
    return output.toString();
  }

  public ListIterator<T> listIterator()
  {
      return new ArrayListIterator<T>(this);
  }

  public Iterator<T> iterator()
  {
      return new ArrayListIterator<T>(this);
  }
}
