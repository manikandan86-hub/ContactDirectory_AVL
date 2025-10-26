#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

// -------------------- AVL Node Definition --------------------
struct Contact {
    string name;
    string phone;
    string email;
    Contact *left;
    Contact *right;
    int height;
};

// -------------------- Utility Functions --------------------
int height(Contact *N) {
    return (N == nullptr) ? 0 : N->height;
}

int getBalance(Contact *N) {
    if (N == nullptr) return 0;
    return height(N->left) - height(N->right);
}

Contact* newNode(string name, string phone, string email) {
    Contact* node = new Contact();
    node->name = name;
    node->phone = phone;
    node->email = email;
    node->left = node->right = nullptr;
    node->height = 1;
    return node;
}

// -------------------- Rotations --------------------
Contact* rightRotate(Contact* y) {
    Contact* x = y->left;
    Contact* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Contact* leftRotate(Contact* x) {
    Contact* y = x->right;
    Contact* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// -------------------- Insert Operation --------------------
Contact* insert(Contact* node, string name, string phone, string email) {
    if (node == nullptr)
        return newNode(name, phone, email);

    if (name < node->name)
        node->left = insert(node->left, name, phone, email);
    else if (name > node->name)
        node->right = insert(node->right, name, phone, email);
    else
        return node; // duplicate names not allowed

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Balancing
    if (balance > 1 && name < node->left->name)
        return rightRotate(node);
    if (balance < -1 && name > node->right->name)
        return leftRotate(node);
    if (balance > 1 && name > node->left->name) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && name < node->right->name) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// -------------------- Search --------------------
Contact* search(Contact* root, string name) {
    if (root == nullptr || root->name == name)
        return root;
    if (name < root->name)
        return search(root->left, name);
    return search(root->right, name);
}

// -------------------- Find Min Node --------------------
Contact* minValueNode(Contact* node) {
    Contact* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// -------------------- Delete --------------------
Contact* deleteNode(Contact* root, string name) {
    if (root == nullptr)
        return root;

    if (name < root->name)
        root->left = deleteNode(root->left, name);
    else if (name > root->name)
        root->right = deleteNode(root->right, name);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Contact* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Contact* temp = minValueNode(root->right);
            root->name = temp->name;
            root->phone = temp->phone;
            root->email = temp->email;
            root->right = deleteNode(root->right, temp->name);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// -------------------- Inorder Display --------------------
void inorder(Contact* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->name << " | " << root->phone << " | " << root->email << endl;
        inorder(root->right);
    }
}

// -------------------- Load from CSV --------------------
Contact* loadCSV(Contact* root, string filename) {
    ifstream file(filename);
    string line, name, phone, email;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        root = insert(root, name, phone, email);
    }
    file.close();
    return root;
}
// -------------------- Save to CSV --------------------
void saveToCSV(Contact* root, ofstream &file) {
    if (root != nullptr) {
        saveToCSV(root->left, file);
        file << root->name << "," << root->phone << "," << root->email << "\n";
        saveToCSV(root->right, file);
    }
}

void writeCSV(Contact* root, string filename) {
    ofstream file(filename);
    file << "Name,Phone,Email\n"; // header
    saveToCSV(root, file);
    file.close();
}


// -------------------- Main --------------------
int main() {
    Contact* root = nullptr;
    root = loadCSV(root, "contacts.csv");

    int choice;
    string name, phone, email;

    cout << "===== Contact Directory using AVL Tree =====\n";

    do {
        cout << "\n1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Display All Contacts\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Name: "; getline(cin, name);
                cout << "Enter Phone: "; getline(cin, phone);
                cout << "Enter Email: "; getline(cin, email);
                root = insert(root, name, phone, email);
                cout << "Contact added successfully!\n";
                break;

            case 2:
                cout << "Enter Name to search: "; getline(cin, name);
                {
                    Contact* found = search(root, name);
                    if (found)
                        cout << "Found: " << found->name << " | " << found->phone << " | " << found->email << endl;
                    else
                        cout << "Contact not found!\n";
                }
                break;

            case 3:
                cout << "Enter Name to delete: "; getline(cin, name);
                root = deleteNode(root, name);
                cout << "If contact existed, it has been deleted.\n";
                break;

            case 4:
                cout << "\n--- All Contacts (sorted by name) ---\n";
                inorder(root);
                break;

            case 5:
                cout << "Exiting program...\n";
                writeCSV(root, "contacts.csv"); // save all changes to CSV
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
