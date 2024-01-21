//Ilhan Sertelli

#include <iostream>
#include "Board.h"
#include "CharStack.h"
#include <string>
using namespace std;

// Constructor
Board::Board() {
    head = NULL;
    tail = NULL;
    xCnt = 0;
    oCnt = 0;
}

void Board::createEmptySlotEnd() {
    slot * ptr;

    // Check the initial condition (If the board is empty)
    if (tail == NULL && head == NULL) {
        tail = new slot;
        tail->prev = NULL;
        tail->next = NULL;
        head = tail;
    }
    // Means that there is at least 1 slot
    else {
        ptr = tail;
        tail = new slot;
        tail->next = NULL;
        tail->prev = ptr;
        ptr->next = tail;
    }
}

void Board::createSlotEnd(const char &ch, const int &num) {
    slot * ptr;

    // Adding the first empty slot to the board if the board is completely empty
    if (tail == NULL && head == NULL) {
        tail = new slot;
        tail->prev = NULL;
        tail->next = NULL;
        head = tail;
    }
    // Adding an empty slot to the end of the board
    else {
        ptr = tail;
        tail = new slot;
        tail->next = NULL;
        tail->prev = ptr;
        ptr->next = tail;
    }

    ptr = tail;
    // Filling the empty slot that has been created with the given number of given characters
    for (int i = 0; i < num; i++) {
        ptr->slotStack.push(ch);
    }
}

void Board::printBoard() {
    int count = 0;
    slot *ptr;
    ptr = head;
    char symbol;
    string colStr, blankStr;

    // Counting how many slots does the board include
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    CharStack stack;
    cout << endl;
    // Examine each stack 3 times
    for (int c = 0; c < 3; c++) {
        ptr = head;
        stack = ptr->slotStack;
        for (int i = 0; i < count; i++) {
            colStr = "";
            blankStr = "";
            // Converting the elements of the stack into a string form
            while (!(stack.isEmpty())) {
                stack.pop(symbol);
                colStr += symbol;
            }
            // If the stack is not full, add a blank character to the beginning of the string
            if (colStr.length() != 3) {
                for (int j = 0; j < 3 - colStr.length(); j++) {
                    blankStr += " ";
                }
            }
            colStr = blankStr + colStr;
            cout << colStr[c];
            // Avoiding a possible segmentation fault
            if (i != (count - 1)) {
                ptr = ptr->next;
                stack = ptr->slotStack;
            }
        }
        cout << endl;
    }

    for (int k = 0; k < count; k++) {
        cout << "^";
    }
    cout << endl;
}

bool Board::noMove(const char &player, const int &step) {
    slot * ptr = head;
    slot * temp;
    CharStack stack;
    char ch;
    int count = 0;

    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    ptr = head;
    stack = ptr->slotStack;
    for (int k = 0; k < count - step; k++) {
        if (!(stack.isEmpty())) {
            stack.pop(ch);
            // Check if the slot includes the same character with the user
            if (ch == player) {
                temp = ptr;
                // Moving "n" steps forward
                for (int i = 0; i < step; i++) {
                    temp = temp->next;
                    stack = temp->slotStack;
                }
                // Checking whether the target slot is empty or not
                if (stack.isEmpty()) {
                    return false;
                }
                else {
                    // Checking if the target slot includes the same character with the user
                    stack.pop(ch);
                    if (ch == player) {
                        return false;
                    }
                }
            }
        }
        ptr = ptr->next;
        stack = ptr->slotStack;
    }

    ptr = tail;
    stack = ptr->slotStack;
    // Moving backwards this time with using the same process
    for (int j = 0; j < count - step; j++) {
        if (!(stack.isEmpty())) {
            stack.pop(ch);
            if (ch == player) {
                temp = ptr;
                for (int m = 0; m < step; m++) {
                    temp = temp->prev;
                    stack = temp->slotStack;
                }
                if (stack.isEmpty()) {
                    return false;
                }
                else {
                    stack.pop(ch);
                    if (ch == player) {
                        return false;
                    }
                }
            }
        }
        ptr = ptr->prev;
        stack = ptr->slotStack;
    }
    return true;
}

void Board::createSlotBegin(const char &ch, const int &num) {
    slot * ptr;

    // Checking whether the board is empty or not
    if (head == NULL && tail == NULL) {
        head = new slot;
        tail = head;
        head->next = NULL;
        head->prev = NULL;
    }
    else if (head != NULL && tail != NULL) {
        ptr = head;
        head = new slot;
        ptr->prev = head;
        head->next = ptr;
        head->prev = NULL;
    }
    // After creating an empty slot to the beginning of the board, adding characters to the stack
    for (int i = 0; i < num; i++) {
        head->slotStack.push(ch);
    }
}

int Board::validMove(const char &player, const int &index, const int &step, const int &direct) {
    slot * ptr = head;
    slot * temp;
    CharStack stack;
    char ch;
    int count = 0;

    // Counting the amount of the slots
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    // Checking if the index that the character user wants to move is out of range
    if (index < 0 || index + 1 > count) {
        return 1;
    }

    ptr = head;
    stack = ptr->slotStack;
    if (direct == 0) { // left
        for (int i = 0; i < count; i++) {
            if (i == index) {
                // Check if the given index is empty
                if (stack.isEmpty()) {
                    return 4;
                }
                else {
                    // Check if the index includes a different character than the user has
                    stack.pop(ch);
                    if (ch != player) {
                        return 4;
                    }
                    else {
                        // Check if the target index is out of range
                        if (index - step < 0) {
                            return 2;
                        }
                        else {
                            // Moving step times backward in order to reach the target index
                            temp = ptr;
                            for (int j = 0; j < step; j++) {
                                temp = temp->prev;
                                stack = temp->slotStack;
                            }
                            // Check if the target slot includes a different character than the user has
                            if (!(stack.isEmpty())) {
                                stack.pop(ch);
                                if (ch != player) {
                                    return 3;
                                }
                            }
                        }
                    }
                }
            }
            else {
                if (i != (count - 1)) {
                    ptr = ptr->next;
                    stack = ptr->slotStack;
                }
            }
        }
    }
    // Using the same process for moving forward this time
    else if (direct == 1) { // right
        for (int i = 0; i < count; i++) {
            if (i == index) {
                if (stack.isEmpty()) {
                    return 4;
                }
                else {
                    stack.pop(ch);
                    if (ch != player) {
                        return 4;
                    }
                    else {
                        if (index + step >= count) {
                            return 2;
                        }
                        else {
                            temp = ptr;
                            // Move step times forward
                            for (int j = 0; j < step; j++) {
                                temp = temp->next;
                                stack = temp->slotStack;
                            }
                            if (!(stack.isEmpty())) {
                                stack.pop(ch);
                                if (ch != player) {
                                    return 3;
                                }
                            }
                        }
                    }
                }
            }
            else {
                if (i != (count - 1)) {
                    ptr = ptr->next;
                    stack = ptr->slotStack;
                }
            }
        }
    }

    return 0;
}

void Board::movePiece(const int & index, const int & target) {
    slot * ptr = head;
    slot * temp;
    CharStack stack;
    char ch;
    int count = 0;

    // Count the number of slots
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    ptr = head;
    for (int i = 0; i < count; i++) {
        if (i == index) {
            // Remove the top character in the stack
            ptr->slotStack.pop(ch);
            // Check if the character will be moved to the left or right
            if (target < index) {
                temp = ptr;
                // Moving to the left
                for (int j = 0; j < index - target; j++) {
                    temp = temp->prev;
                }
                // Add the character to the target slot
                temp->slotStack.push(ch);
            }
            else if (target > index) {
                temp = ptr;
                // Moving to the right
                for (int j = 0; j < target - index; j++) {
                    temp = temp->next;
                }
                // Add the character to the target slot
                temp->slotStack.push(ch);
            }
        }
        else {
            // Avoiding a possible segmentation fault
            if (i != (count - 1)) {
                ptr = ptr->next;
            }
        }
    }

}

bool Board::targetSlotFull(const int &index) {
    slot * ptr = head;
    CharStack stack;
    char ch;
    int count = 0, numChar;

    // Counting the amount of the slots
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    ptr = head;
    stack = ptr->slotStack;
    for (int i = 0; i < count; i++) {
        numChar = 0;
        if (i == index) {
            // Counting how many characters does the stack of the target slot include
            while (!(stack.isEmpty())) {
                stack.pop(ch);
                numChar++;
            }
            // If there are 4 characters in the given slot, that means the target slot is full
            if (numChar == 4) {
                return true;
            }
        }
        else {
            // Avoiding a possible segmentation fault
            if (i != (count - 1)) {
                ptr = ptr->next;
                stack = ptr->slotStack;
            }
        }
    }

    return false;
}

void Board::destroySlot(const int &index) {
    slot * ptr = head;
    CharStack stack;
    int count = 0;

    // Counting the amount of slots
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    ptr = head;
    // Examining the head and tail nodes separately
    if (index == 0) {
        head = ptr->next;
        head->prev = NULL;
        delete ptr; // Avoiding memory leak
        ptr = NULL;
    }
    // If the given slot is pointed by the tail node
    else if (index == count - 1) {
        ptr = head;
        for (int i = 0; i < count; i++) {
            if (i == index) {
                tail = ptr->prev;
                tail->next = NULL;
                delete ptr; // Avoiding memory leak
                ptr = NULL;
            }
            else {
                // Avoiding a possible segmentation fault
                if (i != (count - 1)) {
                    ptr = ptr->next;
                }
            }
        }
    }
    // Check if the given index is between 0 and (the length of the slot - 1)
    else {
        ptr = head;
        for (int i = 0; i < count; i++) {
            if (i == index) {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                delete ptr; // Avoiding memory leak
                ptr = NULL;
                break;
            }
            else {
                // Avoiding a possible segmentation fault
                if (i != (count - 1)) {
                    ptr = ptr->next;
                }
            }
        }
    }
}

int Board::evaluateGame() {
    int result;
    slot * ptr = head;
    CharStack stack;
    char ch;
    int count = 0;
    xCnt = 0;
    oCnt = 0;

    // Counting the amount of slots
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    ptr = head;
    stack = ptr->slotStack;
    for (int i = 0; i < count; i++) {
        // Count the amount of characters separately as long as the examined slot is not empty
        if (!(stack.isEmpty())) {
            while (!(stack.isEmpty())) {
                stack.pop(ch);
                if (ch == 'x') {
                    xCnt++;
                } else if (ch == 'o') {
                    oCnt++;
                }
            }
        }
        // Avoiding a possible segmentation fault
        if (i != (count - 1)) {
            ptr = ptr->next;
            stack = ptr->slotStack;
        }
    }

    if (xCnt < oCnt) {
        result = 1;
    }
    if (xCnt > oCnt) {
        result = 2;
    }
    if (xCnt == oCnt) {
        result = 3;
    }
    return result;
}

void Board::clearBoard() {
    slot * ptr = head;
    slot * temp;
    int count = 0;

    // Counting the amount of slots
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    ptr = head;
    head = NULL;
    tail = NULL;

    // Deleting the slots one by one starting from the first slot
    for (int i = 0; i < count; i++) {
        if (i != count - 1) {
            temp = ptr;
            ptr = temp->next;
            ptr->prev = NULL;
            temp->next = NULL;
            delete temp; // Avoiding memory leak
            temp = NULL;
        }
        else {
            delete ptr; // Avoiding memory leak
            ptr = NULL;
        }
    }
}
