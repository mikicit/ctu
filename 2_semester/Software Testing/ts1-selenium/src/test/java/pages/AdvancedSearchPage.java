package pages;

import org.openqa.selenium.By;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;
import org.openqa.selenium.support.ui.Select;

import java.util.List;

public class AdvancedSearchPage {
    private final WebDriver driver;

    @FindBy(id = "all-words")
    private WebElement allWords;

    @FindBy(id = "exact-phrase")
    private WebElement exactPhrase;

    @FindBy(id = "least-words")
    private WebElement leastWords;

    @FindBy(id = "without-words")
    private WebElement withoutWords;

    @FindBy(id = "title-is")
    private WebElement titleIs;

    @FindBy(id = "date-facet-mode")
    private WebElement dateFacetMode;

    @FindBy(id = "facet-start-year")
    private WebElement facetStartYear;

    @FindBy(id = "submit-advanced-search")
    private WebElement submitButton;

    public AdvancedSearchPage(WebDriver driver) {
        this.driver = driver;
        driver.get("https://link.springer.com/advanced-search");

        PageFactory.initElements(driver, this);

        closeCookies();
        closePopup();
    }

    public AdvancedSearchPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);

        // Cookies button
        try {
            driver.findElement(By.cssSelector("button[data-cc-action='accept']")).click();
        } catch (NoSuchElementException e) {}
    }

    public void setAllWords(String text) {
        this.allWords.sendKeys(text);
    }

    public void setExactPhrase(String text) {
        this.exactPhrase.sendKeys(text);
    }

    public void setLeastWords(String text) {
        this.leastWords.sendKeys(text);
    }

    public void setWithoutWords(String text) {
        this.withoutWords.sendKeys(text);
    }

    public void setTitleIsWords(String text) {
        this.titleIs.sendKeys(text);
    }

    public void setDateFacetModeToIn() {
        Select select = new Select(this.dateFacetMode);
        select.selectByIndex(1);
    }

    public void setFacetStartYear(String year) {
        this.facetStartYear.clear();
        this.facetStartYear.sendKeys(year);
    }

    public void sendForm() {
        this.submitButton.click();
    }

    public void closeCookies() {
        try {
            driver.findElement(By.cssSelector("button[data-cc-action='accept']")).click();
        } catch (NoSuchElementException e) {}
    }

    public void closePopup() {
        try {
            WebElement window = driver.findElement(By.className("QSIWebResponsive"));
            List<WebElement> buttons = window.findElements(By.cssSelector("button"));

            for (WebElement button : buttons) {
                if (button.getText().equals("No Thanks")) {
                    button.click();
                    break;
                }
            }

        } catch (NoSuchElementException e) {}
    }
}
