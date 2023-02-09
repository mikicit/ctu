package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Journey;

import javax.persistence.EntityManager;

public class JourneyDao extends AbstractJpaDAO<Journey> {
    public JourneyDao() {
        super();
        setCurrentClass(Journey.class);
    }
}
