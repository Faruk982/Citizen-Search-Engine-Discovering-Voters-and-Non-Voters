# Citizen Search Engine: Voters and Non-Voters

This project is a small C++ citizen search engine that reads records from `input.txt`, classifies each person as a voter or non-voter based on date of birth, and lets the user list records or search for a specific profile from the command line.

## What Changed

The project is now structured around real OOP responsibilities instead of keeping all logic inside `main()`.

- `Person` is an abstract base class that encapsulates the common citizen data.
- `Voter` and `NonVoter` inherit from `Person` and override the polymorphic display behavior.
- `CitizenRegistry` owns the collection of records, file loading, filtering, counting, and search.
- The `<<` operator works through the `Person` interface, so output is handled polymorphically.

## OOP Principles Used

Encapsulation: citizen fields stay private inside `Person`, and access happens through controlled methods.

Inheritance: `Voter` and `NonVoter` reuse the shared state and behavior from `Person`.

Polymorphism: the program stores records through `unique_ptr<Person>` and prints them through virtual functions.

Abstraction: the registry hides the storage and lookup details behind a small interface.

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
