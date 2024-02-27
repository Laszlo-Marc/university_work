package View;

import commands.ExitCommand;
import commands.RunCommand;
import controller.Controller;
import model.adt.MyDict;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.expressions.*;
import model.statements.*;
import model.types.*;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;

public class View {
    public static void main(String[] args) throws ExecutionException {

        TextMenu menu = new TextMenu();

        Controller c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14;

        IStatement ex1 = new CompStmt(new VarDecStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExpression(new IntValue(2))), new PrintStmt(new VarExpression("v"))));

        IStatement ex2 = new CompStmt(new VarDecStmt("a", new IntType()),
                new CompStmt(new VarDecStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExpression(new ValueExpression(new IntValue(2)), new ArithExpression(new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')),
                                new CompStmt(new AssignStmt("b", new ArithExpression(new VarExpression("a"), new ValueExpression(new IntValue(1)), '+')), new PrintStmt(new VarExpression("b"))))));

        IStatement ex3 = new CompStmt(new VarDecStmt("a", new BoolType()),
                new CompStmt(new VarDecStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExpression(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExpression("a"), new AssignStmt("v", new ValueExpression(new IntValue(2))), new AssignStmt("v", new ValueExpression(new IntValue(3)))), new PrintStmt(new VarExpression("v"))))));


        IStatement ex4 = new CompStmt(
                new VarDecStmt("varf", new StringType()),
                new CompStmt(
                        new AssignStmt("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompStmt(
                                new OpenFileStatement(new VarExpression("varf")),
                                new CompStmt(
                                        new VarDecStmt("varc", new IntType()),
                                        new CompStmt(
                                                new ReadFileStatement(new VarExpression("varf"), "varc"),
                                                new CompStmt(
                                                        new PrintStmt(new VarExpression("varc")),
                                                        new CompStmt(
                                                                new ReadFileStatement(new VarExpression("varf"), "varc"),
                                                                new CompStmt(
                                                                        new PrintStmt(new VarExpression("varc")),
                                                                        new CloseFileStatement(new VarExpression("varf"))))))))));

        IStatement ex5 = new CompStmt(new CompStmt(new VarDecStmt("a", new IntType()), new VarDecStmt("b", new IntType())),
                new CompStmt(new CompStmt(new AssignStmt("a", new ValueExpression(new IntValue(5))),
                        new AssignStmt("b", new ValueExpression(new IntValue(15)))),
                        new IfStmt(new RelationalExpression(new VarExpression("a"), new VarExpression("b"), "<"),
                                new PrintStmt(new VarExpression("a")), new PrintStmt(new VarExpression("b")))));

        IStatement ex6 = new CompStmt(new VarDecStmt("v", new RefType(new IntType())), new CompStmt(new HeapNewStmt("v", new ValueExpression(new IntValue(20))),
                new CompStmt(new VarDecStmt("a", new RefType(new RefType(new IntType()))), new CompStmt(
                        new HeapNewStmt("a", new VarExpression("v")), new CompStmt(new PrintStmt(new VarExpression("v")),
                        new PrintStmt(new VarExpression("a")))))));

        IStatement ex7 = new CompStmt(
                new VarDecStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new HeapNewStmt("v", new ValueExpression(new IntValue(20))),
                        new CompStmt(
                                new VarDecStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new HeapNewStmt("a", new VarExpression("v")),
                                        new CompStmt(
                                                new HeapNewStmt("v", new ValueExpression(new IntValue(30))),
                                                new PrintStmt(new HeapReadExpression(new HeapReadExpression(new VarExpression("a")))))))));

        IStatement ex9 = new CompStmt(
                new VarDecStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new HeapNewStmt("v", new ValueExpression(new IntValue(20))),
                        new CompStmt(
                                new PrintStmt(new HeapReadExpression(new VarExpression("v"))),
                                new CompStmt(
                                        new HeapWriteStmt("v", new ValueExpression(new IntValue(30))),
                                        new PrintStmt(new ArithExpression(new HeapReadExpression(new VarExpression("v")), new ValueExpression(new IntValue(5)), '+'))))));

        IStatement ex10 = new CompStmt(
                new VarDecStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new HeapNewStmt("v", new ValueExpression(new IntValue(20))),
                        new CompStmt(
                                new HeapNewStmt("v", new ValueExpression(new IntValue(30))),
                                new PrintStmt(new HeapReadExpression(new VarExpression("v"))))));


        IStatement ex8 = new CompStmt(
                new VarDecStmt("v", new IntType()),
                new CompStmt(
                        new AssignStmt("v", new ValueExpression(new IntValue(4))),
                        new CompStmt(
                                new WhileStmt(
                                        new RelationalExpression(new VarExpression("v"), new ValueExpression(new IntValue(0)), ">"),
                                        new CompStmt(
                                                new PrintStmt(new VarExpression("v")),
                                                new AssignStmt("v", new ArithExpression(new VarExpression("v"), new ValueExpression(new IntValue(1)), '-')))),
                                new PrintStmt(new VarExpression("v")))));

        IStatement ex11 = new CompStmt(
                new VarDecStmt("v", new IntType()),
                new CompStmt(
                        new VarDecStmt("a", new RefType(new IntType())),
                        new CompStmt(
                                new AssignStmt("v", new ValueExpression(new IntValue(10))),
                                new CompStmt(
                                        new HeapNewStmt("a", new ValueExpression(new IntValue(22))),
                                        new CompStmt(
                                                new ForkStmt(
                                                        new CompStmt(
                                                                new HeapWriteStmt("a", new ValueExpression(new IntValue(30))),
                                                                new CompStmt(
                                                                        new AssignStmt("v", new ValueExpression(new IntValue(32))),
                                                                        new CompStmt(
                                                                                new PrintStmt(new VarExpression("v")),
                                                                                new PrintStmt(new HeapReadExpression(new VarExpression("a"))))))),
                                                new CompStmt(
                                                        new PrintStmt(new VarExpression("v")),
                                                        new PrintStmt(new HeapReadExpression(new VarExpression("a")))))))));

        IStatement ex12 = new CompStmt(new VarDecStmt("a", new RefType(new IntType())), new CompStmt(
                new VarDecStmt("counter", new IntType()),
                new WhileStmt(new RelationalExpression(new VarExpression("counter"),
                        new ValueExpression(new IntValue(10)), "<"),
                        new CompStmt(new ForkStmt(new ForkStmt(new CompStmt(
                                new HeapNewStmt("a",
                                        new VarExpression("counter")),
                                new PrintStmt(new HeapReadExpression(
                                        new VarExpression("a")))))),
                                new AssignStmt("counter", new ArithExpression(
                                        new VarExpression("counter"),
                                        new ValueExpression(new IntValue(1)),
                                        '+'))))));



        menu.addCommand(new ExitCommand("0", "exit"));
        try {
            ex1.typeCheck(new MyDict<String, IType>());
            c1 = new Controller("log1.txt", false);
            c1.addProgram(ex1);
            RunCommand r1 = new RunCommand(ex1, "1", ex1.toString(), c1);
            menu.addCommand(r1);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex2.typeCheck(new MyDict<String, IType>());
            c2 = new Controller("log2.txt", false);
            c2.addProgram(ex2);
            RunCommand r2 = new RunCommand(ex2, "2", ex2.toString(), c2);
            menu.addCommand(r2);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex3.typeCheck(new MyDict<String, IType>());
            c3 = new Controller("log3.txt", false);
            c3.addProgram(ex3);
            RunCommand r3 = new RunCommand(ex3, "3", ex3.toString(), c3);
            menu.addCommand(r3);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex4.typeCheck(new MyDict<String, IType>());
            c4 = new Controller("log6.txt", false);
            c4.addProgram(ex4);
            RunCommand r4 = new RunCommand(ex4, "4", ex4.toString(), c4);
            menu.addCommand(r4);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex5.typeCheck(new MyDict<String, IType>());
            c5 = new Controller("log5.txt", false);
            c5.addProgram(ex5);
            RunCommand r5 = new RunCommand(ex5, "5", ex5.toString(), c5);
            menu.addCommand(r5);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex6.typeCheck(new MyDict<String, IType>());
            c6 = new Controller("log6.txt", false);
            c6.addProgram(ex6);
            RunCommand r6 = new RunCommand(ex6, "6", ex6.toString(), c6);
            menu.addCommand(r6);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex11.typeCheck(new MyDict<String, IType>());
            c7 = new Controller("log7.txt", false);
            c7.addProgram(ex7);
            RunCommand r7 = new RunCommand(ex7, "7", ex7.toString(), c7);
            menu.addCommand(r7);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex8.typeCheck(new MyDict<String, IType>());
            c8 = new Controller("log8.txt", false);
            c8.addProgram(ex8);
            RunCommand r8 = new RunCommand(ex8, "8", ex8.toString(), c8);
            menu.addCommand(r8);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex9.typeCheck(new MyDict<String, IType>());
            c9 = new Controller("log9.txt", false);
            c9.addProgram(ex9);
            RunCommand r11 = new RunCommand(ex9, "9", ex9.toString(), c9);
            menu.addCommand(r11);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }

        try {
            ex10.typeCheck(new MyDict<String, IType>());
            c10 = new Controller("log10.txt", false);
            c10.addProgram(ex10);
            RunCommand r10 = new RunCommand(ex10, "10", ex10.toString(), c10);
            menu.addCommand(r10);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
        try {
            ex11.typeCheck(new MyDict<String, IType>());
            c11 = new Controller("log11.txt", false);
            c11.addProgram(ex11);
            RunCommand r11 = new RunCommand(ex11, "11", ex11.toString(), c11);
            menu.addCommand(r11);
        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }

        try {
            ex12.typeCheck(new MyDict<String, IType>());
            c12 = new Controller("log12.txt", false);
            c12.addProgram(ex12);
            RunCommand r12 = new RunCommand(ex12, "12", ex12.toString(), c12);
            menu.addCommand(r12);

        } catch (EvaluationException e) {
            System.out.println(e.getMessage());
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }


        menu.show();


    }

}
