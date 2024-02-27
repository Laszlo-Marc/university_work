package repository;

import model.adt.PrgState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    //PrgState getCrtPrg();
    void add(PrgState e);
    String getLogFilePath();
    List<PrgState> getProgramStates();

    void logProgramStateExec(PrgState state)throws IOException;
    void setProgramStates(List<PrgState> prgStates);
}