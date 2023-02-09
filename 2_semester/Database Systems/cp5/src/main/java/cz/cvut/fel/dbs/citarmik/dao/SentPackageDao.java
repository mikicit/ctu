package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.SentPackage;

import javax.persistence.EntityManager;

public class SentPackageDao extends AbstractJpaDAO<SentPackage> {
    public SentPackageDao() {
        super();
        setCurrentClass(SentPackage.class);
    }
}
