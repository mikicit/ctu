package page;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.List;

public class ShoppingCartPage {
    private final WebDriver driver;

    @FindBy(className = "cart_item")
    private List<WebElement> products;

    public ShoppingCartPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public ShoppingCartPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }
}
