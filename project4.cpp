#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h> 
#include <vector>  
#include <sstream> 
#include <windows.h>

using namespace std;

// Function to set text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to reset text color
void resetColor() {
    setColor(7); // Default console color
}

class Student {
private:
    int roll;
    string name;
    string faculty;
    string sec;
    string ph;
    char attendance;
    string date;

public:
    int getRoll() const { return roll; }
    void setRoll(int r) { roll = r; }

    string getName() const { return name; }
    void setName(const string& n) { name = n; }

    string getFaculty() const { return faculty; }
    void setFaculty(const string& f) { faculty = f; }

    string getSection() const { return sec; }
    void setSection(const string& s) { sec = s; }

    string getPhone() const { return ph; }
    void setPhone(const string& p) { ph = p; }

    char getAttendance() const { return attendance; }
    void setAttendance(char a) { attendance = a; }

    string getDate() const { return date; }
    void setDate(const string& d) { date = d; }

    void add() {
        ofstream fptr("record.txt", ios::app);
        if (!fptr) {
            cout << "File cannot be created!!!" << endl;
            return;
        }
        char choice;
        do {
            system("cls");
            cout << "Enter RollNo:\n";
            int roll;
            cin >> roll;
            setRoll(roll);

            cout << "Enter Name:\n";
            cin.ignore(); // To ignore the newline character left in the input buffer
            string name;
            getline(cin, name);
            setName(name);

            cout << "Enter Faculty:\n";
            string faculty;
            getline(cin, faculty);
            setFaculty(faculty);

            cout << "Enter Section:\n";
            string sec;
            getline(cin, sec);
            setSection(sec);

            cout << "Enter Phone_No:\n";
            string ph;
            cin >> ph;
            setPhone(ph);

            fptr << getRoll() << " " << getName() << " " << getFaculty() << " " << getSection() << " " << getPhone() << endl;
            system("cls");
            cout << "Record Added Successfully." << endl << endl << endl;
            cout << "Do you want to add a new record(Y/N):";

            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
        fptr.close();
    }

    void display() {
        system("cls");
        ifstream fptr("record.txt");
        if (!fptr) {
            cout << "File cannot be opened!!!" << endl;
            return;
        }

        cout << "Displaying Records\n\n";
        cout << "Roll_NO\t\t Name\t\tFACULTY\t SECTION\t PHONE_NO\n\n";
        cout << "---------------------------------------------------------------------------\n";

        Student s;
        int roll;
        string name, faculty, sec, ph;
        while (fptr >> roll) {
            fptr.ignore(); // Ignore whitespace
            getline(fptr, name, ' ');
            getline(fptr, faculty, ' ');
            getline(fptr, sec, ' ');
            getline(fptr, ph);

            s.setRoll(roll);
            s.setName(name);
            s.setFaculty(faculty);
            s.setSection(sec);
            s.setPhone(ph);

            cout << s.getRoll() << "\t\t" << s.getName() << "\t\t" << s.getFaculty() << "\t   " << s.getSection() << "\t\t" << s.getPhone() << endl << endl;
        }
        fptr.close();
        cout << endl << endl;
        cout << "Press any key to return to the main menu...";
        getch(); // Wait for the user to press a key
    }

    void search() {
        system("cls");

        int roll;
        bool flag = false;
        ifstream fptr("record.txt");
        if (!fptr) {
            cout << "File cannot be opened." << endl;
            return;
        }

        cout << "Enter roll_no of student: ";
        cin >> roll;

        Student s;
        int r;
        string name, faculty, sec, ph;
        while (fptr >> r) {
            fptr.ignore(); // Ignore whitespace
            s.setRoll(r);

            getline(fptr, name, ' ');
            s.setName(name);

            getline(fptr, faculty, ' ');
            s.setFaculty(faculty);

            getline(fptr, sec, ' ');
            s.setSection(sec);

            getline(fptr, ph);
            s.setPhone(ph);

            if (s.getRoll() == roll) {
                flag = true;
                cout << "\n\nRecord Found.\n\n";
                cout << "Roll_NO\t\t Name\t\tFACULTY\t SECTION\t PHONE_NO\n";
                cout << "---------------------------------------------------------------------------\n";
                cout << s.getRoll() << "\t\t" << s.getName() << "\t\t" << s.getFaculty() << "\t   " << s.getSection() << "\t\t" << s.getPhone() << "\n\n";
                break;
            }
        }

        if (!flag) {
            cout << "Record not Found." << endl;
        }

        fptr.close();
        cout << endl << endl;
        cout << "Press any key to return to the main menu...";
        getch(); // Wait for the user to press a key
    }

    void deleteRecord() {
        system("cls");

        ifstream fp1("record.txt");
        ofstream fp2("temp.txt");
        if (!fp1) {
            cout << "File cannot be opened." << endl;
            return;
        }

        Student s;
        int temp_roll;
        bool found = false;
        cout << "Enter the roll no to delete the record of the student: ";
        cin >> temp_roll;

        int roll;
        string name, faculty, sec, ph;
        while (fp1 >> roll) {
            fp1.ignore(); // Ignore whitespace
            s.setRoll(roll);

            getline(fp1, name, ' ');
            s.setName(name);

            getline(fp1, faculty, ' ');
            s.setFaculty(faculty);

            getline(fp1, sec, ' ');
            s.setSection(sec);

            getline(fp1, ph);
            s.setPhone(ph);

            if (temp_roll == s.getRoll()) {
                found = true;
                continue; // Skip writing this record to the new file
            }
            fp2 << s.getRoll() << " " << s.getName() << " " << s.getFaculty() << " " << s.getSection() << " " << s.getPhone() << endl;
        }

        if (found) {
            cout << "\nThe record of student with roll " << temp_roll << " is deleted!" << endl;
        } else {
            cout << "\nRecord not found for roll number " << temp_roll << "!" << endl;
        }

        fp1.close();
        fp2.close();
        remove("record.txt");
        rename("temp.txt", "record.txt");
        cout << endl << endl;
        cout << "Press any key to return to the main menu...";
        getch(); // Wait for the user to press a key
    }

    void update() {
        system("cls");

        ifstream fptr("record.txt");
        ofstream temp_file("temp.txt");
        if (!fptr) {
            cout << "File cannot be opened." << endl;
            return;
        }

        Student s;
        int temp_roll;
        bool found = false;

        cout << "Enter the roll no to update: ";
        cin >> temp_roll;

        int roll;
        string name, faculty, sec, ph;
        while (fptr >> roll) {
            fptr.ignore(); // Ignore whitespace
            s.setRoll(roll);

            getline(fptr, name, ' ');
            s.setName(name);

            getline(fptr, faculty, ' ');
            s.setFaculty(faculty);

            getline(fptr, sec, ' ');
            s.setSection(sec);

            getline(fptr, ph);
            s.setPhone(ph);

            if (temp_roll == s.getRoll()) {
                found = true;
                int upd;
                bool continueUpdating = true;
                while (continueUpdating) {
                    cout << "UPDATE MENU\n";
                    cout << "1. Name\n2. Faculty\n3. Section\n4. Phone_No\n5. Exit\n";
                    cout << "Enter choice: ";
                    cin >> upd;
                    cin.ignore();

                    switch (upd) {
                        case 1:
                            cout << "Enter New Name: ";
                            getline(cin, name);
                            s.setName(name);
                            break;
                        case 2:
                            cout << "Enter New Faculty: ";
                            getline(cin, faculty);
                            s.setFaculty(faculty);
                            break;
                        case 3:
                            cout << "Enter New Section: ";
                            getline(cin, sec);
                            s.setSection(sec);
                            break;
                        case 4:
                            cout << "Enter New Phone_No: ";
                            cin >> ph;
                            s.setPhone(ph);
                            break;
                        case 5:
                            continueUpdating = false;
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                            break;
                    }
                }
            }
            temp_file << s.getRoll() << " " << s.getName() << " " << s.getFaculty() << " " << s.getSection() << " " << s.getPhone() << endl;
        }

        if (found) {
            cout << "\nRecord updated successfully!" << endl;
        } else {
            cout << "\nRecord not found!" << endl;
        }

        fptr.close();
        temp_file.close();
        remove("record.txt");
        rename("temp.txt", "record.txt");
        cout << endl << endl;
        cout << "Press any key to return to the main menu...";
        getch(); // Wait for the user to press a key
    }

  void mark_attendance() {
    system("cls");

    vector<Student> students; // Use vector to dynamically manage students
    int totalAbsent, totalStudents = 0;
    vector<int> absentRolls; // Dynamic list of absent roll numbers

    ifstream fptr_record("record.txt");
    if (!fptr_record) {
        cout << "Error opening record file." << endl;
        return;
    }

    Student temp;
    int roll;
    string name, faculty, sec, ph;
    while (fptr_record >> roll) {
        fptr_record.ignore();
        getline(fptr_record, name, ' ');
        getline(fptr_record, faculty, ' ');
        getline(fptr_record, sec, ' ');
        getline(fptr_record, ph);

        temp.setRoll(roll);
        temp.setName(name);
        temp.setFaculty(faculty);
        temp.setSection(sec);
        temp.setPhone(ph);

        students.push_back(temp);
        totalStudents++;
    }
    fptr_record.close();

    cout << "Enter the total number of absent students: ";
    cin >> totalAbsent;
    absentRolls.resize(totalAbsent); // Resize to the number of absent students

    cout << "Enter the roll numbers of absent students:\n";
    for (int i = 0; i < totalAbsent; i++) {
        cout << "Absent student " << i + 1 << ": ";
        cin >> absentRolls[i];
    }

    ofstream fptr_attendance("attendance.txt", ios::app);
    if (!fptr_attendance) {
        cout << "Error opening attendance file." << endl;
        return;
    }

    string date;
    cout << "Enter today's Date (DD/MM/YYYY): ";
    cin >> date;

    fptr_attendance << "Date: " << date << endl;

    for (auto& student : students) {
        char attendance = 'P'; // Assume present by default
        for (const auto& roll : absentRolls) {
            if (student.getRoll() == roll) {
                attendance = 'A'; // Mark as absent
                break;
            }
        }
        fptr_attendance << student.getRoll() << " " << student.getName() << " " << student.getFaculty() << " " << student.getSection() << " " << attendance << endl;
    }

    fptr_attendance.close();
    cout << "Attendance recorded successfully." << endl;
    cout << "Press any key to return to the main menu...";
    getch(); // Wait for the user to press a key
}

void display_attendance() {
    

    ifstream file("attendance.txt");
    if (!file) {
        cout << "Error opening attendance file." << endl;
        return;
    }

    Student s;
    string dateLine, name, faculty, sec;
    int roll;
    char attendance;

    cout << "Date-wise Attendance Records\n";
    cout << "Roll_NO\t\t Name\t\tFACULTY\t SECTION\t ATTENDANCE\n";
    cout << "--------------------------------------------------------------------------\n";

    while (getline(file, dateLine)) {
        if (dateLine.find("Date:") != string::npos) {
            cout << dateLine << endl; // Display the date
            cout << "--------------------------------------------------------------------------\n";
        } else {
            stringstream ss(dateLine);
            ss >> roll >> name >> faculty >> sec >> attendance;

            s.setRoll(roll);
            s.setName(name);
            s.setFaculty(faculty);
            s.setSection(sec);
            s.setAttendance(attendance); 

            cout << s.getRoll() << "\t\t" << s.getName() << "\t\t" << s.getFaculty() << "\t\t" << s.getSection() << "\t\t" << s.getAttendance() << endl;
        }
    }

    file.close();
    cout << "Press any key to return to the main menu...";
    getch(); // Wait for the user to press a key
}
 void search_attendance() {
    system("cls");
    
    int roll_no;
    cout << "Enter the Roll No to search for: ";
    cin >> roll_no;
    ifstream file("attendance.txt");
    if (!file) {
        cerr << "Error opening attendance file!" << endl;
        return;
    }

    Student s;
    string line;
    int total_days = 0;
    int present_days = 0;
    bool name_found = false;

    while (getline(file, line)) {
        if (line.find("Date:") != string::npos) {
            // Skip the date lines
            continue;
        } else {
            stringstream ss(line);
            int roll;
            string name, faculty, section;
            char attendance;
            ss >> roll >> name >> faculty >> section >> attendance;

           
            s.setRoll(roll);
            s.setName(name);
            s.setFaculty(faculty);
            s.setSection(section);
            s.setAttendance(attendance);

            if (s.getRoll() == roll_no) {
                name_found = true;
                total_days++;
                if (s.getAttendance() == 'P') {
                    present_days++;
                }
            }
        }
    }

    if (name_found) {
        double percentage = (total_days > 0) ? (static_cast<double>(present_days) / total_days) * 100 : 0;
        setColor(10);
        cout << "Name: " << s.getName() << endl;
        cout << "Total Days: " << total_days << endl;
        cout << "Present Days: " << present_days << endl;
        cout << "Attendance Percentage: " << percentage << "%" << endl;
        if(percentage > 70){
            cout<<"You are eligible for exam";
        }
        else{
            cout<<"You are not eligible for exam"<<endl;
        }
    } else {
        cout << "No attendance record found for Roll No: " << roll_no << endl;
    }
 resetColor();
    file.close();

     cout << "Press any key to return to the main menu...";
        getch(); // Wait for the user to press a key
}



};

int main() {
    int roleChoice;
    
    start: 
    system("cls");
    setColor(13); // Light Magenta
    cout << " Welcome to the Student Management System! " << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Manage student records efficiently with ease." << endl;
    cout << "------------------------------------------------" << endl;
    resetColor();
    cout << endl << endl;
    cout << " CHOOSE A MODE" << endl;
    setColor(13);
    cout << "------------------------------------------------" << endl;
    resetColor();
    setColor(10);
    cout << "------------------------------------------------" << endl;
    cout << "1. Admin\n2. Teacher\n3. Student\n ";
    cout << "------------------------------------------------" << endl;
    resetColor();
    cout << "Enter your choice: ";
    cin >> roleChoice;

    if (roleChoice == 1) {
        int choice;
        do {
            Student admin;
            system("cls");
            setColor(11);

            cout << "======================================================" << endl;
            cout << "W     W  EEEEE  L      CCCCC  OOOOO  M     M  EEEEE" << endl;
            cout << "W     W  E      L      C      O   O  MM   MM  E    " << endl;
            cout << "W  W  W  EEEEE  L      C      O   O  M M M M  EEEEE" << endl;
            cout << " W W W   E      L      C      O   O  M  M  M  E    " << endl;
            cout << "  W W    EEEEE  LLLLL  CCCCC  OOOOO  M     M  EEEEE" << endl;
            cout << "======================================================" << endl;

            resetColor();
            setColor(10);
            cout<<"================================";
            cout<<"Choose an option "<< endl;
            cout << " 1. Add Record" << endl;
            cout << " 2. Display Record" << endl;
            cout << " 3. Search Record" << endl;
            cout << " 4. Update Record" << endl;
            cout << " 5. Delete Record" << endl;
            cout << " 6. Go to main menu" << endl;
            cout << "====================================" << endl;
            resetColor();

            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: admin.add(); break;
                case 2: admin.display(); break;
                case 3: admin.search(); break;
                case 4: admin.update(); break;
                case 5: admin.deleteRecord(); break;
                case 6: goto start; break;
                default: cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    } else if (roleChoice == 2) {
        int choice;
        Student teach;
        do {
            system("cls");

            setColor(14);
            cout << "========================================================" << endl;
            cout << "W     W  EEEEE  L      CCCCC  OOOOO  M     M  EEEEE" << endl;
            cout << "W     W  E      L      C      O   O  MM   MM  E    " << endl;
            cout << "W  W  W  EEEEE  L      C      O   O  M M M M  EEEEE" << endl;
            cout << " W W W   E      L      C      O   O  M  M  M  E    " << endl;
            cout << "  W W    EEEEE  LLLLL  CCCCC  OOOOO  M     M  EEEEE" << endl;
            cout << "=======================================================" << endl;

            resetColor();
            setColor(10);
            cout << "1. Display Record\n2. Search Record\n3. Mark attendance\n4. Display attenance\n5. Search attenance\n6. Go to main menu"<<endl<<endl;
            resetColor();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: teach.display(); break;
                case 2: teach.search(); break;
                case 3: teach.mark_attendance(); break;
                case 4: teach.display_attendance(); break;
                case 5: teach.search_attendance(); break;
                case 6: goto start; break;
                default: cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    }
    else if(roleChoice==3){
        int choice;
        Student stu;
        do {
            system("cls");

            setColor(14);
            cout << "======================================================" << endl;
            cout << "W     W  EEEEE  L      CCCCC  OOOOO  M     M  EEEEE" << endl;
            cout << "W     W  E      L      C      O   O  MM   MM  E    " << endl;
            cout << "W  W  W  EEEEE  L      C      O   O  M M M M  EEEEE" << endl;
            cout << " W W W   E      L      C      O   O  M  M  M  E    " << endl;
            cout << "  W W    EEEEE  LLLLL  CCCCC  OOOOO  M     M  EEEEE" << endl;
            cout << "======================================================" << endl;

            resetColor();
            setColor(10);
            cout << "1. See your personal record\n2. See Your attendance Status\n3. Go to main menu"<<endl;
            resetColor();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
        
                case 1: stu.search(); break;
                case 2: stu.search_attendance(); break;
                case 3: goto start; break;
                default: cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    

    } else {
        cout << "Invalid mode selected. Exiting..." << endl;
    }

    return 0;
}