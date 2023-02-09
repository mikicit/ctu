package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import page.AuthPage;
import page.WishListPage;

public class WishListPageTest {
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
    public void defaultWishListExistsTest() {
        // ACT
        WishListPage wishlistPage = new WishListPage(driver, "http://automationpractice.com/index.php?fc=module&module=blockwishlist&controller=mywishlist");

        // ASSERT
        driver.findElement(By.linkText("My wishlist"));
    }
}
