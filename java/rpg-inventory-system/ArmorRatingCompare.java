//Written by rosss001

import java.util.Comparator;

public class ArmorRatingCompare implements Comparator<Armor>
{
  public int compare(Armor a, Armor b)
  {
    if(a.getSlot()==b.getSlot())
    {
      return a.getRating()-b.getRating();
    }
    return 0;
  }
}
