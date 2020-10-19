//Written by rosss001

import java.util.Comparator;

public class DamageCompare implements Comparator<Weapon>
{
  public int compare(Weapon a, Weapon b)
  {
    return a.getDamage()-b.getDamage();
  }
}
