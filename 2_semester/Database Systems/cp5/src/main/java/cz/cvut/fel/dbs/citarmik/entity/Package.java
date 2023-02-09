package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "Package")
public class Package {
    @Id
    @SequenceGenerator(name="package_package_id_seq",
            sequenceName="package_package_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="package_package_id_seq")
    @Column(name = "package_id", updatable = false)
    private long id;
    @ManyToOne(cascade = CascadeType.REFRESH)
    @JoinColumn(name = "order_id", nullable = false)
    private Order order;
    @Column(name = "package_type", length = 32, nullable = false)
    private String type;
    @Column(name = "package_weight", nullable = false)
    private Float weight;
    @Column(name = "package_width", nullable = false)
    private Float width;
    @Column(name = "package_height", nullable = false)
    private Float height;
    @Column(name = "package_depth", nullable = false)
    private Float depth;

    @ManyToMany(mappedBy = "packages", fetch = FetchType.LAZY, cascade = CascadeType.ALL)
    private List<Journey> journeys = new ArrayList<>();

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

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Float getWeight() {
        return weight;
    }

    public void setWeight(Float weight) {
        this.weight = weight;
    }

    public Float getWidth() {
        return width;
    }

    public void setWidth(Float width) {
        this.width = width;
    }

    public Float getHeight() {
        return height;
    }

    public void setHeight(Float height) {
        this.height = height;
    }

    public Float getDepth() {
        return depth;
    }

    public void setDepth(Float depth) {
        this.depth = depth;
    }

    public List<Journey> getJourneys() {
        return journeys;
    }

    public void setJourneys(List<Journey> journeys) {
        this.journeys = journeys;
    }
}
