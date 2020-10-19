//Written by rosss001

import java.util.Comparator;

public class WeightComp implements Comparator<Item>
{
  public int compare(Item a, Item b)
  {
    if(a.getWeight()>0)
    {
      return 0;
    }
    return -1;
  }
}
