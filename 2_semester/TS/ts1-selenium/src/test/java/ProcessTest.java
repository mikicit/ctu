import io.github.bonigarcia.wdm.WebDriverManager;
import org.checkerframework.checker.units.qual.A;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;
import org.junit.jupiter.params.provider.CsvSource;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import pages.*;

import java.io.*;
import java.time.Duration;
import java.time.LocalDate;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ProcessTest {
    private WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(2));
    }

    @AfterEach
    public void closeWindow() {
        driver.quit();
    }

    @Test
    public void prepareData() {
        // Home Page
        HomePage homePage = new HomePage(driver, "https://link.springer.com/");
        homePage.clickAdvancedSearchLink();

        // Advanced Search Page
        AdvancedSearchPage advancedSearchPage = new AdvancedSearchPage(driver, driver.getCurrentUrl());
        advancedSearchPage.setAllWords("Page Object Model");
        advancedSearchPage.setLeastWords("Sellenium Testing");
        advancedSearchPage.setDateFacetModeToIn();
        advancedSearchPage.setFacetStartYear(String.valueOf(LocalDate.now().getYear()));
        advancedSearchPage.sendForm();

        // Search Page
        SearchPage searchPage = new SearchPage(driver, driver.getCurrentUrl());
        searchPage.setContentType("Article");

        ArrayList<String> links = searchPage.getResultsLinks(4);

        // Data of articles
        StringBuilder dataForCSV = new StringBuilder();

        for (String link : links) {
            ArticlePage page = new ArticlePage(driver, link);
            dataForCSV.append(page.getName()).append(", ");
            dataForCSV.append(page.getDate()).append(", ");
            dataForCSV.append(page.getDOI()).append("\n");
        }

        // Writing in CSV
        try {
            FileWriter myWriter = new FileWriter("src/test/resources/data.csv");
            myWriter.write(dataForCSV.toString());
            myWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/data.csv")
    public void parameterizedTest(String name, String date, String DOI) {
        // Home
        HomePage homePage = new HomePage(driver, "https://link.springer.com/");
        homePage.clickRegisterLink();

        // Login
        SignupLoginPage signupLoginPage = new SignupLoginPage(driver);
        signupLoginPage.setLoginEmail("titorovichnikita@gmail.com");
        signupLoginPage.setLoginPassword("MikitaCitarovic123");
        signupLoginPage.sendLoginForm();

        // From home page to search
        homePage.clickAdvancedSearchLink();

        // Search
        AdvancedSearchPage advancedSearchPage = new AdvancedSearchPage(driver);
        advancedSearchPage.setTitleIsWords(name);
        advancedSearchPage.sendForm();

        // Get
        SearchPage searchPage = new SearchPage(driver);

        // Article Page
        ArticlePage articlePage = new ArticlePage(driver, searchPage.getResultsLinks(1).get(0));

        // ASSERT
        assertEquals(name, articlePage.getName());
        assertEquals(date, articlePage.getDate());
        assertEquals(DOI, articlePage.getDOI());
    }
}
