# Citizen-Search-Engine-Discovering-Voters-and-Non-Voters

My code is a citizen search engine that allows users to discover information about voters and non-voters based on a provided input file. It incorporates several features:

1. File Input: The program reads data from an input file named "input.txt" that contains information about individuals, including their names, dates of birth, father's names, and mother's names.

2. Object-Oriented Design: The code follows an object-oriented approach by defining three classes: `Person`, `Voter`, and `NonVoter`. Each class encapsulates relevant data and functionality related to a person, with `Voter` and `NonVoter` inheriting from the `Person` class.

3. Inheritance: The `Voter` and `NonVoter` classes inherit properties and behaviors from the `Person` class. This allows for code reuse and supports the distinction between voters and non-voters.

4. Polymorphism: Polymorphism is achieved using virtual functions defined in the `Person` class. This enables the program to dynamically invoke appropriate functions based on the actual object type at runtime.

5. Operator Overloading: The code overloads the `<<` operator for both the `Voter` and `NonVoter` classes, facilitating the display of voter and non-voter information using the standard output stream in a user-friendly format.

6. Data Processing: The program processes the data from the input file, creating instances of `Voter` and `NonVoter` objects based on the provided information. It determines whether an individual is a voter or non-voter based on their date of birth and age calculation.

7. User Query: The program prompts the user to enter a query to retrieve specific information. Users can request the list of voters, the list of non-voters, or search for a specific person by name and date of birth.

8. Search Functionality: The code includes a search feature that allows users to find a specific person by providing their name and date of birth. It searches the `vi` and `nvi` vectors to find a match and displays the person's information if found.

9. User Interaction: The program interacts with the user through a command-line interface. It repeatedly prompts the user for queries and displays the results in an organized and readable manner. The user can choose to continue searching or exit the program.

In summary, my code serves as a citizen search engine, empowering users to explore information about voters and non-voters. It provides an intuitive interface for managing and retrieving data related to individuals' voting status.
