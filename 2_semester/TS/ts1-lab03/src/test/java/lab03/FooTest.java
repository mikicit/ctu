package lab03;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class FooTest {
    Foo foo;

    @BeforeEach
    public void singleTestSetup() {
        foo = new Foo();
    }

    @Test
    public void returnNumber_returnSpecificNumber_five() {
        // ARRANGE
        int expectedValue = 5;

        // ACT
        int result = foo.returnNumber();

        // ASSERT
        Assertions.assertEquals(expectedValue, result);
    }

    @Test
    public void getNum_returnCurrentNumber_exists() {
        // ARRANGE
        int expectedValue = 0;

        // ACT
        int result = foo.getNum();

        // ASSERT
        Assertions.assertEquals(expectedValue, result);
    }

    @Test
    public void increment_incrementingValueByOne_one() {
        // ARRANGE
        int expectedValue = foo.getNum() + 1;

        // ACT
        foo.increment();

        // ASSERT
        Assertions.assertEquals(expectedValue, foo.getNum());
    }

    @Test
    public void exceptionThrown_callingMethod_exception() throws Exception {
        // ACT + ASSERT
        Assertions.assertThrows(Exception.class, () -> {
           foo.exceptionThrown();
        });
    }
}
