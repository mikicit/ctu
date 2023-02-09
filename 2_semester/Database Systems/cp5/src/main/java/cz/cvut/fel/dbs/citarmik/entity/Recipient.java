package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;

@Entity
@Table(name = "Recipient")
public class Recipient {
    @Id
    @SequenceGenerator(name="recipient_recipient_id_seq",
            sequenceName="recipient_recipient_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="recipient_recipient_id_seq")
    @Column(name = "recipient_id", updatable = false)
    private long id;
    @OneToOne(cascade = CascadeType.PERSIST)
    @JoinColumn(name = "order_id")
    private Order order;
    @Column(name = "first_name", length = 32, nullable = false)
    private String firstName;
    @Column(name = "last_name", length = 32, nullable = false)
    private String lastName;
    @Column(name = "phone_number", length = 20, nullable = false)
    private String phoneNumber;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Order getOrder() {
        return order;
    }

    public void setOrder(Order order) {
        this.order = order;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }
}
