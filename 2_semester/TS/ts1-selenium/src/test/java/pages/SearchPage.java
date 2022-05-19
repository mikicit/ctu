package pages;

import org.openqa.selenium.*;
import org.openqa.selenium.support.PageFactory;

import java.util.ArrayList;
import java.util.List;

public class SearchPage {
    private final WebDriver driver;

    public SearchPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);

        closeCookies();
        closePopup();
    }

    public SearchPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);

        // Cookies button
        try {
            driver.findElement(By.cssSelector("button[data-cc-action='accept']")).click();
        } catch (NoSuchElementException e) {}
    }

    public void setContentType(String type) {
        WebElement contentType = driver.findElement(By.id("content-type-facet"));
        List<WebElement> links = contentType.findElements(By.className("facet-link"));

        for (WebElement element : links) {
            if (element.findElement(By.className("facet-title")).getText().equals(type)) {
                element.click();
                break;
            }
        }
    }

    public void setPage(int page) {
        WebElement pageNumberField = driver.findElement(By.cssSelector("input[name='go-to-page']"));
        pageNumberField.clear();
        pageNumberField.sendKeys(String.valueOf(page));
        pageNumberField.sendKeys(Keys.ENTER);
    }

    public ArrayList<String> getResultsLinks(int quantity) {
        WebElement resultList = driver.findElement(By.id("results-list"));
        List<WebElement> elements = resultList.findElements(By.className("title"));
        ArrayList<String> links = new ArrayList<>();


        if (elements.size() < quantity) {
            for (WebElement element : elements) {
                links.add(element.getAttribute("href"));
            }

            return links;
        }

        for (WebElement element : elements.subList(0, quantity)) {
            links.add(element.getAttribute("href"));
        }

        return links;
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
