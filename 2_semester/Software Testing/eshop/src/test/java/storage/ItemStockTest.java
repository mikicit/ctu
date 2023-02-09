package storage;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.ValueSource;
import shop.Order;
import shop.StandardItem;

import static org.junit.jupiter.api.Assertions.*;

public class ItemStockTest {
    StandardItem standardItem;
    ItemStock itemStock;

    @BeforeEach
    public void initTest() {
        standardItem = new StandardItem(1, "Test item", (float) 30.1, "Test category", 10);
    }

    @Test
    public void constructorTest() {
        // ARRANGE
        int expectedCount = 0;

        // ACT
        ItemStock itemStock = new ItemStock(standardItem);

        // ASSERT
        assertEquals(expectedCount, itemStock.getCount());
        assertSame(standardItem, itemStock.getItem());
    }

    @Test
    public void increaseItemArgumentLessThanOne() {
        // ACT + ASSERT
        assertThrows(IllegalArgumentException.class, () -> {
            new ItemStock(standardItem).IncreaseItemCount(-5);
        });
    }

    @Test
    public void decreaseItemArgumentLessThanOne() {
        // ACT + ASSERT
        assertThrows(IllegalArgumentException.class, () -> {
            new ItemStock(standardItem).decreaseItemCount(-5);
        });
    }

    @ParameterizedTest()
    @CsvSource(value = {"0:1:1", "1:2:3", "1:1:2", "3:10:13"}, delimiter = ':')
    public void increaseItemCountTest(int initialCount, int count, int expected) {
        // ACT
        ItemStock itemStock = new ItemStock(standardItem);
        itemStock.setCount(initialCount);
        itemStock.IncreaseItemCount(count);

        // ASSERT
        assertEquals(expected, itemStock.getCount());
    }

    @ParameterizedTest()
    @CsvSource(value = {"0:1:0", "0:2:0", "1:10:0", "10:5:5"}, delimiter = ':')
    public void decreaseItemCountTest(int initialCount, int count, int expected) {
        // ACT
        ItemStock itemStock = new ItemStock(standardItem);
        itemStock.setCount(initialCount);
        itemStock.decreaseItemCount(count);

        // ASSERT
        assertEquals(expected, itemStock.getCount());
    }
}
