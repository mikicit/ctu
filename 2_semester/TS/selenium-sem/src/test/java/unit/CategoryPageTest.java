package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import page.CategoryPage;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class CategoryPageTest {
    private static WebDriver driver;
    private static CategoryPage page;

    @BeforeAll
    public static void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
        page = new CategoryPage(driver, "http://automationpractice.com/index.php?id_category=3&controller=category");
    }

    @Test
    public void addToCartTest() {
        // ACT
        page.addToCart(1);

        // ASSERT
        assertTrue(page.isPopup());
    }

    @Test
    public void addToWishListTest() {
        // ACT
        page.addToWishList(1);

        // ASSERT
        assertTrue(page.isWishListPopup());
    }
}
