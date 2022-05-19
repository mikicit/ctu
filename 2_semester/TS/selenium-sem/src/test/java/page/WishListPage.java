package page;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class WishListPage {
    private final WebDriver driver;

    @FindBy(id = "block-history")
    private WebElement wishListBlock;

    public WishListPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public WishListPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }

    public void showWishList(String name) {
        WebElement link = wishListBlock.findElement(By.linkText(name));
        link.click();
    }
}
