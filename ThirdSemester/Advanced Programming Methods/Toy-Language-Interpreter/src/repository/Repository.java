package repository;

import model.adt.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Repository implements IRepository{
    List<PrgState> progStates;
    private final int currentPos;
    String logFilePath;
    public Repository(String lfp) {
        this.progStates = new LinkedList<>();
        this.currentPos=0;
        this.logFilePath=lfp;
        this.clearFile();
    }
    public Repository(PrgState programState, String logFilePath) throws IOException {
        this.logFilePath = logFilePath;
        this.progStates = new ArrayList<>();
        this.currentPos=0;
        this.add(programState);
        this.clearFile();
    }

    public String getLogFilePath(){

        return this.logFilePath;
    }
    public void add(PrgState e) {

        this.progStates.add(e);
    }
    /*
        public PrgState getCrtPrg() {
                return progStates.get(currentPos);
        }

     */
    public List<PrgState> getProgramStates(){

        return progStates;
    }
    @Override
    public String toString() {

        return "Repository: {" + progStates;
    }

    public void clearFile() {
        try {
            PrintWriter logFile;
            logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, false)));
            logFile.close();
        }catch (IOException e){
            System.out.println(e.getMessage());
        }
    }
    public void logProgramStateExec(PrgState state)throws IOException {
        PrintWriter logFile;
        logFile= new PrintWriter(new BufferedWriter(new FileWriter(logFilePath,true)));
        logFile.println(state.toString());
        logFile.close();
    }
    public void setProgramStates(List<PrgState> prgStates){
        this.progStates=prgStates;
    }
}
