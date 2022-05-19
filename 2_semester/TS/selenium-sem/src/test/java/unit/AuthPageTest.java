package unit;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;
import org.openqa.selenium.By;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import page.AuthPage;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class AuthPageTest {
    WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
        driver = new ChromeDriver();
        driver.manage().window().setPosition(new Point(0,0));
        driver.manage().window().setSize(new Dimension(1600,900));
    }

    @Test
    public void validRegistrationTest() {
        // ARRANGE
        String expectedUrl = "http://automationpractice.com/index.php?controller=my-account";

        // ACT

        // Personal
        AuthPage authPage = new AuthPage(driver, "http://automationpractice.com/index.php?controller=authentication&back=my-account");
        authPage.setFirstRegistrationEmail("test145443@gmail.com");
        authPage.submitRegistrationStartForm();
        authPage.setRegistrationGender("m");
        authPage.setRegistrationFirstName("Mikita");
        authPage.setRegistrationLastName("Citarovic");
        authPage.setRegistrationPassword("28053155");
        authPage.setRegistrationDOBDay("23");
        authPage.setRegistrationDOBMonth("December ");
        authPage.setRegistrationDOBYear("1997");

        // Address
        authPage.setAddressFirstName("Mikita");
        authPage.setAddressLastName("Citarovic");
        authPage.setAddressCompany("MCCorp");
        authPage.setAddressAddressOne("Thakurova");
        authPage.setAddressAddressTwo("1");
        authPage.setAddressCity("Prague");
        authPage.setAddressState("Alaska");
        authPage.setAddressPostalCode("16000");
        authPage.setAddressCountry("United States");
        authPage.setAddressOther("Test");
        authPage.setAddressHomePhone("420606169911");
        authPage.setAddressMobilePhone("420606169911");
        authPage.setAddressAlias("420606169911");

        authPage.submitRegistrationForm();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }

    @Test
    public void validLoginTest() {
        // ARRANGE
        String expectedUrl = "http://automationpractice.com/index.php?controller=my-account";

        // ACT
        AuthPage authPage = new AuthPage(driver, "http://automationpractice.com/index.php?controller=authentication&back=my-account");
        authPage.setLoginEmail("titorovichnikita@gmail.com");
        authPage.setLoginPassword("28053155");
        authPage.submitLoginForm();

        // ASSERT
        assertEquals(expectedUrl, driver.getCurrentUrl());
    }

    @ParameterizedTest
    @CsvFileSource(resources = "/invalid-login-data.csv")
    public void invalidLoginTest(String email, String password, String expectedResult) {
        // ACT
        AuthPage authPage = new AuthPage(driver, "http://automationpractice.com/index.php?controller=authentication&back=my-account");
        authPage.setLoginEmail(email);
        authPage.setLoginPassword(password);
        authPage.submitLoginForm();

        String result = driver.findElement(By.cssSelector(".alert-danger ol li")).getText();

        // ASSERT
        assertEquals(expectedResult, result);
    }
}
