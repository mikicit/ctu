package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.Date;

@Entity
@Table(
        name = "SentPackage",
        uniqueConstraints = {
                @UniqueConstraint(name = "sentpackage_data_key", columnNames = {"package_id", "department_id"})
        }
)
public class SentPackage {
    @Id
    @SequenceGenerator(name="sentpackage_sent_package_id_seq",
            sequenceName="sentpackage_sent_package_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="sentpackage_sent_package_id_seq")
    @Column(name = "sent_package_id", updatable = false)
    private long id;
    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "package_id")
    private Package packageEntity;
    @ManyToOne()
    @JoinColumn(name = "department_id")
    private Department department;
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "sent_date_time", nullable = false)
    private Date sentDateTime;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Package getPackageEntity() {
        return packageEntity;
    }

    public void setPackageEntity(Package packageEntity) {
        this.packageEntity = packageEntity;
    }

    public Department getDepartment() {
        return department;
    }

    public void setDepartment(Department department) {
        this.department = department;
    }

    public Date getSentDateTime() {
        return sentDateTime;
    }

    public void setSentDateTime(Date sentDateTime) {
        this.sentDateTime = sentDateTime;
    }

    @PrePersist
    protected void onCreate() {
        sentDateTime = new Date();
    }
}
