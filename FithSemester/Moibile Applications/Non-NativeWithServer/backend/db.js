// db.js
const sqlite3 = require("sqlite3").verbose();

const db = new sqlite3.Database("expenses.db", (err) => {
  if (err) console.error("Database connection error:", err);
  else console.log("Connected to SQLite database.");
});

// Initialize table
db.serialize(() => {
  db.run(`
    CREATE TABLE IF NOT EXISTS expenses (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      category TEXT NOT NULL,
      description TEXT,
      amount REAL NOT NULL,
      date TEXT NOT NULL,
      transactionAccount TEXT,
      merchant TEXT,
      icon TEXT
    );
  `);
});

module.exports = db;
