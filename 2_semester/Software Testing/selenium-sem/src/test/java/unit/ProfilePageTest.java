package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import page.AuthPage;
import page.ProfilePage;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ProfilePageTest {
    private static WebDriver driver;

    @BeforeAll
    public static void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));

        AuthPage authPage = new AuthPage(driver, "http://automationpractice.com/index.php?controller=authentication&back=my-account");
        authPage.setLoginEmail("titorovichnikita@gmail.com");
        authPage.setLoginPassword("28053155");
        authPage.submitLoginForm();
    }

    @Test
    public void wishListLinkTest() {
        // ARRANGE
        String expectedUrl = "http://automationpractice.com/index.php?fc=module&module=blockwishlist&controller=mywishlist";

        // ACT
        ProfilePage profilePage = new ProfilePage(driver, "http://automationpractice.com/index.php?controller=my-account");
        profilePage.goToWishList();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }

    @Test
    public void ordersLinkTest() {
        // ARRANGE
        String expectedUrl = "http://automationpractice.com/index.php?controller=history";

        // ACT
        ProfilePage profilePage = new ProfilePage(driver, "http://automationpractice.com/index.php?controller=my-account");
        profilePage.goToOrders();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }
}
