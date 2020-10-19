import java.lang.Math;

public class BankAccount{
  private double balance;
  private String ownerName;
  private String accountNumber;

  public BankAccount(double b, String oN, String aN){
    balance=b;
    ownerName=oN;
    accountNumber=aN;
  }

  public void setBalance(double b){
    balance=b;
  }
  public void setOwner(String oN){
    ownerName=oN;
  }
  public void setAccout(String aN){
    accountNumber=aN;
  }

  public double getBalance(){
    return balance;
  }
  public String getOwner(){
    return ownerName;
  }
  public String getAccount(){
    return accountNumber;
  }

  public void deposit(double amount){
    balance=balance+amount;
  }
  public void withraw(double amount){
    balance=balance-amount;
  }

  public double compoundInterest(int numYears,double rate,int numCompounds){
    return balance*Math.pow(1+rate/numCompounds,numYears*numCompounds);
  }
  public double simpleInterest(int numYears, double rate){
    return balance*(1+rate*numYears);
  }

  public static void main(String[] args){
    BankAccount jenny=new BankAccount(1000,"Jenny","8675309");
    BankAccount thanos=new BankAccount(10000,"Thanos","626");
    BankAccount sauron=new BankAccount(10000,"Sauron","1");
    System.out.println(jenny.getAccount());
    jenny.setBalance(1050);
    System.out.println(jenny.getBalance());
    System.out.println(thanos.simpleInterest(10,.045));
    System.out.println(sauron.compoundInterest(10,.04,12));
  }
}
