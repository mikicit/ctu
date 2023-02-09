// package cz.cvut.fel.pjv;

/**
 * @author Jirka Sebek
 */
public class Start {

    public static void main(String[] args) {

         
        /* homework */
        // Queue queue = new CircularArrayQueue(10);
        Queue queue = new CircularArrayQueue(); // 5


        // System.out.println("Start: ");
        // queue.enqueue("Starkiller");
        // queue.enqueue("C-3PO");
        // queue.enqueue("Jabba the Hutt");
        // queue.enqueue("HK-47");
        // queue.enqueue("Darth Nihilus");
        // // queue.enqueue("Count Dooku");
        // queue.printAllElements();
        // System.out.println("size: " + queue.size());
        // System.out.println("-----------");

        // System.out.println("Deleting: ");
        // System.out.println("Value dequeued from CircularArrayQueue: " + queue.dequeue());
        // System.out.println("Value dequeued from CircularArrayQueue: " + queue.dequeue());
        // queue.printAllElements();
        // System.out.println("size: " + queue.size());
        // System.out.println("-----------");

        // System.out.println("Adding: ");
        // queue.enqueue("Jango Fett");
        // queue.printAllElements();
        // System.out.println("size: " + queue.size());
        // System.out.println("-----------");


        // System.out.println("Deleting: ");
        // System.out.println("Value dequeued from CircularArrayQueue: " + queue.dequeue());
        // System.out.println("Value dequeued from CircularArrayQueue: " + queue.dequeue());
        // queue.printAllElements();
        // System.out.println("size: " + queue.size());
        // System.out.println("-----------");

        // System.out.println("Deleting: ");
        // System.out.println("Value dequeued from CircularArrayQueue: " + queue.dequeue());
        // queue.printAllElements();
        // System.out.println("size: " + queue.size());
        // System.out.println("-----------");

        queue.enqueue("Starkiller 1");
        queue.dequeue();
        queue.dequeue();
        queue.enqueue("Starkiller 2");
        queue.dequeue();
        queue.dequeue();
        queue.dequeue();
        queue.dequeue();
        queue.enqueue("Starkiller 3");
        queue.enqueue("Starkiller 4");
        queue.enqueue("Starkiller 5");
        queue.enqueue("Starkiller 6");
        queue.dequeue();
        System.out.println("size: " + queue.size());
        queue.printAllElements();

        queue.dequeue();
        System.out.println("size: " + queue.size());
        queue.printAllElements();
    }
}
