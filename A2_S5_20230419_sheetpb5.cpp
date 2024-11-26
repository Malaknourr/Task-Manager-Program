//Author : Malak NourElhussien
//ID : 20230419
//purpose : A task manager program (simulator)
//Date : 24/11/2024
//version : V5

#include <bits/stdc++.h>
using namespace std;

class Process {
    string imageName;       //Name of the process
    int PID = 0;            //Process ID
    string sessionName;     //Session type
    int sessionNumber = 0;  //Associated session number.
    int memoryUsage = 0;    //Memory usage in kilobytes.

    string formatMemory(int memory) const {
        string memStr = to_string(memory);
        int n = memStr.length();
        // Insert commas every 3 digits
        for (int i = n - 3; i > 0; i -= 3) {
            memStr.insert(i, ",");
        }
        return memStr;
    }

public:
    Process(string imageName_, int PID_, string sessionName_, int sessionNumber_, int memoryUsage_)
        : imageName(imageName_), PID(PID_), sessionName(sessionName_),
          sessionNumber(sessionNumber_), memoryUsage(memoryUsage_) {}

    void Display() const { //setw(x): Sets column width for alignment.
        cout << left //content to the left
             << setw(30) << imageName        // Image Name
             << setw(10) << PID              // PID
             << setw(20) << sessionName      // Session Name
             << setw(12) << sessionNumber    // Session Number
             << setw(9) << formatMemory(memoryUsage) << " K" << endl;
    }

    string getName() const { return imageName; }
    int getPID() const { return PID; }
    int getMemoryUsage() const { return memoryUsage; }
    string getSessionName() const { return sessionName; }
    int getSessionNumber() const { return sessionNumber; }
};

class List_of_Process {
    vector<Process> processes;
public:
    void fetchProcesses() {
        //Executes the tasklist command and writes the output to tasklist.txt.
        system("tasklist > tasklist.txt");

        ifstream file("tasklist.txt");//Opens the file for reading
        if (!file) {
            cerr << "Error: Could not open tasklist.txt." << endl;
            return;
        }

        string line;
        int lineCount = 0;

        while (getline(file, line)) {
            if (lineCount < 3) { // Skip header lines
                lineCount++;
                continue;
            }

            // Split the line into parts
            regex processRegex(R"(^\s*(.+?)\s+(\d+)\s+(\S+)\s+(\d+)\s+([\d,]+)\s*K\s*$)");
            smatch match; //"string match" is used to store the results of a regular expression search or match in a string.

            if (regex_search(line, match, processRegex)) {
                // Checks if the line matches the pattern in processRegex. If a match is found, it stores the captured groups in the match object.
                /*
                match[x] accesses a specific captured group from the regex match stored in std::smatch:
                match[0]: The full match (entire part of the string that matched the regex).
                match[1]: The first capturing group (first set of parentheses in your regex).
                match[2]: The second capturing group, and so on.
                 */
                string imageName = match[1].str();
                int PID = stoi(match[2].str());
                string sessionName = match[3].str();
                int sessionNumber = stoi(match[4].str());
                string memStr = match[5].str();

                // Remove commas from memory usage string
                erase(memStr, ',');
                int memoryUsage = stoi(memStr);

                processes.emplace_back(imageName, PID, sessionName, sessionNumber, memoryUsage);
            }

        }

        file.close();
    }

    void sortByName() {
        sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
            return p1.getName() < p2.getName();
        });
    }

    void sortByPID() {
        sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
            return p1.getPID() < p2.getPID();
        });
    }

    void sortByMemory() {
        sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
            return p1.getMemoryUsage() < p2.getMemoryUsage();
        });
    }

    void displayProcesses() const {
        cout << string(84, '_') << endl;
        cout << left
             << setw(30) << "Image Name"
             << setw(10) << "PID"
             << setw(20) << "Session Name"
             << setw(12) << "Session#"
             << setw(12) << "Mem Usage" << endl;
        cout << string(84, '_') << endl;

        for (const auto& process : processes) {
            process.Display();
        }
    }
};

int main() {
    List_of_Process processList;
    processList.fetchProcesses();

    cout << "---------------------------------------" << endl;
    cout << "WELCOME TO THE TASK MANAGER PROGRAM !\n";
    cout << "---------------------------------------" << endl;

    while (true) {
        cout << "Choose Sorting Criteria >> \n";
        cout << "1. Unsorted\n";
        cout << "2. Sort by Name\n";
        cout << "3. Sort by PID\n";
        cout << "4. Sort by Memory Usage\n";
        cout << "5. Exit\n";

        int choice;
        cout << "Enter your choice: ";

        // Check if the input is valid (an integer)
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a valid number between 1 and 5.\n";
            // Clear the input buffer to discard the invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your choice:";
        }

        // Switch-case for the user's choice
        switch (choice) {
            case 1:
                system("tasklist");  // Run the tasklist command to show unsorted processes
                break;
            case 2:
                cout << "--------------------SORTING BY NAME----------------------\n";
                processList.sortByName();  // Sort processes by Name
                break;
            case 3:
                cout << "----------------------SORTING BY PID---------------------\n";

                processList.sortByPID();  // Sort processes by PID
                break;
            case 4:
                cout << "-------------------SORTING BY MEMORY USAGE---------------\n";
                processList.sortByMemory();  // Sort processes by Memory Usage
                break;
            case 5:
                cout << "--------------------Exiting the program !----------------\n";
                return 0;  // Exit the program
            default:
                cout << "Invalid choice. Please select a valid option between 1 and 5.\n";
                continue;  // Go back to the menu if input is invalid
        }

        // Display the sorted processes after each choice
        if(choice != 1) {
            cout << "PROCESSES CAPTURED : \n";
            processList.displayProcesses();
        }
    }
}

