package hm2;

public class Calculator {
    public int add(int a, int b) {
        return a + b;
    }

    public int subtract(int a, int b) {
        return a - b;
    }

    public int multiply(int a, int b) {
       return a * b;
    }

    public int divide(int a, int b) throws Exception {
        if (a == 0) {
            throw new Exception("Illegal operation, division by zero!");
        }

        return a / b;
    }
}
