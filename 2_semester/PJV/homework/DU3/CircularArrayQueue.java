package cz.cvut.fel.pjv;

/**
 * Implementation of the {@link Queue} backed by fixed size array.
 */
public class CircularArrayQueue implements Queue {
    String[] elements;
    int tail = 0;
    int head = 0;
    int size = 0;
    int maxSize = 5;

    /**
     * Creates the queue with capacity set to the value of 5.
     */
    public CircularArrayQueue() {
        elements = new String[maxSize];
    }


    /**
     * Creates the queue with given {@code capacity}. The capacity represents maximal number of elements that the
     * queue is able to store.
     * @param capacity of the queue
     */
    public CircularArrayQueue(int capacity) {
        elements = new String[capacity];
        maxSize = capacity;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        if (size == 0) {
            return true;
        }

        return false;
    }

    @Override
    public boolean isFull() {
        if (size == maxSize) {
            return true;
        }

        return false;
    }

    @Override
    public boolean enqueue(String obj) {
        if (isFull() || obj == null) {
            return false;
        }

        if (isEmpty()) {
            elements[head] = obj;
        } else {
            if (tail == maxSize - 1) {
                elements[0] = obj;
                tail = 0;
            } else {
                tail++;
                elements[tail] = obj;
            }
        }

        size++;
        return true;
    }

    @Override
    public String dequeue() {
        if (isEmpty()) return null;
        String result = elements[head];
        elements[head] = null;
        size--;

        if (!isEmpty()) {
            head = (head == maxSize - 1) ? 0 : head + 1;
        }

        return result;
    }

    @Override
    public void printAllElements() {
        if (isEmpty()) return;

        // // If size is 1 (head == tail)
        // if (size == 1) {
        //     System.out.println("Index: " + head + " " + elements[head] + " [Head and Tail] Head - " + head + " Tail - " + tail);
        //     return;
        // }

        // // Head
        // System.out.println("Index: " + head + " " + elements[head] + " [Head] Head - " + head + " Tail - " + tail);

        // int nextElem = (head + 1 > maxSize - 1) ? 0 : head + 1;

        // while (nextElem != tail) {
        //     System.out.println("Index: " + nextElem + " " + elements[nextElem]);
        //     nextElem = (nextElem + 1 > maxSize - 1) ? 0 : nextElem + 1;
        // }

        // // Tail
        // System.out.println("Index: " + tail + " " + elements[tail] + " [Tail] Head - " + head + " Tail - " + tail);

        // // If size is 1 (head == tail)
        // if (size == 1) {
        //     System.out.println(elements[head]);
        //     return;
        // }

        int nextElem = head;

        while (nextElem != tail) {
            System.out.println(elements[nextElem]);
            nextElem = (nextElem + 1 > maxSize - 1) ? 0 : nextElem + 1;
        }

        // Tail or Tail and Head (where is 1 elem)
        System.out.println(elements[nextElem]);
    }
}
