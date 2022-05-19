package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Entity
@Table(name = "Journey")
public class Journey {
    @Id
    @SequenceGenerator(name="journey_journey_id_seq",
            sequenceName="journey_journey_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="journey_journey_id_seq")
    @Column(name = "journey_id", updatable = false)
    private long id;
    @ManyToOne()
    @JoinColumn(name = "department_from_id", nullable = false)
    private Department departmentFrom;
    @ManyToOne()
    @JoinColumn(name = "department_to_id", nullable = false)
    private Department departmentTo;
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "departure_date_time", nullable = false)
    private Date departureDateTime;
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "arrival_date_time", nullable = false)
    private Date arrivalDateTime;
    @ManyToOne()
    @JoinColumn(name = "auto_id")
    private Auto auto;

    @ManyToMany(fetch = FetchType.LAZY, cascade = CascadeType.ALL)
    @JoinTable(
            name = "JourneyPackage",
            joinColumns = @JoinColumn(name = "journey_id"),
            inverseJoinColumns = @JoinColumn(name = "package_id"))
    private List<Package> packages = new ArrayList<>();

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
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

    public Date getDepartureDateTime() {
        return departureDateTime;
    }

    public void setDepartureDateTime(Date departureDateTime) {
        this.departureDateTime = departureDateTime;
    }

    public Date getArrivalDateTime() {
        return arrivalDateTime;
    }

    public void setArrivalDateTime(Date arrivalDateTime) {
        this.arrivalDateTime = arrivalDateTime;
    }

    public List<Package> getPackages() {
        return packages;
    }

    public void setPackages(List<Package> packages) {
        this.packages = packages;
    }

    public Auto getAuto() {
        return auto;
    }

    public void setAuto(Auto auto) {
        this.auto = auto;
    }
}
