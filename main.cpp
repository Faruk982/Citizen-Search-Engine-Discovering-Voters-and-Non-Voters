#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace
{
string toLowerCopy(string value)
{
    transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(tolower(ch));
    });
    return value;
}

string canonicalType(string value)
{
    value = toLowerCopy(value);
    value.erase(remove_if(value.begin(), value.end(), [](unsigned char ch) {
        return ch == ' ' || ch == '-';
    }), value.end());
    return value;
}

string promptLine(const string& message)
{
    cout << message;
    string input;
    getline(cin, input);
    while (input.empty() && cin)
    {
        getline(cin, input);
    }
    return input;
}

bool parseDate(const string& dateText, int& year, int& month, int& day)
{
    char firstDash = '\0';
    char secondDash = '\0';
    istringstream stream(dateText);
    if (!(stream >> year >> firstDash >> month >> secondDash >> day))
    {
        return false;
    }

    return firstDash == '-' && secondDash == '-' && !stream.fail();
}

string todayDate()
{
    const auto now = chrono::system_clock::now();
    const time_t nowTime = chrono::system_clock::to_time_t(now);
    tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &nowTime);
#else
    localtime_r(&nowTime, &localTime);
#endif

    ostringstream stream;
    stream << put_time(&localTime, "%Y-%m-%d");
    return stream.str();
}
} // namespace

class Person
{
private:
    string name;
    string dateOfBirth;
    string fatherName;
    string motherName;

protected:
    Person(const string& name, const string& dateOfBirth,
           const string& fatherName, const string& motherName)
        : name(name), dateOfBirth(dateOfBirth), fatherName(fatherName), motherName(motherName)
    {
    }

    void printCommonDetails(ostream& os) const
    {
        os << "Name: " << name << '\n';
        os << "Date of Birth: " << dateOfBirth << '\n';
        os << "Father's Name: " << fatherName << '\n';
        os << "Mother's Name: " << motherName << '\n';
    }

public:
    virtual ~Person() = default;

    const string& getName() const
    {
        return name;
    }

    const string& getDateOfBirth() const
    {
        return dateOfBirth;
    }

    const string& getFatherName() const
    {
        return fatherName;
    }

    const string& getMotherName() const
    {
        return motherName;
    }

    bool matches(const string& candidateName, const string& candidateDob) const
    {
        return name == candidateName && dateOfBirth == candidateDob;
    }

    virtual string typeLabel() const = 0;
    virtual void printDetails(ostream& os) const = 0;

    static bool isAdult(const string& dateText)
    {
        int birthYear = 0;
        int birthMonth = 0;
        int birthDay = 0;
        int currentYear = 0;
        int currentMonth = 0;
        int currentDay = 0;

        if (!parseDate(dateText, birthYear, birthMonth, birthDay))
        {
            return false;
        }

        const string currentDate = todayDate();
        if (!parseDate(currentDate, currentYear, currentMonth, currentDay))
        {
            return false;
        }

        const int yearDifference = currentYear - birthYear;
        if (yearDifference > 18)
        {
            return true;
        }

        if (yearDifference < 18)
        {
            return false;
        }

        if (currentMonth > birthMonth)
        {
            return true;
        }

        if (currentMonth < birthMonth)
        {
            return false;
        }

        return currentDay >= birthDay;
    }
};

class Voter : public Person
{
public:
    Voter(const string& name, const string& dateOfBirth,
          const string& fatherName, const string& motherName)
        : Person(name, dateOfBirth, fatherName, motherName)
    {
    }

    string typeLabel() const override
    {
        return "Voter";
    }

    void printDetails(ostream& os) const override
    {
        printCommonDetails(os);
    }
};

class NonVoter : public Person
{
public:
    NonVoter(const string& name, const string& dateOfBirth,
             const string& fatherName, const string& motherName)
        : Person(name, dateOfBirth, fatherName, motherName)
    {
    }

    string typeLabel() const override
    {
        return "Non-Voter";
    }

    void printDetails(ostream& os) const override
    {
        printCommonDetails(os);
    }
};

ostream& operator<<(ostream& os, const Person& person)
{
    os << person.typeLabel() << '\n';
    person.printDetails(os);
    return os;
}

class CitizenRegistry
{
private:
    vector<unique_ptr<Person>> citizens;

public:
    bool loadFromFile(const string& filePath)
    {
        ifstream inputFile(filePath);
        if (!inputFile)
        {
            return false;
        }

        string recordId;
        string name;
        string dateOfBirth;
        string fatherName;
        string motherName;

        while (getline(inputFile, recordId))
        {
            if (recordId.empty())
            {
                continue;
            }

            if (!getline(inputFile, name) || !getline(inputFile, dateOfBirth) ||
                !getline(inputFile, fatherName) || !getline(inputFile, motherName))
            {
                break;
            }

            if (Person::isAdult(dateOfBirth))
            {
                citizens.push_back(make_unique<Voter>(name, dateOfBirth, fatherName, motherName));
            }
            else
            {
                citizens.push_back(make_unique<NonVoter>(name, dateOfBirth, fatherName, motherName));
            }
        }

        return true;
    }

    size_t size() const
    {
        return citizens.size();
    }

    size_t countByType(const string& typeName) const
    {
        const string requestedType = canonicalType(typeName);
        size_t count = 0;
        for (const auto& citizen : citizens)
        {
            if (canonicalType(citizen->typeLabel()) == requestedType)
            {
                ++count;
            }
        }

        return count;
    }

    const Person* findByNameAndDob(const string& name, const string& dob) const
    {
        for (const auto& citizen : citizens)
        {
            if (citizen->matches(name, dob))
            {
                return citizen.get();
            }
        }

        return nullptr;
    }

    void printAll(ostream& os) const
    {
        for (const auto& citizen : citizens)
        {
            os << *citizen << '\n';
        }
    }

    void printByType(ostream& os, const string& typeName) const
    {
        const string requestedType = canonicalType(typeName);
        bool printedAny = false;

        for (const auto& citizen : citizens)
        {
            if (canonicalType(citizen->typeLabel()) == requestedType)
            {
                os << *citizen << '\n';
                printedAny = true;
            }
        }

        if (!printedAny)
        {
            os << "No records found for the selected type.\n";
        }
    }
};

int main()
{
    CitizenRegistry registry;
    if (!registry.loadFromFile("input.txt"))
    {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    while (true)
    {
        const string action = canonicalType(promptLine("What do you want to see? (list/profile): "));

        if (action == "list")
        {
            const string listChoice = canonicalType(promptLine("What kind of list? (all/voter/nonvoter): "));

            if (listChoice == "all")
            {
                cout << "\nTotal records: " << registry.size() << "\n\n";
                registry.printAll(cout);
            }
            else if (listChoice == "voter")
            {
                cout << "\nTotal voters: " << registry.countByType("voter") << "\n\n";
                registry.printByType(cout, "voter");
            }
            else if (listChoice == "nonvoter")
            {
                cout << "\nTotal non-voters: " << registry.countByType("nonvoter") << "\n\n";
                registry.printByType(cout, "nonvoter");
            }
            else
            {
                cout << "Invalid list type.\n";
            }
        }
        else if (action == "profile")
        {
            const string name = promptLine("Enter name: ");
            const string dob = promptLine("Enter date of birth (yyyy-mm-dd): ");

            const Person* citizen = registry.findByNameAndDob(name, dob);
            if (citizen == nullptr)
            {
                cout << "\nNot found.\n\n";
            }
            else
            {
                cout << "\n" << *citizen << '\n';
            }
        }
        else
        {
            cout << "Invalid choice.\n";
        }

        const string continueChoice = canonicalType(promptLine("Do you want to see more? (Yes/No): "));
        if (continueChoice != "yes")
        {
            break;
        }

        cout << '\n';
    }

    return 0;
}
