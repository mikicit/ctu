package cz.cvut.fel.pjv;

public class Main {
    public static void main(String[] args) {
        int[] values = {};
        TreeImpl tree = new TreeImpl();
        tree.setTree(values);
        System.out.println(tree);
        System.out.println(tree.getRoot().getValue());
    }
}
