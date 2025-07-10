// ToDoList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>


class LinkedList {
    private:
        class ListNode {
        public:
            std::string title;
            std::string desc;
            bool done;
            ListNode* nextPtr;

            ListNode(std::string pTitle, std::string pDesc) {
                title = pTitle;
                desc = pDesc;
                done = false;
                nextPtr = NULL;
            }

            ~ListNode() {
                
            }
        };
        ListNode* head;

    public:
        static void printMenu() {
            std::cout << "\n===== TO-DO MENU =====\n";
            std::cout << "1. Add Task\n";
            std::cout << "2. View Tasks\n";
            std::cout << "3. Mark Task as Done\n";
            std::cout << "4. Delete Task\n";
            std::cout << "5. Exit\n";
            std::cout << "==================\n";
        }

        LinkedList() {
            head = NULL;
        }

        void append(std::string pTitle, std::string pDesc) {
            if (head == NULL) {
                head = new ListNode(pTitle, pDesc);
                system("cls");
                printMenu();
                return;
            }
            ListNode* tmp = head;
            while (tmp->nextPtr != NULL) {
                tmp = tmp->nextPtr;
            }
            tmp->nextPtr = new ListNode(pTitle, pDesc);
            system("cls");
            printMenu();
        }

        void display() {
            ListNode* tmp = head;
            std::cout << "\n=== TO-DO LIST ===\n";
            int i = 1;
            while (tmp != NULL) {
                std::cout << i << ". " << tmp->title << " | ";
                std::cout << tmp->desc << (tmp->done ? " Done" : " ") << std::endl;
                tmp = tmp->nextPtr;
                i++;
            }
            std::cout << "==================\n";
        }

        void markDone(int index) {
            ListNode* tmp = head;
            int current = 1;
            while (tmp != NULL && current < index) {
                tmp = tmp->nextPtr;
                current++;
            }
            
            if (tmp != NULL) {
                tmp->done = true;
                system("cls");
                printMenu();
                std::cout << tmp->title << " has been marked as done\n";
            } 
            else {
                system("cls");
                printMenu();
                std::cout << "Invalid task number\n";
            }
            
        }

        void remove(int index) {
            if (head == NULL) {
                system("cls");
                printMenu();
                std::cout << "List is empty\n";
                return;
            }

            if (index == 1) {
                ListNode* toDelete = head;
                head = head->nextPtr;
                delete toDelete;
                system("cls");
                printMenu();
                std::cout << "Task deleted\n";
                return;
            }

            ListNode* tmp = head;
            int current = 1;
            while (tmp != NULL && current < index - 1) {
                tmp = tmp->nextPtr;
                current++;
            }

            if (tmp == NULL || tmp->nextPtr == NULL) {
                system("cls");
                printMenu();
                std::cout << "Invalid task number.\n";
                return;
            }

            ListNode* toDelete = tmp->nextPtr;
            tmp->nextPtr = toDelete->nextPtr;
            delete toDelete;
            system("cls");
            printMenu();
            std::cout << "Task deleted.\n";
        }

        ~LinkedList() {
            ListNode* current = head;
            while (current != nullptr) {
                ListNode* next = current->nextPtr;
                delete current;
                current = next;
            }
        }
};


int main()
{
    LinkedList todo;
    int choice;
    std::string title;
    std::string desc;
    int taskId;

    LinkedList::printMenu();
    
    

    while (true) {
       
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        switch (choice) {
        case 1:
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task description: ";
            std::getline(std::cin, desc);
            todo.append(title, desc);
            std::cout << "New task has been added\n";
            break;
        case 2:
            system("cls");
            LinkedList::printMenu();
            todo.display();
            break;
        case 3:
            std::cout << "Enter task title to mark as done: ";
            std::cin >> taskId;
            todo.markDone(taskId);
            break;
        case 4:
            std::cout << "Enter task number to delete: ";
            std::cin >> taskId;
            todo.remove(taskId);
            break;
        case 5:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}
