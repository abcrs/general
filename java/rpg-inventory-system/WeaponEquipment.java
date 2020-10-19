//Written by rosss001

public class WeaponEquipment implements Weapon
{
  private String weaponName;
  private int goldValue;
  private double weaponWeight;
  private double valueWeightRatio;
  private int weaponDamage;

  public WeaponEquipment(String name, int value, double weight, int damage)
  {
    weaponName=name;
    goldValue=value;
    weaponWeight=weight;
    valueWeightRatio=value/weight;
    weaponDamage=damage;
  }

  public String getName()
  {
    return weaponName;
  }

  public int getGoldValue()
  {
    return goldValue;
  }

  public double getWeight()
  {
    return weaponWeight;
  }

  public double getValueWeightRatio()
  {
    return valueWeightRatio;
  }

  public int getDamage()
  {
    return weaponDamage;
  }

  public String toString()
  {
    return weaponName+"\t|   "+goldValue+" GP\t|   "+weaponWeight+" lbs.\t|   "+valueWeightRatio+"\t| "+weaponDamage+" DMG";
  }
}
