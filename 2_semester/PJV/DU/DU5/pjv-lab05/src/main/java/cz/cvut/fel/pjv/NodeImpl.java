package cz.cvut.fel.pjv;

public class NodeImpl implements Node {
    private int value;
    private Node leftNode = null;
    private Node rightNode = null;

    public Node getLeft() {
        return leftNode;
    }

    public Node getRight() {
        return rightNode;
    }

    public int getValue() {
        return value;
    }

    public void setLeft(Node node) {
        leftNode = node;
    }

    public void setRight(Node node) {
        rightNode = node;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
