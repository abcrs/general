public class Turns
{
  private int turn=0;
  private int shot=0;
  private int boatTotal;
  private int[] sunkArray;
  private int debug=0;
  BattleboatBoard tBoard;

  public Turns(BattleboatBoard board, int debugChoice)
  {
    tBoard=board;
    boatTotal=tBoard.getBoatNumber();
    sunkArray=new int[boatTotal];
    debug=debugChoice;
  }

  public int getTurn()
  {
    return turn;
  }

  public int getShot()
  {
    return shot;
  }

  public int turnsGo(int r, int c, String input)
  {
    if(input.equals("shot"))
    {
      shot++;
      hitCheck(r,c);
    }
    else if(input.equals("drone"))
    {
      droneCheck(r,c);
      turn=turn+4;
    }
    turn++;
    if(debug!=1)
    {
      tBoard.printTurn();
    }
    else
    {
      tBoard.printAll();
    }
    return boatTotal;
  }

  private void droneCheck(int x, int y)
  {
    if(x>=0 && x<tBoard.getRow() && y>=0 && y<tBoard.getCol())
    {
      System.out.println("Recon!");
      tBoard.drone(x,y);
    }
    else
    {
      System.out.println("Penalty! Out of bounds drone.");
    }
  }

  private void hitCheck(int x, int y)
  {
    int hit;
    if(x>=0 && x<tBoard.getRow() && y>=0 && y<tBoard.getCol())
    {
      char target=tBoard.checkTarget(x,y);
      if(target=='-')
      {
        System.out.println("Miss!");
        tBoard.setTarget(x,y,'O');
      }
      else if(target=='X' || target=='O')
      {
        System.out.println("Penalty! Repeat shot.");
        turn++;
      }
      else
      {
        hit=Character.getNumericValue(target)-1;
        sunkArray[hit]++;
        System.out.println("Hit!");
        if(sunkArray[hit]==3)
        {
          System.out.println("You sunk a boat!");
          boatTotal--;
        }
        tBoard.setTarget(x,y,'X');
      }
    }
    else
    {
      System.out.println("Penalty! Out of bounds shot.");
      turn++;
    }
  }
}
