import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.*;


public class Testing{
    public static void main(String[] args) throws FileNotFoundException {
        //this is the main method used for testing the binary decision diagram
        System.out.println("🧪 TESTING STARTS 🧪");
        BDD bdd = new BDD();
        BooleanFunctionGenerator bfg = new BooleanFunctionGenerator();
        Scanner scanner = new Scanner(System.in);

        //choosing from options and based on options selected, you input additional data
        System.out.println("What method would you like to test");
        System.out.println("1. BDD_create");
        System.out.println("2. BDD_create_with_best_order");
        System.out.println("3. BDD_use");


        int choice = scanner.nextInt();

        switch (choice) {
            case 1 -> {
                System.out.println("How many functions would you like to test ?");
                int numFunctions = scanner.nextInt();
                System.out.println("And how many variables would you like to be used? (max 26, min 2)");
                int numVariables = scanner.nextInt();
                if(numVariables > 26 || numVariables < 2){
                    System.out.println("The amount of variables cannot exceed 26, try again !");
                    break;
                }
                bfg.generateAndMeasureBDDCreate(numFunctions, numVariables);
            }
            case 2 -> {
                System.out.println("How many functions would you like to test ?");
                int numFunctionsBest = scanner.nextInt();
                System.out.println("And how many variables would you like to be used (max 26, min 2)?");
                int numVariablesBest = scanner.nextInt();
                if(numVariablesBest > 26 || numVariablesBest < 2){
                    System.out.println("The amount of variables cannot exceed 26, try again !");
                    break;
                }
                bfg.generateAndMeasureBDDCreateWithBestOrder(numFunctionsBest, numVariablesBest);
            }
            case 3 -> {
                System.out.println("Input the Boolean function for which you would like to test BDD_use method !");
                String bfunction = scanner.next();
                System.out.println("Input the order of the variables !");
                String order = scanner.next();
                bdd = bdd.BDD_create(bfunction, Arrays.asList(order.split("")));
                BinaryTreePrinter printer = new BinaryTreePrinter(bdd.root);
                printer.print(new PrintStream("./data.txt"));
                System.out.println("The bdd has been created and is now printed in text file \"data.txt\"");
                System.out.println("Please input the binary string to represent the input for the boolean function, please note that amount of bits has to be equal to the amount of variables used !");
                String input = scanner.next();
                char x = bdd.BDD_use(bdd, input);
                System.out.println("The output of the boolean function for the input " + input + " is " + x);
            }
            default -> System.out.println("⚠️ Invalid input, please try again ⚠️");
        }

    }
}
