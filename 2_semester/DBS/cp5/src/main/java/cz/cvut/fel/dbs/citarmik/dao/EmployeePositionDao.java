package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.EmployeePosition;

import javax.persistence.EntityManager;

public class EmployeePositionDao extends AbstractJpaDAO<EmployeePosition> {
    public EmployeePositionDao() {
        super();
        setCurrentClass(EmployeePosition.class);
    }
}
