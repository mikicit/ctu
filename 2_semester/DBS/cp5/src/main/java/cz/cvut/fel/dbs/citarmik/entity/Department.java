package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.List;

@Entity
@Table(
        name = "department",
        uniqueConstraints = {
                @UniqueConstraint(name = "department_address_key", columnNames = {"city", "postal_code", "street"})
        }
)
public class Department {
    @Id
    @SequenceGenerator(name="department_department_id_seq",
            sequenceName="department_department_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="department_department_id_seq")
    @Column(name = "department_id", updatable = false)
    private long id;
    @Column(name = "department_number", nullable = false, unique = true)
    private Integer departmentNumber;
    @Column(name = "city", length = 32, nullable = false)
    private String city;
    @Column(name = "postal_code", length = 32, nullable = false)
    private String postalCode;
    @Column(name = "street", length = 32, nullable = false)
    private String street;

    @OneToMany(mappedBy = "department", fetch = FetchType.LAZY)
    private List<AcceptedPackage> acceptedPackages;
    @OneToMany(mappedBy = "department", fetch = FetchType.LAZY)
    private List<SentPackage> sentPackages;
    @OneToMany(mappedBy = "department", fetch = FetchType.LAZY)
    private List<Employee> employees;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Integer getDepartmentNumber() {
        return departmentNumber;
    }

    public void setDepartmentNumber(Integer departmentNumber) {
        this.departmentNumber = departmentNumber;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getPostalCode() {
        return postalCode;
    }

    public void setPostalCode(String postalCode) {
        this.postalCode = postalCode;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    public List<AcceptedPackage> getAcceptedPackages() {
        return acceptedPackages;
    }

    public void setAcceptedPackages(List<AcceptedPackage> acceptedPackages) {
        this.acceptedPackages = acceptedPackages;
    }

    public List<SentPackage> getSentPackages() {
        return sentPackages;
    }

    public void setSentPackages(List<SentPackage> sentPackages) {
        this.sentPackages = sentPackages;
    }

    public List<Employee> getEmployees() {
        return employees;
    }

    public void setEmployees(List<Employee> employees) {
        this.employees = employees;
    }
}
