package pages;

import org.openqa.selenium.*;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.List;

public class ArticlePage {
    WebDriver driver;

    @FindBy(className = "c-article-title")
    private WebElement name;

    @FindBy(css = ".c-article-header time")
    private WebElement date;

    @FindBy(css = ".c-bibliographic-information__list-item--doi .c-bibliographic-information__value")
    private WebElement doi;

    public ArticlePage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);

        closeCookies();
        closePopup();
    }

    public ArticlePage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);

        // Cookies button
        try {
            driver.findElement(By.cssSelector("button[data-cc-action='accept']")).click();
        } catch (NoSuchElementException e) {}
    }

    public String getName() {
        return name.getText();
    }

    public String getDate() {
        return date.getText();
    }

    public String getDOI() {
        return doi.getText();
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
