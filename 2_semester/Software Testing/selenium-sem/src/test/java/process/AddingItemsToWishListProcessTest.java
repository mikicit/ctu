package process;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import page.AuthPage;
import page.ProductPage;
import page.WishListPage;

import java.time.Duration;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

public class AddingItemsToWishListProcessTest {
    private WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
    }

    @Test
    public void addOneItemToWishListAuthorizedTest() {
        // ASSERT
        String expectedTitle = "Faded Short Sleeve T-shirts";
        AuthPage authPage = new AuthPage(driver, "http://automationpractice.com/index.php?controller=authentication&back=my-account");
        authPage.setLoginEmail("titorovichnikita@gmail.com");
        authPage.setLoginPassword("28053155");
        authPage.submitLoginForm();

        // ACT
        ProductPage productPage = new ProductPage(driver, "http://automationpractice.com/index.php?id_product=1&controller=product");
        productPage.addToWishList();

        // ASSERT
        WishListPage wishListPage = new WishListPage(driver, "http://automationpractice.com/index.php?fc=module&module=blockwishlist&controller=mywishlist");
        wishListPage.showWishList("My wishlist");

        WebElement listContainer = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.id("wishlistLinkTop")));

        List<WebElement> wishedItems = listContainer.findElements(By.cssSelector(".wlp_bought_list .product-name"));

        for (WebElement item : wishedItems) {
            if (item.getText().trim().equals(expectedTitle)) {
                assertTrue(true);
            }
        }

        fail();
    }
}
