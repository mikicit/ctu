package page;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;

public class AuthPage {
    private final WebDriver driver;

    // Registration

    // Start
    @FindBy(css = "input[name=\"email_create\"]")
    private WebElement firstRegistrationEmailField;
    @FindBy(css = "#create-account_form #SubmitCreate")
    private WebElement registrationStartSubmitButton;

    // Personal Info
    @FindBy(css = "#account-creation_form #id_gender1")
    private WebElement registrationGenderMaleRadio;
    @FindBy(css = "#account-creation_form #id_gender2")
    private WebElement registrationGenderFemaleRadio;
    @FindBy(css = "#account-creation_form #customer_firstname")
    private WebElement registrationFirstNameField;
    @FindBy(css = "#account-creation_form #customer_lastname")
    private WebElement registrationLastNameField;
    @FindBy(css = "#account-creation_form #email")
    private WebElement registrationEmailField;
    @FindBy(css = "#account-creation_form #passwd")
    private WebElement registrationPasswordField;
    @FindBy(css = "#account-creation_form #days")
    private WebElement registrationDOBDaysSelect;
    @FindBy(css = "#account-creation_form #months")
    private WebElement registrationDOBMonthsSelect;
    @FindBy(css = "#account-creation_form #years")
    private WebElement registrationDOBYearsSelect;

    // Address
    @FindBy(css = "#account-creation_form #firstname")
    private WebElement registrationAddressFirstNameField;
    @FindBy(css = "#account-creation_form #lastname")
    private WebElement registrationAddressLastNameField;
    @FindBy(css = "#account-creation_form #company")
    private WebElement registrationAddressCompanyField;
    @FindBy(css = "#account-creation_form #address1")
    private WebElement registrationAddressAddressOneField;
    @FindBy(css = "#account-creation_form #address2")
    private WebElement registrationAddressAddressTwoField;
    @FindBy(css = "#account-creation_form #city")
    private WebElement registrationAddressCityField;
    @FindBy(css = "#account-creation_form #id_state")
    private WebElement registrationAddressStateSelect;
    @FindBy(css = "#account-creation_form #postcode")
    private WebElement registrationAddressPostalCodeField;
    @FindBy(css = "#account-creation_form #id_country")
    private WebElement registrationAddressCountrySelect;
    @FindBy(css = "#account-creation_form #other")
    private WebElement registrationAddressOtherTextarea;
    @FindBy(css = "#account-creation_form #phone")
    private WebElement registrationAddressHomePhoneField;
    @FindBy(css = "#account-creation_form #phone_mobile")
    private WebElement registrationAddressMobilePhoneField;
    @FindBy(css = "#account-creation_form #alias")
    private WebElement registrationAddressAliasField;
    @FindBy(css = "#account-creation_form #submitAccount")
    private WebElement registrationSubmitButton;

    // Login
    @FindBy(css = "#login_form #email")
    private WebElement loginEmailField;
    @FindBy(css = "#login_form #passwd")
    private WebElement loginPasswordField;
    @FindBy(css = "#login_form #SubmitLogin")
    private WebElement submitLoginFormButton;

    public AuthPage(WebDriver driver) {
        this.driver = driver;

        PageFactory.initElements(driver, this);
    }

    public AuthPage(WebDriver driver, String queryString) {
        this.driver = driver;
        driver.get(queryString);

        PageFactory.initElements(driver, this);
    }

    // Login
    public void setLoginEmail(String email) {
        loginEmailField.sendKeys(email);
    }

    public void setLoginPassword(String password) {
        loginPasswordField.sendKeys(password);
    }

    public void submitLoginForm() {
        submitLoginFormButton.click();
    }

    // Registration

    // Personal Info
    public void setFirstRegistrationEmail(String email) {
        firstRegistrationEmailField.clear();
        firstRegistrationEmailField.sendKeys(email);
    }

    public void submitRegistrationStartForm() {
        registrationStartSubmitButton.click();

        WebElement registrationForm = new WebDriverWait(driver, Duration.ofSeconds(10))
                .until(ExpectedConditions.elementToBeClickable(By.id("account-creation_form")));
    }

    public void setRegistrationGender(String gender) {
        if (gender.equals("m")) {
            registrationGenderMaleRadio.click();
        } else if (gender.equals("f")) {
            registrationGenderFemaleRadio.click();
        }
    }

    public void setRegistrationFirstName(String firstName) {
        registrationFirstNameField.sendKeys(firstName);
    }

    public void setRegistrationLastName(String lastName) {
        registrationLastNameField.sendKeys(lastName);
    }

    public void setRegistrationEmail(String email) {
        registrationEmailField.sendKeys(email);
    }

    public void setRegistrationPassword(String password) {
        registrationPasswordField.sendKeys(password);
    }

    public void setRegistrationDOBDay(String day) {
        Select select = new Select(this.registrationDOBDaysSelect);
        select.selectByValue(day);
    }

    public void setRegistrationDOBMonth(String month) {
        Select select = new Select(this.registrationDOBMonthsSelect);
        select.selectByVisibleText(month);
    }

    public void setRegistrationDOBYear(String year) {
        Select select = new Select(this.registrationDOBYearsSelect);
        select.selectByValue(year);
    }

    // Address
    public void setAddressFirstName(String firstName) {
        registrationAddressFirstNameField.sendKeys(firstName);
    }

    public void setAddressLastName(String lastName) {
        registrationAddressLastNameField.sendKeys(lastName);
    }

    public void setAddressCompany(String company) {
        registrationAddressCompanyField.sendKeys(company);
    }

    public void setAddressAddressOne(String address) {
        registrationAddressAddressOneField.sendKeys(address);
    }

    public void setAddressAddressTwo(String address) {
        registrationAddressAddressTwoField.sendKeys(address);
    }

    public void setAddressCity(String city) {
        registrationAddressCityField.sendKeys(city);
    }

    public void setAddressState(String state)  {
        Select select = new Select(this.registrationAddressStateSelect);
        select.selectByVisibleText(state);
    }

    public void setAddressPostalCode(String postalCode) {
        registrationAddressPostalCodeField.sendKeys(postalCode);
    }

    public void setAddressCountry(String country) {
        Select select = new Select(this.registrationAddressCountrySelect);
        select.selectByVisibleText(country);
    }

    public void setAddressOther(String text) {
        registrationAddressOtherTextarea.sendKeys(text);
    }

    public void setAddressHomePhone(String phone) {
        registrationAddressHomePhoneField.sendKeys(phone);
    }

    public void setAddressMobilePhone(String phone) {
        registrationAddressMobilePhoneField.sendKeys(phone);
    }

    public void setAddressAlias(String alias) {
        registrationAddressAliasField.sendKeys(alias);
    }

    public void submitRegistrationForm() {
        registrationSubmitButton.click();
    }
}
