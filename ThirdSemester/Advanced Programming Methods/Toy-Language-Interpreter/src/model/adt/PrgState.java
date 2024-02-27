package model.adt;

import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.excep.StackException;
import model.statements.IStatement;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class PrgState {
    MyIStack<IStatement> exeStack;
    MyIDict<String, IValue> symTable;
    MyIList<String> out;
    MyIDict<StringValue, BufferedReader> fileTable;

    public IHeap heap;
    static public Lock lock = new ReentrantLock();
    ILatchTable latchTable;
    private static int id;
    private int currentId;

    private static synchronized Integer newId() {
        id++;
        return id;
    }

    public int getId() {
        return this.currentId;
    }

    public PrgState(IStatement originalProgram) {
        exeStack = new MyStack<>();
        symTable = new MyDict<>();
        out = new MyList<>();
        fileTable = new MyDict<>();
        heap = new MyHeap();
        latchTable=new LatchTable();
        exeStack.push(originalProgram);
        this.currentId = newId();
    }

    public PrgState(MyIStack<IStatement> exeStack, MyIDict<String, IValue> symTable, MyIList<String> out, MyIDict<StringValue, BufferedReader> fileTable, IHeap heap,ILatchTable latchTable) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.heap = heap;
        this.latchTable=latchTable;
        this.currentId = newId();
    }
    public PrgState(MyIStack<IStatement> exeStack, MyIDict<String, IValue> symTable, MyIList<String> out, MyIDict<StringValue, BufferedReader> fileTable, IHeap heap,IStatement program,ILatchTable latchTable) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.heap = heap;
        this.latchTable=latchTable;
        exeStack.push(program);
        this.currentId = newId();
    }

    public IHeap getHeap() {

        return heap;
    }


    public MyIStack<IStatement> getExStack() {

        return exeStack;
    }


    public MyIList<String> getOut() {

        return out;
    }

    public MyIDict<String,IValue> getSymTable(){
        return this.symTable;
    }
    public MyIDict<StringValue, BufferedReader> getFileTable() {
        return this.fileTable;
    }


    public void setSymTable(MyIDict<String, IValue> symTable) {
        this.symTable=symTable;
    }

    public ILatchTable getLatchTable(){
        return this.latchTable;
    }
    public void setLatchTable(ILatchTable latchTable){
        this.latchTable=latchTable;
    }

    public String outToString() {
        StringBuilder outStringBuilder = new StringBuilder();
        for (String object : out) {
            outStringBuilder.append(object).append("\n");
        }
        return outStringBuilder.toString();
    }

    public String fileTableToString() {
        StringBuilder fileTblStringBuilder = new StringBuilder();
        for (StringValue key : fileTable.keySet()) { // enumeration to list
            fileTblStringBuilder.append(String.format("%s\n", key.toString()));
        }

        return fileTblStringBuilder.toString();
    }

    public String heapToString() {
        StringBuilder heapStringBuilder = new StringBuilder();

        for (Integer position : heap.getContent().keySet()) {
            heapStringBuilder.append(position).append(" -> ").append(heap.getContent().get(position).toString()).append("\n");
        }

        return heapStringBuilder.toString();
    }

    public String latchTableToString() throws ExecutionException {
        StringBuilder latchTableStringBuilder = new StringBuilder();
        for (int key: latchTable.keySet()) {
            latchTableStringBuilder.append(String.format("%d -> %d\n", key, latchTable.get(key)));
        }
        return latchTableStringBuilder.toString();
    }


    @Override
    public String toString() {


        return String.format("ID:%d\n\n~ EXECUTION STACK ~\n%s\n~ SYMBOL TABLE ~\n%s\n~ OUTPUT ~\n%s\n~ FILE TABLE~\n%s\n~ HEAP ~\n%s\n~ LATCH TABLE ~\n%s", id, exeStack, symTable.toString(), out, fileTableToString(), heapToString(),latchTable.toString());



    }

    public PrgState oneStep() throws EvaluationException, ExecutionException, StackException {
        if (exeStack.isEmpty())
            throw new ExecutionException("Execution stack is empty!");
        IStatement crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }


    public boolean isNotCompleted() {
        return !exeStack.isEmpty();
    }

    public void setExStack(MyIStack<IStatement> exeStack) {
        this.exeStack=exeStack;
    }
}

