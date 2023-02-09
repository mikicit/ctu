package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.Date;

@Entity
@Table(name = "ClientOrder")
public class Order {
    @Id
    @SequenceGenerator(name="clientorder_order_id_seq",
            sequenceName="clientorder_order_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="clientorder_order_id_seq")
    @Column(name = "order_id", updatable = false)
    private long id;
    @ManyToOne(cascade = CascadeType.REMOVE)
    @JoinColumn(name = "client_id", nullable = false)
    private Client client;
    @ManyToOne()
    @JoinColumn(name = "department_from_id", nullable = false)
    private Department departmentFrom;
    @ManyToOne()
    @JoinColumn(name = "department_to_id", nullable = false)
    private Department departmentTo;
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "creaiton_date_time", nullable = false)
    private Date creationDateTime;
    @Column(name = "price", nullable = false, precision = 6, scale = 2)
    private Float price;
    @OneToOne(mappedBy = "order", cascade = CascadeType.PERSIST)
    private Recipient recipient;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public Department getDepartmentFrom() {
        return departmentFrom;
    }

    public void setDepartmentFrom(Department departmentFrom) {
        this.departmentFrom = departmentFrom;
    }

    public Department getDepartmentTo() {
        return departmentTo;
    }

    public void setDepartmentTo(Department departmentTo) {
        this.departmentTo = departmentTo;
    }

    public Date getCreationDateTime() {
        return creationDateTime;
    }

    public void setCreationDateTime(Date creationDateTime) {
        this.creationDateTime = creationDateTime;
    }

    public Float getPrice() {
        return price;
    }

    public void setPrice(Float price) {
        this.price = price;
    }

    public Recipient getRecipient() {
        return recipient;
    }

    public void setRecipient(Recipient recipient) {
        this.recipient = recipient;
    }

    @PrePersist
    protected void onCreate() {
        creationDateTime = new Date();
    }
}
