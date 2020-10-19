//Written by rosss001

public class Inventory implements Item
{
  private String itemName;
  private int goldValue;
  private double itemWeight;
  private double valueWeightRatio;

  public Inventory(String name, int value, double weight)
  {
    itemName=name;
    goldValue=value;
    itemWeight=weight;
    valueWeightRatio=value/weight;
  }

  public String getName()
  {
    return itemName;
  }

  public int getGoldValue()
  {
    return goldValue;
  }

  public double getWeight()
  {
    return itemWeight;
  }

  public double getValueWeightRatio()
  {
    return valueWeightRatio;
  }

  public String toString()
  {
    return itemName+"\t|   "+goldValue+" GP\t|   "+itemWeight+" lbs.\t|   "+valueWeightRatio;
  }
}
