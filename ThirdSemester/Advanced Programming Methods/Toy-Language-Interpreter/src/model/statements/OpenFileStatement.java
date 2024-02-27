package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.expressions.IExpression;
import model.types.IType;
import model.types.StringType;
import model.values.IValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenFileStatement implements IStatement {
    private final IExpression exp;

    public OpenFileStatement(IExpression exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws ExecutionException, EvaluationException {
        IValue value = exp.eval(state.getSymTable(),state.getHeap());
        if (!value.getType().equals(new StringType()))
            throw new EvaluationException(exp+" does not evaluate to StringType!");
        StringValue fileName = (StringValue) value;
        MyIDict<StringValue, BufferedReader> fileTable = state.getFileTable();
        if (fileTable.containsKey(fileName))
            throw new ExecutionException(fileName+" is already opened!");
        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader(fileName.getStringValue()));
        } catch (IOException e) {
            throw new EvaluationException(fileName+" could not be opened!");
        }
        fileTable.put(fileName, br);
        return null;
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException {
        if (!exp.typeCheck(typeEnv).equals(new StringType()))
            throw new EvaluationException("OpenReadFile error: StringType expression required!");
        return typeEnv;
    }

    @Override
    public String toString() {
        return "OpenReadFile{"+exp+"}";
    }
}
