import { MaterialIcons } from "@expo/vector-icons";
import { useRouter } from "expo-router";
import React from "react";
import { Pressable, StyleSheet, Text, View } from "react-native";

interface TopBarProps {
  title: string;
  onGoBack?: () => void; // Optional custom callback for "go back"
}

const TopBar: React.FC<TopBarProps> = ({ title, onGoBack }) => {
  const router = useRouter();

  const handleGoBack = () => {
    if (onGoBack) {
      onGoBack();
    } else if (router.canGoBack()) {
      // Ensure `expo-router` supports this
      router.back();
    } else {
      router.push("/"); // Navigate to the home screen if no history
    }
  };

  return (
    <View style={styles.container}>
      <Pressable onPress={handleGoBack} style={styles.backButton}>
        <MaterialIcons name="arrow-back" size={24} color="#333" />
      </Pressable>
      <Text style={styles.title}>{title}</Text>
    </View>
  );
};

export default TopBar;

const styles = StyleSheet.create({
  container: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
    height: 60,
    backgroundColor: "#f8f8f8",
    paddingHorizontal: 16,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
    elevation: 2,
    marginTop: 50, // Adjust for safe area
    borderRadius: 8,
  },
  backButton: {
    padding: 8,
    borderRadius: 8,
  },
  title: {
    flex: 1,
    textAlign: "center",
    fontSize: 20,
    fontWeight: "bold",
    color: "#333",
  },
});
