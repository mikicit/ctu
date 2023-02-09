package page;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;
import java.util.List;

public class CategoryPage {
    private final WebDriver driver;

    @FindBy(className = "selectProductSort")
    private WebElement selectProductSort;
    @FindBy(className = "product-container")
    private List<WebElement> products;

    public CategoryPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public CategoryPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }

    // Controls

    public void setSortBy(String sortBy) {
        Select select = new Select(selectProductSort);
        select.selectByValue(sortBy);
    }

    public void goToProductPage(int number) {
        if (products.size() > number - 1) {
            Actions actions = new Actions(driver);

            WebElement product = products.get(number - 1);

            actions.moveToElement(product).perform();
            product.findElement(By.cssSelector(".button.lnk_view")).click();
        }
    }

    public void addToCart(int number) {
        if (products.size() > number - 1) {
            Actions actions = new Actions(driver);

            WebElement product = products.get(number - 1);

            actions.moveToElement(product).perform();
            product.findElement(By.cssSelector(".ajax_add_to_cart_button")).click();
        }
    }

    public void addToWishList(int number) {
        if (products.size() > number - 1) {
            Actions actions = new Actions(driver);

            WebElement product = products.get(number - 1);

            actions.moveToElement(product).perform();
            product.findElement(By.cssSelector(".addToWishlist")).click();
        }
    }

    public void popupClose() {
        WebElement closeButton = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.cssSelector("#layer_cart .cross")));

        closeButton.click();
    }

    public void popupContinueShopping() {
        WebElement continueButton = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.cssSelector("#layer_cart .button-container .continue.btn")));

        continueButton.click();
    }

    public void popupToShoppingCart() {
        WebElement toShoppingCartButton = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.cssSelector("#layer_cart .button-container a.btn.btn-default")));

        toShoppingCartButton.click();
    }

    public void wishListPopupClose() {
        WebElement closeButton = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.cssSelector(".fancybox-overlay a[title=\"Close\"]")));

        closeButton.click();
    }

    // Getters


    // Checkers
    public boolean isPopup() {
        try {
            WebElement popup = new WebDriverWait(driver, Duration.ofSeconds(10))
                    .until(ExpectedConditions.elementToBeClickable(By.id("layer_cart")));
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public boolean isWishListPopup() {
        try {
            WebElement popup = new WebDriverWait(driver, Duration.ofSeconds(10))
                    .until(ExpectedConditions.elementToBeClickable(By.className("fancybox-overlay")));
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}
