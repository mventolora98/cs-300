// ProjectTwo.cpp
// This program loads course data from "courses.csv"
// Make sure "courses.csv" is in the same directory as the executable when running

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Load courses from CSV file
void loadCourses(map<string, Course>& courses, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "ERROR: Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string item;
        vector<string> tokens;

        while (getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() < 2) {
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseName = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }
        courses[course.courseNumber] = course;
    }
    file.close();

    cout << "Total courses loaded: " << courses.size() << endl;
}

// Print all courses sorted by course number
void printCourseList(const map<string, Course>& courses) {
    cout << "Total courses available to print: " << courses.size() << endl;

    vector<string> sortedKeys;
    for (const auto& pair : courses) {
        sortedKeys.push_back(pair.first);
    }
    sort(sortedKeys.begin(), sortedKeys.end());

    for (const string& key : sortedKeys) {
        const Course& course = courses.at(key);
        cout << course.courseNumber << ", " << course.courseName << endl;
    }
}

// Print details for a specific course
void printCourseDetails(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ", " << course.courseName << endl;

        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        } else {
            cout << "Prerequisites: None" << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}

int main() {
    map<string, Course> courses;
    int choice;
    string input;
    bool loaded = false;

    cout << "Welcome to the course planner.\n";

    do {
        cout << "\n  1. Load Data Structure\n  2. Print Course List\n  3. Print Course\n  9. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                loadCourses(courses, "courses.csv");
                loaded = true;
                break;
            }
            case 2:
                if (loaded) printCourseList(courses);
                else cout << "Please load the data first." << endl;
                break;
            case 3:
                if (loaded) {
                    cout << "What course do you want to know about? ";
                    cin >> input;
                    printCourseDetails(courses, input);
                } else {
                    cout << "Please load the data first." << endl;
                }
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    } while (choice != 9);

    return 0;
}

