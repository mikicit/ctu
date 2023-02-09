package page;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;

public class ProductPage {
    private final WebDriver driver;

    @FindBy(id = "quantity_wanted")
    private WebElement quantityField;
    @FindBy(id = "group_1")
    private WebElement sizeSelect;
    @FindBy(css = "#add_to_cart button")
    private WebElement addToCartButton;
    @FindBy(id = "wishlist_button")
    private WebElement addToWishListLink;

    public ProductPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public ProductPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }

    public void setQuantity(String quantity) {
        quantityField.clear();
        quantityField.sendKeys(quantity);
    }

    public void setSize(String size) {
        Select select = new Select(this.sizeSelect);
        select.selectByVisibleText(size);
    }

    public void setColor(String color) {
        WebElement colorPick = driver.findElement(By.cssSelector(".color_pick[name=\"" + color +"\"]"));
        colorPick.click();
    }

    public void addToCart() {
        addToCartButton.click();
    }

    public void addToWishList() {
        addToWishListLink.click();
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
}
