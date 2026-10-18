//Project 2
//CS-300
//Kaitlyn OConnell
//2026-04-17

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
STRUCT: Course
Holds course ID, title, and prerequisite list
The function of struct is to group related data together for easier management and access. 
It allows us to represent a course as a single entity with multiple attributes, 
making it easier to store and manipulate course information in the hash table.
*/
struct Course {
    string courseId;
    string courseTitle;
    vector<string> preList;
};

/*
NODE: Used for separate chaining in hash table
The Node struct is used to implement separate chaining in the hash table.
Each node contains a Course object and a pointer to the next node in the chain.
The node's significance is to  act as a container for the course data and to enable the chaining mechanism, 
allowing multiple courses to be stored at the same hash index in case of collisions.
If two courses hash to the same index, they will be stored in a linked list (chain) at that index, and form a linked list of nodes. 
*/
struct Node {
    Course course;
    Node* next;

    Node(Course c) {
        course = c;
        next = nullptr;
    }
};

/*
CLASS: HashTable
Implements hash table with separate chaining
The HashTable class implements a hash table data structure using separate chaining to handle collisions.
It converts a string key (course ID) into an index for storing and retrieving course information efficiently.
This helps efficient mapping of course IDs to their corresponding course details, allowing for quick insertion and search operations in the hash table.
*/
class HashTable {

private:
    static const int SIZE = 101;
    Node* table[SIZE];

    /*
   
    FUNCTION: hash
    Converts courseId into table index
	Usinging sizing and character values to create a hash function allows us to generate a unique index for each course ID,
	which helps in efficiently storing and retrieving course information in the hash table.
  
    */
    int hash(string key) {
        int sum = 0;
        for (char c : key) {
            sum += toupper(c);
        }
        return sum % SIZE;
    }

public:
    /*
 
    CONSTRUCTOR
	Initializes hash table with null pointers
	this constructor initializes the hash table by setting all entries in the table array to nullptr.
  
    */
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = nullptr;
        }
    }

    /*
    FUNCTION: Insert
    Inserts course into hash table
	This function reviews the index using the hash function and creates a new node for the course.
	if its empty it will insert the course, if not it will traverse the linked list at that index and add the new node to the end of the list.
	This prevents overwriting existing courses in case of hash collisions, 
    allowing multiple courses to be stored at the same index without losing data.
    */
    void Insert(Course course) {

        int index = hash(course.courseId);
        Node* newNode = new Node(course);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    /*
    FUNCTION: Search
   Hashing the course ID allows for efficient retrieval of course information from the hash table,
   We are traversing the linked list at the computed index to find the course with a matching ID,
   comparing course IDs in a case-insensitive manner ensures 
   that the search is robust and can find courses regardless of the case used in the input,
   return matching course or empty course if not found.

    
    */
    Course Search(string courseId) {

        int index = hash(courseId);
        Node* current = table[index];

        while (current != nullptr) {

            string stored = current->course.courseId;
            string search = courseId;

            transform(stored.begin(), stored.end(), stored.begin(), ::toupper);
            transform(search.begin(), search.end(), search.begin(), ::toupper);

            if (stored == search) {
                return current->course;
            }

            current = current->next;
        }

        return Course();
    }

    /*
    FUNCTION: GetAllCourses
	we are walking through the table and traversing each linked list to collect all courses into a vector.
	hash tables arent sorted, so we need to gather all courses and sort them before printing. 
    Then sort the vector of courses by course ID in alphanumeric order, 
    which allows us to display the courses in a user-friendly and organized manner when printing the course list.
    */
    vector<Course> GetAllCourses() {

        vector<Course> list;

        for (int i = 0; i < SIZE; i++) {
            Node* current = table[i];

            while (current != nullptr) {
                list.push_back(current->course);
                current = current->next;
            }
        }

        return list;
    }
};

/*
FUNCTION: validateCourse
Validates course ID and title before insertion
This is ensuring the existance of a course ID and title, and checks for basic formatting of the course ID (length and character type).
This is to validate the course data before inserting it into the hash table, 
ensuring that only well-formed and complete course information is stored, 
which helps maintain data integrity and prevents issues during retrieval and display of course information.
*/
bool validateCourse(const Course& c) {

    if (c.courseId.empty() || c.courseTitle.empty()) {
        return false;
    }

    
    if (c.courseId.length() < 15) {
        return false;
    }

    return true;
}

/*
FUNCTION: loadCourses
Reads file and loads into hash table
we are opening the file to read it line by line, parsing each line to extract course information, 
and then inserting valid courses into the hash table.
this helps managing user input and file handling, 
ensuring that the course data is correctly loaded into the hash table for later retrieval and display.
used stringstream to parse the line, which allows us to easily separate the course ID, title, 
and prerequisites based on the comma delimiter.

*/
void loadCourses(string fileName, HashTable* table) {

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;

        Course course;

        getline(ss, course.courseId, ',');
        getline(ss, course.courseTitle, ',');

        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                course.preList.push_back(token);
            }
        }

        // validation before insert
        if (!validateCourse(course)) {
            cout << "Invalid course data skipped." << endl;
            continue;
        }

        table->Insert(course);
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

/*
FUNCTION: displayCourse
Prints course details and provides output for course search
*/
void displayCourse(Course course) {

    cout << course.courseId << ", " << course.courseTitle << endl;
    cout << "Prerequisites: ";

    if (course.preList.empty()) {
        cout << "none" << endl;
    }
    else {
        for (size_t i = 0; i < course.preList.size(); i++) {
            cout << course.preList[i];
            if (i < course.preList.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

/*
FUNCTION: printSortedCourses
Sort + print alphanumeric list
lambda function in the sort call allows us to sort the courses by their course ID in alphanumeric order, 
begin function by getting all courses from the hash table, then sort them using the sort function from the algorithm library,
end function by printing the sorted list of courses to the user in a clear and organized manner,
*/
void printSortedCourses(HashTable* table) {

    vector<Course> list = table->GetAllCourses();

    sort(list.begin(), list.end(),
        [](const Course& a, const Course& b) {
            return a.courseId < b.courseId;
        });

    cout << "\nHere is a sample schedule:" << endl;

    for (Course course : list) {
        cout << course.courseId << ", " << course.courseTitle << endl;
    }
}

/*
FUNCTION: toUpper
Converts string to uppercase
converting the input string to uppercase ensures that the search for courses is case-insensitive,
*/
void toUpper(string& str) {
    for (char& c : str) {
        c = toupper(c);
    }
}

/*
MAIN PROGRAM
Provides user interface and handles user input
This uses a loop to present a menu to the user, allowing them to load course data, 
print the course list, or search for specific courses.
uses switch statement to handle user choices and calls the appropriate functions based on the user's input,
the if sttement prevents crashes from invalid input and prompts the user to enter a valid option,

*/
int main() {

    HashTable* courseTable = new HashTable();

    string fileName;
    string courseKey;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {

        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;

        cout << "\nWhat would you like to do? ";
        cin >> choice;

        // input validation
        if (cin.fail() || (choice != 1 && choice != 2 && choice != 3 && choice != 9)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << choice << " is not a valid option." << endl;
            continue;
        }

        switch (choice) {

        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadCourses(fileName, courseTable);
            break;

        case 2:
            printSortedCourses(courseTable);
            break;

        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseKey;

            toUpper(courseKey);

            {
                Course course = courseTable->Search(courseKey);

                if (course.courseId.empty()) {
                    cout << "Course not found." << endl;
                }
                else {
                    displayCourse(course);
                }
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
    }

    return 0;
}