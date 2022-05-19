import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import pages.AdvancedSearchPage;

import java.time.Duration;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class AdvancedSearchTest {
    WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(2));
    }

    @Test
    public void basicTest() {
        // ARRANGE
        String expectedUrl = "https://link.springer.com/search?query=Page+AND+Object+AND+Model+AND+%28Sellenium+OR+Testing%29&date-facet-mode=in&facet-start-year=2022&showAll=true";

        // ACT
        AdvancedSearchPage advancedSearchPage = new AdvancedSearchPage(driver);
        advancedSearchPage.setAllWords("Page Object Model");
        advancedSearchPage.setLeastWords("Sellenium Testing");
        advancedSearchPage.setDateFacetModeToIn();
        advancedSearchPage.setFacetStartYear("2022");
        advancedSearchPage.sendForm();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }
}
