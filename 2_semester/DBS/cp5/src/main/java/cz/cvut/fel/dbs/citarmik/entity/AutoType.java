package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;

@Entity
@Table(name = "AutoType")
public class AutoType {
    @Id
    @SequenceGenerator(name="autotype_auto_type_id_seq",
            sequenceName="autotype_auto_type_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="autotype_auto_type_id_seq")
    @Column(name = "auto_type_id", updatable = false)
    private long id;
    @Column(name = "type_name", length = 32, nullable = false, unique = true)
    private String name;
    @Column(name = "capacity", nullable = false)
    private Integer capacity;

    public long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public Integer getCapacity() {
        return capacity;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setCapacity(Integer capacity) {
        this.capacity = capacity;
    }
}
