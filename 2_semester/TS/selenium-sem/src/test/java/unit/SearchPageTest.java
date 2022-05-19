package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import page.SearchPage;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class SearchPageTest {
    private WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
    }

    @Test
    public void searchWithResultsTest() {
        // ARRANGE
        String expectedQueryString = "\"printed summer dress\"";

        // ACT
        SearchPage searchPage = new SearchPage(driver, "http://automationpractice.com/index.php?controller=search");
        searchPage.setSearchRequest("Printed Summer Dress");
        searchPage.submitSearchForm();

        // ASSERT
        assertEquals(expectedQueryString, driver.findElement(By.cssSelector(".product-listing .lighter")).getText().toLowerCase());
    }

    @Test
    public void searchWithNoResultsTest() {
        // ARRANGE
        String expectedQueryString = "no results were found for your search \"test\"";

        // ACT
        SearchPage searchPage = new SearchPage(driver, "http://automationpractice.com/index.php?controller=search");
        searchPage.setSearchRequest("test");
        searchPage.submitSearchForm();

        // ASSERT
        assertEquals(expectedQueryString, driver.findElement(By.className("alert-warning")).getText().toLowerCase());
    }
}
