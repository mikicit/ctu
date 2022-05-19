package shop;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.*;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

public class StandardItemTest {
    StandardItem standardItem;

    @BeforeEach
    public void setup() {
        standardItem = new StandardItem(1, "Test item", (float) 30.1, "Test category", 10);
    }

    @Test
    public void constructorTest() {
        // ARRANGE
        int expectedId = 1;
        String expectedName = "Test name";
        float expectedPrice = (float) 30.1;
        String expectedCategory = "Test category";
        int expectedLoyaltyPoints = 10;

        // ACT
        StandardItem standardItem = new StandardItem(expectedId, expectedName, expectedPrice, expectedCategory, expectedLoyaltyPoints);

        // ASSERT
        assertEquals(expectedId, standardItem.getID());
        assertEquals(expectedName, standardItem.getName());
        assertEquals(expectedPrice, standardItem.getPrice());
        assertEquals(expectedCategory, standardItem.getCategory());
        assertEquals(expectedLoyaltyPoints, standardItem.getLoyaltyPoints());
    }

    @Test
    public void copyTest() {
        // ACT
        StandardItem copiedStandardItem = standardItem.copy();

        // ASSERT
        assertNotSame(standardItem, copiedStandardItem);
        assertEquals(standardItem, copiedStandardItem);
    }

    @ParameterizedTest()
    @MethodSource("generator")
    public void equalsWithSameObjetTest(StandardItem firstItem, StandardItem secondItem, boolean expected) {
        // ACT + ASSERT
        assertEquals(expected, firstItem.equals(secondItem));
    }

    @Test
    public void equalsWithAnotherObjectTest() {
        // ACT
        Object notStandardItem = new Object();

        // ASSERT
        assertNotEquals(standardItem, notStandardItem);
    }

    private static Stream<Arguments> generator() {
        return Stream.of(
                Arguments.of(
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 10),
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 10),
                        true
                ),
                Arguments.of(
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 10),
                        new StandardItem(2, "Test name", (float) 30.1, "Test category", 10),
                        false
                ),
                Arguments.of(
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 10),
                        new StandardItem(1, "Test", (float) 30.1, "Test category", 10),
                        false
                ),
                Arguments.of(
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 10),
                        new StandardItem(1, "Test name", (float) 54, "Test category", 10),
                        false
                ),
                Arguments.of(
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 10),
                        new StandardItem(1, "Test name", (float) 30.1, "Test", 10),
                        false
                ),
                Arguments.of(
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 10),
                        new StandardItem(1, "Test name", (float) 30.1, "Test category", 54),
                        false
                )
        );
    }
}
