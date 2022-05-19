package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.JourneyPackage;

import javax.persistence.EntityManager;

public class JourneyPackageDao extends AbstractJpaDAO<JourneyPackage> {
    public JourneyPackageDao() {
        super();
        setCurrentClass(JourneyPackage.class);
    }
}
