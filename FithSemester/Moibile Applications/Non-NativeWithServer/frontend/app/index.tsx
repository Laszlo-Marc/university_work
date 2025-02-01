import { useRouter } from "expo-router";
import React, { useCallback, useEffect } from "react";
import { Alert, FlatList, StyleSheet, Text, View } from "react-native";
import AddExpenseButton from "../components/AddExpenseButton";
import ExpenseItem from "../components/ExpenseItem";
import { useRepo } from "../context/Context";

export default function Index() {
  const { expenses, deleteExpense } = useRepo();
  const router = useRouter();

  const confirmDelete = useCallback(
    (id: number) => {
      Alert.alert(
        "Confirm Deletion",
        "Are you sure you want to delete this expense?",
        [
          { text: "Cancel", style: "cancel" },
          {
            text: "Delete",
            style: "destructive",
            onPress: async () => {
              try {
                await deleteExpense(id); // Await completion for immediate UI update
              } catch (error) {
                Alert.alert(
                  "Error",
                  "Failed to delete expense. Please try again."
                );
              }
            },
          },
        ]
      );
    },
    [deleteExpense]
  );
  useEffect(() => {}, [expenses]);
  return (
    <View style={styles.container}>
      {/* Top Bar Section */}
      <View style={styles.topBar}>
        <Text style={styles.title}>Expenses</Text>
      </View>

      {/* FlatList with Expenses */}
      <FlatList
        data={expenses}
        extraData={expenses}
        keyExtractor={(item) => item.id.toString()}
        renderItem={({ item }) => (
          <ExpenseItem
            expense={item}
            onEdit={() => router.push(`/update?id=${item.id}`)}
            onPress={() => router.push(`/details?id=${item.id}`)}
            onDelete={() => confirmDelete(item.id)}
          />
        )}
        contentContainerStyle={styles.listContent}
      />

      {/* Add Expense Button */}
      <View style={styles.buttonContainer}>
        <AddExpenseButton onPress={() => router.push("/create")} />
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 16,
  },
  topBar: {
    height: 60,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#f8f8f8",
    borderRadius: 8,
    marginBottom: 16,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
    elevation: 2,
    marginTop: 35,
  },
  title: {
    fontSize: 20,
    fontWeight: "bold",
    color: "#333",
  },
  listContent: {
    paddingBottom: 72,
  },
  buttonContainer: {
    position: "absolute",
    bottom: 16,
    alignSelf: "center",
  },
});
