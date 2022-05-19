package cz.fel.cvut.ts1;

public class Username {
    public long factorial(int n) {
        if (n == 0) return 1;
        if (n < 0) return -1;

        return n * factorial(n - 1);
    }
}
