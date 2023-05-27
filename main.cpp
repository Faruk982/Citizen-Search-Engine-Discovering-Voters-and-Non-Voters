#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Person
{
private:
    string name;
    string dateOfBirth;
    string fatherName;
    string motherName;

public:
    // Constructor
    Person(const string& name, const string& dateOfBirth,
           const string& fatherName, const string& motherName)
    {
        this->name = name;
        this->dateOfBirth = dateOfBirth;
        this->fatherName = fatherName;
        this->motherName = motherName;
    }

    // Getter methods
    string getName() const
    {
        return name;
    }

    string getDateOfBirth() const
    {
        return dateOfBirth;
    }

    string getFatherName() const
    {
        return fatherName;
    }

    string getMotherName() const
    {
        return motherName;
    }
};

class Voter : public Person
{
public:
    // Constructor
    Voter(const string& name, const string& dateOfBirth,
          const string& fatherName, const string& motherName)
        : Person(name, dateOfBirth, fatherName, motherName) {}

    // Overloaded << operator for Voter class
    friend ostream& operator<<(ostream& os, const Voter& voter)
    {
        os << "Voter Name: " << voter.getName() << endl;
        os << "Date of Birth: " << voter.getDateOfBirth() << endl;
        os << "Father's Name: " << voter.getFatherName() << endl;
        os << "Mother's Name: " << voter.getMotherName() << endl;
        return os;
    }
};

class NonVoter : public Person
{
public:
    // Constructor
    NonVoter(const string& name, const string& dateOfBirth,
             const string& fatherName, const string& motherName)
        : Person(name, dateOfBirth, fatherName, motherName) {}

    // Overloaded << operator for NonVoter class
    friend ostream& operator<<(ostream& os, const NonVoter& nonVoter)
    {
        os << "NonVoter Name: " << nonVoter.getName() << endl;
        os << "Date of Birth: " << nonVoter.getDateOfBirth() << endl;
        os << "Father's Name: " << nonVoter.getFatherName() << endl;
        os << "Mother's Name: " << nonVoter.getMotherName() << endl;
        return os;
    }
};

bool isAbove18(const string& dateOfBirth)
{
    string currentDate = "2023-05-26";

    // Compare the birth date with the current date
    // Assuming the date format is "yyyy-mm-dd"
    string yearOfBirth = dateOfBirth.substr(0, 4);
    string yearOfCurrentDate = currentDate.substr(0, 4);

    int age = stoi(yearOfCurrentDate) - stoi(yearOfBirth);
    return age > 18;
}

int main()
{
    ifstream inputFile("input.txt"); // Open the input file
    string s, s1 = "voter", s2 = "Nonvoter";
    vector<Voter> vi;
    vector<NonVoter> nvi;
    if (!inputFile)
    {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string inputType, name, dateOfBirth, fatherName, motherName;

    // Read and process each set of data from the file
    while (inputFile >> inputType)
    {
        // Read the person's data
        inputFile.ignore(); // Ignore the newline character
        getline(inputFile, name);
        getline(inputFile, dateOfBirth);
        getline(inputFile, fatherName);
        getline(inputFile, motherName);

        if (isAbove18(dateOfBirth))
        {
            // Create an instance of Voter with the read data
            Voter voter(name, dateOfBirth, fatherName, motherName);

            // Access and display the information using overloaded operator
            vi.push_back(voter);
        }
        else
        {
            // Create an instance of NonVoter with the read data
            NonVoter nonVoter(name, dateOfBirth, fatherName, motherName);

            // Access and display the information using overloaded operator
            nvi.push_back(nonVoter);
        }
    }

    string j;
    j = "Yes";
    while (j == "Yes")
    {
        cout << "What do you want to see:(list/profile)"<<endl;
        cin>>s;
        if(s=="list")
        {
            cout<<"What kind of list:(all/voter/Nonvoter)"<<endl;
            cin>>s;
            int c=0;
            if(s=="all")
            {
                c=1;cout<<"\nTotal Number in the list"<<endl;
                cout<<vi.size()+nvi.size()<<endl;
            }
            if (s == s1||c)
            {
             if(!c)  {cout<<"\nTotal Number of voter in the list"<<endl;
                cout<<vi.size()<<endl;
             }
                for (auto x : vi)
                    cout << x << endl;
            }
            if (s == s2||c)
            {
               if(!c) {cout<<"\nTotal Number of nonvoter in the list"<<endl;
                cout<<nvi.size()<<endl;
               }
                for (auto x : nvi)
                    cout << x << endl;
            }
        }
        else
        {
            cin.ignore(); // Ignore the newline character
            string dob;
            string name;
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter date of birth (yyyy-mm-dd): ";
            getline(cin, dob);
            int i,k=0;
            if (isAbove18(dob))
            {

                for (i = 0; i < vi.size(); i++)
                {
                    if (vi[i].getDateOfBirth() == dob && vi[i].getName() == name)
                    {
                         cout << "\n\nType: Voter" << endl;
                        cout << vi[i] << endl;k=1;
                    }
                }

            }
            else
            {

                for (i = 0; i < nvi.size(); i++)
                {
                    if (nvi[i].getDateOfBirth() == dob && nvi[i].getName() == name)
                    {
                        cout << "\n\nType: Non Voter" << endl;
                        cout << nvi[i] << endl;k=1;
                    }
                }
                //if(k)
            }

            if(!k)cout<<"\nNot_Found\n"<<endl;
        }
        cout << "Do you want to see more (Yes/No): ";
        cin >> j;
        if (j != "Yes")
            break;
        cout<<endl;
    }
    inputFile.close(); // Close the input file

    return 0;
}
