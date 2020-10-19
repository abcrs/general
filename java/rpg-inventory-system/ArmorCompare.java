//Written by rosss001

import java.util.Comparator;

public class ArmorCompare implements Comparator<Armor>
{
  public int compare(Armor a, Armor b)
  {
    if(a.getName()==b.getName() && a.getGoldValue()==b.getGoldValue() && a.getWeight()==b.getWeight() && a.getSlot()==b.getSlot() && a.getRating()==b.getRating())
    {
      return 0;
    }
    return -1;
  }
}
