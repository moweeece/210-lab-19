// COMSC-210 | Lab 19 | Mauricio Espinosa
// IDE Used: Visual Studio Code & Github

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>  // for srand()
#include <vector>
#include <fstream>
using namespace std;

struct Node
{
    float rating;
    string comment;
    Node *next;
};

class LinkedList
{
    private:
    Node *head;

    public:
    // constructor
    LinkedList();

    // function delcarations
    void addNodeToHead(float, const string&);
    void display() const;

    // destructor
    ~LinkedList();
};

class Movie
{
    private:
    string title;
    LinkedList reivews;

    public:
    // constructor
    Movie(const string& movieTitle);

    // function declarations
    void addReview(float, const string&);
    void display() const;
};

int main() {

    // seed random number generator
    srand(time(0));

    vector<Movie> movies;

    ifstream inputFile("reviews.txt");





    
    int userChoice;
    char anotherReview;

    // getting user inputs
    cout << "Which linked list method should we use" << endl;
    cout << "\t [1] New nodes are added at the head of the linked list" << endl;
    cout << "\t [2] New nodes are added at the tail of the linked list" << endl;
    cout << "Choice: ";
    cin >> userChoice;

    // do while loop for inputting while user says Y or y
    do {
        float rating;
        string comment;

        cout << "Enter review rating 0-5: ";
        cin >> rating;
        cin.ignore();
        cout << "Enter review comment: ";
        getline (cin, comment);

        // add node to head or tail depending on user input
        if (userChoice == 1)
        {
            reviewsList.addNodeToHead(rating, comment);
        }
        else if (userChoice == 2)
        {
            reviewsList.addNodeToTail(rating, comment);
        }

        cout << "Enter another review? Y/N: ";
        cin >> anotherReview;
    } while (anotherReview == 'Y' || anotherReview == 'y');

    cout << "Outputting all reviews: " << endl;
    reviewsList.display();

    return 0;
}


// function definitions

// constructor
LinkedList::LinkedList() : head(nullptr) {}

// function to add node to the front of the linked list
void LinkedList::addNodeToHead(float userRating, const string& userComment)
{
    // create a new memory allocation for the new node
    Node *newNode = new Node;
    newNode->next = nullptr;

    // set newNodes values
    newNode->rating = userRating;
    newNode->comment = userComment;

    // have head now point to the new node
    newNode->next = head;
    head = newNode;
}

// function to add node to the tail of the linked list
void LinkedList::addNodeToTail(float userRating, const string& userComment)
{
    // create a new memory allocation for the new node
    Node *newNode = new Node;
    newNode->next = nullptr;

    // set newNodes values
    newNode->rating = userRating;
    newNode->comment = userComment;

    // if the list is empty
    if (!head)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        // while the next pointer is not pointing at nullpointer
        // move pointer to next node
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }

}


// function to display the reviews and an average
void LinkedList::display()
{

    Node *temp = head;
    int count = 0;
    float sum = 0.0;
    float average = 0.0;

    // while not at the end of the list, display reviews
    while (temp != nullptr)
    {
        cout << setw(13) << "> Review #" << count + 1 << ": " << temp->rating << ": " << temp->comment << endl;
        sum += temp->rating;
        count++;
        temp = temp->next;
    }

    // calculate and display average
    average = sum / count;
    cout << setprecision(6) << setw(14) << "> Average: " << average << endl;
}


// linked list destructor
LinkedList::~LinkedList()
{
    // while not at the end of the list
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;    // move to next node
        delete temp;          // delete it
    }

}