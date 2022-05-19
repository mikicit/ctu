package cz.cvut.fel.dbs.citarmik.entity;

import javax.persistence.*;

@Entity
@Table(name = "supervisor")
public class Supervisor {
        @Id
        @SequenceGenerator(name="supervisor_supervisor_id_seq",
                sequenceName="supervisor_supervisor_id_seq",
                allocationSize=1)
        @GeneratedValue(strategy = GenerationType.SEQUENCE,
                generator="supervisor_supervisor_id_seq")
        @Column(name = "supervisor_id", updatable = false)
        private long id;
        @OneToOne(cascade = CascadeType.REMOVE)
        @JoinColumn(name = "employee", nullable = false, unique = true)
        private Employee employee;
        @ManyToOne(cascade = CascadeType.REMOVE)
        @JoinColumn(name = "supervisor", nullable = false)
        private Employee supervisor;

        public long getId() {
                return id;
        }

        public void setId(long id) {
                this.id = id;
        }

        public Employee getEmployee() {
                return employee;
        }

        public void setEmployee(Employee employee) {
                this.employee = employee;
        }

        public Employee getSupervisor() {
                return supervisor;
        }

        public void setSupervisor(Employee supervisor) {
                this.supervisor = supervisor;
        }
}
