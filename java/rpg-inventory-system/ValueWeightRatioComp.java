//Written by rosss001

import java.util.Comparator;

public class ValueWeightRatioComp implements Comparator<Item>
{
  public int compare(Item a, Item b)
  //If one Item has no weight or value, assumes it is higher priority
  {
    if(a.getWeight()==0 && a.getGoldValue()==0)
    {
      return 1;
    }
    if(b.getWeight()==0 && b.getGoldValue()==0)
    {
      return -1;
    }
    double result=a.getValueWeightRatio()-b.getValueWeightRatio();
    if (result>0 && result<1)
    {
      return 1;
    }
    int resultInt=(int)Math.floor(result);
    return resultInt;
  }
}
