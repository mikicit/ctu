package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import javax.persistence.EntityManager;

public class PackageDao extends AbstractJpaDAO<Package> {
    public PackageDao() {
        super();
        setCurrentClass(Package.class);
    }
}
