package cz.cvut.fel.pjv;

public class Lab02 {
   public void start(String[] args) {
      homework();
   }

   public void homework()
   {
      TextIO textIO = new TextIO();
      String nextLine = textIO.getLine();
      int nextLineNumber = 1;
      byte counter = 0;
      double[] numbers = new double[10];

      while (nextLine.length() > 0) {
         if (TextIO.isDouble(nextLine)) {
            numbers[counter] = Double.parseDouble(nextLine);
            counter++;
         } else {
            System.out.println("A number has not been parsed from line " + nextLineNumber);
         }
         
         boolean wasPrinted = false;

         if (counter >= 10) {
            printCalculationLine(numbers, 10);

            counter = 0;
            wasPrinted = true;
            numbers = new double[10];
         }

         nextLine = textIO.getLine();

         if (nextLine.length() == 0) {
            System.out.println("End of input detected!");
  
            if (wasPrinted == false && counter > 1) {
               printCalculationLine(numbers, counter);
            }
         }

         nextLineNumber++;
      }
   }

   public double calculateAverage(double[] numbers, int quantity)
   {
      double result = 0;

      for (int i = 0; i < quantity; i++) {
         result += numbers[i];
      }

      result = result / quantity;

      return result;
   }

   public double calculateDeviation(double[] numbers, double avarage, int quantity)
   {
      double deviation;
      double dispersion;

      double[] squaredDeviations = new double[quantity];

      for (int i = 0; i < quantity; i++) {
         squaredDeviations[i] = Math.pow(numbers[i] - avarage, 2);
      }

      dispersion = calculateAverage(squaredDeviations, quantity);
      deviation = Math.sqrt(dispersion);

      return deviation;
   }

   public void printCalculationLine(double[] numbers, int quantity)
   {
      double avarage = calculateAverage(numbers, quantity);
      double deviation = calculateDeviation(numbers, avarage, quantity);

      System.out.printf("%2d %.3f %.3f%n", quantity, avarage, deviation);
   }
}