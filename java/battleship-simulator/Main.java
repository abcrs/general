import java.util.Scanner;

public class Main
{
  public static void main(String[] args)
  {
    Scanner input=new Scanner(System.in);
    int row, column;
    int debug=0;
    int fail;
    String debugChoice;
    String inputCheck="";
    int r=-1;
    int c=-1;
    System.out.println("Would you like to enter debug mode? y/n");
    debugChoice=input.next();
    if(debugChoice.equals("y") || debugChoice.equals("yes") || debugChoice.equals("Y") || debugChoice.equals("YES"))
    {
      debug=1;
      System.out.println("Hidden objects are bracketed in [ ].");
    }
    System.out.println("How large would you like the board to be? Enter the row then column, separated by a space.");
    row=input.nextInt();
    column=input.nextInt();
    BattleboatBoard board=new BattleboatBoard(row,column);
    int boatTotal=board.getBoatNumber();
    System.out.println("There are "+boatTotal+" boat(s).");
    Turns game=new Turns(board,debug);
    if(debug!=1)
    {
      board.printTurn();
    }
    else
    {
      board.printAll();
    }
    System.out.println("Enter your shots in the format: [row] [column].");
    System.out.println("If you wish to use the drone, enter: drone [row] [column]");
    do
    {
      fail=1;
      System.out.print("Enter a shot: ");
      Scanner shot=new Scanner(System.in);
      try
      {
        inputCheck=shot.next();
        if(!inputCheck.equals("drone"))
        {
          r=Integer.parseInt(inputCheck);
          c=shot.nextInt();
          inputCheck="shot";
        }
        else if(inputCheck.equals("drone"))
        {
          r=shot.nextInt();
          c=shot.nextInt();
          inputCheck="drone";
        }
      }
      catch (Exception e)
      {
        System.out.println("Invalid input. No penalty.");
        fail=0;
      }
      if(fail!=0)
      {
        boatTotal=game.turnsGo(r,c,inputCheck);
      }
    } while(boatTotal>0);
    System.out.println("You took "+game.getShot()+" shots over "+game.getTurn()+" turns to sink "+board.getBoatNumber()+" boat(s).");
  }
}
