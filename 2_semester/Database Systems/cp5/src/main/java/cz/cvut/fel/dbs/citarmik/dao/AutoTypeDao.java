package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.AutoType;
import javax.persistence.EntityManager;

public class AutoTypeDao extends AbstractJpaDAO<AutoType> {
    public AutoTypeDao() {
        super();
        setCurrentClass(AutoType.class);
    }
}
