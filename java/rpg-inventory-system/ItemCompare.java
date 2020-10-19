//Written by rosss001

import java.util.Comparator;

public class ItemCompare implements Comparator<Item>
{
  public int compare(Item a, Item b)
  {
    if(a.getName()==b.getName() && a.getGoldValue()==b.getGoldValue() && a.getWeight()==b.getWeight())
    {
      return 0;
    }
    return -1;
  }
}
