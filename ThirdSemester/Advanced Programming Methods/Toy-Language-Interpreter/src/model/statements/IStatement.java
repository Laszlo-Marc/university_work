package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.types.IType;

public interface IStatement {
    PrgState execute(PrgState state) throws ExecutionException, EvaluationException;
    MyIDict<String, IType> typeCheck(MyIDict<String,IType> type) throws EvaluationException,ExecutionException;


}