package cz.cvut.fel.dbs.citarmik.service;

import cz.cvut.fel.dbs.citarmik.dao.ClientDao;
import cz.cvut.fel.dbs.citarmik.dao.DepartmentDao;
import cz.cvut.fel.dbs.citarmik.dao.EmployeeDao;
import cz.cvut.fel.dbs.citarmik.dao.EmployeePositionDao;
import cz.cvut.fel.dbs.citarmik.entity.Client;
import cz.cvut.fel.dbs.citarmik.entity.Department;
import cz.cvut.fel.dbs.citarmik.entity.Employee;
import cz.cvut.fel.dbs.citarmik.entity.EmployeePosition;

public class EmployeeService {
    public Employee getEmployee(long id) {
        EmployeeDao employeeDao = new EmployeeDao();
        return employeeDao.get(id);
    }

    public void createEmployee(
            String email,
            String firstName,
            String lastName,
            String address,
            String phoneNumber,
            int cardNumber,
            long departmentId,
            long employeePositionId) {
        EmployeeDao employeeDao = new EmployeeDao();
        Employee employee = new Employee();

        employee.setEmail(email);
        employee.setFirstName(firstName);
        employee.setLastName(lastName);
        employee.setAddress(address);
        employee.setPhoneNumber(phoneNumber);
        employee.setCardNumber(cardNumber);

        DepartmentDao departmentDao = new DepartmentDao();
        Department department = departmentDao.get(departmentId);

        EmployeePositionDao positionDao = new EmployeePositionDao();
        EmployeePosition position = positionDao.get(employeePositionId);

        employee.setDepartment(department);
        employee.setPosition(position);

        employeeDao.save(employee);
    }
}
