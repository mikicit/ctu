package cz.cvut.fel.dbs.citarmik.entity;

import cz.cvut.fel.dbs.citarmik.core.PersonClassExtractor;
import org.eclipse.persistence.annotations.ClassExtractor;

import javax.persistence.*;

@Entity
@Table(
        name = "person",
        uniqueConstraints = {
            @UniqueConstraint(name = "person_data_key", columnNames = {"first_name", "last_name", "address"})
        }
)
@Inheritance(strategy = InheritanceType.JOINED)
@ClassExtractor(PersonClassExtractor.class)
public class Person {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="person_person_id_seq")
    @SequenceGenerator(name="person_person_id_seq",
            sequenceName="person_person_id_seq",
            allocationSize=1)
    @Column(name = "person_id", updatable = false)
    private long id;
    @Column(name = "email", length = 100, nullable = false, unique = true)
    private String email;
    @Column(name = "first_name", length = 32, nullable = false)
    private String firstName;
    @Column(name = "last_name", length = 32, nullable = false)
    private String lastName;
    @Column(name = "address", length = 100, nullable = false)
    private String address;
    @Column(name = "phone_number", length = 20)
    private String phoneNumber;

    public void setId(long id) {
        this.id = id;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public long getId() {
        return id;
    }

    public String getEmail() {
        return email;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getAddress() {
        return address;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }
}
