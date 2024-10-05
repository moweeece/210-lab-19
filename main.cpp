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
    LinkedList reviews;

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
    string fileComment;

    ifstream inputFile("reviews.txt");

    // file opening validation
    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // create movie objects
    movies.push_back(Movie("Inception"));
    movies.push_back(Movie("Dunkirk"));
    movies.push_back(Movie("Interstellar"));
    movies.push_back(Movie("The Prestige"));


    // loop through each movie and assign 3 random reviews
    for (Movie& movie : movies)
    {
        // loops 3 times
        for (int i = 0; i < 3; i++)
        {
            if (getline(inputFile, fileComment))
            {
                float rating = 1.0 + static_cast<float>(rand()) / (RAND_MAX / 4.0); // random rating
                movie.addReview(rating, fileComment);
            }
            else
            {
                break;
            }
        }
    }

    // close the file
    inputFile.close();

    // display movie reviews
    for (const Movie& movie : movies)
    {
        movie.display();
    }

    return 0;
}


// function definitions

// constructors
LinkedList::LinkedList() : head(nullptr) {}

Movie::Movie(const string& movieTitle) : title(movieTitle) {}

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

// function to display the reviews and an average
void LinkedList::display() const
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

// Add movie review method
void Movie::addReview(float rating, const string& fileComment)
{
    reviews.addNodeToHead(rating, fileComment);
}


// Display method
void Movie::display() const
{
    cout << "Movie: " << title << endl;
    reviews.display();
    cout << endl;
}

