import java.util.Scanner;

public class ConvertRoman{
  public static Integer convertDigit(char letter){
    char digits[]=new char[]{'I','V','X','L','C','D','M'};
    int values[]=new int[]{1,5,10,50,100,500,1000};
    int i=0;
    while (i<digits.length && letter!=digits[i]){
      i++;
    }
    if (i<digits.length){
      return values[i];
    }
    return 0;
  }

  public static Integer convertRoman(String istr){
    int lastvalue=0;
    int decimalval=0;
    int currentval;
    char[] numeral=istr.toCharArray();
    for (char c: numeral){
      currentval=convertDigit(c);
      if (lastvalue<currentval){
        decimalval=decimalval-lastvalue;
      }
      else {
        decimalval=decimalval+lastvalue;
      }
      lastvalue=currentval;
    }
    return decimalval+lastvalue;
  }

  public static void main(String[] args) {
    boolean go=false;
    String romannumeral;
    Scanner scn=new Scanner(System.in);
    Integer value;
    while (go==false){
      System.out.print("Enter a Roman Numeral as a string: ");
      romannumeral=scn.nextLine();
      if (romannumeral.length()==0){
        go=true;
      }
      else{
        value=convertRoman(romannumeral);
        System.out.println("Decimal Value: "+value);
      }
    }
  }
}
