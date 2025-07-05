// ToDoList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

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
        };
        ListNode* head;

    public:
        LinkedList() {
            head = NULL;
        }

        void append(std::string pTitle, std::string pDesc) {
            if (head == NULL) {
                head = new ListNode(pTitle, pDesc);
                return;
            }
            ListNode* tmp = head;
            while (tmp->nextPtr != NULL) {
                tmp = tmp->nextPtr;
            }
            tmp->nextPtr = new ListNode(pTitle, pDesc);
        }

        void display() {
            ListNode* tmp = head;
            std::cout << "\n=== TO-DO LIST ===\n";
            while (tmp != NULL) {
                std::cout << tmp->title << " || ";
                std::cout << tmp->desc<<std::endl;
                tmp = tmp->nextPtr;
            }
            std::cout << "==================\n";
        }
};



int main()
{
    LinkedList todo;
    int choice;
    std::string title;
    std::string desc;
    int taskNumber;

    while (true) {
        std::cout << "\n===== TO-DO MENU =====\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Mark Task as Done\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Exit\n";
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
            break;
        case 2:
            todo.display();
            break;
        case 3:
            std::cout << "Enter task number to mark as done: ";
            std::cin >> taskNumber;
            //todo.markDone(taskNumber);
            break;
        case 4:
            std::cout << "Enter task number to delete: ";
            std::cin >> taskNumber;
            //todo.remove(taskNumber);
            break;
        case 5:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice.\n";
        }
    }

    
    todo.display();


   
}

