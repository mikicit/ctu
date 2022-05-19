package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;

@Entity
@Table(
        name = "JourneyPackage",
        uniqueConstraints = {
                @UniqueConstraint(name = "journey_package_data_key", columnNames = {"journey_id", "package_id"})
        }
)
public class JourneyPackage {
    @Id
    @SequenceGenerator(name="journeypackage_journey_package_id_seq",
            sequenceName="journeypackage_journey_package_id_seq",
            allocationSize=1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE,
            generator="journeypackage_journey_package_id_seq")
    @Column(name = "journey_package_id", updatable = false)
    private long id;
    @ManyToOne()
    @JoinColumn(name = "journey_id")
    private Journey journey;
    @ManyToOne()
    @JoinColumn(name = "package_id")
    private Package packageEntity;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Journey getJourney() {
        return journey;
    }

    public void setJourney(Journey journey) {
        this.journey = journey;
    }

    public Package getPackage() {
        return packageEntity;
    }

    public void setPackageEntity(Package packageEntity) {
        this.packageEntity = packageEntity;
    }
}
