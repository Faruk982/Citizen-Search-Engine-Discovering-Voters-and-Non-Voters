# Citizen Search Engine: Voters and Non-Voters

This project is a small C++ citizen search engine that reads records from `input.txt`, classifies each person as a voter or non-voter based on date of birth, and lets the user list records or search for a specific profile from the command line.

## Project Overview

This project is a C++ citizen search engine that reads records from `input.txt`, classifies each person as a voter or non-voter based on age, and lets the user list records or search for a specific profile from the command line.

The program stores all citizens in one collection, then uses runtime type behavior to print and filter them as needed. It supports three list modes: all citizens, only voters, and only non-voters.

## OOP Concepts Used

Encapsulation: the common citizen details are kept inside the `Person` base class and accessed through member functions.

Inheritance: `Voter` and `NonVoter` both derive from `Person` and reuse the shared data and behavior.

Polymorphism: the program stores citizens as `unique_ptr<Person>` and uses virtual functions so each derived type can provide its own label and display behavior.

Abstraction: `CitizenRegistry` hides file loading, searching, counting, and filtering behind a simple interface.

## Features

- Reads records from `input.txt`.
- Classifies each citizen by age using the current system date.
- Lists all citizens, only voters, or only non-voters.
- Searches by exact name and date of birth.
- Uses a single unified collection instead of separate voter and non-voter vectors.

## Input Format

Each record in `input.txt` uses five lines:

1. Record id
2. Name
3. Date of birth in `yyyy-mm-dd`
4. Father's name
5. Mother's name

## Build and Run

Use any C++17 compiler. Example:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o citizen-search
./citizen-search
```

On Windows with MinGW, the executable name will usually be `citizen-search.exe`.

## Notes

- The adult check uses the current system date at runtime.
- The search is exact on name and date of birth.
- The console prompts accept `list` or `profile`, and `all`, `voter`, or `nonvoter` for list filtering.
