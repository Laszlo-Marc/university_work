import Expense from "@/data/Expense";
import ExpenseRepository from "@/data/ExpenseRepository";
import React, { createContext, useContext, useState } from "react";

const repo = new ExpenseRepository();

type RepoContextType = {
  expenses: Expense[];
  addExpense: (expense: Expense) => void;
  updateExpense: (expense: Expense) => void;
  deleteExpense: (id: number) => void;
};

const RepoContext = createContext<RepoContextType | undefined>(undefined);

export const RepoProvider: React.FC<{ children: React.ReactNode }> = ({
  children,
}) => {
  const [expenses, setExpenses] = useState(repo.getExpenses());

  const addExpense = (expense: Expense) => {
    repo.addExpense(expense);
    setExpenses((prev) => {
      if (!prev.some((e) => e.id === expense.id)) {
        return [...prev, expense];
      }
      return prev;
    });
  };

  const updateExpense = (expense: Expense) => {
    repo.updateExpense(expense);
    setExpenses((prev) =>
      prev.map((e) => (e.id === expense.id ? { ...e, ...expense } : e))
    );
  };

  const deleteExpense = (id: number) => {
    repo.deleteExpense(id);
    setExpenses((prev) => prev.filter((e) => e.id !== id));
  };

  return (
    <RepoContext.Provider
      value={{ expenses, addExpense, updateExpense, deleteExpense }}
    >
      {children}
    </RepoContext.Provider>
  );
};

export const useRepo = (): RepoContextType => {
  const context = useContext(RepoContext);
  if (!context) {
    throw new Error("useRepo must be used within a RepoProvider");
  }
  return context;
};
