import { Ionicons } from "@expo/vector-icons";
import { LinearGradient } from "expo-linear-gradient";
import { useRouter } from "expo-router";
import { useSearchParams } from "expo-router/build/hooks";
import React from "react";
import { Button, StyleSheet, Text, TouchableOpacity, View } from "react-native";
import { useRepo } from "../context/Context";

export default function DetailExpenseScreen() {
  const { expenses } = useRepo();
  const router = useRouter();
  const searchParams = useSearchParams();
  const id = searchParams.get("id");

  const expense = expenses.find((e) => e.id === Number(id));

  if (!expense) {
    return (
      <View style={styles.container}>
        <Text style={styles.errorText}>Expense not found.</Text>
        <Button title="Go Back" onPress={() => router.push("/")} />
      </View>
    );
  }

  return (
    <LinearGradient colors={["#f9f9f9", "#ffffff"]} style={styles.screen}>
      <View style={styles.container}>
        <View style={styles.card}>
          <Text style={styles.field}>
            <Ionicons
              name="wallet"
              size={20}
              color="#007AFF"
              style={styles.icon}
            />
            <Text style={styles.label}>Category:</Text> {expense.category}
          </Text>
          <Text style={styles.field}>
            <Ionicons
              name="clipboard"
              size={20}
              color="#007AFF"
              style={styles.icon}
            />
            <Text style={styles.label}>Description:</Text> {expense.description}
          </Text>
          <Text style={styles.field}>
            <Ionicons
              name="cash"
              size={20}
              color="#007AFF"
              style={styles.icon}
            />
            <Text style={styles.label}>Amount:</Text> $
            {expense.amount.toFixed(2)}
          </Text>
          <Text style={styles.field}>
            <Ionicons
              name="calendar"
              size={20}
              color="#007AFF"
              style={styles.icon}
            />
            <Text style={styles.label}>Date:</Text>{" "}
            {expense.date.toDateString()}
          </Text>
          <Text style={styles.field}>
            <Ionicons
              name="card"
              size={20}
              color="#007AFF"
              style={styles.icon}
            />
            <Text style={styles.label}>Account:</Text>{" "}
            {expense.transactionAccount}
          </Text>
          <Text style={styles.field}>
            <Ionicons
              name="business"
              size={20}
              color="#007AFF"
              style={styles.icon}
            />
            <Text style={styles.label}>Merchant:</Text> {expense.merchant}
          </Text>
        </View>
        <TouchableOpacity
          style={styles.button}
          onPress={() => router.push("/")}
        >
          <Text style={styles.buttonText}>Go Back</Text>
        </TouchableOpacity>
      </View>
    </LinearGradient>
  );
}

const styles = StyleSheet.create({
  screen: {
    flex: 1,
  },
  container: {
    flex: 1,
    paddingHorizontal: 16,
    alignItems: "center",
    justifyContent: "center", // Center contents vertically
  },
  card: {
    width: "90%",
    padding: 16,
    backgroundColor: "#ffffff",
    borderRadius: 10,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 5 },
    shadowOpacity: 0.2,
    shadowRadius: 3,
    elevation: 5,
    marginBottom: 30, // Space between card and button
  },
  field: {
    fontSize: 18,
    marginVertical: 4,
    color: "#4A4A4A",
  },
  label: {
    fontWeight: "bold",
    color: "#007AFF",
  },
  icon: {
    marginRight: 8,
  },
  errorText: {
    fontSize: 18,
    color: "red",
    textAlign: "center",
    marginBottom: 16,
  },
  button: {
    backgroundColor: "#007AFF",
    paddingVertical: 12,
    paddingHorizontal: 20,
    borderRadius: 25,
    alignItems: "center",
    justifyContent: "center",
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 3 },
    shadowOpacity: 0.1,
    shadowRadius: 5,
    elevation: 3,
    marginBottom: 20, // Ensure spacing at the bottom
  },
  buttonText: {
    color: "#fff",
    fontSize: 16,
    fontWeight: "600",
    letterSpacing: 0.5,
  },
});
