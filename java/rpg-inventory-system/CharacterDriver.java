//Written by rosss001 & poppe090

import java.util.Comparator;
import java.util.Scanner;

public class CharacterDriver
{
  private static int getInput(CharacterImplementation c)
  //Get selection from user and move to appropriate method
  {
    Scanner option=new Scanner(System.in);
    int choice=-1;
    double maxWeight=-1;
    try
    {
      choice=option.nextInt();
      if (choice<0 || choice>6)
      {
        throw new IllegalArgumentException();
      }
    }
    catch (Exception e)
    {
      System.out.println("That's not a valid option! Please enter an integer from 0 to 6.");
    }
    switch(choice)
    {
      case 0:
      {
        String b=c.print(2);
        System.out.print(b);
        break;
      }
      case 1:
      {
        setAbility(c);
        break;
      }
      case 2:
      {
        addNewSkill(c);
        break;
      }
      case 3:
      {
        changeSkillRanks(c);
        break;
      }
      case 4:
      {
        getAbility(c);
        break;
      }
      case 5:
      {
        getSkill(c);
        break;
      }
      case 6:
      {
        System.out.println("\nHope you enjoyed your ARSE Rolls! Good bye\n");
        return 6;
      }
      default: return 0;
    }
    return 0;
  }

  private static void setAbility(Character c)
  //Obtain new Ability and Ability score from user, add to Map
  {
    String newAbility="";
    int newScore=10;
    int go=0;
    do {
      go=1;
      Scanner input=new Scanner(System.in);
      try
      {
        System.out.print("Enter the ability name: ");
        newAbility=input.nextLine();
        System.out.print("Enter the ability score: ");
        newScore=input.nextInt();
        if(newScore<0)
        {
          throw new IllegalArgumentException();
        }
      }
      catch (NumberFormatException e)
      {
        System.out.println("Ability score must be an integer! Try again.");
        go=0;
      }
      catch (IllegalArgumentException e)
      {
        System.out.println("Ability score can't be negative! Try again.");
        go=0;
      }
    } while (go==0);
    c.setAbilityScore(newAbility,newScore);
  }

  private static void addNewSkill(Character c)
  //Obtain new skill, related ability, and starting ranks, add to Map
  {
    String newSkill="";
    String ability="";
    int startRanks=0;
    int go=0;
    do {
      go=1;
      Scanner input=new Scanner(System.in);
      try
      {
        System.out.print("Enter the skill name: ");
        newSkill=input.nextLine();
        System.out.print("Enter the related ability: ");
        ability=input.nextLine();
        System.out.print("Enter the initial ranks of the skill: ");
        startRanks=input.nextInt();
        if(startRanks<0)
        {
          throw new IllegalArgumentException();
        }
      }
      catch (NumberFormatException e)
      {
        System.out.println("Skill ranks must be an integer! Try again.");
        go=0;
      }
      catch (IllegalArgumentException e)
      {
        System.out.println("Skill ranks can't be negative! Try again.");
        go=0;
      }
    } while (go==0);
    c.addSkill(newSkill,ability,startRanks);
  }

  private static void changeSkillRanks(Character c)
  //Obtain skill and the new rank amount, change Map
  {
    String skill="";
    int newRanks=10;
    int go=0;
    do {
      go=1;
      Scanner input=new Scanner(System.in);
      try
      {
        System.out.print("Enter the skill name: ");
        skill=input.nextLine();
        System.out.print("Enter the new rank total: ");
        newRanks=input.nextInt();
        if(newRanks<0)
        {
          throw new IllegalArgumentException();
        }
      }
      catch (NumberFormatException e)
      {
        System.out.println("Skill rank must be an integer! Try again.");
        go=0;
      }
      catch (IllegalArgumentException e)
      {
        System.out.println("Skill rank can't be negative! Try again.");
        go=0;
      }
    } while (go==0);
    c.setSkillRanks(skill,newRanks);
  }

  private static void getAbility(Character c)
  //Obtain ability to be checked and difficulty, print success or failure
  {
    String ability="";
    int check=0;
    boolean score=false;
    int go;
    do {
      go=1;
      Scanner input=new Scanner(System.in);
      try
      {
        System.out.print("Enter the ability name: ");
        ability=input.nextLine();
        System.out.print("Enter the difficulty of the check: ");
        check=input.nextInt();
        if(check<0)
        {
          throw new IllegalArgumentException();
        }
      }
      catch (NumberFormatException e)
      {
        System.out.println("Difficulty must be an integer! Try again.");
        go=0;
      }
      catch (IllegalArgumentException e)
      {
        System.out.println("Difficulty can't be negative! Try again.");
        go=0;
      }
    } while (go==0);
    score=c.checkAbility(ability,check);
    if(score)
    {
      System.out.println("You were successful!");
    }
    else
    {
      System.out.println("FAILURE!!");
    }
  }

  private static void getSkill(Character c)
  //Obtain skill to be checked and difficulty, print success or failure
  {
    String skill="";
    int check=0;
    boolean score=false;
    int go=0;
    do {
      go=1;
      Scanner input=new Scanner(System.in);
      try
      {
        System.out.print("Enter the skill name: ");
        skill=input.nextLine();
        System.out.print("Enter the difficulty of the check: ");
        check=input.nextInt();
        if(check<0)
        {
          throw new IllegalArgumentException();
        }
      }
      catch (NumberFormatException e)
      {
        System.out.println("Difficulty must be an integer! Try again.");
        go=0;
      }
      catch (IllegalArgumentException e)
      {
        System.out.println("Difficulty can't be negative! Try again.");
        go=0;
      }
    } while (go==0);
    score=c.checkSkill(skill,check);
    if(score)
    {
      System.out.println("You were successful!");
    }
    else
    {
      System.out.println("FAILURE!!");
    }
  }

  public static void main(String[] args)
  {
    CharacterImplementation c=new CharacterImplementation();
    int quit=0;

    System.out.println("Welcome to the Ability and Related Skill Experience!");
    do {
      System.out.println("\n************************************************");
      System.out.println("\t0: Print Character Sheet");
      System.out.println("\t1: Set Ability Score");
      System.out.println("\t2: Add Skill");
      System.out.println("\t3: Set Skill Ranks");
      System.out.println("\t4: Perform Ability Check");
      System.out.println("\t5: Perform Skill Check");
      System.out.println("\t6: Quit");
      System.out.println("\n************************************************");
      System.out.print("Select your roll: ");
      quit=getInput(c);
    } while (quit!=6);
  }
}
