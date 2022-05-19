package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Employee;

import javax.persistence.EntityManager;

public class EmployeeDao extends AbstractJpaDAO<Employee> {
    public EmployeeDao(EntityManager em) {
        super(em);
        setCurrentClass(Employee.class);
    }
}
