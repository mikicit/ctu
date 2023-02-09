package cz.cvut.fel.pjv;

public class TreeImpl implements Tree{
    NodeImpl root;
    int[] values;

    public TreeImpl() {

    }

    public void setTree(int[] values) {
        if (values.length == 0) return;

        this.values = values;
        int start = 0;
        int end = values.length - 1;

        root = new NodeImpl();
        int middleIndex = getMiddleIndex(start, end);
        root.setValue(values[middleIndex]);

        root.setLeft(recursivelySetTree(start, middleIndex - 1));
        root.setRight(recursivelySetTree(middleIndex + 1, end));
    }

    public NodeImpl recursivelySetTree(int start, int end) {
        System.out.println("Start: " + start + " End: " + end);

        NodeImpl node = new NodeImpl();

        if (end < 0 || start > end) {
            return null;
        }

        if (end == start) {
            node.setValue(values[start]);
            return node;
        }

        if (end - start == 1) {
            NodeImpl nodeLeft = new NodeImpl();

            node.setValue(values[end]);
            nodeLeft.setValue(values[start]);
            node.setLeft(nodeLeft);
            return node;
        }

        int middleIndex = getMiddleIndex(start, end);

        node.setValue(values[middleIndex]);
        node.setLeft(recursivelySetTree(start, middleIndex - 1));
        node.setRight(recursivelySetTree(middleIndex + 1, end));

        return node;
    }

    private int getMiddleIndex(int start, int end) {
        if (start == end) {
            return start;
        }

        int length = end - start + 1;
        int result = length / 2;

        return result + start;
    }

    public Node getRoot() {
        return root;
    }

    public String toString() {
        if (root == null) return "";

        StringBuilder result = new StringBuilder();
        recursivelyTreeToString(root, 0, result);
        return result.toString();
    }

    private void recursivelyTreeToString(Node node, int level, StringBuilder accumulator) {
        if (node == null) {
            return;
        }

        accumulator.append(stringRepeat(" ", level)).append("- ").append(node.getValue()).append("\n");

        recursivelyTreeToString(node.getLeft(), level + 1, accumulator);
        recursivelyTreeToString(node.getRight(), level + 1, accumulator);
    }

    private String stringRepeat(String str, int count) {
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < count; i++) {
            result.append(str);
        }

        return result.toString();
    }
}