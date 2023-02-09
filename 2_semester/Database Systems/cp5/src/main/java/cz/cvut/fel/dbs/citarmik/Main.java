package cz.cvut.fel.dbs.citarmik;

import cz.cvut.fel.dbs.citarmik.core.EntityManagerFactoryUtil;
import cz.cvut.fel.dbs.citarmik.dao.ClientDao;
import cz.cvut.fel.dbs.citarmik.dao.DepartmentDao;
import cz.cvut.fel.dbs.citarmik.entity.*;
import cz.cvut.fel.dbs.citarmik.service.ClientService;
import cz.cvut.fel.dbs.citarmik.service.EmployeeService;
import cz.cvut.fel.dbs.citarmik.service.OrderService;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;


public class Main {
    public static void main(String[] args) {
        // Service Testing

        // Client Service
//        ClientService client = new ClientService();
//
//        // Create new Client
//        client.createClient("test@gmail.com", "Name Test", "Last Name Test", "Address", "passid");
//
//        // Points transfer
//        client.transferPoints(9, 12, 50);

        // Order Service

        // Create Order
//        OrderService order = new OrderService();
//        order.createOrder(
//                180,
//                1,
//                3,
//                300,
//                "Mikita",
//                "Citarovic",
//                "420606169911");

        // Employee Service
        EmployeeService employeeService = new EmployeeService();

//        // Get Employee
//        Employee employee = employeeService.getEmployee(1);
//        System.out.println(employee.getFirstName());

        // Create Employee
        employeeService.createEmployee(
                "testemp@gmail.com",
                "Michal",
                "Pinolade",
                "Thakurova 1",
                "420606169911",
                1984089435,
                3,
                3
        );
    }
}
