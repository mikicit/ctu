package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Department;

import javax.persistence.EntityManager;

public class DepartmentDao extends AbstractJpaDAO<Department> {
    public DepartmentDao() {
        super();
        setCurrentClass(Department.class);
    }
}
