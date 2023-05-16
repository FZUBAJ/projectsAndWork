public class BDDNode {
    public String variable; //this stores the variable that we are decomposing by
    public String formula; //formula stores the boolean function in DNF
    public BDDNode leftZero; //this is the left and negated child, that's why it is leftZero
    public BDDNode rightOne; //this is the right and not negated child, that's why it is rightOne
    public BDDNode parent; //node to set the parent of the node
    public static int nodeCounter = 0; //initialise the node counter to zero and add each time node is created

    //getter methods
    public String getVariable() {
        return variable;
    }

    public String getFormula() {
        return "(" +variable+")"+formula + " " + this;
    }

    public BDDNode getLeftZero() {
        return leftZero;
    }

    public BDDNode getRightOne() {
        return rightOne;
    }

    public BDDNode getParent() {
        return parent;
    }

    public static int getNodeCounter() {
        return nodeCounter;
    }

    public int getAmountOfNodes() {
        return nodeCounter;
    }
    public BDDNode(String variable, String formula, BDDNode parent){ //constructor for the node
        this.variable = variable;
        this.formula = formula;
        this.leftZero = null;
        this.rightOne = null; //set child nodes to null, they will be assigned later
        this.parent = parent;
        nodeCounter++; //increment each time node is created
    }
}
