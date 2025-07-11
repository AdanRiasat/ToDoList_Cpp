// ToDoList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include "MenuChoice.h"

namespace Messages {
    /// <summary>
    /// Error messages
    /// </summary>
    const std::string notNum = "Invalid input. Please enter a number.\n";
    const std::string invalidNum = "Invalid choice.\n";
    const std::string listEmpty = "List is empty\n";

    /// <summary>
    /// Other messages
    /// </summary>
    const std::string taskDeleted = "Task deleted\n";
    const std::string taskCompleted = "has been marked as done\n";
}


void printMenu() {
    std::cout << "\n===== TO-DO MENU =====\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Mark Task as Done\n";
    std::cout << "4. Delete Task\n";
    std::cout << "5. Exit\n";
    std::cout << "==================\n";
}

void refreshUI() {
    system("cls");
    printMenu();
}


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

        void append(std::string& pTitle, std::string& pDesc) {
            if (head == NULL) {
                head = new ListNode(pTitle, pDesc);
                refreshUI();
                return;
            }
            ListNode* tmp = head;
            while (tmp->nextPtr != NULL) {
                tmp = tmp->nextPtr;
            }
            tmp->nextPtr = new ListNode(pTitle, pDesc);
            refreshUI();
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
                refreshUI();
                std::cout << tmp->title << " " << Messages::taskCompleted;
            } 
            else {
                refreshUI();
                std::cout << Messages::invalidNum;
            }
            
        }

        void deleteTask(int index) {
            if (head == NULL) {
                refreshUI();
                std::cout << Messages::listEmpty;
                return;
            }

            if (index == 1) {
                ListNode* toDelete = head;
                head = head->nextPtr;
                delete toDelete;
                refreshUI();
                std::cout << Messages::taskDeleted;
                return;
            }

            ListNode* tmp = head;
            int current = 1;
            while (tmp != NULL && current < index - 1) {
                tmp = tmp->nextPtr;
                current++;
            }

            if (tmp == NULL || tmp->nextPtr == NULL) {
                refreshUI();
                std::cout << Messages::invalidNum;
                return;
            }

            ListNode* toDelete = tmp->nextPtr;
            tmp->nextPtr = toDelete->nextPtr;
            delete toDelete;
            refreshUI();
            std::cout << Messages::taskDeleted;
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

int getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    try {
        return std::stoi(input);
    }
    catch (...) {
        refreshUI();
        std::cout << Messages::notNum;
        return -1;
    }
}


int main()
{
    LinkedList todo;
    int numericChoice;
    MenuChoice choice;
    std::string title;
    std::string desc;
    int taskId;

    printMenu();
    

    while (true) {
        numericChoice = getInput("Choose an option: ");
        if (numericChoice == -1) {
            continue;
        }

        choice = static_cast<MenuChoice>(numericChoice);

        switch (choice) {
        case MenuChoice::Add:
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task description: ";
            std::getline(std::cin, desc);
            todo.append(title, desc);
            std::cout << "New task has been added\n";
            break;
        case MenuChoice::View:
            refreshUI();
            todo.display();
            break;
        case MenuChoice::MarkDone:
            taskId = getInput("Enter task number to mark as done: ");

            if (taskId != -1) {
                todo.markDone(taskId);
            }

            break;
        case MenuChoice::Delete:
            taskId = getInput("Enter task number to delete: ");

            if (taskId != -1) {
                todo.deleteTask(taskId);
            }

            break;
        case MenuChoice::Exit:
            std::cout << "Exiting...\n";
            return 0;
        default:
            refreshUI();
            std::cout << Messages::invalidNum;
        }
    }
}
