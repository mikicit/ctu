package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Auto;

import javax.persistence.EntityManager;

public class AutoDao extends AbstractJpaDAO<Auto> {
    public AutoDao() {
        super();
        setCurrentClass(Auto.class);
    }
}
