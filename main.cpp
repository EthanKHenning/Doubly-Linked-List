#include <iostream> 
#include <fstream> //files
#include <cctype> //tolower
#include <string> //just makes working with strings easier
using namespace std;


class Node
{
private:  //why not set null/ empty values here
    string data;
    Node* next;
    Node* prev;
public:

    Node()
    {
        prev = nullptr;
        next = nullptr;
        data = "";
    }

    string getData()
    {
        return data;
    }
    void setData(string input)
    {
        data = input;
    }

    // Getter and setter for next
    Node* getNext()
    {
        return next;
    }
    void setNext(Node* newNext)
    {
        next = newNext;
    }

    // Getter and setter for prev
    Node* getPrev()
    {
        return prev;
    }
    void setPrev(Node* newPrev)
    {
        prev = newPrev;
    }
};
//implied public?
//constructor, by giving empty values I am allocating space in memory  


class DoublyLinkedList
{
private:
    Node* head;
    Node* tail;
    Node* curr;
    int size;

public:
    int getSize()
    {
        return size;
    }
    void setSize(int updatedSize)
    {
        size = updatedSize;
    }

    DoublyLinkedList()
    {
        head = new Node();
        head->setData("");
        tail = head;
        curr = head;
        setSize(1);
    }

    ~DoublyLinkedList()
    {
        curr = head;
        while (curr)
        {
            //this will erase everything behind it as it moves from the head to the tail
            curr->setPrev(nullptr); 
            curr = curr->getNext();
            if (curr == tail)
            {
                //once we reach the tail we want to erase curr but I also make sure to set everything next to it as null just incase  
                curr->setPrev(nullptr);
                curr->setNext(nullptr);
                delete curr->getPrev();
            }
        }
    }


    string lower(string input)
    {
        for (int i = 0; i < input.length(); i++) //makes everything lowercase
        {
            input[i] = tolower(input[i]);
        }
        return input;
    }


    void alphaOrder(string input)
    {
        Node* newNode = new Node(); // Create a new node
        newNode->setData(input); // Input the string for that node

        // If the list is empty
        if (head->getData() == "")
        {
            head = newNode;
            tail = newNode;
            setSize(1);
            return;
        }

        // Start from the head of the list
        curr = head;
        int comp;

        while (curr)
        {
            comp = input.compare(curr->getData());

            // If input goes before curr alphabetically
            if (comp < 0)
            {
                // Insert before curr
                newNode->setNext(curr);
                newNode->setPrev(curr->getPrev());

                if (curr->getPrev() != nullptr)
                {
                    curr->getPrev()->setNext(newNode);
                }
                else
                {
                    head = newNode; // If inserting at the beginning
                }
                
                curr->setPrev(newNode);
                setSize(size + 1);
                return;
            }
            // If we've reached the end of the list
            else if (curr->getNext() == nullptr)
            {
                // Insert at the end
                curr->setNext(newNode);
                newNode->setPrev(curr);
                tail = newNode;

                setSize(size + 1);
                return;
            }
            curr = curr->getNext();
        }
    }


    void deleteNode(string input)
    {
        if (!head) return; // this would mean the list is empty because I set a dummy node for head at the beginning 

        curr = head;
        while (curr)
        {
            if (input == curr->getData())
            {
                if (curr == head)
                {
                    head = curr->getNext();
                    if (head != nullptr)
                    {
                        head->setPrev(nullptr);
                    }
                }
                else if (curr == tail)
                {
                    tail = curr->getPrev();
                    if (tail != nullptr)
                    {
                        tail->setNext(nullptr);
                    }
                }
                else
                {
                    curr->getPrev()->setNext(curr->getNext());
                    curr->getNext()->setPrev(curr->getPrev());
                }

                delete curr;
                setSize(size - 1);
                return;
            }

            // Move to the next node only if we're not at the tail
            else
            {
                curr = curr->getNext();
            }
        }
    }
   

    //I think I'll make this always insert after curr
    //compare() allows me to put things in order based on return 
    void insertFromFile()
    {
        bool del = false;
        string ignore;
        string input;
        ifstream file("inputs.txt");
        if (!file) { cout << "failed"; }
        while (file >> input)
        {
            input = lower(input);
            if (del == true)
            {
                deleteNode(input);
                del = false;
                ignore = input;
            }

            if (input == "delete")
            {
                del = true;
            }
            if (input != ignore && input != "delete")
            {
                alphaOrder(input);
            }
        }
        if (del == true) 
        {
            deleteNode(input);
            del = false;
            ignore = input;
        }
        file.close();
    }


    void traverseDecending()
    {
        ofstream file("output.txt");

        if (!head) 
        {
            file << "List is empty" << endl;
        }
        else 
        {
            curr = head;
            while (curr) 
            {
                file << curr->getData() << endl;
                curr = curr->getNext();
            }
        }
        file.close();
    }


    void traverseAscending()
    {
        ofstream file("output.txt", ios::app);

        if (!tail) 
        {
            file << "List is empty" << endl;
        }
        else 
        {
            file << "===================" << endl;
            curr = tail;
            while (curr) 
            {
                file << curr->getData() << endl;
                curr = curr->getPrev();
            }
        }
        file.close();
    }
};

int main()
{
    DoublyLinkedList list;
    list.insertFromFile();
    list.traverseDecending();
    list.traverseAscending(); 
    return 0;
}

/*
In the 1st minute should explain the difference between deleting a node from a singly
versus a doubly linked list.

In the 2nd minute should explain how you can were able to create a sorted linked list
without using a sort function

In the 3rd minute, explain the difference between a doubly circular linked list and a
doubly linked list

In the 4th minute, show the text file that contains your data. Run your program that
shows that it compiles and displays the information correctly. Make sure that you are
both inserting and deleting. Explain your code in detail. Prove to the audience that you
were the one who wrote the code.
*/