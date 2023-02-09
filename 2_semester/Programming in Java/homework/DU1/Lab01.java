package cz.cvut.fel.pjv;

import java.util.Scanner;

public class Lab01 {
   
   public void start(String[] args) {
     homework();
   }

   public void homework()
   {
      Scanner sc = null;

      try {
         sc = new Scanner(System.in);
         System.out.println("Vyber operaci (1-soucet, 2-rozdil, 3-soucin, 4-podil):");

         int operationId = sc.nextInt();

         if (operationId < 1 || operationId > 4) {
            throw new Exception("Chybna volba!");
         }

         System.out.println(getXPrint(operationId));
         double x = sc.nextDouble();

         System.out.println(getYPrint(operationId));
         double y = sc.nextDouble();

         String sign = "";
         double result = 0;

         switch (operationId) {
            case 1:
               result = addition(x, y);
               sign = "+";
               break;
            case 2:
               result = subtraction(x, y);
               sign = "-";
               break;
            case 3:
               result = multiplication(x, y);
               sign = "*";
               break;
            case 4:
               result = division(x, y);
               sign = "/";
               break;
         }

         System.out.println("Zadej pocet desetinnych mist: ");
         int numberOfDecimalPlaces = sc.nextInt();

         if (numberOfDecimalPlaces < 0) {
            throw new Exception("Chyba - musi byt zadane kladne cislo!");
         }

         String numberFormat = "%."+ numberOfDecimalPlaces + "f";

         System.out.printf(numberFormat + " " + sign + " " + numberFormat + " = " + numberFormat + "%n", x, y, result); // todo 
      } catch(Exception e) {
         System.out.println(e.getMessage());
      } finally {
         if (sc != null) {
            sc.close();
         }
      }
   }

   public double addition(double x, double y)
   {
      return x + y;
   }

   public double subtraction(double x, double y)
   {
      return x - y;
   }

   public double multiplication(double x, double y)
   {
      return x * y;
   }

   public double division(double x, double y) throws Exception
   {
      if (y == 0) {
         throw new Exception("Pokus o deleni nulou!");
      }

      return x / y;
   }

   public String getXPrint(int operationId)
   {
      String result = "";

      switch (operationId) {
         case 1:
            result = "Zadej scitanec: ";
            break;
         case 2:
            result = "Zadej mensenec: ";
            break;
         case 3:
            result = "Zadej cinitel: ";
            break;
         case 4:
            result = "Zadej delenec: ";
            break;
      }

      return result;
   }

   public String getYPrint(int operationId)
   {
      String result = "";

      switch (operationId) {
         case 1:
            result = "Zadej scitanec: ";
            break;
         case 2:
            result = "Zadej mensitel: ";
            break;
         case 3:
            result = "Zadej cinitel: ";
            break;
         case 4:
            result = "Zadej delitel: ";
            break;
      }

      return result;
   }
}