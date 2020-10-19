public class Calculator{
  private double value1;
  private double value2;

  public Calculator(double v1, double v2){
    value1=v1;
    value2=v2;
  }

  public void setValue(double v1, double v2){
    value1=v1;
    value2=v2;
  }

  public double sum(){
    return value1+value2;
  }

  public double difference(){
    return value1-value2;
  }

  public double product(){
    return value1*value2;
  }

  public double quotient(){
    return value1/value2;
  }


  public static void main(String[] args){
    Calculator c=new Calculator(0,0);
    Calculator[] table=new Calculator[20];
    double sum=0;
    c.setValue(3,4);
    System.out.println("sum "+c.sum());
    System.out.println("difference "+c.difference());
    System.out.println("product "+c.product());
    System.out.println("quotient "+c.quotient());
    for (int i=0;i<20;i++){
      Calculator t=new Calculator(i+1,i+1);
      table[i]=t;
    }
    for (int j=0;j<table.length;j++){
      sum=sum+table[j].product();
    }
    System.out.println("The sum of products is: "+sum);
  }
}
