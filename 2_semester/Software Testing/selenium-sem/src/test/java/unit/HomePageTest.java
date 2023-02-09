package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import page.HomePage;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class HomePageTest {
    WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
    }

    @Test
    public void authLinkLinkTest() {
        // ARRANGE
        String expectedUrl = "http://automationpractice.com/index.php?controller=authentication&back=my-account";

        // ACT
        HomePage homePage = new HomePage(driver, "http://automationpractice.com/");
        homePage.authLinkClick();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }

    @Test
    public void shoppingCartLinkTest() {
        // ARRANGE
        String expectedUrl = "http://automationpractice.com/index.php?controller=order";

        // ACT
        HomePage homePage = new HomePage(driver, "http://automationpractice.com/");
        homePage.shoppingCartClick();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }

    @Test
    public void searchFormInputTest() {
        // ARRANGE
        String expected = "test";

        // ACT
        HomePage homePage = new HomePage(driver, "http://automationpractice.com/");
        homePage.setSearchRequest("test");

        // ASSERT
        assertEquals(expected, driver.findElement(By.className("search_query")).getAttribute("value"));
    }
}
