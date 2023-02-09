package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.AcceptedPackage;

import javax.persistence.EntityManager;

public class AcceptedPackageDao extends AbstractJpaDAO<AcceptedPackage> {
    public AcceptedPackageDao() {
        super();
        setCurrentClass(AcceptedPackage.class);
    }
}
