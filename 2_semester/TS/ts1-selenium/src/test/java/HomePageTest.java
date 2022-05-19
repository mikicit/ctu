import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import pages.HomePage;

import java.time.Duration;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class HomePageTest {
    WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));
    }

    @Test
    public void registrationLinkTest() {
        // ARRANGE
        String expectedUrl = "https://link.springer.com/signup-login?previousUrl=https%3A%2F%2Flink.springer.com%2F";

        // ACT
        HomePage homePage = new HomePage(driver, "https://link.springer.com/");
        homePage.clickRegisterLink();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }

    @Test
    public void advancedSearchLinkTest() {
        // ARRANGE
        String expectedUrl = "https://link.springer.com/advanced-search";

        // ACT
        HomePage homePage = new HomePage(driver, "https://link.springer.com/");
        homePage.clickAdvancedSearchLink();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }
}
