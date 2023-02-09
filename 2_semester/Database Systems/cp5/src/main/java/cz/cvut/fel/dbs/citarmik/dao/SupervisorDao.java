package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Supervisor;

import javax.persistence.EntityManager;

public class SupervisorDao extends AbstractJpaDAO<Supervisor> {
    public SupervisorDao() {
        super();
        setCurrentClass(Supervisor.class);
    }
}
