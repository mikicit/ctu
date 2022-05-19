package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import page.SearchPage;
import page.ShoppingCartPage;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ShoppingCartPageTest {
    private WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
    }

    @Test
    public void emptyCartTest() {
        // ARRANGE
        String expectedQueryString = "Your shopping cart is empty.";

        // ACT
        ShoppingCartPage shoppingCartPage = new ShoppingCartPage(driver, "http://automationpractice.com/index.php?controller=order");

        // ASSERT
        assertEquals(expectedQueryString, driver.findElement(By.className("alert-warning")).getText());
    }
}
