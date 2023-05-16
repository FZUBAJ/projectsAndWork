import java.io.PrintStream;

public class BinaryTreePrinter {

    private BDDNode tree;

    public BinaryTreePrinter(BDDNode tree) {
        this.tree = tree;
    }



    private String traversePreOrder(BDDNode root) {

        if (root == null) {
            return "";
        }

        StringBuilder sb = new StringBuilder();
        sb.append(root.getFormula());

        if(root.getLeftZero() == null && root.getRightOne() == null){
            return sb.toString();
        }
        String pointerRight = "└──";
        String pointerLeft = (root.getRightOne() != null) ? "├──" : "└──";

        traverseNodes(sb, "", pointerLeft, root.getLeftZero(), root.getRightOne() != null);
        traverseNodes(sb, "", pointerRight, root.getRightOne(), false);

        return sb.toString();
    }

    private void traverseNodes(StringBuilder sb, String padding, String pointer, BDDNode node,
                               boolean hasRightSibling) {

        if (node != null) {

            sb.append("\n");
            sb.append(padding);
            sb.append(pointer);
            sb.append(node.getFormula());
            //sb.append(" (").append(System.identityHashCode(node)).append(")");

            StringBuilder paddingBuilder = new StringBuilder(padding);
            if (hasRightSibling) {
                paddingBuilder.append("│  ");
            } else {
                paddingBuilder.append("   ");
            }

            String paddingForBoth = paddingBuilder.toString();
            String pointerRight = "└──";
            String pointerLeft = (node.getRightOne() != null) ? "├──" : "└──";

            traverseNodes(sb, paddingForBoth, pointerLeft, node.getLeftZero(), node.getRightOne()!= null);
            traverseNodes(sb, paddingForBoth, pointerRight, node.getRightOne(), false);

        }

    }

    public void print(PrintStream os) {
        os.print(traversePreOrder(tree));
    }

}
