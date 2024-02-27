package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.types.IType;

public class NopStmt implements IStatement {
    public PrgState execute(PrgState state) {
        return state;
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException {
        return type;
    }

    @Override
    public String toString() {
        return "no operation";
    }
}
