#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
using namespace std;

struct stClient
{
    string accountNumber;
    string pinCode;
    string fullName;
    string phone;
    double accountBalance = 0;
    bool markDelete = false;
};

struct stUser
{
    string username;
    string password;
    int permission = 0;
    bool markDelete = false;
};

enum enMainMenu
{
    _showAllClient = 1,
    _addNewClient,
    _deleteClient,
    _updateClientData,
    _findClient,
    _transactions,
    _manageUsers,
    _logOut,
};

enum enTransactionMenu
{
    _deposit = 1,
    _withdraw,
    _totalBalances,
    _mainMenu
};

enum enManageUsers
{
    _listUsers = 1,
    _addNewUser,
    _deleteUser,
    _updateUser,
    _findUser,
    __mainMenu,
};

const string clientFileName = "clients.txt", usersFileName = "users.txt";

stUser user;

void mainMenu();

void mangeUsersMenu(const stUser user);

bool userExistsByUsername(string username, const vector<stUser> usersData, stUser& foundUser);

bool userExistsByUsername(string username, const vector<stUser> usersData);

stClient readClientData(const vector<stClient>& clientsData);

stClient readUpdatedClientData(string accountNumber);

void transactionMenu(stUser user);

// -++-+-+-+-++-+-+-+--+-++--+-+-++-+-+-+--++-

short getDividerLength(string mainStr)
{

    return 30 + mainStr.length();
}

void printHeader(string mainStr)
{

    string formattedStr = mainStr;

    short dividerLength = getDividerLength(mainStr);

    for (int i = 0; i < (dividerLength - mainStr.length()) / 2; i++)
    {

        formattedStr = i >= 5 ? '=' + formattedStr + '=' : i == 2 ? '+' + formattedStr + '+' : ' ' + formattedStr + ' ';
    }

    cout << string(dividerLength, '=') << endl;
    cout << formattedStr << endl;
    cout << string(dividerLength, '=') << endl;
}

string recordToLine(stClient clientData, string separator = "#//#")
{

    string dataLine;

    dataLine = clientData.accountNumber + separator;
    dataLine += clientData.pinCode + separator;
    dataLine += clientData.fullName + separator;
    dataLine += clientData.phone + separator;
    dataLine += to_string(clientData.accountBalance);

    return dataLine;
}

string recordToLine(stUser userData, string separator = "#//#")
{

    string dataLine;

    dataLine = userData.username + separator;
    dataLine += userData.password + separator;
    dataLine += to_string(userData.permission);

    return dataLine;
}

void saveClientDataToFile(const vector<stClient>& clientsData, bool append = false)
{

    fstream clientFile;

    ios::openmode mode = append ? (ios::out | ios::app) : ios::out;
    clientFile.open(clientFileName, mode);

    if (clientFile.is_open())
    {

        for (const stClient& client : clientsData)
        {
            if (!client.markDelete)
                clientFile << recordToLine(client) << endl;
        }

        clientFile.close();
    }
    else
    {
        cout << "Error opening file\n";
    }
}

vector<string> splitString(string str, string delimeter = "#//#")
{

    vector<string> stringSeparated;
    int pos = 0;

    while ((pos = str.find(delimeter)) != string::npos)
    {

        stringSeparated.push_back(str.substr(0, pos));

        str.erase(0, pos + delimeter.length());
    }

    // adds the last word since the string doest end with the delimeter.
    stringSeparated.push_back(str);

    return stringSeparated;
}

stClient ClientDataLineToRecord(string dataline, string delimeter = "#//#")
{

    stClient ClientData;

    vector<string> dataLineSeparated = splitString(dataline);

    ClientData.accountNumber = dataLineSeparated.at(0);
    ClientData.pinCode = dataLineSeparated.at(1);
    ClientData.fullName = dataLineSeparated.at(2);
    ClientData.phone = dataLineSeparated.at(3);
    ClientData.accountBalance = stod(dataLineSeparated.at(4));

    return ClientData;
}

stUser userDataLineToRecord(string dataline, string delimeter = "#//#")
{

    stUser usersData;

    vector<string> dataLineSeparated = splitString(dataline);

    usersData.username = dataLineSeparated.at(0);
    usersData.password = dataLineSeparated.at(1);
    usersData.permission = stoi(dataLineSeparated.at(2));

    return usersData;
}

vector<stClient> loadClientsFromFile(string clientFileName)
{

    vector<stClient> clientsData;

    fstream clientFile;
    clientFile.open(clientFileName, ios::in);

    if (clientFile.is_open())
    {

        string dataLine;

        while (getline(clientFile, dataLine))
        {
            clientsData.push_back(ClientDataLineToRecord(dataLine));
        }

        clientFile.close();
    }
    else
    {
        cout << "Error opening file\n";
    }

    return clientsData;
}

int readNumber(string message, int from, int to)
{

    int number;

    cout << message << endl;

    cin >> number;

    while (cin.fail() || (number < from || number > to))
    {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input, please enter a valid number : " << endl;
        cin >> number;
    }

    return number;
}

int readNumber(string message)
{

    int number;

    cout << message << endl;

    cin >> number;

    while (cin.fail())
    {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input, please enter a valid number : " << endl;
        cin >> number;
    }

    return number;
}

string readString(string message)
{
    string input;

    cout << message;
    cin >> input;

    return input;
}

char readChar(string message)
{

    char character;

    cout << message;
    cin >> character;

    return character;
}

void printClientDataCard(const stClient clientData)
{
    printHeader("Client card");
    cout << "  Account number  : " << clientData.accountNumber << endl;
    cout << "  Pin code        : " << clientData.pinCode << endl;
    cout << "  Full name       : " << clientData.fullName << endl;
    cout << "  Phone           : " << clientData.phone << endl;
    cout << "  Account balance : " << clientData.accountBalance << endl;
    cout << string(getDividerLength("Client card"), '=') << endl;
}

bool findClientByAccountNumber(string accountNumber, const vector<stClient>& clientsData, stClient& foundClient)
{

    for (const stClient& client : clientsData)
    {
        if (client.accountNumber == accountNumber)
        {
            foundClient = client;
            return true;
        }
    }

    return false;
}

bool findClientByAccountNumber(string accountNumber, const vector<stClient>& clientsData)
{

    for (const stClient& client : clientsData)
    {
        if (client.accountNumber == accountNumber)
        {
            return true;
        }
    }

    return false;
}

void findClient(vector<stClient>& clientsData)
{

    string searchedAccountNumber;
    stClient searchedClient;

    printHeader("Find client");

    searchedAccountNumber = readString("Enter the account number : ");

    if (findClientByAccountNumber(searchedAccountNumber, clientsData, searchedClient))
    {
        printClientDataCard(searchedClient);
    }
    else
    {
        cout << "Client with account number (" << searchedAccountNumber << ") is not found!" << endl;
    }
}

void printClientsTableHead()
{
    cout << string(125, '-') << endl;

    cout << left << '|' << setw(20) << " Account number" << '|' << setw(20) << " Pin code" << '|' << setw(45) << " Full name" << '|' << setw(14) << " Phone" << '|' << setw(20) << " Account balance" << '|' << endl;

    cout << string(125, '-') << endl;
}

void printClientInTable(const stClient clientData)
{
    cout << left << '|' << ' ' << setw(20 - 1) << clientData.accountNumber << '|' << ' ' << setw(20 - 1) << clientData.pinCode << '|' << ' ' << setw(45 - 1) << clientData.fullName << '|' << ' ' << setw(14 - 1) << clientData.phone << '|' << ' ' << setw(20 - 1) << clientData.accountBalance << '|' << ' ' << endl;
}

void showAllClients(const vector<stClient>& clientsData)
{

    cout << string(125 / 2 - 15, ' ') << "Clients List (" << clientsData.size() << ") client(s)." << endl;

    printClientsTableHead();

    for (const stClient& client : clientsData)
    {
        printClientInTable(client);
    }

    cout << string(125, '-') << endl;
}

bool markClientToDeleteByAccountNumber(string accountNumber, vector<stClient>& clientsData)
{
    for (stClient& client : clientsData)
    {
        if (client.accountNumber == accountNumber)
        {
            client.markDelete = true;
            return true;
        }
    }

    return false;
}

void deleteClient(vector<stClient>& clientsData)
{

    string searchedAccountNumber;
    stClient markedClient;

    printHeader("Delete client screen");

    searchedAccountNumber = readString("Enter the account number : ");

    if (findClientByAccountNumber(searchedAccountNumber, clientsData, markedClient))
    {
        char doDelete;

        printClientDataCard(markedClient);

        cout << "Are you sure to delete this client [Y/N] ? " << endl;
        cin >> doDelete;

        if (toupper(doDelete) == 'Y')
        {
            markClientToDeleteByAccountNumber(searchedAccountNumber, clientsData);
            cout << "The client deleted successfully!" << endl;
            saveClientDataToFile(clientsData);
        }
    }
    else
    {
        cout << "Client with account number (" << searchedAccountNumber << ") is already exists , enter another account Number : ";
    }
}

void updateClientData(vector<stClient>& clientsData)
{

    string searchedAccountNumber;
    stClient searchedClient;

    printHeader("Update client data");

    searchedAccountNumber = readString("Enter the account number : ");

    if (findClientByAccountNumber(searchedAccountNumber, clientsData, searchedClient))
    {
        char doUpdate;

        printClientDataCard(searchedClient);

        cout << "Are you sure to Update this client [Y/N] ? " << endl;
        cin >> doUpdate;

        if (toupper(doUpdate) == 'Y')
        {

            for (stClient& client : clientsData)
            {
                if (client.accountNumber == searchedAccountNumber)
                {
                    client = readUpdatedClientData(searchedAccountNumber);
                    break;
                }
            }

            saveClientDataToFile(clientsData);
        }
    }
    else
    {
        cout << "Client with account number (" << searchedAccountNumber << ") is not found!" << endl;
    }
}

void exitProgram()
{

    printHeader("Exit the program");
    cout << "the program has stopped!" << endl;
}

stClient readClientData(const vector<stClient>& clientsData)
{

    stClient newClient;

    cout << "Enter client's account number : ";

    while (true)
    {

        cin >> newClient.accountNumber;
        cin.ignore();

        if (findClientByAccountNumber(newClient.accountNumber, clientsData))
        {
            cout << "Client with account number (" << newClient.accountNumber << ") is already exists , enter another account Number : ";
        }
        else
        {
            break;
        }
    }

    cout << "Enter client's pin code : ";
    cin >> newClient.pinCode;
    cin.ignore();
    cout << "Enter client's full name : ";
    getline(cin, newClient.fullName);
    cout << "Enter client's phone : ";
    getline(cin, newClient.phone);
    cout << "Enter client's account balance : ";
    cin >> newClient.accountBalance;

    return newClient;
}

stClient readUpdatedClientData(string accountNumber)
{

    stClient newClient;

    newClient.accountNumber = accountNumber;

    cout << "Enter client's pin code : ";
    cin >> newClient.pinCode;
    cin.ignore();
    cout << "Enter client's full name : ";
    getline(cin, newClient.fullName);
    cout << "Enter client's phone : ";
    getline(cin, newClient.phone);
    cout << "Enter client's account balance : ";
    cin >> newClient.accountBalance;

    return newClient;
}

void addNewClient(vector<stClient>& clientsData)
{

    char isAddMore = 'y';

    printHeader("Adding new client screen");

    while (toupper(isAddMore) == 'Y')
    {

        clientsData.push_back(readClientData(clientsData));

        isAddMore = readChar("Do you want to add more clients [Y/N] ? ");
    }

    saveClientDataToFile(clientsData);
}

bool depositToClient(vector<stClient>& clientsData, string accountNumber, int depositAmount)
{
    for (auto& client : clientsData)
    {
        if (client.accountNumber == accountNumber)
        {
            client.accountBalance += depositAmount;
            saveClientDataToFile(clientsData);
            return true;
        }
    }
    return false;
}

bool withdrawFromClient(vector<stClient>& clientsData, string accountNumber, int withdrawAmount)
{
    for (auto& client : clientsData)
    {
        if (client.accountNumber == accountNumber)
        {
            client.accountBalance -= withdrawAmount;
            saveClientDataToFile(clientsData);
            return true;
        }
    }
    return false;
}

void withdraw(vector<stClient>& clientsData)
{
    stClient foundClient;
    int withdrawAmount;
    string accountNumber;

    printHeader("Deposit");

    accountNumber = readString("Enter the account number : ");

    if (findClientByAccountNumber(accountNumber, clientsData, foundClient))
    {
        char doWithdraw;

        printClientDataCard(foundClient);

        while (true)
        {
            withdrawAmount = readNumber("Enter the deposit amount : ");
            if (withdrawAmount > foundClient.accountBalance)
            {
                cout << "Amount exceed the balance, you can withdraw up to (" << foundClient.accountBalance << ")" << endl;
            }
            else
            {
                break;
            }
        }

        cout << "Are you sure to withdraw the amount from this client [Y/N] ? " << endl;
        cin >> doWithdraw;

        if (toupper(doWithdraw) == 'Y')
        {
            if (withdrawFromClient(clientsData, accountNumber, withdrawAmount))
            {
                cout << "The withdraw done successfully!" << endl;
            }
            else
            {
                cout << "The withdraw done unsuccessfully!" << endl;
            }
        }
    }
    else
    {
        cout << "Client with account number (" << accountNumber << ") is not found!" << endl;
    }
}

void deposit(vector<stClient>& clientsData)
{
    stClient foundClient;
    int depositAmount;
    string accountNumber;

    printHeader("Deposit");

    accountNumber = readString("Enter the account number : ");

    if (findClientByAccountNumber(accountNumber, clientsData, foundClient))
    {
        char doDeposit;

        printClientDataCard(foundClient);

        depositAmount = readNumber("Enter the deposit amount : ");

        cout << "Are you sure to deposit the amount in this client [Y/N] ? " << endl;
        cin >> doDeposit;

        if (toupper(doDeposit) == 'Y')
        {
            if (depositToClient(clientsData, accountNumber, depositAmount))
            {
                cout << "The deposit done successfully!" << endl;
            }
            else
            {
                cout << "The deposit done unsuccessfully!" << endl;
            }
        }
    }
    else
    {
        cout << "Client with account number (" << accountNumber << ") is not found!" << endl;
    }
}

int getTotalBalances(const vector<stClient>& clientsData)
{
    int totalBalance = 0;

    for (const auto &client : clientsData)
    {
        totalBalance += client.accountBalance;
    }

    return totalBalance;
}

void printTotalBalancesTableHead()
{
    cout << string(98, '-') << endl;
    cout << left << '|' << ' ' << setw(20) << "Account number" << '|' << ' ' << setw(50) << "Full name" << '|' << ' ' << setw(20) << "Account balance" << '|' << ' ' << endl;
    cout << string(98, '-') << endl;
}

void printClientInTotalBalancesTable(const stClient clientData)
{
    cout << left << '|' << ' ' << setw(20) << clientData.accountNumber << '|' << ' ' << setw(50) << clientData.fullName << '|' << ' ' << setw(20) << clientData.accountBalance << '|' << ' ' << endl;
}

void printTotalBalancesTable(const vector<stClient>& clientsData)
{
    cout << string(98 / 2 - 22, ' ') << "Total balances list (" << (clientsData.size()) << ") clients(s)." << endl;

    printTotalBalancesTableHead();

    for (const auto& client : clientsData)
    {
        printClientInTotalBalancesTable(client);
    }

    cout << string(98, '-') << endl;
}

void totalBalances(const vector<stClient>& clientsData)
{

    printTotalBalancesTable(clientsData);

    cout << string(98 / 2 - 22, ' ') << "Total balances = " << getTotalBalances(clientsData) << endl;
}

void printMainMenuScreen()
{

    system("cls");
    printHeader("Main menu screen");

    cout << " [1] Show client list." << endl;
    cout << " [2] Add new client." << endl;
    cout << " [3] Delete client." << endl;
    cout << " [4] Update client data." << endl;
    cout << " [5] Find client." << endl;
    cout << " [6] Transaction." << endl;
    cout << " [7] Manage users." << endl;
    cout << " [8] Log out." << endl;
    cout << string(getDividerLength("Main menu screen"), '=') << endl;
}

void goBackToMainMenu()
{
    cout << "Press any key to go back to main menu..." << endl;
    system("pause>0");
    mainMenu();
}

void goBackToManageUsers(const stUser user)
{
    cout << "Press any key to go back to manage users menu..." << endl;
    system("pause>0");
    mangeUsersMenu(user);
}

int readPermission()
{
    char giveAccess = 'y';

    giveAccess = readChar("Do you want to give full access [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') return -1;

    int permission = 0;

    cout << "Do you want to give access to : " << endl;
    giveAccess = readChar("Show client list [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') permission += pow(2, static_cast<int>(enMainMenu::_showAllClient) - 1);

    giveAccess = readChar("Add new client [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') permission += pow(2, static_cast<int>(enMainMenu::_addNewClient) - 1);

    giveAccess = readChar("Delete client [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') permission += pow(2, static_cast<int>(enMainMenu::_deleteClient) - 1);

    giveAccess = readChar("Update client data [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') permission += pow(2, static_cast<int>(enMainMenu::_updateClientData) - 1);

    giveAccess = readChar("Find client [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') permission += pow(2, static_cast<int>(enMainMenu::_findClient) - 1);

    giveAccess = readChar("Transactions [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') permission += pow(2, static_cast<int>(enMainMenu::_transactions) - 1);

    giveAccess = readChar("Manage users [Y/N] ? ");
    if (toupper(giveAccess) == 'Y') permission += pow(2, static_cast<int>(enMainMenu::_manageUsers) - 1);

    return permission;
}

stUser readUserData(const vector<stUser>& usersData, bool askPermission = false, bool update = false)
{
    stUser user;
    if (!update)
    {
        while (true)
        {
            cout << "Enter user name : ";
            getline(cin >> ws, user.username);

            if (userExistsByUsername(user.username, usersData))
                cout << "User with username [" << user.username << "] already exists!" << endl;
            else
                break;
        }
    }

    cout << "Enter password : ";
    getline(cin>>ws ,user.password);

    if (askPermission)
    {
        user.permission = readPermission();
    }
    return user;
}

stUser readUserData(bool askPermission = false, bool update = false, string username = "")
{
    stUser user;

    if (update)
    {
        user.username = username;
    }
    else
    {
        cout << "Enter user name : ";
        getline(cin >> ws, user.username);
    }

    cout << "Enter password : ";
    getline(cin, user.password);

    if (askPermission)
    {
        user.permission = readPermission();
    }
    return user;
}

void saveUsersDataToFile(string usersFileName, const vector<stUser>& usersData, bool append = false)
{
    fstream usersFile;

    ios::openmode mode = append ? (ios::out | ios::app) : ios::out;
    usersFile.open(usersFileName, mode);

    if (usersFile.is_open())
    {
        for (const auto& user : usersData)
        {
            if (!user.markDelete)
                usersFile << recordToLine(user) << endl;
        }

        usersFile.close();
    }
    else
    {
        cout << "Error opening file\n";
    }
}

vector<stUser> loadUsersDataFromFile(string usersFileName)
{
    vector<stUser> usersData;

    fstream usersFile;
    usersFile.open(usersFileName, ios::in);


    if (usersFile.is_open())
    {
        string dataLine;

        while (getline(usersFile, dataLine))
        {
            usersData.push_back(userDataLineToRecord(dataLine));
        }

        usersFile.close();
    }
    else
    {
        cout << "Error opening file\n";
    }
    return usersData;
}

bool findUserByUsernameAndPassword(string username, string password, const vector<stUser> usersData, stUser& foundUser)
{
    for (const auto& user : usersData)
    {
        if (user.username == username)
        {
            if (user.password == password)
            {
                foundUser = user;
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

bool findUserByUsernameAndPassword(string username, string password, const vector<stUser> usersData)
{
    for (const auto& user : usersData)
    {
        if (user.username == username)
        {
            if (user.password == password)
                return true;
            else
                return false;
        }
    }
    return false;
}

bool userExistsByUsername(string username, const vector<stUser> usersData, stUser& foundUser)
{
    for (const auto& user : usersData)
    {
        if (user.username == username)
        {
            foundUser = user;
            return true;
        }
    }
    return false;
}

bool userExistsByUsername(string username, const vector<stUser> usersData)
{
    for (const auto& user : usersData)
    {
        if (user.username == username)
        {
            return true;
        }
    }
    return false;
}

void logInScreen()
{
    vector<stUser> usersData = loadUsersDataFromFile(usersFileName);

    printHeader("Log in");

    user = readUserData();

    while (!findUserByUsernameAndPassword(user.username, user.password, usersData, user))
    {
        cout << "Incorrect username or password!" << endl;
        user = readUserData();
    }

    mainMenu();
}

void printManageUsersMenu()
{
    system("cls");
    printHeader("Mange Users");
    cout << " [1] List users." << endl;
    cout << " [2] Add new user." << endl;
    cout << " [3] Delete user." << endl;
    cout << " [4] Update user data." << endl;
    cout << " [5] Find user." << endl;
    cout << " [6] Main menu." << endl;
    cout << string(getDividerLength("Mange Users"), '=') << endl;
}

void printListUsersTableHead()
{
    cout << string(98, '-') << endl;
    cout << left << '|' << ' ' << setw(20) << "Username" << '|' << ' ' << setw(50) << "Password" << '|' << ' ' << setw(20) << "Permission" << '|' << ' ' << endl;
    cout << string(98, '-') << endl;
}

void printUserDataInListUsersTable(const stUser& usersData)
{
    cout << left << '|' << ' ' << setw(20) << usersData.username << '|' << ' ' << setw(50) << usersData.password << '|' << ' ' << setw(20) << usersData.permission << '|' << ' ' << endl;
}

void listUsers(const vector<stUser>& usersDate)
{
    cout << string(98 / 2 - 13, ' ') << "Users list (" << (usersDate.size()) << ") User(s)." << endl;

    printListUsersTableHead();

    for (const auto &user : usersDate)
    {
        printUserDataInListUsersTable(user);
    }

    cout << string(98, '-') << endl;
}

void addNewUser(vector<stUser>& usersData)
{
    char addMore = 'y';

    printHeader("Add new user screen");

    while (toupper(addMore) == 'Y')
    {
        usersData.push_back(readUserData(usersData, true));

        addMore = readChar("Do you want to add more clients [Y/N] ? ");
    }

    saveUsersDataToFile(usersFileName, usersData);
}

void printUserCard(stUser user)
{
    printHeader("User card");
    cout << "  Username : " << user.username << endl;
    cout << "  Password : " << user.password << endl;
    cout << "  Permission : " << user.permission << endl;
    cout << string(getDividerLength("User card"), '=') << endl;
}

bool markUserToDeleteByUsername(vector<stUser>& usersData, string username)
{
    for (stUser& user : usersData)
    {
        if (user.username == username)
        {
            user.markDelete = true;
            return true;
        }
    }
    return false;
}

void deleteUser(vector<stUser> usersData)
{
    string searchedUsername;
    stUser foundUser;

    printHeader("Delete User");
    searchedUsername = readString("Enter the username : ");

    if (foundUser.username == "Admin")
    {
        cout << "You can't delete this user!" << endl;
        return;
    }

    if (userExistsByUsername(searchedUsername, usersData, foundUser))
    {
        char doDelete = 'n';

        printUserCard(foundUser);

        cout << "Are you sure you want to delete this user [Y/N] ? ";
        cin >> doDelete;

        if (toupper(doDelete) == 'Y')
        {
            if (markUserToDeleteByUsername(usersData, searchedUsername))
                cout << "The user deleted successfully!" << endl;
            else
                cout << "The user is not deleted!" << endl;

            saveUsersDataToFile(usersFileName, usersData);
        }
    }
    else
    {
        cout << "User with username [" << searchedUsername << "] is not found!" << endl;
    }
}

bool readUserUpdatedDataByUsername(vector<stUser>& usersData, string username)
{
    for (auto& user : usersData)
    {
        if (user.username == username)
        {
            user = readUserData(true, true, username);
            return true;
        }
    }
    return false;
}

void updateUserData(vector<stUser> usersData)
{
    string searchedUsername;
    stUser foundUser;

    printHeader("Delete User");
    searchedUsername = readString("Enter the username : ");

    if (userExistsByUsername(searchedUsername, usersData, foundUser))
    {
        char doUpdate = 'n';

        printUserCard(foundUser);

        cout << "Are you sure you want to update this user [Y/N] ? ";
        cin >> doUpdate;

        if (toupper(doUpdate) == 'Y')
        {
            if (readUserUpdatedDataByUsername(usersData, searchedUsername))
                cout << "The user updated successfully!" << endl;
            else
                cout << "The user is not updated!" << endl;

            saveUsersDataToFile(usersFileName, usersData);
        }
    }
    else
    {
        cout << "User with username [" << searchedUsername << "] is not found!" << endl;
    }
}

void findUser(vector<stUser> usersData)
{
    string searchedUsername;
    stUser foundUser;

    printHeader("Find User");
    searchedUsername = readString("Enter the username : ");

    if (userExistsByUsername(searchedUsername, usersData, foundUser))
    {
        printUserCard(foundUser);
    }
    else
    {
        cout << "User with username [" << searchedUsername << "] is not found!" << endl;
    }
}

void mangeUsersMenu(const stUser user)
{
    vector<stUser> usersData = loadUsersDataFromFile(usersFileName);
    short menuChoice;

    printManageUsersMenu();
    menuChoice = readNumber("Please choose one [" + to_string(enManageUsers::_listUsers) + "-" + to_string(enManageUsers::__mainMenu) + "] : ", enManageUsers::_listUsers, enManageUsers::__mainMenu);

    switch (static_cast<enManageUsers>(menuChoice))
    {
    case enManageUsers::_listUsers:
        system("cls");
        listUsers(usersData);
        goBackToManageUsers(user);
        break;
    case enManageUsers::_addNewUser:
        system("cls");
        addNewUser(usersData);
        goBackToManageUsers(user);
        break;
    case enManageUsers::_deleteUser:
        system("cls");
        deleteUser(usersData);
        goBackToManageUsers(user);
        break;
    case enManageUsers::_updateUser:
        system("cls");
        updateUserData(usersData);
        goBackToManageUsers(user);
        break;
    case enManageUsers::_findUser:
        system("cls");
        findUser(usersData);
        goBackToManageUsers(user);
        break;
    case enManageUsers::__mainMenu:
        system("cls");
        mainMenu();
        break;
    }
}

bool doesUserHasPermission(enMainMenu wantsAccessTo, int userPermission)
{
    if ((userPermission == -1) || wantsAccessTo == enMainMenu::_logOut) return true;

    int permissionNeeded = pow(2, wantsAccessTo - 1);

    return (userPermission & permissionNeeded);
}

void printAccessDenied()
{
    printHeader("Access Denied");
    cout << "You don't have access to do this,\nplease contact you admin!" << endl;

}

void mainMenu()
{

    vector<stClient> clientsData = loadClientsFromFile(clientFileName);
    short menuChoice;

    printMainMenuScreen();
    menuChoice = readNumber("Please choose one [" + to_string(enMainMenu::_showAllClient) + "-" + to_string(enMainMenu::_logOut) + "] : ", enMainMenu::_showAllClient, enMainMenu::_logOut);

    if (!doesUserHasPermission(static_cast<enMainMenu>(menuChoice), user.permission))
    {
        printAccessDenied();
        goBackToMainMenu();
    }

    switch (static_cast<enMainMenu>(menuChoice))
    {
    case enMainMenu::_showAllClient:
        system("cls");
        showAllClients(clientsData);
        goBackToMainMenu();
        break;
    case enMainMenu::_addNewClient:
        system("cls");
        addNewClient(clientsData);
        goBackToMainMenu();
        break;
    case enMainMenu::_deleteClient:
        system("cls");
        deleteClient(clientsData);
        goBackToMainMenu();
        break;
    case enMainMenu::_updateClientData:
        system("cls");
        updateClientData(clientsData);
        goBackToMainMenu();
        break;
    case enMainMenu::_findClient:
        system("cls");
        findClient(clientsData);
        goBackToMainMenu();
        break;
    case enMainMenu::_transactions:
        system("cls");
        transactionMenu(user);
        goBackToMainMenu();
        break;
    case enMainMenu::_manageUsers:
        system("cls");
        mangeUsersMenu(user);
        break;
    case enMainMenu::_logOut:
        system("cls");
        logInScreen();
        break;
    default:
        cout << "defaulted" << endl;
    }
}

void goBackToTransaction(stUser user)
{
    cout << "Press any key to go back to transaction menu ..." << endl;
    system("pause>0");
    transactionMenu(user);
}

void printTransactionMenu()
{
    system("cls");
    printHeader("Transaction menu screen");

    cout << " [1] deposit." << endl;
    cout << " [2] withdraw." << endl;
    cout << " [3] Total balances." << endl;
    cout << " [4] Main menu." << endl;

    cout << string(getDividerLength("Transaction menu screen"), '=') << endl;
}

void transactionMenu(stUser user)
{
    vector<stClient> clientsData = loadClientsFromFile(clientFileName);
    short transactionMenuChoice = 0;

    printTransactionMenu();
    transactionMenuChoice = readNumber("Please choose one [1-4] : ", 1, 4);

    switch (static_cast<enTransactionMenu>(transactionMenuChoice))
    {
    case enTransactionMenu::_deposit:
        system("cls");
        deposit(clientsData);
        goBackToTransaction(user);
        break;
    case enTransactionMenu::_withdraw:
        system("cls");
        withdraw(clientsData);
        goBackToTransaction(user);
        break;
    case enTransactionMenu::_totalBalances:
        system("cls");
        totalBalances(clientsData);
        goBackToTransaction(user);
        break;
    case enTransactionMenu::_mainMenu:
        system("cls");
        mainMenu();
        break;
    }
}

int main()
{

    logInScreen();

    return 0;
}