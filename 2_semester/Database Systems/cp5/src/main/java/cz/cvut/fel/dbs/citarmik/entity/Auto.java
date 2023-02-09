package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;

@Entity
@Table(name = "auto")
public class Auto {
    @Id
    @SequenceGenerator(name="auto_auto_id_seq",
            sequenceName="auto_auto_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="auto_auto_id_seq")
    @Column(name = "auto_id", updatable = false)
    private long id;
    @Column(name = "reg_number", length = 32, nullable = false, unique = true)
    private String regNumber;
    @ManyToOne(cascade = CascadeType.MERGE)
    @JoinColumn(name = "driver")
    private Employee driver;
    @ManyToOne()
    @JoinColumn(name = "type_id", nullable = false)
    private AutoType type;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getRegNumber() {
        return regNumber;
    }

    public void setRegNumber(String regNumber) {
        this.regNumber = regNumber;
    }

    public Employee getDriver() {
        return driver;
    }

    public void setDriver(Employee driver) {
        this.driver = driver;
    }

    public AutoType getType() {
        return type;
    }

    public void setType(AutoType type) {
        this.type = type;
    }
}
