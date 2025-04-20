# 🏦 Banking System Management (C++)

A comprehensive **C++ banking system** that supports user authentication, client management, transactions, and admin-level user controls with permission-based access.

---

## 🔑 Features

### ✅ User Authentication
- Secure login with username and password
- Permission-based access control using bitmasking
- Active session management

### 👥 Client Management
- Add, delete, update client details
- Search for clients by account number or name
- View all clients in a clean, formatted table

### 💰 Transaction Processing
- Deposit and withdraw funds
- Display total account balances
- View client transaction history

### 🛠️ User Administration (Admin Only)
- Add or remove system users
- Set specific permissions for users
- Update user credentials (username/password)

### 💾 Data Persistence
- All client, user, and transaction data saved to local text files
- Automatic loading and saving on system startup/shutdown

---

## 🧱 Permissions System

The system uses a **bitmask-based permission system** to control user access:

| Permission Bit | Value | Functionality          |
|----------------|-------|------------------------|
| Show clients   | 1     | View client list       |
| Add client     | 2     | Add new client         |
| Delete client  | 4     | Remove a client        |
| Update client  | 8     | Modify client details  |
| Find client    | 16    | Search for a client    |
| Transactions   | 32    | Deposit/Withdraw funds |
| Manage users   | 64    | Admin control panel    |
| Full Access    | -1    | All permissions (admin)|

---

## 🚀 Getting Started

### ✅ Prerequisites
- A C++ compiler (GCC, Clang, or MSVC)

### 🧪 Build & Run
```bash
g++ main.cpp -o BankingSystem
./BankingSystem
```
### 👤 Default Admin Credentials
For testing purposes:
- Username: admin
- Password: 1234

### 📄 License
This project is open-source — free to use, modify, and distribute.
