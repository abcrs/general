//Written by rosss001+poppe090

import java.util.Iterator;

public class CharacterImplementation implements Character
{
  private ArrayList<Item> inventoryArray=new ArrayList<Item>(10);
  private Map<String,String[]> skillMap=new HashMap<String,String[]>(10);
  private Map<String,Integer> abilityMap=new HashMap<String,Integer>(12);

  //Differe comparators required for different methods
  private ValueWeightRatioComp comp=new ValueWeightRatioComp();
  private ItemCompare iComp=new ItemCompare();
  private ArmorCompare aComp=new ArmorCompare();
  private WeaponCompare wComp=new WeaponCompare();
  private ArmorRatingCompare arComp=new ArmorRatingCompare();
  private DamageCompare dmgComp=new DamageCompare();
  private WeightComp weightComp=new WeightComp();

  //A static array created to hold the equipped armor
  private Armor[] equippedArmor=new ArmorEquipment[6];
  //A static weapon to hold the equipped weapon
  private Weapon equippedWeapon;
  private double totalWeight=0;

  public Iterator<Item> inventory()
  {
    Iterator<Item> iterator=new ArrayListIterator<Item>(inventoryArray);
    return iterator;
  }

  public void addItem(Item itemTemplate)
  //Takes in item template and adds to inventory
  //If any values are illegal, set to default
  //Increment total weight
  {
    String name;
    int goldValue;
    double weight;
    if (itemTemplate.getName()!=null)
    {
      name=itemTemplate.getName();
    }
    else
    {
      name="";
    }
    if (itemTemplate.getGoldValue()>0)
    {
      goldValue=itemTemplate.getGoldValue();
    }
    else
    {
      goldValue=0;
    }
    if (itemTemplate.getWeight()>0)
    {
      weight=itemTemplate.getWeight();
    }
    else
    {
      weight=0;
    }
    Item newItem=new Inventory(name,goldValue,weight);
    if(goldValue==0 && weight==0)
    {
        inventoryArray.addFirst(newItem);
    }
    else
    {
      inventoryArray.add(newItem);
    }
    totalWeight+=weight;
  }

  public void addItem(Armor armorTemplate)
  //Same as addItem for Item, but with Armor
  {
    String name;
    int goldValue;
    double weight;
    int armorSlot;
    int armorRating;
    if (armorTemplate.getName()!=null)
    {
      name=armorTemplate.getName();
    }
    else
    {
      name="";
    }
    if (armorTemplate.getGoldValue()<0)
    {
      goldValue=0;
    }
    else
    {
      goldValue=armorTemplate.getGoldValue();
    }
    if (armorTemplate.getWeight()<0)
    {
      weight=0;
    }
    else
    {
      weight=armorTemplate.getWeight();
    }
    if (armorTemplate.getSlot()<0 || armorTemplate.getSlot()>5)
    {
      armorSlot=0;
    }
    else
    {
      armorSlot=armorTemplate.getSlot();
    }
    if (armorTemplate.getRating()<0)
    {
      armorRating=0;
    }
    else
    {
      armorRating=armorTemplate.getRating();
    }
    Armor newArmor=new ArmorEquipment(name,goldValue,weight,armorSlot,armorRating);
    inventoryArray.add(newArmor);
    totalWeight+=weight;
  }

  public void addItem(Weapon weaponTemplate)
  //Same as addItem for Item, but with Weapon
  {
    String name;
    int goldValue;
    double weight;
    int weaponDamage;
    if (weaponTemplate.getName()!=null)
    {
      name=weaponTemplate.getName();
    }
    else
    {
      name="";
    }
    if (weaponTemplate.getGoldValue()>0)
    {
      goldValue=weaponTemplate.getGoldValue();
    }
    else
    {
      goldValue=0;
    }
    if (weaponTemplate.getWeight()>0)
    {
      weight=weaponTemplate.getWeight();
    }
    else
    {
      weight=0;
    }
    if (weaponTemplate.getDamage()<0)
    {
      weaponDamage=0;
    }
    else
    {
      weaponDamage=weaponTemplate.getDamage();
    }
    Weapon newWeapon=new WeaponEquipment(name,goldValue,weight,weaponDamage);
    inventoryArray.add(newWeapon);
    totalWeight+=weight;
  }

  public void dropItem(Item item)
  //Search for item, and drop if found
  //If not found, print error message
  //If found, remove from array list, and decrease weight
  {
    String found="";
    if(item==null)
    {
      try
      {
        throw new NullPointerException();
      }
      catch (NullPointerException e)
      {
        System.out.println("Must enter item.");
      }
    }
    else
    //findItem method looks for item and drops it if found
    {
      found=inventoryArray.findItem(item,iComp,aComp,wComp);
      if (found==null)
      {
        try
        {
          throw new ItemNotFoundException();
        }
        catch (ItemNotFoundException e)
        {
          System.out.println("Item isn't in inventory.");
        }
      }
      else
      {
        totalWeight-=item.getWeight();
      }
    }
  }

  public double getTotalWeight()
  {
    return totalWeight;
  }

  public Armor getEquippedArmor(int slot)
  //Makes sure slot is valid slot number
  //If not, return null
  //If valid, return armor in that slot
  {
    try
    {
      if(slot<0 || slot>5)
      {
        throw new IllegalArgumentException();
      }
    }
    catch (IllegalArgumentException e)
    {
      System.out.println("Must choose a slot between 0 and 5.");
      return null;
    }
    return equippedArmor[slot];
  }

  public int getTotalArmorRating()
  //Returns sum of rating of all equipped armor
  {
    int totalRating=0;
    for(Armor a:equippedArmor)
    {
      if(a!=null)
      {
        totalRating+=a.getRating();
      }
    }
    return totalRating;
  }

  public void equipArmor(Armor armor)
  //Equips armor if it can find it in the inventory
  {
    if(armor==null)
    {
      for(int i=0; i<6; i++)
      {
        this.unequipArmor(i);
      }
    }
    else
    {
      int slot=inventoryArray.findArmor(armor,aComp);
      try
      {
        if(slot==-1)
        {
          throw new ItemNotFoundException();
        }
        else
        {
          if(equippedArmor[slot]!=null)
          //If armor found, put old piece in inventory
          //Equip the new piece of armor
          //Reduce weight(because it is re-added with addItem)
          {
            this.addItem(equippedArmor[slot]);
            totalWeight-=equippedArmor[slot].getWeight();
          }
          equippedArmor[slot]=armor;
        }
      }
      catch (ItemNotFoundException e)
      {
        System.out.println("You don't have that armor in your inventory.");
      }
    }
  }

  public void unequipArmor(int slot)
  //If a valid slot is passed, remove armor from that slot
  //Put in inventory
  {
    try
    {
      if(slot<0 || slot>5)
      {
        throw new IllegalArgumentException();
      }
      else
      {
        if(equippedArmor[slot]!=null)
        {
          this.addItem(equippedArmor[slot]);
          totalWeight-=equippedArmor[slot].getWeight();
          equippedArmor[slot]=null;
        }
      }
    }
    catch (IllegalArgumentException e)
    {
      System.out.println("Not a valid armor slot.");
    }
  }

  public Weapon getEquippedWeapon()
  {
    return equippedWeapon;
  }

  public void equipWeapon(Weapon weapon)
  //Looks for passed in Weapon in Inventory
  //If found, equip passed in Weapon and add previous equipped Weapon to Inventory
  {
    Weapon newWeapon=null;
    if(weapon==null)
    {
      this.unequipWeapon();
    }
    else
    {
      try
      {
        newWeapon=inventoryArray.findWeapon(weapon,wComp);
        if(newWeapon==null)
        {
          throw new ItemNotFoundException();
        }
        else
        {
          if(equippedWeapon!=null)
          {
            this.addItem(equippedWeapon);
            totalWeight-=equippedWeapon.getWeight();
          }
          equippedWeapon=newWeapon;
        }
      }
      catch (ItemNotFoundException e)
      {
        System.out.println("You don't have that weapon in your inventory.");
      }
    }
  }

  public void unequipWeapon()
  //Unequips current Weapon and places it in Inventory
  {
    if(equippedWeapon!=null)
    {
      this.addItem(equippedWeapon);
      totalWeight-=equippedWeapon.getWeight();
      equippedWeapon=null;
    }
  }

  public void optimizeInventory(double maximumWeight)
  //Takes in maximum carry weight, and removes items, one at a time
  //Remove the lowest value/weight ratio items first
  //Reduce weight each time, and stop removing when below maximum weight
  {
    Item noWeight=new Inventory("",0,0);
    double equippedWeight=0;
    for(Armor a:equippedArmor)
    {
      if(a!=null)
      {
        equippedWeight+=a.getWeight();
      }
    }
    if(equippedWeapon!=null)
    {
      equippedWeight+=equippedWeapon.getWeight();
    }
    try
    {
      if(maximumWeight<0)
      {
        throw new IllegalArgumentException();
      }
      else
      {
        inventoryArray.sort(comp);
        if(totalWeight>=maximumWeight)
        {
          System.out.println("Items removed:\n");
        }
        else
        {
          System.out.println("Already below target weight.");
        }
        if(equippedWeight>maximumWeight)
        {
            inventoryArray.removeAll(noWeight,weightComp);
            totalWeight=equippedWeight;
        }
        else
        {
          while(totalWeight>=maximumWeight)
          {
            Item removed=null;
            removed=inventoryArray.removeLowest(noWeight,weightComp);
            if(removed!=null)
            {
              totalWeight-=removed.getWeight();
            }
            else
            {
              maximumWeight=totalWeight+1;
            }
          }
        }
      }
    }
    catch (IllegalArgumentException e)
    {
      System.out.println("Your maximum weight must be at least 0.");
    }
  }

  public void optimizeEquipment()
  //Finds highest rating Armor and highest damage Weapon in Inventory
  //Equips them if higher rating/damage than currently equipped item
  {
    for(int i=0; i<6; i++)
    {
      Armor newArmor=null;
      int rating=0;
      if(equippedArmor[i]!=null)
      {
        newArmor=inventoryArray.findBestArmor(equippedArmor[i],arComp);
      }
      else
      {
        Armor tempArmor=new ArmorEquipment("",0,0,i,0);
        newArmor=inventoryArray.findBestArmor(tempArmor,arComp);
      }
      if(newArmor!=null)
      {
        if(equippedArmor[i]!=null)
        {
          this.addItem(equippedArmor[i]);
          totalWeight-=equippedArmor[i].getWeight();
        }
        equippedArmor[i]=newArmor;
      }
    }
    Weapon newWeapon=null;
    if(equippedWeapon!=null)
    {
      newWeapon=inventoryArray.findBestWeapon(equippedWeapon,dmgComp);
    }
    else
    {
      Weapon tempWeapon=new WeaponEquipment("",0,0,0);
      newWeapon=inventoryArray.findBestWeapon(tempWeapon,dmgComp);
    }
    if(newWeapon!=null)
    {
      if(equippedWeapon!=null)
      {
        this.addItem(equippedWeapon);
        totalWeight-=equippedWeapon.getWeight();
      }
      equippedWeapon=newWeapon;
    }
  }

  public void addAll(Item[] addArray)
  //For testing, to add multiple items at once, sorted
  {
    inventoryArray.addAll(addArray,comp);
    for(Item w:addArray)
    {
      totalWeight+=w.getWeight();
    }
  }

  public int getAbilityScore(String abilityName)
  //Find and return abilityScore for abilityName
  //Return 10 if abilityName not found in abilityMap
  {
    Integer abilityScore=0;
    try
    {
      if(abilityName.equals(null))
      {
        throw new NullPointerException();
      }
      else
      {
        abilityScore=abilityMap.get(abilityName);
        if(abilityScore==null)
        {
          return 10;
        }
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    return abilityScore;
  }

  public void setAbilityScore(String abilityName, int abilityScore)
  //Add abilityScore to corresponding abilityName
  //Override old score value if abilityName exists
  //Create new entry if it does not
  {
    try
    {
      if(abilityName.equals(null))
      {
        throw new NullPointerException();
      }
      else if(abilityScore<0)
      {
        throw new IllegalArgumentException();
      }
      else
      {
        abilityMap.put(abilityName,abilityScore);
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    catch (IllegalArgumentException e)
    {
      e.printStackTrace();
    }
  }

  public int getAbilityModifier(String abilityName)
  //Return ability modifier for abilityName
  //getAbilityScore to get the score
  {
    Integer abilityMod=0;
    try
    {
      if(abilityName.equals(null))
      {
        throw new NullPointerException();
      }
      else
      {
        abilityMod=getAbilityScore(abilityName);
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    return (int)(abilityMod/2)-5;
  }

  public boolean checkAbility(String abilityName, int difficulty)
  //Check abilityName against Difficulty
  //Add getAbilityModifier to random 1-20 (inclusive) roll
  {
    int roll=(int)(Math.random()*(20))+1;
    Integer abilityScore=0;
    try
    {
      if(abilityName.equals(null))
      {
        throw new NullPointerException();
      }
      else if(difficulty<0)
      {
        throw new IllegalArgumentException();
      }
      else
      {
        int mod=getAbilityModifier(abilityName);
        System.out.println("You rolled a "+roll+" with a modifier of "+mod+".");
        if((roll+mod)>=difficulty)
        {
          return true;
        }
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    catch (IllegalArgumentException e)
    {
      e.printStackTrace();
    }
    return false;
  }

  public void addSkill(String skillName, String relatedAbility, int skillRanks)
  //Add new skillName with relatedAbility and starting getSkillRanks
  //Store skillName as key to map and a String[] array as the values
  //Store skillRanks as Integer with parseInt
  {
    try
    {
      if(skillName.equals(null) || relatedAbility.equals(null))
      {
        throw new NullPointerException();
      }
      else if(skillRanks<0)
      {
        throw new IllegalArgumentException();
      }
      else if(skillMap.get(skillName)!=null)
      {
        throw new ArrayStoreException();
      }
      else
      {
        String[] skillInfo=new String[]{relatedAbility,Integer.toString(skillRanks)};
        skillMap.put(skillName,skillInfo);
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    catch (IllegalArgumentException e)
    {
      e.printStackTrace();
    }
    catch (ArrayStoreException e)
    {
      e.printStackTrace();
    }
  }

  public String getRelatedAbility(String skillName)
  //Find and return relatedAbility for skillName
  //Error if skillName not in skillMap
  {
    try
    {
      if(skillName.equals(null))
      {
        throw new NullPointerException();
      }
      else if(skillMap.get(skillName)==null)
      {
        throw new ArrayStoreException();
      }
      else
      {
        String[] skillInfo=skillMap.get(skillName);
        return skillInfo[0];
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    catch (ArrayStoreException e)
    {
      e.printStackTrace();
    }
    return "";
  }

  public int getSkillRanks(String skillName)
  //Find and return skillRanks for skillName
  //Error if skillName not in skillMap
  {
    Integer skillRank=0;
    try
    {
      if(skillName.equals(null))
      {
        throw new NullPointerException();
      }
      else if(skillMap.get(skillName).equals(null))
      {
        skillRank=0;
      }
      else
      {
        String[] skillInfo=skillMap.get(skillName);
        skillRank=Integer.parseInt(skillInfo[1]);
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    return skillRank;
  }

  public void setSkillRanks(String skillName, int skillRanks)
  //Alter skillRanks for skillName
  //Error if skillName not in skillMap
  {
    try
    {
      if(skillName.equals(null))
      {
        throw new NullPointerException();
      }
      else if(skillRanks<0)
      {
        throw new IllegalArgumentException();
      }
      else if(skillMap.get(skillName).equals(null))
      {
        throw new ArrayStoreException();
      }
      else
      {
        String[] skillInfo=skillMap.get(skillName);
        skillInfo[1]=Integer.toString(skillRanks);
        skillMap.put(skillName,skillInfo);
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();;
    }
    catch (IllegalArgumentException e)
    {
      e.printStackTrace();
    }
    catch (ArrayStoreException e)
    {
      e.printStackTrace();
    }
  }

  public int getSkillModifier(String skillName)
  //Get skillMod for skillName
  //Combine skillRanks and getAbilityModifier for relatedAbility
  //Error if skillName not in skillMap
  {
    int skillMod=0;
    try
    {
      if(skillName.equals(null))
      {
        throw new NullPointerException();
      }
      else if(skillMap.get(skillName).equals(null))
      {
        skillMod=0;
      }
      else
      {
        String[] skillInfo=skillMap.get(skillName);
        skillMod=getSkillRanks(skillName)+getAbilityModifier(skillInfo[0]);
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    return skillMod;
  }

  public boolean checkSkill(String skillName, int difficulty)
  //Check skillName against Difficulty
  //Add getSkillModifier to random 1-20 (inclusive) roll
  {
    int roll=(int)(Math.random()*(20))+1;
    try
    {
      if(skillName.equals(null))
      {
        throw new NullPointerException();
      }
      else if(difficulty<0)
      {
        throw new IllegalArgumentException();
      }
      else
      {
        int mod=getSkillModifier(skillName);
        System.out.println("You rolled a "+roll+" with a modifier of "+mod+".");
        if((roll+mod)>=difficulty)
        {
          return true;
        }
      }
    }
    catch (NullPointerException e)
    {
      e.printStackTrace();
    }
    catch (IllegalArgumentException e)
    {
      e.printStackTrace();
    }
    return false;
  }

  public String print(int choice)
  //Print Character information
  //choice allows ability to print Inventory and Equipment
  //Or print Ability and Skill information
  //Return concatenated String
  {
    StringBuilder output=new StringBuilder();
    if(choice==1)
    {
      inventoryArray.sort(comp);
      output.append(this.printEquipment());
      output.append("\nItem\t\t   Value\t    Weight\t    Ratio");
      output.append(inventoryArray.print());
      output.append("Total Weight: "+totalWeight+" lbs.\n");
    }
    else
    {
      output=this.printSheet();
    }
    return output.toString();
  }

  private StringBuilder printEquipment()
  //Formats printing for equipped Armor and Weapon, so it looks distinct from items in Inventory
  {
    StringBuilder output=new StringBuilder();
    output.append("\nEquipped Armor");
    for(int i=0; i<6; i++)
    {
      if(equippedArmor[i]!=null)
      {
        int armorSlot=equippedArmor[i].getSlot();
        if(armorSlot==0)
        {
          output.append("0/Chest  ");
        }
        else if(armorSlot==1)
        {
          output.append("1/Legs   ");
        }
        else if(armorSlot==2)
        {
          output.append("2/Hands  ");
        }
        else if(armorSlot==3)
        {
          output.append("3/Feet   ");
        }
        else if(armorSlot==4)
        {
          output.append("4/Head   ");
        }
        else if(armorSlot==5)
        {
          output.append("5/Shield ");
        }
        output.append("| "+equippedArmor[i].getName()+"   \t| "+equippedArmor[i].getRating()+" AR\t|  "+equippedArmor[i].getGoldValue()+" GP\t|   "+equippedArmor[i].getWeight()+" lbs.");
      }
    }
    output.append("\nTotal AR: "+this.getTotalArmorRating());
    output.append("\nEquipped Weapon");
    if(equippedWeapon!=null)
    {
      output.append(equippedWeapon.getName()+"\t| "+equippedWeapon.getDamage()+" DMG\t|   "+equippedWeapon.getGoldValue()+" GP\t|   "+equippedWeapon.getWeight()+" lbs.");
    }
    return output;
  }

  public StringBuilder printSheet()
  //Use for:each loop to read through and create StringBuilder
  //For both Ability and Skill HashMap, return to print method
  {
    StringBuilder output=new StringBuilder();
    for(Map.Entry<String,Integer> e:abilityMap.entrySet())
    {
      String ability=e.getKey();
      Integer score=e.getValue();
      output.append("Ability: "+ability+" \t| Score: "+score+"\n");
    }
    for(Map.Entry<String,String[]> s:skillMap.entrySet())
    {
      String skill=s.getKey();
      String[] info=s.getValue();
      output.append("Skill: "+skill+"\t| Ranks: "+info[1]+"\t| Related Ability: "+info[0]+"\n");
    }
    return output;
  }
}
