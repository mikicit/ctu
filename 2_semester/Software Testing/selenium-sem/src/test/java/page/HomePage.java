package page;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class HomePage {
    private final WebDriver driver;

    @FindBy(css = ".header_user_info > a.login")
    private WebElement authLink;
    @FindBy(css = ".shopping_cart > a")
    private WebElement shoppingCartClick;
    @FindBy(className = "search_query")
    private WebElement searchInput;
    @FindBy(className = "button-search")
    private WebElement buttonSearch;

    public HomePage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public HomePage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }

    public void authLinkClick() {
        authLink.click();
    }

    public void shoppingCartClick() {
        shoppingCartClick.click();
    }

    public void setSearchRequest(String request) {
        searchInput.clear();
        searchInput.sendKeys(request);
    }

    public void submitSearchForm() {
        buttonSearch.click();
    }
}
