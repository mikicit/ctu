import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.security.Key;

public class FlightFormPage {
    private final WebDriver driver;

    @FindBy(id = "flight_form_firstName")
    private WebElement firstName;

    @FindBy(id = "flight_form_lastName")
    private WebElement lastName;

    @FindBy(id = "flight_form_email")
    private WebElement email;

    @FindBy(id = "flight_form_birthDate")
    private WebElement birthDate;

    @FindBy(id = "flight_form_submit")
    private WebElement sendButton;

    public FlightFormPage(WebDriver driver) {
        this.driver = driver;
        driver.get("https://flight-order.herokuapp.com");

        PageFactory.initElements(driver, this);
    }

    public void setFirstName(String firstName) {
        this.firstName.sendKeys(firstName);
    }

    public void setLastName(String lastName) {
        this.lastName.sendKeys(lastName);
    }

    public void setEmail(String email) {
        this.email.sendKeys(email);
    }

    public void setBirthDate(String birthDate) {
        this.birthDate.sendKeys(birthDate);
    }

    public void sendForm() {
        sendButton.click();
    }
}
