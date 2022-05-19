package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "Client")
@PrimaryKeyJoinColumn(name = "client_id")
public class Client extends Person {
    @Column(name = "pass_id", length = 32, nullable = false, unique = true)
    private String passId;
    @Column(name = "bonus_points", nullable = false)
    private Integer bonusPoints = 0;
    @OneToMany(mappedBy = "client", fetch = FetchType.LAZY)
    private List<Order> orders = new ArrayList<>();

    public String getPassId() {
        return passId;
    }

    public void setPassId(String passId) {
        this.passId = passId;
    }

    public Integer getBonusPoints() {
        return bonusPoints;
    }

    public void setBonusPoints(Integer bonusPoints) {
        this.bonusPoints = bonusPoints;
    }

    public List<Order> getOrders() {
        return orders;
    }

    public void setOrders(List<Order> orders) {
        this.orders = orders;
    }
}
