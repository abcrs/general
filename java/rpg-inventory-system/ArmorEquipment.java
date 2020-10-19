//Written by rosss001

public class ArmorEquipment implements Armor
{
  private String armorName;
  private int goldValue;
  private double armorWeight;
  private double valueWeightRatio;
  private int armorSlot;
  private int armorRating;

  public ArmorEquipment(String name, int value, double weight, int slot, int rating)
  {
    armorName=name;
    goldValue=value;
    armorWeight=weight;
    valueWeightRatio=value/weight;
    armorSlot=slot;
    armorRating=rating;
  }

  public String getName()
  {
    return armorName;
  }

  public int getGoldValue()
  {
    return goldValue;
  }

  public double getWeight()
  {
    return armorWeight;
  }

  public double getValueWeightRatio()
  {
    return valueWeightRatio;
  }

  public int getSlot()
  {
    return armorSlot;
  }

  public int getRating()
  {
    return armorRating;
  }

  public String toString()
  {
    return armorName+"\t|   "+goldValue+" GP\t|   "+armorWeight+" lbs.\t|   "+valueWeightRatio+"\t| "+armorRating+" AR";
  }
}
