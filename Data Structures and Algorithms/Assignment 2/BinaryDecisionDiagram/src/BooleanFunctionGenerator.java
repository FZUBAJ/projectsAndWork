import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class BooleanFunctionGenerator {
    private Random random;
    public BooleanFunctionGenerator() {
        random = new Random();
    }

    public void generateAndMeasureBDDCreate(int numFunctions, int numVariables) {
        //variables to save the total time and number of nodes
        long totalTime = 0;
        int totalNumNodes = 0;
        //for loop to create the BDD using order and boolean function
        for (int i = 0; i < numFunctions; i++) {
            String booleanFunction = generateBooleanFunction(numVariables);
            List<String> order = generateVariableOrder(numVariables);
            //measure the time for creating the BDD and add it to the total time
            long startTime = System.nanoTime();
            BDD bdd = new BDD().BDD_create(booleanFunction, order);
            totalNumNodes += BDDNode.nodeCounter;
            long endTime = System.nanoTime();
            //set node counter to zero for the next BDD
            BDDNode.nodeCounter = 0;

            long elapsedTime = endTime - startTime;
            totalTime += elapsedTime;
        }
        //print the statistics
        long averageTime = totalTime / numFunctions;
        System.out.println("Average BDD create time for: " + numFunctions +" is : " + averageTime + " nanoseconds");
        System.out.println("Average number of nodes for: " + numFunctions +" is : " + totalNumNodes / numFunctions);
    }

    public void generateAndMeasureBDDCreateWithBestOrder(int numFunctions, int numVariables) {
        long totalTime = 0;
        int totalNumNodes = 0;
        //same as previously but for create with best order
        for (int i = 0; i < numFunctions; i++) {
            String booleanFunction = generateBooleanFunction(numVariables);

            long startTime = System.nanoTime();
            BDD bdd = new BDD().BDD_create_with_best_order(booleanFunction);
            totalNumNodes += BDDNode.nodeCounter;
            long endTime = System.nanoTime();

            BDDNode.nodeCounter = 0;

            long elapsedTime = endTime - startTime;
            totalTime += elapsedTime;
        }

        long averageTime = totalTime / numFunctions;
        System.out.println("\n\nAverage BDD create time for " + numFunctions +" functions is " + averageTime + " nanoseconds");
        System.out.println("Average number of nodes for " + numFunctions +" functions is " + totalNumNodes / numFunctions);
    }

    public String generateBooleanFunction(int numVariables) {
        //using string builder to construct string which will be the boolean formula
        StringBuilder sb = new StringBuilder();
        int upperBound = random.nextInt(1,6);
        //generating DNF formula, which consists maximally of 5 conjunctions
        for(int x = 0; x < upperBound; x++) {
            //each conjunction consist of N variables alphabetically ordered
            //negations are randomly added
            for (int i = 0; i < numVariables; i++) {
                sb.append(random.nextBoolean() ? "!" : "");
                sb.append((char) ('A' + i));
                if(i != numVariables - 1) {
                    sb.append("*");
                }
            }
            //to not add the plus sign to the end of the formula
            if (x != upperBound - 1){
                sb.append("+");
            }
        }
        System.out.println("\nThe generated function for next BDD is: "+sb.toString());
        return sb.toString();
    }

    public List<String> generateVariableOrder(int numVariables) {
        List<String> order = new ArrayList<>();
        //creating the order for my boolean function
        for (int i = 0; i < numVariables; i++){
            order.add(String.valueOf((char) ('A' + i)));
        }
        //this is to shuffle the order of the variables so the order wont have alphabetical order
        Collections.shuffle(order);
        //printing the order
        System.out.println("The order is: "+order);
        return order;
    }
}
