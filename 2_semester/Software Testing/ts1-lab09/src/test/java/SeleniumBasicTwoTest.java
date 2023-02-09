import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.Keys;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.support.ui.Select;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class SeleniumBasicTwoTest {
    WebDriver driver;

    @BeforeEach
    public void setUp() {
        WebDriverManager.chromedriver().setup();
//        System.setProperty("webdriver.chrome.driver", "C:\\MC\\CVUT\\TS\\ts1-lab09\\src\\test\\resources\\chromedriver.exe");
        driver = new ChromeDriver();
    }

    @Test
    public void flightFormTest() {
        driver.get("https://flight-order.herokuapp.com");
        String text = driver.findElement(By.cssSelector("body > div > h1")).getAttribute("textContent");
        assertEquals("Flight order", text);

        driver.findElement(By.id("flight_form_firstName")).sendKeys("Honza");
        Select selectDestination = new Select(driver.findElement(By.id("flight_form_destination")));selectDestination.selectByVisibleText("London");
        driver.findElement(By.cssSelector("body > div > div > form > div > button")).click();
    }

    @Test
    public void flightFullTest() {
        // ARRANGE
        String firstName = "Tom";
        String lastName = "Ivanov";

        // ACT
        driver.get("https://flight-order.herokuapp.com");
        driver.findElement(By.id("flight_form_firstName")).sendKeys(firstName);
        driver.findElement(By.id("flight_form_lastName")).sendKeys(lastName);
        driver.findElement(By.id("flight_form_email")).sendKeys("myemail@mail.com");
        driver.findElement(By.id("flight_form_birthDate")).sendKeys("11.3.2001");

        // select destination London
        Select selectDestination = new Select(driver.findElement(By.id("flight_form_destination")));
        selectDestination.selectByVisibleText("London");

        // select discount Senior
        driver.findElement(By.id("flight_form_discount_1")).click();

        // send form
        driver.findElement(By.id("flight_form_submit")).click();

        // check outputs
        String fullName = driver.findElement(By.cssSelector("tr:nth-child(1) td")).getAttribute("textContent");

        // ASSERT
        assertEquals(firstName + " " + lastName, fullName);
    }

    @Test
    public void seleniumPageFactoryBasic() {
        // ARRANGE
        String firstName = "Tom";
        String lastName = "Ivanov";
        String email = "myemail@mail.com";
        String birthDate = "11.3.2001";

        // ACT
        FlightFormPage flightFormPage = new FlightFormPage(driver);

        flightFormPage.setFirstName(firstName);
        flightFormPage.setLastName(lastName);
        flightFormPage.setEmail(email);
        flightFormPage.setBirthDate(birthDate);
        flightFormPage.sendForm();

        // ASSERT
        String fullName = driver.findElement(By.cssSelector("tr:nth-child(1) td")).getAttribute("textContent");

        assertEquals(firstName + " " + lastName, fullName);
    }
}
