#include <stdio.h>
#include <string.h>

char employeeNames[20][30];
char employeePasswords[20][20];
int employeeCount = 0;

int accountNumbers[50];
char customerNames[50][30];
char customerPasswords[50][20];

float balances[50];
int verified[50];   
/* 0 = Pending, 1 = Approved, 2 = Rejected */

char complaints[50][100];
char complaintReplies[50][100];
int complaintStatus[50];
/* 0 = No complaint, 1 = Not Resolved, 2 = Resolved */

char history[50][20][100];
int historyCount[50];

int customerCount = 0;
int nextAccountNumber = 1001;

int inputInt() {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Invalid input! Enter number only: ");
        while (getchar() != '\n');
    }
    return value;
}

float inputFloat() {
    float value;
    while (scanf("%f", &value) != 1) {
        printf("Invalid input! Enter amount only: ");
        while (getchar() != '\n');
    }
    return value;
}

int findEmployee(char name[]) {
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (strcmp(employeeNames[i], name) == 0)
            return i;
    }
    return -1;
}

int findCustomerByName(char name[]) {
    int i;
    for (i = 0; i < customerCount; i++) {
        if (strcmp(customerNames[i], name) == 0)
            return i;
    }
    return -1;
}

int findCustomerByAccount(int accNo) {
    int i;
    for (i = 0; i < customerCount; i++) {
        if (accountNumbers[i] == accNo)
            return i;
    }
    return -1;
}

void addHistory(int index, char text[]) {
    if (historyCount[index] < 20) {
        strcpy(history[index][historyCount[index]], text);
        historyCount[index]++;
    }
}

void addDefaultData() {
    int i;

    strcpy(employeeNames[0], "Humna");
    strcpy(employeePasswords[0], "Humna123");

    strcpy(employeeNames[1], "Sana");
    strcpy(employeePasswords[1], "Sana123");

    employeeCount = 2;

    strcpy(customerNames[0], "Ali");
    strcpy(customerPasswords[0], "Ali123");
    accountNumbers[0] = nextAccountNumber++;
    balances[0] = 5000;
    verified[0] = 1;

    strcpy(customerNames[1], "Abdullah");
    strcpy(customerPasswords[1], "Abdullah123");
    accountNumbers[1] = nextAccountNumber++;
    balances[1] = 6000;
    verified[1] = 1;

    strcpy(customerNames[2], "Sara");
    strcpy(customerPasswords[2], "Sara123");
    accountNumbers[2] = nextAccountNumber++;
    balances[2] = 7000;
    verified[2] = 1;

    strcpy(customerNames[3], "Rida");
    strcpy(customerPasswords[3], "Rida123");
    accountNumbers[3] = nextAccountNumber++;
    balances[3] = 8000;
    verified[3] = 1;

    for (i = 0; i < 4; i++) {
        historyCount[i] = 0;
        complaintStatus[i] = 0;
        strcpy(complaints[i], "No complaint");
        strcpy(complaintReplies[i], "No reply");
    }

    customerCount = 4;
}

void customerSignup() {
    char name[30];

    if (customerCount >= 50) {
        printf("Customer limit full.\n");
        return;
    }

    printf("Enter customer name: ");
    scanf("%s", name);

    if (findCustomerByName(name) != -1) {
        printf("Customer already exists.\n");
        return;
    }

    strcpy(customerNames[customerCount], name);

    printf("Enter password: ");
    scanf("%s", customerPasswords[customerCount]);

    accountNumbers[customerCount] = nextAccountNumber++;
    balances[customerCount] = 0;
    verified[customerCount] = 0;
    historyCount[customerCount] = 0;
    complaintStatus[customerCount] = 0;

    strcpy(complaints[customerCount], "No complaint");
    strcpy(complaintReplies[customerCount], "No reply");

    printf("Sign Up Successful.\n");
    printf("Your Account Number is: %d\n", accountNumbers[customerCount]);
    printf("Status: Pending Verification.\n");

    customerCount++;
}

void addEmployee() {
    char name[30];

    if (employeeCount >= 20) {
        printf("Employee limit full.\n");
        return;
    }

    printf("Enter employee name: ");
    scanf("%s", name);

    if (findEmployee(name) != -1) {
        printf("Employee already exists.\n");
        return;
    }

    strcpy(employeeNames[employeeCount], name);

    printf("Enter employee password: ");
    scanf("%s", employeePasswords[employeeCount]);

    employeeCount++;
    printf("Employee added successfully.\n");
}

void viewEmployees() {
    int i;

    if (employeeCount == 0) {
        printf("No employee found.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++) {
        printf("%d. Name: %s\n", i + 1, employeeNames[i]);
    }
}

void deleteEmployee() {
    int num, i;

    if (employeeCount <= 1) {
        printf("Cannot delete last employee.\n");
        return;
    }

    viewEmployees();

    printf("Enter employee number to delete: ");
    num = inputInt();
    num--;

    if (num >= 0 && num < employeeCount) {
        for (i = num; i < employeeCount - 1; i++) {
            strcpy(employeeNames[i], employeeNames[i + 1]);
            strcpy(employeePasswords[i], employeePasswords[i + 1]);
        }

        employeeCount--;
        printf("Employee deleted successfully.\n");
    } else {
        printf("Invalid employee number.\n");
    }
}

void searchEmployee() {
    char name[30];
    int index;

    printf("Enter employee name: ");
    scanf("%s", name);

    index = findEmployee(name);

    if (index != -1)
        printf("Employee Found: %s\n", employeeNames[index]);
    else
        printf("Employee not found.\n");
}

void editEmployee() {
    int num;
    char newName[30];

    viewEmployees();

    printf("Enter employee number to edit: ");
    num = inputInt();
    num--;

    if (num >= 0 && num < employeeCount) {
        printf("Enter new name: ");
        scanf("%s", newName);

        strcpy(employeeNames[num], newName);

        printf("Enter new password: ");
        scanf("%s", employeePasswords[num]);

        printf("Employee updated successfully.\n");
    } else {
        printf("Invalid employee number.\n");
    }
}

void adminMenu() {
    char username[20], password[20];
    int choice, attempts = 0;

    while (attempts < 3) {
        printf("Enter Admin Username: ");
        scanf("%s", username);

        printf("Enter Admin Password: ");
        scanf("%s", password);

        if (strcmp(username, "Aiman") == 0 &&
            strcmp(password, "Aiman123") == 0) {

            do {
                printf("\n--- ADMIN MENU ---\n");
                printf("1. Add Employee\n");
                printf("2. Delete Employee\n");
                printf("3. View Employees\n");
                printf("4. Search Employee\n");
                printf("5. Edit Employee\n");
                printf("6. Logout\n");
                printf("Enter choice: ");
                choice = inputInt();

                switch(choice) {
                    case 1: addEmployee(); break;
                    case 2: deleteEmployee(); break;
                    case 3: viewEmployees(); break;
                    case 4: searchEmployee(); break;
                    case 5: editEmployee(); break;
                    case 6: printf("Logout Successful\n"); break;
                    default: printf("Invalid Choice\n");
                }

            } while(choice != 6);

            return;
        }

        attempts++;
        printf("Invalid Login! Attempts left: %d\n", 3 - attempts);
    }

    printf("Too many wrong attempts.\n");
}

void viewCustomers() {
    int i;

    if (customerCount == 0) {
        printf("No customer found.\n");
        return;
    }

    for(i = 0; i < customerCount; i++) {
        printf("\nAccount No: %d\n", accountNumbers[i]);
        printf("Name: %s\n", customerNames[i]);
        printf("Balance: %.2f\n", balances[i]);

        if(verified[i] == 0)
            printf("Status: Pending\n");
        else if(verified[i] == 1)
            printf("Status: Approved\n");
        else
            printf("Status: Rejected\n");
    }
}

void searchCustomer() {
    int accNo, index;

    printf("Enter Account Number: ");
    accNo = inputInt();

    index = findCustomerByAccount(accNo);

    if(index != -1) {
        printf("Account No: %d\n", accountNumbers[index]);
        printf("Name: %s\n", customerNames[index]);
        printf("Balance: %.2f\n", balances[index]);
    } else {
        printf("Customer not found.\n");
    }
}

void editCustomer() {
    int accNo, index;
    char newName[30];

    printf("Enter Account Number to edit: ");
    accNo = inputInt();

    index = findCustomerByAccount(accNo);

    if (index != -1) {
        printf("Enter new name: ");
        scanf("%s", newName);

        strcpy(customerNames[index], newName);

        printf("Enter new password: ");
        scanf("%s", customerPasswords[index]);

        printf("Customer updated successfully.\n");
    } else {
        printf("Invalid account number.\n");
    }
}

void deleteCustomer() {
    int accNo, index, i, j;

    viewCustomers();

    printf("Enter Account Number to delete: ");
    accNo = inputInt();

    index = findCustomerByAccount(accNo);

    if (index != -1) {
        for (i = index; i < customerCount - 1; i++) {
            accountNumbers[i] = accountNumbers[i + 1];
            strcpy(customerNames[i], customerNames[i + 1]);
            strcpy(customerPasswords[i], customerPasswords[i + 1]);

            balances[i] = balances[i + 1];
            verified[i] = verified[i + 1];
            complaintStatus[i] = complaintStatus[i + 1];
            historyCount[i] = historyCount[i + 1];

            strcpy(complaints[i], complaints[i + 1]);
            strcpy(complaintReplies[i], complaintReplies[i + 1]);

            for (j = 0; j < historyCount[i + 1]; j++) {
                strcpy(history[i][j], history[i + 1][j]);
            }
        }

        customerCount--;
        printf("Customer deleted successfully.\n");
    } else {
        printf("Invalid account number.\n");
    }
}

void verifyAccount() {
    int i, accNo, index, choice;
    int found = 0;

    printf("\n--- Pending Requests ---\n");

    for(i = 0; i < customerCount; i++) {
        if(verified[i] == 0) {
            printf("Account No: %d | Name: %s\n",
                   accountNumbers[i], customerNames[i]);
            found = 1;
        }
    }

    if(found == 0) {
        printf("No Pending Requests.\n");
        return;
    }

    printf("Enter Account Number: ");
    accNo = inputInt();

    index = findCustomerByAccount(accNo);

    if(index != -1 && verified[index] == 0) {
        printf("1. Approve\n");
        printf("2. Reject\n");
        printf("Enter choice: ");
        choice = inputInt();

        if(choice == 1) {
            verified[index] = 1;
            printf("Customer Approved.\n");
        }
        else if(choice == 2) {
            verified[index] = 2;
            printf("Customer Rejected.\n");
        }
        else {
            printf("Invalid choice.\n");
        }
    } else {
        printf("Invalid or already processed account.\n");
    }
}

void viewComplaints() {
    int i, found = 0;

    for(i = 0; i < customerCount; i++) {
        if(complaintStatus[i] == 1) {
            found = 1;

            printf("\nAccount No: %d\n", accountNumbers[i]);
            printf("Customer: %s\n", customerNames[i]);
            printf("Complaint: %s\n", complaints[i]);

            printf("Enter Reply: ");
            getchar();
            fgets(complaintReplies[i], 100, stdin);

            complaintStatus[i] = 2;

            printf("Complaint Resolved.\n");
        }
    }

    if(found == 0)
        printf("No Complaints Found.\n");
}

int employeeLogin() {
    char username[20];
    char password[20];
    int i, attempt;

    for(attempt = 0; attempt < 3; attempt++) {
        printf("Enter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        for(i = 0; i < employeeCount; i++) {
            if(strcmp(employeeNames[i], username) == 0 &&
               strcmp(employeePasswords[i], password) == 0) {
                return 1;
            }
        }

        printf("Invalid Login. Attempts left: %d\n", 2 - attempt);
    }

    return 0;
}

void employeeMenu() {
    int choice;

    if(employeeLogin() == 0) {
        printf("Login Failed\n");
        return;
    }

    do {
        printf("\n--- EMPLOYEE MENU ---\n");
        printf("1. Add Customer\n");
        printf("2. Delete Customer\n");
        printf("3. View Customers\n");
        printf("4. Search Customer\n");
        printf("5. Edit Customer\n");
        printf("6. Verify Requests\n");
        printf("7. View Complaints\n");
        printf("8. Logout\n");
        printf("Enter choice: ");

        choice = inputInt();

        switch(choice) {
            case 1: customerSignup(); break;
            case 2: deleteCustomer(); break;
            case 3: viewCustomers(); break;
            case 4: searchCustomer(); break;
            case 5: editCustomer(); break;
            case 6: verifyAccount(); break;
            case 7: viewComplaints(); break;
            case 8: printf("Logout Successful\n"); break;
            default: printf("Invalid Choice\n");
        }

    } while(choice != 8);
}

int customerLogin() {
    int accNo;
    int index;
    char password[20];
    int attempt;

    for (attempt = 0; attempt < 3; attempt++) {
        printf("Enter Account Number: ");
        accNo = inputInt();

        printf("Enter Password: ");
        scanf("%s", password);

        index = findCustomerByAccount(accNo);

        if(index != -1 &&
           strcmp(customerPasswords[index], password) == 0)
            return index;

        printf("Invalid Login. Attempts left: %d\n", 2 - attempt);
    }

    return -1;
}

void customerMenu() {
    int index;
    int choice;
    int i;
    float amount;
    char text[100];

    index = customerLogin();

    if(index == -1) {
        printf("Invalid Login\n");
        return;
    }

    do {
        printf("\n--- CUSTOMER MENU ---\n");
        printf("1. Check Status\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance\n");
        printf("5. Transaction History\n");
        printf("6. Complaint\n");
        printf("7. Complaint Status\n");
        printf("8. Reapply Verification\n");
        printf("9. Logout\n");
        printf("Enter choice: ");

        choice = inputInt();

        switch(choice) {
            case 1:
                if(verified[index] == 0)
                    printf("Pending Verification\n");
                else if(verified[index] == 1)
                    printf("Approved\n");
                else
                    printf("Rejected\n");
                break;

            case 2:
                if(verified[index] != 1) {
                    printf("Banking Operations Not Allowed\n");
                }
                else {
                    printf("Enter Amount: ");
                    amount = inputFloat();

                    if (amount > 0) {
                        balances[index] += amount;

                        sprintf(text,
                        "Deposited %.2f | Balance %.2f",
                        amount, balances[index]);

                        addHistory(index,text);
                        printf("Deposit Successful\n");
                    } else {
                        printf("Invalid amount.\n");
                    }
                }
                break;

            case 3:
                if(verified[index] != 1) {
                    printf("Banking Operations Not Allowed\n");
                }
                else {
                    printf("Enter Amount: ");
                    amount = inputFloat();

                    if(amount > 0 && balances[index] - amount >= 500) {
                        balances[index] -= amount;

                        sprintf(text,
                        "Withdraw %.2f | Balance %.2f",
                        amount, balances[index]);

                        addHistory(index,text);
                        printf("Withdraw Successful\n");
                    }
                    else {
                        printf("Minimum Balance 500 Required\n");
                    }
                }
                break;

            case 4:
                if(verified[index] == 1)
                    printf("Balance: %.2f\n", balances[index]);
                else
                    printf("Not Allowed\n");
                break;

            case 5:
                if (verified[index] != 1) {
                    printf("Transaction history not available.\n");
                }
                else if (historyCount[index] == 0) {
                    printf("No transaction history.\n");
                }
                else {
                    for(i = 0; i < historyCount[index]; i++) {
                        printf("%d. %s\n", i + 1, history[index][i]);
                    }
                }
                break;

            case 6:
                getchar();
                printf("Enter Complaint: ");
                fgets(complaints[index], 100, stdin);

                if (strlen(complaints[index]) <= 1) {
                    printf("Empty complaint not allowed.\n");
                    strcpy(complaints[index], "No complaint");
                } else {
                    complaintStatus[index] = 1;
                    strcpy(complaintReplies[index], "No reply yet");
                    printf("Complaint Submitted\n");
                }
                break;

            case 7:
                if(complaintStatus[index] == 0)
                    printf("No Complaint\n");
                else if(complaintStatus[index] == 1)
                    printf("Not Resolved\nReply: No reply yet\n");
                else {
                    printf("Resolved\n");
                    printf("Reply: %s\n", complaintReplies[index]);
                }
                break;

       case 8:

    if (verified[index] == 2) {
        verified[index] = 0;
        printf("Reapply Successful.\n");
        printf("Status Changed To Pending Verification.\n");
    }

    else if (verified[index] == 1) {
        printf("Account Already Approved.\n");
        printf("Reapply Option Not Available.\n");
    }

    else if (verified[index] == 0) {
        printf("Your Request Is Already Pending.\n");
        printf("Please Wait For Employee Approval.\n");
    }

    break;

            case 9:
                printf("Logout Successful\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice != 9);
}

int main() {
    int choice;

    addDefaultData();

    do {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Admin Login\n");
        printf("2. Employee Login\n");
        printf("3. Customer Sign Up\n");
        printf("4. Customer Login\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        choice = inputInt();

        switch(choice) {
            case 1: adminMenu(); break;
            case 2: employeeMenu(); break;
            case 3: customerSignup(); break;
            case 4: customerMenu(); break;
            case 5: printf("Thank You\n"); break;
            default: printf("Invalid Choice\n");
        }

    } while(choice != 5);

    return 0;
}
