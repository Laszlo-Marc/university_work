package View.GUI;

import controller.Controller;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import model.adt.PrgState;
import model.expressions.*;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import repository.IRepository;
import repository.Repository;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ProgramListSelector {
    private ProgramRunController programController;
    @FXML
    private List<IStatement> programStatements;

    public void setProgramController(ProgramRunController programController) {
        this.programController = programController;
        this.programController.firstExec = true;
    }

    @FXML
    private ListView<IStatement> programList;
    @FXML
    private Button displayButton;

    private void buildProgramList(){
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
                new CompStmt(new CompStmt(new AssignStmt("a", new ValueExpression(new BoolValue(true))),
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

        programStatements = new ArrayList<>(Arrays.asList(ex1, ex2, ex3, ex4, ex5, ex6, ex7, ex8, ex9, ex10, ex11, ex12));
    }
    @FXML
    public void initialize() {
        buildProgramList();
        programList.setItems(FXCollections.observableArrayList(programStatements));

        displayButton.setOnAction(actionEvent -> {
            int index = programList.getSelectionModel().getSelectedIndex();

            if (index < 0)
                return;

            PrgState initialProgramState = new PrgState(programStatements.get(index));
            IRepository repository = new Repository("logFile" + (index + 1));
            repository.add(initialProgramState);
            Controller ctrl = new Controller(repository);
            try {
                ctrl.runTypeChecker();
            } catch (Exception e) {
                System.out.println(e.getMessage());
                System.exit(1);
            }
            programController.setController(ctrl);
        });
    }
}