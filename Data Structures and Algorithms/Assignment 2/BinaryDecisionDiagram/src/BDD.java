import java.util.*;

import static java.util.Collections.shuffle;

//add counter for the reduced nodes
public class BDD {

    BDDNode root; //root of the tree
    //these are the two final nodes in which the tree will end
    int amountOfVariables; //this will store the amount of variables in the boolean function
    List<String> orderOfBDD; //this will store the order of the BDD
    //getters and setters
    public BDDNode getRoot() {
        return root;
    }

    public int getAmountOfVariables() {
        return amountOfVariables;
    }

    public List<String> getOrderOfBDD() {
        return orderOfBDD;
    }

    public BDD(){ //constructor for BDD
        this.amountOfVariables = 0;
        this.orderOfBDD = new ArrayList<>();
    }



    int getAmountOfNodes(){
        return BDDNode.nodeCounter;
    }


    public BDD BDD_create(String booleanFunction, List<String> order) {
        BDD bdd = new BDD();

        bdd.orderOfBDD.addAll(order);

        amountOfVariables = getAmountOfVariables(booleanFunction); //getting amount of variables because we have to store it
        int amountOfNodesBeforeReduction = (int) (Math.pow(2, (amountOfVariables + 1)) -1);

        HashMap<String, BDDNode> cache = new HashMap<>(); //hashmap will help us to avoid creating the same node twice

        //creating the two final nodes
        BDDNode zeroNode = new BDDNode("0", "0", null);
        BDDNode oneNode = new BDDNode("1", "1", null);

        //creating the tree
        String firstVar = order.get(0); //first variable from the order
        this.root = new BDDNode(firstVar, booleanFunction, null); //create the root node with particular variable and formula

        //creating the queue to hold nodes that are supposed to be decomposed
        Queue<BDDNode> nodesToBeDecomposed = new LinkedList<>(); //I use queue to store nodes to be decomposed
        nodesToBeDecomposed.add(root); //adding first node to the queue
        //the queue to hold the nodes to decompose
        while(!nodesToBeDecomposed.isEmpty()){
            //get the next node to be decomposed from the queue
            BDDNode node = nodesToBeDecomposed.poll();
            //adding nodes to the cache to avoid creating the same nodes twice
            cache.put(node.formula, node);
            //I set these to be true, if the node is already in hashmap, so no new nodes will be created if they already exist
            boolean cachedLeft = false;
            boolean cachedRight = false;
            //looking for the top variable from the order located in formula
            node.variable = compareFormulaWithOrder(node.formula, order);
            //check if the formula is in the final form, if it is, than we don't need to decompose it and we don't add new nodes for decomposition

            //decompose the formula from node, to create formulas for children
            String leftZeroFormula = fullDecomposition(node.formula, node.variable, true);
            String rightOneFormula = fullDecomposition(node.formula, node.variable, false);
            //we look for the variable that we will decompose by in the order
            String leftZeroVariable = compareFormulaWithOrder(leftZeroFormula, order);
            String rightOneVariable = compareFormulaWithOrder(rightOneFormula, order);

            //both children are one, therefore I can set their parent to be one, and its parent to point to one
            if(leftZeroFormula.equals("1") && rightOneFormula.equals("1")){
                if(node.parent.leftZero == node){
                    node.parent.leftZero = oneNode;
                }else{
                    node.parent.rightOne = oneNode;
                }
                continue;
            }
            //both children are zero, therefore I can set their parent to be zero
            if(leftZeroFormula.equals("0") && rightOneFormula.equals("0")){
                if(node.parent.leftZero == node){
                    node.parent.leftZero = zeroNode;
                }else{
                    node.parent.rightOne = zeroNode;
                }
                continue;
            }

            //if the two children are equal, their parent is redundant, therefore the parents child pointer will point to the one of the children
            if(leftZeroFormula.equals(rightOneFormula)){
                if(node == root){ //if the redundant node is the root, we need to set a new root, by placing the formula which is in both children in to root node
                    BDDNode newNode = new BDDNode(leftZeroVariable, leftZeroFormula, node); //new root
                    this.root = newNode;
                    nodesToBeDecomposed.add(newNode);
                    BDDNode.nodeCounter--; //original root is being deleted
                    continue;
                }
                if(node.parent.leftZero == node){ //these two are because it may happen to left or right child of the parent, and we need to know which one
                    BDDNode newNode = new BDDNode(leftZeroVariable, leftZeroFormula, node.parent);
                    node.parent.leftZero = newNode;
                    nodesToBeDecomposed.add(newNode); //always add to queue, so we will continue with the decoposition
                    BDDNode.nodeCounter -= 2;
                    continue;
                }else{
                    BDDNode newNode = new BDDNode(rightOneVariable, rightOneFormula, node.parent);
                    node.parent.rightOne = newNode;
                    nodesToBeDecomposed.add(newNode);
                    BDDNode.nodeCounter -= 2;
                    continue;
                }
            }

            //check whether the child nodes are not already in cache, if yes we do the reduction and set boolean to true
            if (cache.containsKey(leftZeroFormula) || cache.containsKey(rightOneFormula)) {
                if (cache.containsKey(leftZeroFormula)) {
                    BDDNode cachedNodeLeft = cache.get(leftZeroFormula);
                    if (leftZeroVariable.equals(cachedNodeLeft.variable)) {
                        node.leftZero = cachedNodeLeft;
                        cachedLeft = true;
                    }
                }

                if (cache.containsKey(rightOneFormula)){
                    BDDNode cachedNodeRight = cache.get(rightOneFormula);
                    if (rightOneVariable.equals(cachedNodeRight.variable)) {
                        node.rightOne = cachedNodeRight;
                        cachedRight = true;
                    }
                }
            }
            //if some of the children is not already initialised, go there
            if (node.leftZero == null || node.rightOne == null) {
                //if it is 0 or 1, set it to be the constant node zero or one
                if (leftZeroFormula.equals("0")) {
                    node.leftZero = zeroNode;
                }
                if (leftZeroFormula.equals("1")) {
                    node.leftZero = oneNode;
                }
                if (rightOneFormula.equals("0")) {
                    node.rightOne = zeroNode;
                }
                if (rightOneFormula.equals("1")) {
                    node.rightOne = oneNode;
                }

                //if nothing previously set the children, we need to create new nodes, add their formula to cache and to queue
                if (node.leftZero == null && !cachedLeft && !leftZeroFormula.equals("0") && !leftZeroFormula.equals("1")) {
                    node.leftZero = new BDDNode(leftZeroVariable, leftZeroFormula, node);
                    cache.put(node.leftZero.formula, node.leftZero);    //adding nodes to the cache to avoid creating the same nodes twice
                    nodesToBeDecomposed.add(node.leftZero);
                }
                if (node.rightOne == null && !cachedRight && !rightOneFormula.equals("0") && !rightOneFormula.equals("1")) {
                    node.rightOne = new BDDNode(rightOneVariable, rightOneFormula, node);
                    cache.put(node.rightOne.formula, node.rightOne);
                    nodesToBeDecomposed.add(node.rightOne);
                }
            }
        }

        //printing all the necessary data
        System.out.println("✅ Construction of BDD is successful ✅");
        System.out.println("Amount of nodes without reduction: "+ amountOfNodesBeforeReduction);
        System.out.println("Amount of nodes: "+ BDDNode.nodeCounter);
        int reducedNodes = amountOfNodesBeforeReduction - BDDNode.nodeCounter;
        System.out.println("Reduced nodes: "+ reducedNodes);
        double reductionRate = (100 - ((double)BDDNode.nodeCounter/(double)amountOfNodesBeforeReduction)* 100);
        System.out.println("Rate of the reduction: "+ ((reductionRate + " %")));
        System.out.println("Amount of variables: "+ amountOfVariables);

        bdd.root = root;
        bdd.amountOfVariables = amountOfVariables;

        //return the bdd with its atributes
        return bdd;
    }

    public String fullDecomposition(String booleanFunctionInDNF, String variable, boolean negation){

        //split functions by the plus signs into separate parts
        String[] disjunctions = booleanFunctionInDNF.split("\\+");
        //String[] updatedDisjunctions = new String[disjunctions.length];
        HashSet<String> updatedDisjunctions = new HashSet<>();

       for(int i = 0; i < disjunctions.length; i++){
           //decompose each part of the function and update into new array
           String disjunction = decompositionBy(disjunctions[i], variable, negation);
           updatedDisjunctions.add(disjunction);
       }
       String[] finalDisjunctions = new String[updatedDisjunctions.size()];
        updatedDisjunctions.toArray(finalDisjunctions);
       //used to connect the parts together again
        return createDisjunction(finalDisjunctions);
    }


    public String createDisjunction(String[] conjunctions){
        String result = "";
        //only one conjunction, no need to create a disjunction
        if(conjunctions.length == 1){
            return conjunctions[0];
        }

        for(String conjunction : conjunctions){
            //if one of the conjunctions in DNF is 1 then the whole formula is 1
            if(conjunction.equals("1")){
                return "1";
            }else if(conjunction.equals("0")){ //if the conjunction is 0, than we don't need to add it to the formula, we just ignore it
                continue;
            }else{
                result += conjunction + "+";
            }
        }
        //one plus sign will be extra, so I will erase it
        if(result.endsWith("+")){
            result = result.substring(0, result.length() - 1);
        }
        return result;
    }


    public String decompositionBy(String conjunctions, String var, boolean negation){
        //if the whole conjunction doesn't include the variable, no changes will be made, so it would only
        //slower the program to check every single literal
        if(!(conjunctions.contains(var))){
            return conjunctions;
        }

        String[] literals = conjunctions.split("\\*");
        //decomposing the conjunction into literals
        String[] updatedLiterals = new String[literals.length]; // Create a new array to store the updated literals

        for (int i = 0; i < literals.length; i++) {
            String literal = literals[i];
            //the literal contains variable
            if (literal.contains(var)) {
                //if the literal is only one variable, and it is same as the var we are looking for
                if (literal.length() == 1 && literal.equals(var)) {
                    //based on negation it will be one if right subtree and zero if left subtree
                    if (negation) {
                        updatedLiterals[i] = "0";
                    } else {
                        updatedLiterals[i] = "1";
                    }
                } else if (literal.length() == 2 && literal.contains(var) && literal.contains("!")) {
                    //opposite case of the previous one, the negation sign will change the value
                    if (negation) {
                        updatedLiterals[i] = "1";
                    } else {
                        updatedLiterals[i] = "0";
                    }
                }
            } else {
                //literal doesn't contain the variable
                updatedLiterals[i] = literal;
            }
        }

        String result = "";

        boolean allOnes = true;
        //checking if all the literals are 1 and if they are, the while conjunction will be 1
        for(String literal : updatedLiterals){
            if(!literal.equals("1")){
                allOnes = false;
                break;
            }
        }

        if(allOnes){
            return "1";
        }

        for (String literal : updatedLiterals) {
            if(literal.equals("0")){
                return "0";
            }
            else if (literal.equals("!")) { //if it is negated we add the exclamation mark
                result += "!";
            } else if(literal.equals("1")){ //we ignore the 1 because it doesn't change the conjunction, we just erase it
                continue;
            } else {
                result += literal + "*";
            }
        }

        // Getting rid of the last * because there will be one extra
        if(result.endsWith("*")){
            result = result.substring(0, result.length() - 1);
        }

        //returning the resulting conjunction
        return result;
    }

    public int getAmountOfVariables(String booleanFunction){
        //this is a set of variables, not for loop because we can't count same variable more than once
        Set<String> variablesInFunction = new HashSet<>();
        //go through the boolean function to find all the variables inside
        for(int i = 0; i < booleanFunction.length(); i++){
            //checking all the characters on the different indexes of the string
            char c = booleanFunction.charAt(i);
            //if it is a letter we add it to our set, in Set we can't have equal elements so there won't be any duplicates
            if(Character.isLetter(c)){
                variablesInFunction.add(String.valueOf(c));
            }
        }
        //the size of the set is the amount of variables
        return variablesInFunction.size();
    }

    public String compareFormulaWithOrder(String formula, List<String> order){
        //here I look for the top variable from order which is in the formula
        for(String variable : order){ //go from the top and compare with characters from the formula
            if(formula.contains(variable)){
                return variable;
            }
        }
        if(formula.contains("1")){
            return "1";
        } else if(formula.contains("0")){
            return "0";
        }

        return null; //if there is no variable from the order in the formula, we return the first variable from the order
    }


    public BDD BDD_create_with_best_order(String booleanFunction){
        int amountOfVariables = getAmountOfVariables(booleanFunction); //get amount of variables
        BDD[] bdds = new BDD[amountOfVariables]; //create the array to store bdds
        int[] amountOfNodes = new int[amountOfVariables]; //create the array to store amount of nodes in each bdd

        HashSet<String> variables = new HashSet<>(); //create a set to store variables

        //get all of the variables from the boolean function and create array from them
        for(char c : booleanFunction.toCharArray()){
            if(Character.isLetter(c)){
                variables.add(String.valueOf(c));
            }
        }

        String[] variablesArray = new String[variables.size()];
        variables.toArray(variablesArray);

        for(int i = 0; i < amountOfVariables; i++){ //for loop to create bdds with different orders

            bdds[i] = BDD_create(booleanFunction, Arrays.stream(variablesArray).toList());
            amountOfNodes[i] = bdds[i].getAmountOfNodes();
            BDDNode.nodeCounter = 0;
            shuffleArrayByOne(variablesArray); //shuffling the order by one = creating permutations
        }

        int min = amountOfNodes[0]; //set the minimum to the first value
        int indexOfMinimal = 0; //finding the index of the minimal amount of nodes

        for(int i = 1; i < amountOfNodes.length; i++){ //if it is smaller, set the minimum to this index
            if(amountOfNodes[i] < min){
                min = amountOfNodes[i];
                indexOfMinimal = i; //save the index of the array with the smallest amount of nodes
            }
        }

        System.out.println("\n\nThe best order is: " + Arrays.toString(variablesArray));
        System.out.println("The amount of nodes is: " + min);
        BDDNode.nodeCounter = amountOfNodes[indexOfMinimal];
        return bdds[indexOfMinimal]; //return the bdd with the smallest amount of nodes
    }

    public static void shuffleArrayByOne(String[] arr) {
        String temp = arr[arr.length-1]; // save the last element
        for(int i = arr.length-1; i > 0; i--){
            arr[i] = arr[i-1]; // shift elements to the right
        }
        arr[0] = temp; // set the first element to the saved last element
    }

    char BDD_use(BDD bdd, String inputs){
        if(inputs.length() != bdd.amountOfVariables){ //check the correct length of the input
            System.out.println("⚠️ There is not enough variables in the input you provided. ⚠️");
            return '-';
        }

        BDDNode nodeToTraverse = bdd.root; //set the nodeToTraverse to point to the root
        String result = "";
        int i = 0;


        while(true){
            if(nodeToTraverse == null){ //if there is no node to traverse, it means that the input is not correct
                System.out.println("⚠️ The input you provided is not correct. ⚠️");
                return '-';
            }
            //if there is result already, I return it, this is because, the nodeToTraverse may store final result already
            if(nodeToTraverse.formula.equals("1") || nodeToTraverse.formula.equals("0")){
                return nodeToTraverse.formula.charAt(0);
            }
            //comparing the order of variables and the variables from nodes, to be sure whether it is correct
            if(nodeToTraverse.getVariable() != orderOfBDD.get(i)){
                i++; //if they are not equal, probably reduction has been made and I need to skip the redundant nodes as well
                continue; //so I go to the following iteration of the loop
            }
            //if its zero,I go left
            if(inputs.charAt(i) == '0'){
                nodeToTraverse = nodeToTraverse.leftZero;
                i++;
            } else if (inputs.charAt(i) == '1') { //if its one I go right
                nodeToTraverse = nodeToTraverse.rightOne;
                i++;
            } else{  //if wrong input is provided, I return error mesage and - sign
                System.out.println("⚠️ The input you provided is not correct. ⚠️");
                return '-';
            }
        }
    }



}