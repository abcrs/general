import java.util.Scanner;

public class perfectnum {
  public static void main(String[] args) {
    Scanner scn=new Scanner(System.in);
    int limit;
    int n=1;
    int factorsum;
    int i;
    System.out.print("Enter the upper limit: ");
    limit=scn.nextInt();
    while (n<=limit) {
      factorsum=0;
      i=1;
      while (i<n) {
        if (n%i==0){
          factorsum=factorsum+i;
        }
        i++;
      }
      if (factorsum==n){
        System.out.println(n+" is a perfect number!");
      }
      n++;
    }

  }
}
