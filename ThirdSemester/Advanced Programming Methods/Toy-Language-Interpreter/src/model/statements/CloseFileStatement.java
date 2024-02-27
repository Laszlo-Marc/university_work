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
import java.io.IOException;

public class CloseFileStatement implements IStatement{
    private final IExpression exp;

    public CloseFileStatement(IExpression exp){
        this.exp=exp;
    }
    @Override
    public PrgState execute(PrgState state) throws ExecutionException, EvaluationException {
        IValue value= exp.eval(state.getSymTable(),state.getHeap());
        if(!value.getType().equals(new StringType())){
            throw new EvaluationException(exp+"expression is not of type string");
        }
        StringValue fileName=(StringValue) value;
        MyIDict<StringValue, BufferedReader> fileTable=state.getFileTable();
        if(!fileTable.containsKey(fileName)){
            throw new EvaluationException(value+"is not in the symTable");
        }
        BufferedReader br=fileTable.lookup(fileName);
        try{
            br.close();
        }catch (IOException e) {
            throw new EvaluationException("Unexpected error in closing" + value);
        }
        fileTable.remove(fileName);
        return null;
    }


    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException {
        if (!exp.typeCheck(type).equals(new StringType()))
            throw new EvaluationException("CloseReadFile statement requires a StringType expression!");
        return type;
    }

    @Override
    public String toString() {
        return String.format("CloseReadFile{%s}", exp);
    }
}
