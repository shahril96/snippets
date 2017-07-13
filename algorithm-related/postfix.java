import java.util.*;

public class postfix {

    public static void main(String args[]) {

        String infix = "x-(y*a/b-(z+d*e)+c)/f";

        System.out.println("Infix : " + infix);
        System.out.println("Postfix : " + inf2postf(infix));

    }

    private static String inf2postf(String infix) {

        String postfix = "";
        Stack<Character> operator = new Stack<Character>();
        char popped;

        for (int i = 0; i < infix.length(); i++) {

            char get = infix.charAt(i);

            if (!isOperator(get))
                postfix += get;

            else if (get == ')')
                while ((popped = operator.pop()) != '(')
                    postfix += popped;

            else {
                while (!operator.isEmpty() && get != '(' && precedence(operator.peek()) >= precedence(get))
                    postfix += operator.pop();

                operator.push(get);
            }
        }
        // pop any remaining operator
        while (!operator.isEmpty())
            postfix += operator.pop();

        return postfix;
    }

    private static boolean isOperator(char i) {
        return precedence(i) > 0;
    }

    private static int precedence(char i) {

        if (i == '(' || i == ')') return 1;
        else if (i == '-' || i == '+') return 2;
        else if (i == '*' || i == '/') return 3;
        else return 0;
    }
}


