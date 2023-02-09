package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import page.AuthPage;
import page.ProductPage;

import java.time.Duration;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ProductPageTest {
    private WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/product-data.csv")
    public void addToCartTest(String quantity, String color, String size) {
        // ACT
        ProductPage productPage = new ProductPage(driver, "http://automationpractice.com/index.php?id_product=5&controller=product");
        productPage.setQuantity(quantity);
        productPage.setSize(size);
        productPage.setColor(color);
        productPage.addToCart();

        WebElement layerCart = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.id("layer_cart")));

        String[] attributes = layerCart.findElement(By.id("layer_cart_product_attributes")).getText().split(",");
        String resultColor = attributes[0].trim();
        String resultSize = attributes[1].trim();
        String resultQuantity = driver.findElement(By.id("layer_cart_product_quantity")).getText();

        // ASSERT
        assertEquals(quantity, resultQuantity);
        assertEquals(size, resultSize);
        assertEquals(color, resultColor);
    }

    @Test
    public void addToWishListNotAuthorizedTest() {
        // ARRANGE
        String expected = "You must be logged in to manage your wishlist.";

        // ACT
        ProductPage productPage = new ProductPage(driver, "http://automationpractice.com/index.php?id_product=5&controller=product");
        productPage.addToWishList();

        String result = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.className("fancybox-error"))).getText();

        // ASSERT
        assertEquals(expected, result);
    }

    @Test
    public void addToWishListAuthorizedTest() {
        // ARRANGE
        String expected = "Added to your wishlist.";

        // ACT
        AuthPage authPage = new AuthPage(driver, "http://automationpractice.com/index.php?controller=authentication&back=my-account");
        authPage.setLoginEmail("titorovichnikita@gmail.com");
        authPage.setLoginPassword("28053155");
        authPage.submitLoginForm();

        ProductPage productPage = new ProductPage(driver, "http://automationpractice.com/index.php?id_product=5&controller=product");
        productPage.addToWishList();

        String result = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.className("fancybox-error"))).getText();

        // ASSERT
        assertEquals(expected, result);
    }
}
