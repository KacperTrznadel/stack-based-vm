#include <iostream>
#include <string.h>
using namespace std;

//-----------------------------------------
//---LINKED LIST(AS AN ELEMENT OF STACK)---
//-----------------------------------------

class LINKED_LIST {
private:
    struct LIST_NODE {

        LIST_NODE* next;
        char data;

    };

    LIST_NODE* head;

    LIST_NODE* deepCopyNodes(LIST_NODE* original) {
        if (original == nullptr)
            return nullptr;

        return new LIST_NODE{deepCopyNodes(original->next), original->data};
    }

public:
    LINKED_LIST() {
        head = nullptr;
    }

    LINKED_LIST(LINKED_LIST& other) {
        head = deepCopyNodes(other.head);
    }

    ~LINKED_LIST() {
        deleteList(head);
    }

    void deleteList(LIST_NODE* node) {
        if(node != nullptr) {
            deleteList(node->next);
            delete node;
        }
    }

    void pushFront(char newChar) {
        LIST_NODE* updatedNode = new LIST_NODE;
        updatedNode->data = newChar;
        updatedNode->next = head;
        head = updatedNode;
    }

    void pushBackRecursive(LIST_NODE*& node, char newChar) {
        if (node == nullptr) {
            node = new LIST_NODE;
            node->data = newChar;
            node->next = nullptr;
            return;
        }
        pushBackRecursive(node->next, newChar);
    }


    void pushBack(char newChar) {
        if (head == nullptr) {
            head = new LIST_NODE{nullptr, newChar};
            return;
        }
        pushBackRecursive(head, newChar);
    }

    void popFront() {
        if (head != nullptr) {
            LIST_NODE* temp = head;
            head = head->next;
            delete temp;
        }
    }

    char getFront() {
        return (head != nullptr) ? head->data : '\0';
    }

    char getBackRecursive(LIST_NODE* back) {
        if (back == nullptr) return '\0';
        if (back->next == nullptr)
            return back->data;
        return getBackRecursive(back->next);
    }


    char getBack() {
        if (head == nullptr)
            return '\0';
        return getBackRecursive(head);
    }

    void popBackRecursive(LIST_NODE*& node) {
        if (node == nullptr) return;

        if (node->next == nullptr) {
            delete node;
            node = nullptr;
            return;
        }

        popBackRecursive(node->next);
    }

    void popBack() {
        if (head == nullptr) return;
        popBackRecursive(head);
    }


    bool isEmpty() {
        return head == nullptr;
    }

    LIST_NODE* getHead() {
        if (head == nullptr)
            return nullptr;
        return head;
    }

    int power(int a, int b) {
        if (b == 0) return 1;
        if (b == 1) return a;
        return a * power(a, b - 1);
    }

    int getIntFromList(LIST_NODE* number, int powerValue = 0) {
        int index = 0;
        if (number == nullptr) return index;

        index = (number->data - '0') * power(10, powerValue);
        return index + getIntFromList(number->next, powerValue + 1);
    }

    LIST_NODE* intToListRecursive(int number) {
        if (number == 0) return nullptr;

        int temp = number % 10;
        LIST_NODE* result = new LIST_NODE;
        result->data = (char)(temp + '0');
        result->next = intToListRecursive(number / 10);
        return result;
    }

    void intToList(int number) {
        if (number == 0) {
            head = new LIST_NODE{nullptr, '0'};
            return;
        }
        head = intToListRecursive(number);
    }

    LIST_NODE* addDigitsRecursive(LIST_NODE* A, LIST_NODE* B, int carry) {
        if (A == nullptr && B == nullptr && carry == 0) { // if there is nothing more, end
            return nullptr;
        }

        int aDigit = (A != nullptr) ? (A->data - '0') : 0; // '0' filling if necessary
        int bDigit = (B != nullptr) ? (B->data - '0') : 0; // '0' filling if necessary

        int sum = aDigit + bDigit + carry; // the sum of digits and carry of operation before
        int newDigit = sum % 10;
        int newCarry = sum / 10;

        LIST_NODE* result = new LIST_NODE;
        result->data = (char)(newDigit + '0');
        result->next = addDigitsRecursive(A ? A->next : nullptr, B ? B->next : nullptr, newCarry);

        return result;
    }

    LIST_NODE* subtractDigitsRecursive(LIST_NODE* A, LIST_NODE* B, int borrow) {
        if (A == nullptr && B == nullptr && borrow == 0) {
            return nullptr;
        }

        int aDigit = (A != nullptr) ? (A->data - '0') : 0;
        int bDigit = (B != nullptr) ? (B->data - '0') : 0;

        int diff = aDigit - bDigit - borrow;
        int newBorrow = 0;

        if (diff < 0) {
            diff += 10;
            newBorrow = 1;
        }

        LIST_NODE* result = new LIST_NODE;
        result->data = (char)(diff + '0');
        result->next = subtractDigitsRecursive(A ? A->next : nullptr, B ? B->next : nullptr, newBorrow);

        return result;
    }

    LINKED_LIST* add(LINKED_LIST* other) {
        LINKED_LIST* A = new LINKED_LIST(*this);
        LINKED_LIST* B = new LINKED_LIST(*other);

        bool negA = A->isNegative(A);
        bool negB = B->isNegative(B);

        if (negA) A->popBack();
        if (negB) B->popBack();

        LINKED_LIST* result = new LINKED_LIST();

        if (negA == negB) { //if the sign is the same
            result->head = addDigitsRecursive(A->head, B->head, 0);
            if (negA) result->pushBack('-');
        } else { //if one is positive and another negative
            if (B->isAgreaterThanB(B, A)) { // if B is the greater number, swap lists before subtract. the subtractDigitsRecursive() operates only on A >= B
                LINKED_LIST* tmp = A;
                A = B;
                B = tmp;

                bool tmpNeg = negA; // negation swap
                negA = negB;
                negB = tmpNeg;
            }

            result->head = subtractDigitsRecursive(A->head, B->head, 0);
            result->removeLeadingZeros(result);

            if (negA && !(result->listLength(result->getHead()) == 1 && result->getFront() == '0')) result->pushBack('-');
        }

        delete A;
        delete B;
        return result;
    }

    void mergeAtBackRecursive(LIST_NODE* head, LIST_NODE* newNode) {
        if (head == nullptr) {
            return;
        }
        if (head->next == nullptr) {
            head->next = newNode;
            return;
        }
        return mergeAtBackRecursive(head->next, newNode);

    }

    void mergeAtBack(LIST_NODE* node) {
        return mergeAtBackRecursive(head, node);
    }

    void removeLeadingZeros(LINKED_LIST* list) {
        if (list == nullptr || (list->getBack() != '0' && list->getBack() != '-')) return; //end recursive if there is nothing more to do
        if (list->getBack() == '0' && list->listLength(list->getHead()) == 1) return; //if list contains only of zero, also end recursive
        if (list->isEmpty()) return; //if its empty too
        if (list->getBack() == '-') { // negative number
            list->popBack();
            if (list->isEmpty()) { // if there was only minus
                list->pushBack('0'); // put the zero
                return; // and finish

            } else if (list->getBack() == '0') { //negative number and zero right after
                list->popBack(); // delete the zero
                list->pushBack('-'); // and replace it with minus

            } else { //negative number and something else than zero
                list->pushBack('-'); // put minus back
                return; // end the function
            }
        } else if (list->getBack() == '0') { // positive number, but zero at the beginning
            list->popBack(); // delete it
        }
        return removeLeadingZeros(list); // again
    }

    bool isAgreaterThanBRecursive(LINKED_LIST* A, LINKED_LIST* B) {

        if (A->isEmpty() || B->isEmpty()) return false;
        char digitA = A->getBack();
        char digitB = B->getBack();

        if (digitB < digitA) {
            return true;
        }
        else if (digitB > digitA) {
            return false;
        }
        else {
            A->popBack();
            B->popBack();
            return isAgreaterThanBRecursive(A, B);
        }

    }

    bool isNegative(LINKED_LIST* list) {
        return list->getBack() == '-';
    }

    bool isAgreaterThanB(LINKED_LIST* A, LINKED_LIST* B) {
        LINKED_LIST* tempA = new LINKED_LIST();
        LINKED_LIST* tempB = new LINKED_LIST();

        tempA->head = A->deepCopyNodes(A->getHead());
        tempB->head = B->deepCopyNodes(B->getHead());

        tempA->removeLeadingZeros(tempA);
        tempB->removeLeadingZeros(tempB);

        bool negA = isNegative(tempA);
        bool negB = isNegative(tempB);

        if (negA && !negB) return false;
        if (!negA && negB) return true;

        if (!negA && !negB) {
            int lenA = tempA->listLength(tempA->getHead());
            int lenB = tempB->listLength(tempB->getHead());
            if (lenA != lenB)
                return lenA > lenB;
            return tempA->isAgreaterThanBRecursive(tempA, tempB);
        }

        tempA->popBack();
        tempB->popBack();
        int lenA = tempA->listLength(tempA->getHead());
        int lenB = tempB->listLength(tempB->getHead());
        if (lenA != lenB)
            return lenA < lenB;
        if (isAequalToB(tempA->getHead(), tempB->getHead())) {
            return false;
        }
        return !tempA->isAgreaterThanBRecursive(tempA, tempB);
    }

    bool isEqualRecursive(LIST_NODE* A, LIST_NODE* B) {
        if (A == nullptr && B == nullptr) return true;
        if (A == nullptr || B == nullptr) return false;

        if (A->data != B->data)
            return false;

        return isEqualRecursive(A->next, B->next);
    }

    bool isAequalToB(LIST_NODE* A, LIST_NODE* B) {
        LINKED_LIST tempA, tempB;

        tempA.head = deepCopyNodes(A);
        tempB.head = deepCopyNodes(B);

        tempA.removeLeadingZeros(&tempA);
        tempB.removeLeadingZeros(&tempB);

        return isEqualRecursive(tempA.head, tempB.head);
    }

    void printNode(LIST_NODE* list) {
        if (list == nullptr) return;
        cout << list->data;
        printNode(list->next);
    }

    void printList() {
        if (head == nullptr) return;
        printNode(head);
    }

    int listLength(LIST_NODE* curr) {
        if (curr == nullptr) return 0;
        return 1 + listLength(curr->next);
    }

};

//-----------------------------------------
//------------MAIN STACK CLASS-------------
//-----------------------------------------

class STACK {

private:
    struct NODE {

        NODE* next;
        LINKED_LIST* dataList;

    };

    NODE* head;

public:

    STACK() {
        head = nullptr;
    }

    ~STACK() {
        deleteStack(head);
    }

    void deleteStack(NODE* node) {
        if(node != nullptr) {
            deleteStack(node->next);
            delete node->dataList;
            delete node;
        }
    }

    void pushFront(LINKED_LIST* newList) {
        NODE* updatedNode = new NODE;
        updatedNode->dataList = newList;
        updatedNode->next = head;
        head = updatedNode;
    }

    void popFront() {
        if (head != nullptr) {
            NODE* temp = head;
            head = head->next;
            delete temp->dataList;
            delete temp;
        }
    }

    LINKED_LIST* getFront() {
        return (head != nullptr) ? head->dataList : nullptr;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void swapTop() {
        if (!head || !head->next) return;

        NODE* first = head;
        NODE* second = head->next;

        first->next = second->next;
        second->next = first;
        head = second;
    }

    LINKED_LIST* getIndexRecursive(NODE* head, int index) {
        if (index == 0) return head->dataList;
        return getIndexRecursive(head->next, index-1);
    }

    LINKED_LIST* getIndex(int index) {
        return getIndexRecursive(head, index);
    }

    void printNode(NODE* stack, int depth) {
        if (stack == nullptr) return;
        printNode(stack->next, depth + 1);
        cout << depth << ": ";
        stack->dataList->printList();
        cout << endl;
    }

    void printStack() {
        if (head == nullptr)
            return;
        printNode(head, 0);
    }


};

int main() {

    char* program = new char[20001];

    cin.getline(program, 20001);

    STACK* stack = new STACK();

    for(int instructionPointer = 0; instructionPointer < strlen(program); instructionPointer++) {
        switch(program[instructionPointer]) {
            case '\'':
                stack->pushFront(new LINKED_LIST());
                break;

            case ',':
                stack->popFront();
                break;

            case ':':
                stack->pushFront(new LINKED_LIST(*stack->getFront()));
                break;

            case ';':
                stack->swapTop();
                break;

            case '@': {
                LINKED_LIST* front = stack->getFront();
                int index = front->getIntFromList(front->getHead());
                stack->popFront();
                LINKED_LIST* copy = new LINKED_LIST(*(stack->getIndex(index)));
                stack->pushFront(copy);
                break;
            }

            case '&':
                stack->printStack();
                break;

            case '.': {
                char inputChar;
                cin >> inputChar;
                LINKED_LIST* front = stack->getFront();
                front->pushFront(inputChar);
                break;
            }

            case '>': {
                LINKED_LIST* front = stack->getFront();
                cout << front->getFront();
                stack->popFront();
                break;
            }

            case '-': {
                if (stack->isEmpty()) {
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushBack('-');
                    stack->pushFront(newList);
                } else {
                    LINKED_LIST* stackFront = stack->getFront();
                    char last = stackFront->getBack();
                    if (last == '-') {
                        stackFront->popBack();
                    }
                    else {
                        stackFront->pushBack('-');
                    }
                }
                break;
            }

            case '^': {
                if (!stack->isEmpty()) {
                    LINKED_LIST* stackFront = stack->getFront();
                    char last = stackFront->getBack();
                    if (last == '-') {
                        stackFront->popBack();
                    }
                }
                break;
            }

            case ']': {

                LINKED_LIST* front = stack->getFront();
                int number = front->getIntFromList(front->getHead());
                stack->popFront();
                char ascii = (char)number;
                LINKED_LIST* newList = new LINKED_LIST();
                newList->pushFront(ascii);
                stack->pushFront(newList);
                break;
            }

            case '[': {
                LINKED_LIST* front = stack->getFront();
                char frontChar = front->getFront();
                int asciiValue = (int)frontChar;
                LINKED_LIST* newList = new LINKED_LIST();
                newList->intToList(asciiValue);
                stack->popFront();
                stack->pushFront(newList);
                break;
            }

            case '$': {
                LINKED_LIST* front = stack->getFront();
                char frontChar = front->getFront();
                front->popFront();
                LINKED_LIST* newList = new LINKED_LIST();
                newList->pushFront(frontChar);
                stack->pushFront(newList);
                break;
            }

            case '#': {
                LINKED_LIST* front = stack->getFront();
                LINKED_LIST* newList = new LINKED_LIST(*front);
                stack->popFront();
                LINKED_LIST* newFront = stack->getFront();
                newFront->mergeAtBack(newList->getHead());
                break;
            }

            case '<': {
                LINKED_LIST* A = stack->getFront();
                LINKED_LIST* copyA = new LINKED_LIST(*A);
                stack->popFront();
                LINKED_LIST* B = stack->getFront();
                LINKED_LIST* copyB = new LINKED_LIST(*B);
                stack->popFront();

                bool isAgreater = copyA->isAgreaterThanB(copyA,copyB);

                if (isAgreater) {
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushFront('1');
                    stack->pushFront(newList);
                } else {
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushFront('0');
                    stack->pushFront(newList);
                }
                delete copyA;
                delete copyB;
                break;
            }

            case '=': {
                LINKED_LIST* A = stack->getFront();
                LINKED_LIST* copyA = new LINKED_LIST(*A);
                stack->popFront();
                LINKED_LIST* B = stack->getFront();
                LINKED_LIST* copyB = new LINKED_LIST(*B);
                stack->popFront();

                bool isEqual = copyA->isAequalToB(copyA->getHead(),copyB->getHead());

                if (isEqual) {
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushFront('1');
                    stack->pushFront(newList);
                } else {
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushFront('0');
                    stack->pushFront(newList);
                }
                delete copyA;
                delete copyB;
                break;
            }

            case '!': {
                LINKED_LIST* A = stack->getFront();
                if (A->isEmpty() || (A->getFront() == '0' && A->listLength(A->getHead()) == 1)) {
                    stack->popFront();
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushFront('1');
                    stack->pushFront(newList);
                } else {
                    stack->popFront();
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushFront('0');
                    stack->pushFront(newList);
                }
                break;
            }

            case '~': {
                LINKED_LIST* list = new LINKED_LIST();
                list->intToList(instructionPointer);
                stack->pushFront(list);
                break;
            }

            case '?': {
                LINKED_LIST* T = stack->getFront();
                LINKED_LIST* copyT = new LINKED_LIST(*T);
                stack->popFront();
                LINKED_LIST* W = stack->getFront();

                if (!(W->isEmpty() || (W->getFront() == '0' && W->listLength(W->getHead()) == 1))) {
                    stack->popFront();
                    int t = copyT->getIntFromList(copyT->getHead());
                    instructionPointer = t - 1;
                } else {
                    stack->popFront();
                }
                delete copyT;
                break;
            }

            case '+': {
                LINKED_LIST* A = stack->getFront();
                LINKED_LIST* copyA = new LINKED_LIST(*A);
                stack->popFront();
                LINKED_LIST* B = stack->getFront();
                LINKED_LIST* copyB = new LINKED_LIST(*B);
                stack->popFront();

                LINKED_LIST* result = copyA->add(copyB);
                stack->pushFront(result);

                delete copyA;
                delete copyB;
                break;
            }

            default:
                if (!stack->isEmpty()) {
                    stack->getFront()->pushFront(program[instructionPointer]);
                } else {
                    LINKED_LIST* newList = new LINKED_LIST();
                    newList->pushFront(program[instructionPointer]);
                    stack->pushFront(newList);
                }
                break;
        }
    }

    delete stack;
    delete[] program;
    return 0;
}