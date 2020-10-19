//Written by rosss001

import java.util.Comparator;

public class WeaponCompare implements Comparator<Weapon>
{
  public int compare(Weapon a, Weapon b)
  {
    if(a.getName()==b.getName() && a.getGoldValue()==b.getGoldValue() && a.getWeight()==b.getWeight() && a.getDamage()==b.getDamage())
    {
      return 0;
    }
    return -1;
  }
}
