package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "Employee")
@PrimaryKeyJoinColumn(name = "employee_id")
public class Employee extends Person {
    @Column(name = "card_number", nullable = false, unique = true)
    private Integer cardNumber;
    @ManyToOne(cascade = CascadeType.MERGE)
    @JoinColumn(name = "position_id")
    private EmployeePosition position;
    @ManyToOne()
    @JoinColumn(name = "department_id", nullable = false)
    private Department department;
    @OneToOne(mappedBy = "employee")
    private Supervisor supervisor;
    @OneToMany(mappedBy = "supervisor")
    private List<Supervisor> subordinates = new ArrayList<>();

    public long getCardNumber() {
        return cardNumber;
    }

    public void setCardNumber(Integer cardNumber) {
        this.cardNumber = cardNumber;
    }

    public EmployeePosition getPosition() {
        return position;
    }

    public void setPosition(EmployeePosition position) {
        this.position = position;
    }

    public Department getDepartment() {
        return department;
    }

    public void setDepartment(Department department) {
        this.department = department;
    }

    public Supervisor getSupervisor() {
        return supervisor;
    }

    public void setSupervisor(Supervisor supervisor) {
        this.supervisor = supervisor;
    }

    public List<Supervisor> getSubordinates() {
        return subordinates;
    }

    public void setSubordinates(List<Supervisor> subordinates) {
        this.subordinates = subordinates;
    }
}
