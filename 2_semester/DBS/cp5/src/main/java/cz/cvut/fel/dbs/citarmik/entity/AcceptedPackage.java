package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.Date;

@Entity
@Table(
        name = "AcceptedPackage",
        uniqueConstraints = {
                @UniqueConstraint(name = "acceptedpackage_data_key", columnNames = {"package_id", "department_id"})
        }
)
public class AcceptedPackage {
    @Id
    @SequenceGenerator(name="acceptedpackage_accepted_package_id_seq",
            sequenceName="acceptedpackage_accepted_package_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="acceptedpackage_accepted_package_id_seq")
    @Column(name = "accepted_package_id", updatable = false)
    private long id;
    @ManyToOne(cascade = CascadeType.REMOVE)
    @JoinColumn(name = "package_id", nullable = false)
    private Package packageEntity;
    @ManyToOne()
    @JoinColumn(name = "department_id", nullable = false)
    private Department department;
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "accepted_date_time", nullable = false)
    private Date acceptedDateTime;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Package getPackage() {
        return packageEntity;
    }

    public void setPackage(Package packageEntity) {
        this.packageEntity = packageEntity;
    }

    public Department getDepartment() {
        return department;
    }

    public void setDepartment(Department department) {
        this.department = department;
    }

    public Date getSentDateTime() {
        return acceptedDateTime;
    }

    public void setSentDateTime(Date sentDateTime) {
        this.acceptedDateTime = sentDateTime;
    }

    @PrePersist
    protected void onCreate() {
        acceptedDateTime = new Date();
    }
}
