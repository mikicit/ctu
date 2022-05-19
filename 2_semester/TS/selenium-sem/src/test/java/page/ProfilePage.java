package page;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class ProfilePage {
    private final WebDriver driver;

    @FindBy(css = ".lnk_wishlist a")
    private WebElement linkToWishList;
    @FindBy(css = ".myaccount-link-list a[title=\"Orders\"]")
    private WebElement linkToOrders;

    public ProfilePage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public ProfilePage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }

    public void goToWishList() {
        linkToWishList.click();
    }

    public void goToOrders() {
        linkToOrders.click();
    }
}
