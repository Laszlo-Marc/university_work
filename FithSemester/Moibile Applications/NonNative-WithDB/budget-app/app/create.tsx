import TopBar from "@/components/TopBar";
import { getCategoryIcon } from "@/constants/categoryIcons";
import { useRepo } from "@/context/Context";
import { useRouter } from "expo-router";
import React from "react";
import { View } from "react-native";
import ExpenseForm from "../components/ExpenseForm";
export default function CreateExpenseScreen() {
  const router = useRouter();
  const { expenses, addExpense } = useRepo();

  const handleSubmit = (data: any) => {
    const newId =
      expenses.length > 0 ? Math.max(...expenses.map((e) => e.id)) + 1 : 1;
    const expense = {
      id: newId,
      ...data,
      icon: getCategoryIcon(data.category),
    };
    addExpense(expense);
    router.push("/");
  };

  return (
    <View style={{ flex: 1 }}>
      <TopBar title="Create Expense" />
      <View style={{ flex: 1 }}>
        <ExpenseForm
          onSubmit={handleSubmit}
          defaultValues={{
            category: "",
            description: "",
            amount: 0,
            date: new Date(),
            transactionAccount: "",
            merchant: "",
          }}
        />
      </View>
    </View>
  );
}
