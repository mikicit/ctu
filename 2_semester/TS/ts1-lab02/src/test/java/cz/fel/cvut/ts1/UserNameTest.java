package cz.fel.cvut.ts1;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class UserNameTest {
    @Test
    public void factorialTest() {
        Username username = new Username();
        int n = 0;
        long expectedValue = 1;

        long result = username.factorial(n);

        Assertions.assertEquals(expectedValue, result);
    }
}
