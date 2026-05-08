import java.util.*;
import java.io.*;

public class Interpreter {
    public static void main(String[] args) {
        HashMap<String, Register> regMap = new HashMap<>();
        ArrayList<String> program = new ArrayList<>();
        HashMap<String, Integer> labelMap = new HashMap<>();
        int counter = 0;

        try {
            Scanner scan = new Scanner(new File("input.txt"));
            while (scan.hasNext()) {
                program.add(scan.next());
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found!");
        }

        for (int i = 0; i < program.size(); i++) {
            if (program.get(i).equals("label")) {
                String labelName = program.get(i + 1);
                labelMap.put(labelName, i);
            }
        }
        if(program.get(counter).equals("function"))
        {
            counter+=3; //Eat function and name

       

        while (counter < program.size()) {
            String token = program.get(counter);
            counter++;

            if (token.equals("endfunction")) break;

            else if (token.equals("float") || token.equals("bool") || token.equals("string") || token.equals("vector3")) {
                String varName = program.get(counter);
                counter++;
                regMap.put(varName, new Register(varName, token));
                //System.out.println("Declared " + token + " " + varName);
            }

            else if (token.equals("=")) 
            {

                String varName = program.get(counter);
                counter++;

                String valToken = program.get(counter);
                counter++;

                if (varName.contains(".")) {
                    String[] parts = varName.split("\\.");
                    String base = parts[0];
                    String field = parts[1];

                    float value = resolveValue(valToken, regMap);
                    regMap.get(base).setVector(field, value);
                }
                else {
                    if (regMap.containsKey(valToken)) {
                        valToken = regMap.get(valToken).getValue().toString();
                    }

                    regMap.get(varName).setValue(valToken);
                }
            }

            else if (token.equals("+")) {
                String destination = program.get(counter);
                counter++;
                if (destination.contains("."))
                {
                    String[] parts = destination.split("\\.");
                    String varName = parts[0];
                    String component = parts[1];

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 + op2;

                    regMap.get(varName).setVector(component, result);

                    //System.out.println("Added to " + varName + "." + component +
                      //  " = " + regMap.get(varName).getVector(component));
                    continue;
                }
                if (regMap.get(destination).getType().equals("float")) {
                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 + op2;
                    regMap.get(destination).setValue(result);

                    //System.out.println("Added to " + destination + " = " + regMap.get(destination).getValue());
                }

                else if (regMap.get(destination).getType().equals("bool")) {
                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);
                }
            }

            else if (token.equals("-")) {
                String destination = program.get(counter++);
                if(destination.contains("."))
                {
                    String[] parts = destination.split("\\.");
                    String varName = parts[0];
                    String component = parts[1];

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 - op2;

                    regMap.get(varName).setVector(component, result);

                    //System.out.println("Subtracted from " + varName + "." + component +
                       // " = " + regMap.get(varName).getVector(component));
                    continue;
                }
                if (regMap.get(destination).getType().equals("float")) {

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 - op2;
                    regMap.get(destination).setValue(result);

                    //System.out.println("Subtracted from " + destination + " = " + regMap.get(destination).getValue());
                }
            }

            else if (token.equals("*")) {
                String destination = program.get(counter++);
                if(destination.contains("."))
                {
                    String[] parts = destination.split("\\.");
                    String varName = parts[0];
                    String component = parts[1];

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 * op2;

                    regMap.get(varName).setVector(component, result);

                    //System.out.println("Multiplied to " + varName + "." + component +
                      //  " = " + regMap.get(varName).getVector(component));
                    continue;
                }
                if (regMap.get(destination).getType().equals("float")) {

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 * op2;
                    regMap.get(destination).setValue(result);

                    //System.out.println("Multiplied to " + destination + " = " + regMap.get(destination).getValue());
                }
            }

            else if (token.equals("/")) {
                String destination = program.get(counter++);
                if(destination.contains("."))
                {
                    String[] parts = destination.split("\\.");
                    String varName = parts[0];
                    String component = parts[1];

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    if (op2 != 0) {
                        float result = op1 / op2;
                        regMap.get(varName).setVector(component, result);
                        //System.out.println("Divided from " + varName + "." + component +
                            //" = " + regMap.get(varName).getVector(component));
                    } else {
                        //System.out.println("Error: Division by zero");
                    }
                    continue;
                }
                if (regMap.get(destination).getType().equals("float")) {

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    if (op2 != 0) {
                        float result = op1 / op2;
                        regMap.get(destination).setValue(result);
                        //System.out.println("Divided from " + destination + " = " + regMap.get(destination).getValue());
                    } else {
                        //System.out.println("Error: Division by zero");
                    }
                }
            }

            else if (token.equals("==")) {
                String destination = program.get(counter++);
                if(destination.contains("."))
                {
                    String[] parts = destination.split("\\.");
                    String varName = parts[0];
                    String component = parts[1];

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    if (op1 == op2) {
                        regMap.get(varName).setVector(component, 1.0f);
                        //System.out.println("Compared " + varName + "." + component + " = true");
                    } else {
                        regMap.get(varName).setVector(component, 0.0f);
                        //System.out.println("Compared " + varName + "." + component + " = false");
                    }
                    continue;
                }
                if (regMap.get(destination).getType().equals("bool")) {

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    if (op1 == op2) {
                        regMap.get(destination).setValue(1);
                        //System.out.println("Compared " + destination + " = true");
                    } else {
                        regMap.get(destination).setValue(0);
                        //System.out.println("Compared " + destination + " = false");
                    }
                }

            }
                else if (token.equals("<")) {
                    String destination = program.get(counter++);
                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);
                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);
                    if (op1 < op2)
                        regMap.get(destination).setValue(1);
                    else
                        regMap.get(destination).setValue(0);
                }

                else if (token.equals(">")) {
                    String destination = program.get(counter++);
                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);
                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);
                    if (op1 > op2)
                        regMap.get(destination).setValue(1);
                    else
                        regMap.get(destination).setValue(0);
                }
                else if (token.equals(">=")) {
                String destination = program.get(counter++);
                if (regMap.get(destination).getType().equals("bool"))
                {
                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);
                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    if (op1 >= op2) {
                        regMap.get(destination).setValue(1);
                        //System.out.println("Compared " + destination + " = true");
                    } else {
                        regMap.get(destination).setValue(0);
                        //System.out.println("Compared " + destination + " = false");
                            }
                 }

            }

            else if (token.equals("<=")) {
                String destination = program.get(counter++);
                if (regMap.get(destination).getType().equals("bool")) {

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    if (op1 <= op2) {
                        regMap.get(destination).setValue(1);
                        //System.out.println("Compared " + destination + " = true");
                    } else {
                        regMap.get(destination).setValue(0);
                        //System.out.println("Compared " + destination + " = false");
                    }
                }
            }

            else if (token.equals("!=")) {
                String destination = program.get(counter++);
                if (regMap.get(destination).getType().equals("bool")) {

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    if (op1 != op2) {
                        regMap.get(destination).setValue(1);
                        //System.out.println("Compared " + destination + " = true");
                    } else {
                        regMap.get(destination).setValue(0);
                        //System.out.println("Compared " + destination + " = false");
                    }
                }
            }

            else if (token.equals("%")) {
                String destination = program.get(counter++);
                if(destination.contains("."))
                {
                    String[] parts = destination.split("\\.");
                    String varName = parts[0];
                    String component = parts[1];

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 % op2;

                    regMap.get(varName).setVector(component, result);

                    
                    continue;
                }
                if (regMap.get(destination).getType().equals("float")) {

                    String operand1 = program.get(counter++);
                    String operand2 = program.get(counter++);

                    float op1 = resolveValue(operand1, regMap);
                    float op2 = resolveValue(operand2, regMap);

                    float result = op1 % op2;
                    regMap.get(destination).setValue(result);

                    //System.out.println("Modded " + destination + " = " + regMap.get(destination).getValue());
                }
            }

            else if (token.equals("jump")) {
                String labelname = program.get(counter);
                counter = labelMap.get(labelname);
                counter++;
            }

            else if (token.equals("jumpif")) {
                String condition = program.get(counter);
                counter++;
                String labelname = program.get(counter);
                counter++;
                if (regMap.get(condition).getValue().toString().equals("1")) {
                    counter = labelMap.get(labelname);
                    counter++;
                }
            }
            else if (token.equals("callfunction"))
            {
                ArrayList<String> arglist = new ArrayList<>();
                String funcname = program.get(counter);
                counter++;
                if(funcname.equals("print"))
                {

                String returntype = program.get(counter);
                counter++;
                if(program.get(counter).equals("args"))
                {
                    counter++;
                    while(!program.get(counter).equals("endargs"))
                    {
                        arglist.add(program.get(counter));
                        counter++;
                    }
                    for(int i = 0; i<arglist.size(); i++)
                    {
                        String arg = arglist.get(i);

                        if (arg.contains(".")) {
                            String[] parts = arg.split("\\.");
                            String varName = parts[0];
                            String field = parts[1];

                            float value = regMap.get(varName).getVector(field);
                            System.out.print(value + " ");
                        }
                        else if (regMap.containsKey(arg)) {
                            System.out.print(regMap.get(arg).getValue() + " ");
                        }
                        else {
                            System.out.print(arg + " ");
                        }
                        
                    }
                }
                counter++; //Eat endargs
                System.out.println();
            }
                
            }
        }

    }

        //System.out.println("\nFinal register values:");
        /*for (String key : regMap.keySet()) {
            if (regMap.get(key).getType().equals("vector3")) {
                HashMap<String, Float> vec = (HashMap<String, Float>) regMap.get(key).getValue();
                System.out.println(key + " = (" + vec.get("r") + ", " + vec.get("g") + ", " + vec.get("b") + ")");
            }
            else if (regMap.get(key).getType().equals("bool")) {
                if (regMap.get(key).getValue().toString().equals("0")) {
                    System.out.println(key + " = false");
                } else {
                    System.out.println(key + " = true");
                }
            }
            else {
                System.out.println(key + " = " + regMap.get(key).getValue());
            }
        }*/
    }

        public static float resolveValue(String token, HashMap<String, Register> regMap) {
            if (token.contains(".")) {
                // check if it's a number first
                try {
                    return Float.parseFloat(token);
                } catch (NumberFormatException e) {
                    // it's a vector dot access like v.r
                    String[] parts = token.split("\\.");
                    String varName = parts[0];
                    String field = parts[1];
                    Register r = regMap.get(varName);
                    return r.getVector(field);
                }
            }
            if (regMap.containsKey(token)) {
                return Float.parseFloat(regMap.get(token).getValue().toString());
            } else {
                return Float.parseFloat(token);
            }
        }
}