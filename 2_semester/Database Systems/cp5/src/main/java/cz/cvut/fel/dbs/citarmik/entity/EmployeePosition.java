package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "EmployeePosition")
public class EmployeePosition {
    @Id
    @SequenceGenerator(name="employeeposition_position_id_seq",
            sequenceName="employeeposition_position_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="employeeposition_position_id_seq")
    @Column(name = "position_id", updatable = false)
    private long id;
    @Column(name = "position_name", length = 32, nullable = false, unique = true)
    private String positionName;
    @OneToMany(mappedBy = "position")
    private List<Employee> employees = new ArrayList<Employee>();

    public long getId() {
        return id;
    }

    public String getPositionName() {
        return positionName;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setPositionName(String positionName) {
        this.positionName = positionName;
    }

    public List<Employee> getEmployees() {
        return employees;
    }

    public void setEmployees(List<Employee> employees) {
        this.employees = employees;
    }
}
