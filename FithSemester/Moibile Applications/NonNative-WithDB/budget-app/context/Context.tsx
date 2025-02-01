import Expense from "@/data/Expense";
import * as SQLite from "expo-sqlite";
import React, { createContext, useContext, useEffect, useState } from "react";

const db = SQLite.openDatabaseAsync("expenses.db");

const initializeDatabase = async () => {
  (await db).execAsync(`
    PRAGMA journal_mode = WAL;
    CREATE TABLE IF NOT EXISTS expenses (
      id INTEGER PRIMARY KEY NOT NULL,
      category TEXT NOT NULL,
      description TEXT,
      amount REAL NOT NULL,
      date TEXT NOT NULL,
      account TEXT,
      merchant TEXT,
      icon TEXT
    );
  `);
};

type RepoContextType = {
  expenses: Expense[];
  addExpense: (expense: Expense) => Promise<void>;
  updateExpense: (expense: Expense) => Promise<void>;
  deleteExpense: (id: number) => Promise<void>;
};

const RepoContext = createContext<RepoContextType | undefined>(undefined);

export const RepoProvider: React.FC<{ children: React.ReactNode }> = ({
  children,
}) => {
  const [expenses, setExpenses] = useState<Expense[]>([]);

  // Load initial expenses from the database
  useEffect(() => {
    const fetchExpenses = async () => {
      //await initializeDatabase();
      const allExpenses = (await db).getAllAsync("SELECT * FROM expenses");
      const formattedExpenses = (await allExpenses).map(
        (row: any) =>
          new Expense(
            row.id,
            row.category,
            row.description,
            row.amount,
            new Date(row.date),
            row.account,
            row.merchant,
            row.icon
          )
      );
      setExpenses(formattedExpenses);
    };
    fetchExpenses();
  }, []);

  // Add an expense
  const addExpense = async (expense: Expense) => {
    (await db).runAsync(
      `INSERT INTO expenses (id, category, description, amount, date, account, merchant, icon)
       VALUES (?, ?, ?, ?, ?, ?, ?, ?);`,
      [
        expense.id,
        expense.category,
        expense.description,
        expense.amount,
        expense.date.toISOString(),
        expense.transactionAccount,
        expense.merchant,
        expense.icon,
      ]
    );
    setExpenses((prev) => [...prev, expense]);
  };

  // Update an expense
  const updateExpense = async (expense: Expense) => {
    (await db).runAsync(
      `UPDATE expenses
       SET category = ?, description = ?, amount = ?, date = ?, account = ?, merchant = ?, icon = ?
       WHERE id = ?;`,
      [
        expense.category,
        expense.description,
        expense.amount,
        expense.date.toISOString(),
        expense.transactionAccount,
        expense.merchant,
        expense.icon,
        expense.id,
      ]
    );
    setExpenses((prev) =>
      prev.map((e) => (e.id === expense.id ? { ...e, ...expense } : e))
    );
  };

  // Delete an expense
  const deleteExpense = async (id: number) => {
    (await db).runAsync("DELETE FROM expenses WHERE id = ?;", [id]);
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
