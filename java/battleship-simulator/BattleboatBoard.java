public class BattleboatBoard
{
  private char[][] board;
  private char[][] boardGame;
  private int row=0;
  private int col=0;
  private int boatNumber;

  public BattleboatBoard(int newRow, int newColumn)
  {
    if (!(newRow<3 || newRow>12 || newColumn<3 || newColumn>12))
    {
      row=newRow;
      col=newColumn;
      board=new char[row][col];
      boardGame=new char[row][col];
      for(int i=0; i<row; i++)
      {
        for(int j=0; j<col; j++)
        {
          board[i][j]='-';
          boardGame[i][j]='-';
        }
      }
    }
    else
    {
      throw new IllegalArgumentException("Rows and Columns must be between size 3 and 12");
    }
    placeBoats();
  }

  public int getRow()
  {
    return row;
  }

  public int getCol()
  {
    return col;
  }

  public int getBoatNumber()
  {
    return boatNumber;
  }

  public char checkTarget(int r, int c)
  {
    return board[r][c];
  }

  public void setTarget(int r, int c, char result)
  {
    boardGame[r][c]=result;
    board[r][c]=result;
  }

  public void drone(int r, int c)
  {
    for(int i=r-1; i<=r+1; i++)
    {
      for(int j=c-1; j<=c+1; j++)
      {
        try
        {
          if(board[i][j]=='-')
          {
            boardGame[i][j]='O';
          }
          else
          {
            boardGame[i][j]=board[i][j];
          }
        }
        catch (IndexOutOfBoundsException e)
        {
          System.out.print("");
        }
      }
    }
  }

  private void placeBoats()
  {
    int boats=0;
    int boatDirection, boatX, boatY;
    if (row==3 || col==3)
    {
      boatNumber=1;
    }
    else if (row<=5 || col<=5)
    {
      boatNumber=2;
    }
    else if (row<=7 || col<=7)
    {
      boatNumber=3;
    }
    else if (row<=9 || col<=9)
    {
      boatNumber=4;
    }
    else
    {
      boatNumber=6;
    }
    while (boats<boatNumber)
    {
      boatDirection=(int)Math.floor(Math.random()*2)+1;
      boatX=(int)Math.floor(Math.random()*(row));
      boatY=(int)Math.floor(Math.random()*(col));
      if(boatDirection==1)
      {
        if(board[boatX][boatY]=='-')
        {
          if(boatX+2<row)
          {
            if(board[boatX+1][boatY]=='-')
            {
              if(board[boatX+2][boatY]=='-')
              {
                boats++;
                board[boatX][boatY]=(char)(boats+'0');
                board[boatX+1][boatY]=(char)(boats+'0');
                board[boatX+2][boatY]=(char)(boats+'0');
              }
            }
          }
        }
      }
      else
      {
        if(board[boatX][boatY]=='-')
        {
          if(boatY+2<col)
          {
            if(board[boatX][boatY+1]=='-')
            {
              if(board[boatX][boatY+2]=='-')
              {
                boats++;
                board[boatX][boatY]=(char)(boats+'0');
                board[boatX][boatY+1]=(char)(boats+'0');
                board[boatX][boatY+2]=(char)(boats+'0');
              }
            }
          }
        }
      }
    }
  }

  public void printTurn()
  {
    for(int i=0; i<row; i++)
    {
      for(int j=0; j<col; j++)
      {
        System.out.print(boardGame[i][j]+"\t");
      }
      System.out.print("\n");
    }
  }

  public void printAll()
  {
    for(int i=0; i<row; i++)
    {
      for(int j=0; j<col; j++)
      {
        if(board[i][j]=='-' || board[i][j]=='X' || board[i][j]=='O')
        {
          System.out.print(boardGame[i][j]+"\t");
        }
        else
        {
          System.out.print("["+board[i][j]+"]\t");
        }
      }
      System.out.print("\n");
    }
  }
}
