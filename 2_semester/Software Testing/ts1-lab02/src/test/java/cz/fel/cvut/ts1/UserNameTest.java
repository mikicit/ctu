package cz.fel.cvut.ts1;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class UsernameTest {
    @Test
    public void factorialTest() {
        Username username = new Username();
        int positive = 2;
        int negative = -1;
        int zero = 0;

        int positiveResult = 2;
        int negativeResult = -1;
        int zeroResult = 1;

        // positive testing
        long testingPositiveResult = username.factorial(positive);
        Assertions.assertEquals(positiveResult, testingPositiveResult);

        // negative testing
        long testingNegativeResult = username.factorial(negative);
        Assertions.assertEquals(negativeResult, testingNegativeResult);

        // zero testing
        long testingZeroResult = username.factorial(zero);
        Assertions.assertEquals(zeroResult, testingZeroResult);
    }
}
