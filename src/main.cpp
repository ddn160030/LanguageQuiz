/*
-------------------------------------------------------------------------
Name: Dustin Nguyen
Date: 7/22/2024
Project #:		Exam 3 Project
Status: 		Completed
Class:			COSC 1337
-------------------------------------------------------------------------
Project Objectives: Input, Classes/Struct
-------------------------------------------------------------------------
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

struct totalResults {
    int correct;
    int incorrect;
    double grade;
    int passed;
    int failed;
};

// Declaration of prototypes
void projectStart();
void projectEnd();

//Function to read dictionary.txt
vector<pair<string, string>> readFile(const string& filename) {
    //Vector declaration
    vector<pair<string, string>> words;
    //Opens dictionary.txt
    ifstream file(filename);
    string english;
    string spanish;

    //Reading dictionary.txt
    while (getline(file, english) && getline(file, spanish)) {
        words.push_back({ english, spanish });
    }
    return words;
}

// Quiz Function
totalResults runQuiz(const vector<pair<string, string>>& words, int numberQuestions) {
    totalResults result = { 0, 0, 0.0, 0, 0 };
    cout << "-------------------------\n";
    cout << "Quiz\n";
    cout << "-------------------------\n";
    for (size_t i = 0; i < static_cast<size_t>(numberQuestions); i++) {
        // Random number generator
        size_t index = rand() % words.size();
        auto selection = words[index];

        cout << "Question " << i + 1 << '\n';
        cout << "English word: " << selection.first << '\n';
        cout << "Your answer in Spanish: ";
        string userInput;
        getline(cin, userInput);
        if (userInput == selection.second) {
            cout << "\nResult: Correct!";
            cout << "-------------------------\n";
            ++result.correct;
        }
        else {
            cout << "\nResult: Incorrect.";
            cout << "-------------------------\n";
            ++result.incorrect;
        }
    }
    result.grade = static_cast<double>(result.correct) / numberQuestions * 100;
    return result;
}

// Summary Function
void summary(string userName, const vector<totalResults>& allResults, int numberQuestions) {
    cout << "Quiz Summary\n";
    cout << "Name: " << userName;
    cout << "\n# of Questions in the quiz: " << numberQuestions;

    int totalPassed = 0;
    int totalFailed = 0;
    for (size_t i = 0; i < allResults.size(); ++i) {
        cout << "\nQuiz " << i + 1 << " Results:\n";
        cout << "# of Correct answers: " << allResults[i].correct << "\n";
        cout << "# of Incorrect answers: " << allResults[i].incorrect << "\n";
        cout << "Your % Grade: " << allResults[i].grade << "%\n";

        if (allResults[i].grade < 80.0) {
            cout << "Decision: FAILED. The passing score is 80%\n";
            totalFailed++;
        }
        else {
            cout << "Decision: Passed.\n";
            totalPassed++;
        }
    }
    cout << "Total Passed: " << totalPassed << "\n";
    cout << "Total Failed: " << totalFailed << "\n";
}

//Ending Summary Function
void endingSummary(string userName, const vector<totalResults>& allResults) {
    cout << "-------------------------\n";
    cout << "Quiz Summary\n";
    cout << "-------------------------\n";
    cout << "Student Name: " << userName << '\n';
    cout << "Number of Quizzes\n";
    cout << "Attempted: " << allResults.size() << '\n';

    int totalPassed = 0;
    int totalFailed = 0;
    double highestGrade = 0.0;

    for (size_t i = 0; i < allResults.size(); i++) {
        totalPassed += allResults[i].passed;
        totalFailed += allResults[i].failed;
        if (allResults[i].grade > highestGrade) {
            highestGrade = allResults[i].grade;
        }
    }

    cout << "Passed: " << totalPassed << '\n';
    cout << "Failed: " << totalFailed << '\n';
    cout << "Highest: " << highestGrade << "%\n";
}

int main()
{
    // Displays start of project
    projectStart();

    vector<totalResults> allResults;
    srand(static_cast<unsigned int>(time(nullptr)));
    int numberQuestions = 0;
    string userName;

    cout << "Welcome to the Ally Baba English-Spanish Class.\n";
    cout << "Please enter your name: ";
    getline(cin, userName);
    cout << '\n';
    cout << "Maximum available words in the Quiz: 10 words.\n";
    cout << "How many questions would you like to be quizzed on?: ";
    cin >> numberQuestions;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto words = readFile("dictionary.txt");

    while (true) {
        totalResults quizResult = runQuiz(words, numberQuestions);
        if (quizResult.grade >= 80.0) {
            quizResult.passed = 1;
            quizResult.failed = 0;
        }
        else {
            quizResult.passed = 0;
            quizResult.failed = 1;
        }
        allResults.push_back(quizResult);
        summary(userName, allResults, numberQuestions);
        cout << "---------------------" << endl;
        cout << "Do you want to take the quiz again (Y/N): ";
        char input;
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (input == 'Y' || input == 'y') {
            continue;
        }
        else if (input == 'N' || input == 'n') {
            break;
        }
        else {
            cout << "Invalid input. Exiting the quiz." << endl;
            break;
        }
    }
    endingSummary(userName, allResults);

    // Displays end of project
    projectEnd();
    return 0;
}

// The function will display the start of the project
void projectStart()
{
    cout << "---------------------" << endl;
    cout << "\tExam 3 Project " << endl;
    cout << "\tWritten by: Dustin Nguyen" << endl;
    cout << "\tDate: " << endl;
    cout << "---------------------" << endl;
    cout << "\tProject Objectives" << endl;
    cout << "\t\t" << endl;
    cout << "---------------------" << endl;
    cout << "\tAllyBaba Language Quiz" << endl;
    cout << "---------------------" << endl;
}

// The function will display the end of the project
void projectEnd()
{
    cout << "---------------------" << endl;
    cout << "\tEnd of Exam 3 Project" << endl;
    cout << "---------------------" << endl;
}