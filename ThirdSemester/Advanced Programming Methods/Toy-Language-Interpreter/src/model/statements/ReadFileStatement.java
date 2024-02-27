package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.expressions.IExpression;
import model.types.IType;
import model.types.IntType;
import model.types.StringType;
import model.values.IValue;
import model.values.IntValue;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement{
    private final IExpression exp;
    private final String var;
    public ReadFileStatement(IExpression exp,String var){
        this.exp=exp;
        this.var=var;

    }
    @Override
    public PrgState execute(PrgState state) throws ExecutionException, EvaluationException {
        MyIDict<String, IValue> symTbl=state.getSymTable();
        MyIDict<StringValue, BufferedReader> fileTable = state.getFileTable();

        if(!symTbl.containsKey(var)){
            throw new EvaluationException(var + "is not in the symTable");

        }
        IValue value=symTbl.lookup(var);
        if(!value.getType().equals(new IntType())){
            throw new EvaluationException(value+"is not of type int");

        }
        value = exp.eval(symTbl, state.getHeap());
        if(!value.getType().equals(new StringType())){
            throw new EvaluationException(value +"is not of string type");
        }
        StringValue castVal=(StringValue) value;
        if(!fileTable.containsKey(castVal)){
            throw new EvaluationException("the file table does not contain" + castVal.getStringValue());

        }
        BufferedReader br= fileTable.lookup(castVal);
        try{
            String line=br.readLine();
            if(line==null || line.isEmpty())
                line="0";
            symTbl.put(var,new IntValue(Integer.parseInt(line)));
        }catch (IOException e){
            throw new EvaluationException(("could not read from the file: "+ castVal.getStringValue()));
        }
        return null;
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException {
        if(!exp.typeCheck(type).equals(new StringType())){
            throw new EvaluationException("ReadFile requires a StringType as a parameter");
        }
        if(!type.lookup(var).equals(new IntType())){
            throw new EvaluationException("ReadFile requires an int as a parameter");
        }
        return type;
    }

    @Override
    public String toString() {
        return "ReadFile{" + exp + ", " + var + "}";
    }
}
