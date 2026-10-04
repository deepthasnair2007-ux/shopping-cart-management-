#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int id;
    string name;
    float price;
    int quantity;
    Node *next;

    Node(int i, string n, float p, int q)
    {
        id = i;
        name = n;
        price = p;
        quantity = q;
        next = NULL;
    }
};

class StackNode
{
public:
    string operation;
    int id;
    string name;
    float price;
    int quantity;
    StackNode *next;

    StackNode(string op, int i, string n, float p, int q)
    {
        operation = op;
        id = i;
        name = n;
        price = p;
        quantity = q;
        next = NULL;
    }
};

class ShoppingCart
{
private:
    Node *head;
    StackNode *top;

public:
    ShoppingCart()
    {
        head = NULL;
        top = NULL;
    }

    void push(string operation, int id, string name,
              float price, int quantity)
    {
        StackNode *newNode =
            new StackNode(operation, id, name, price, quantity);

        newNode->next = top;
        top = newNode;
    }

    void addProduct()
    {
        int id, quantity;
        string name;
        float price;

        cout << "\nEnter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin >> name;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;

        Node *newNode = new Node(id, name, price, quantity);

        if (head == NULL)
            head = newNode;
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }

        push("ADD", id, name, price, quantity);
        cout << "Product added successfully!\n";
    }

    void displayCart()
    {
        if (head == NULL)
        {
            cout << "\nCart is empty.\n";
            return;
        }

        Node *temp = head;
        cout << "\n---------------------------------------------\n";
        cout << "ID\tName\tPrice\tQuantity\n";
        cout << "---------------------------------------------\n";

        while (temp != NULL)
        {
            cout << temp->id << "\t"
                 << temp->name << "\t"
                 << temp->price << "\t"
                 << temp->quantity << endl;
            temp = temp->next;
        }
        cout << "---------------------------------------------\n";
    }

    void searchProduct()
    {
        int id;
        cout << "\nEnter Product ID to search: ";
        cin >> id;

        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->id == id)
            {
                cout << "\nProduct Found!\n";
                cout << "ID       : " << temp->id << endl;
                cout << "Name     : " << temp->name << endl;
                cout << "Price    : " << temp->price << endl;
                cout << "Quantity : " << temp->quantity << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Product not found.\n";
    }

    void deleteProduct()
    {
        int id;
        cout << "\nEnter Product ID to delete: ";
        cin >> id;

        Node *temp = head;
        Node *previous = NULL;

        while (temp != NULL && temp->id != id)
        {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Product not found.\n";
            return;
        }

        push("DELETE", temp->id, temp->name,
             temp->price, temp->quantity);

        if (previous == NULL)
            head = temp->next;
        else
            previous->next = temp->next;

        delete temp;
        cout << "Product deleted successfully!\n";
    }

    void updateQuantity()
    {
        int id, newQuantity;
        cout << "\nEnter Product ID: ";
        cin >> id;

        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->id == id)
            {
                cout << "Current Quantity: " << temp->quantity << endl;
                cout << "Enter New Quantity: ";
                cin >> newQuantity;

                push("UPDATE", temp->id, temp->name,
                     temp->price, temp->quantity);
                temp->quantity = newQuantity;

                cout << "Quantity updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Product not found.\n";
    }

    void sortProducts()
    {
        if (head == NULL || head->next == NULL)
        {
            cout << "\nNot enough products to sort.\n";
            return;
        }

        Node *i;
        Node *j;
        for (i = head; i != NULL; i = i->next)
        {
            for (j = i->next; j != NULL; j = j->next)
            {
                if (i->price > j->price)
                {
                    swap(i->id, j->id);
                    swap(i->name, j->name);
                    swap(i->price, j->price);
                    swap(i->quantity, j->quantity);
                }
            }
        }
        cout << "\nProducts sorted by price.\n";
    }

    void calculateTotal()
    {
        float total = 0;
        Node *temp = head;

        while (temp != NULL)
        {
            total = total + (temp->price * temp->quantity);
            temp = temp->next;
        }

        cout << "\nTotal Cart Price = Rs. " << total << endl;
    }

    void undo()
    {
        if (top == NULL)
        {
            cout << "\nNothing to undo.\n";
            return;
        }

        string operation = top->operation;

        if (operation == "ADD")
        {
            int id = top->id;
            Node *temp = head;
            Node *previous = NULL;

            while (temp != NULL && temp->id != id)
            {
                previous = temp;
                temp = temp->next;
            }

            if (temp != NULL)
            {
                if (previous == NULL)
                    head = temp->next;
                else
                    previous->next = temp->next;

                delete temp;
                cout << "\nUndo successful!";
                cout << "\nAdded product was removed.\n";
            }
        }
        else if (operation == "DELETE")
        {
            Node *newNode = new Node(top->id, top->name,
                                     top->price, top->quantity);
            newNode->next = head;
            head = newNode;

            cout << "\nUndo successful!";
            cout << "\nDeleted product was restored.\n";
        }
        else if (operation == "UPDATE")
        {
            Node *temp = head;
            while (temp != NULL)
            {
                if (temp->id == top->id)
                {
                    temp->quantity = top->quantity;
                    cout << "\nUndo successful!";
                    cout << "\nPrevious quantity was restored.\n";
                    break;
                }
                temp = temp->next;
            }
        }

        StackNode *tempStack = top;
        top = top->next;
        delete tempStack;
    }
};

int main()
{
    ShoppingCart cart;
    int choice;

    do
    {
        cout << "\n\n====================================";
        cout << "\n      ONLINE SHOPPING CART";
        cout << "\n====================================";
        cout << "\n1. Add Product";
        cout << "\n2. Delete Product";
        cout << "\n3. Search Product";
        cout << "\n4. Display Cart";
        cout << "\n5. Update Quantity";
        cout << "\n6. Sort Products by Price";
        cout << "\n7. Calculate Total";
        cout << "\n8. Undo Last Operation";
        cout << "\n9. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cart.addProduct();
            break;
        case 2:
            cart.deleteProduct();
            break;
        case 3:
            cart.searchProduct();
            break;
        case 4:
            cart.displayCart();
            break;
        case 5:
            cart.updateQuantity();
            break;
        case 6:
            cart.sortProducts();
            break;
        case 7:
            cart.calculateTotal();
            break;
        case 8:
            cart.undo();
            break;
        case 9:
            cout << "\nThank you!\n";
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 9);

    return 0;
}
