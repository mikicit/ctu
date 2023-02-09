package hm2;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;
import org.junit.jupiter.params.provider.CsvSource;

public class CalculatorTest {
    Calculator calculator;

    @BeforeEach
    public void initTest() {
        calculator = new Calculator();
    }

    @Test
    public void add_sumOfTwoAndFive_seven() {
        // ARRANGE
        int expectedValue = 7;

        // ACT
        int result = calculator.add(2, 5);

        // ASSERT
        Assertions.assertEquals(expectedValue, result);
    }

    @Test
    public void subtract_eightMinusFive_three() {
        // ARRANGE
        int expectedValue = 3;

        // ACT
        int result = calculator.subtract(8, 5);

        // ASSERT
        Assertions.assertEquals(expectedValue, result);
    }

    @Test
    public void multiply_twoTimesThree_six() {
        // ARRANGE
        int expectedValue = 6;

        // ACT
        int result = calculator.multiply(2, 3);

        // ASSERT
        Assertions.assertEquals(expectedValue, result);
    }

    @Test
    public void divide_sixByThree_two() throws Exception {
        // ARRANGE
        int expectedValue = 2;

        //  ACT
        int result = calculator.divide(6, 3);

        // ASSERT
        Assertions.assertEquals(expectedValue, result);
    }

    @Test
    public void divide_byZero_exception() throws Exception {
        // ACT + ASSERT
        Assertions.assertThrows(Exception.class, () -> {
            calculator.divide(0, 5);
        });
    }

    @ParameterizedTest(name = "{0} plus {1} should be equal to {2}")
    @CsvFileSource(resources = "/data.csv", numLinesToSkip = 1)
    public void add_addsAandB_returnsC(int a, int b, int c) {
        // arrange
        int expectedResult = c;

        // act
        int result = calculator.add(a, b);

        // assert
        Assertions.assertEquals(expectedResult, result);
    }
}
