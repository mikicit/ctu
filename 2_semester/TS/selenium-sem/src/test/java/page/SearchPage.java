package page;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;
import org.openqa.selenium.support.ui.Select;

import java.util.List;

public class SearchPage {
    private final WebDriver driver;

    @FindBy(className = "search_query")
    private WebElement searchInput;
    @FindBy(className = "button-search")
    private WebElement buttonSearch;
    @FindBy(className = "selectProductSort")
    private WebElement selectProductSort;
    @FindBy(className = "product-container")
    private List<WebElement> products;

    public SearchPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public SearchPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }

    public void setSearchRequest(String request) {
        searchInput.clear();
        searchInput.sendKeys(request);
    }

    public void submitSearchForm() {
        buttonSearch.click();
    }

    public void setSortBy(String sortBy) {
        Select select = new Select(this.selectProductSort);
        select.selectByValue(sortBy);
    }

    public void clickProductMore(int number) {
        if (products.size() > number - 1) {
            Actions actions = new Actions(driver);

            WebElement product = products.get(number - 1);

            actions.moveToElement(product).perform();
            product.findElement(By.cssSelector(".button.lnk_view")).click();
        }
    }
}
