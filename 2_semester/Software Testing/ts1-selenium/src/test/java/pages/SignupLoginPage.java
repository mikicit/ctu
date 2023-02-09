package pages;

import org.openqa.selenium.By;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.List;

public class SignupLoginPage {
    private final WebDriver driver;

    // Login
    @FindBy(id = "login-box-email")
    private WebElement loginEmailField;

    @FindBy(id = "login-box-pw")
    private WebElement loginPasswordField;

    private WebElement loginFormSubmitButton;

    // Registration
    @FindBy(id = "first-name")
    private WebElement signupFirstNameField;

    @FindBy(id = "last-name")
    private WebElement signupLastNameField;

    @FindBy(id = "email-address")
    private WebElement signupEmailField;

    @FindBy(id = "password")
    private WebElement signupPasswordField;

    @FindBy(id = "password-confirm")
    private WebElement signupPasswordConfirmField;

    private WebElement signupFormSubmitButton;

    public SignupLoginPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);

        closeCookies();
        closePopup();

        loginFormSubmitButton = driver.findElement(By.cssSelector(".btn[title='Log in']"));
        signupFormSubmitButton = driver.findElement(By.cssSelector(".btn[title='Create account']"));
    }

    public SignupLoginPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);

        // Cookies button
        try {
            driver.findElement(By.cssSelector("button[data-cc-action='accept']")).click();
        } catch (NoSuchElementException e) {}

        loginFormSubmitButton = driver.findElement(By.cssSelector(".btn[title='Log in']"));
        signupFormSubmitButton = driver.findElement(By.cssSelector(".btn[title='Create account']"));
    }

    public void setLoginEmail(String email) {
        this.loginEmailField.sendKeys(email);
    }

    public void setLoginPassword(String password) {
        this.loginPasswordField.sendKeys(password);
    }

    public void setSignupFirstName(String firstName) {
        this.signupFirstNameField.sendKeys(firstName);
    }

    public void setSignupLastName(String lastName) {
        this.signupLastNameField.sendKeys(lastName);
    }

    public void setSignupEmail(String email) {
        this.signupEmailField.sendKeys(email);
    }

    public void setSignupPassword(String password) {
        this.signupPasswordField.sendKeys(password);
    }

    public void setSignupPasswordConfirm(String password) {
        this.signupPasswordConfirmField.sendKeys(password);
    }

    public void sendLoginForm() {
        loginFormSubmitButton.click();
    }

    public void sendSignupForm() {
        Actions actions = new Actions(driver);
        actions.moveToElement(signupFormSubmitButton);

        signupFormSubmitButton.click();
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
