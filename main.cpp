#include <iostream>
#include <conio.h>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct User {
    int id = 0;
    string login, password;
};

struct Person {
    int id = 0, userId;
    string name, lastName, phoneNumber, email, address;
    bool operator == (const Person &p) const {return id == p.id;}
};

bool saveToFile(const string, const Person &);

void pressAnyKey() {
    cout << "Nacisnij dowolny klawisz...";
    getch();
}

string inputName() {
    string name;

    cout << "Podaj imie: ";
    getline(cin, name);

    return name;
}

string inputLastName() {
    string lastName;

    cout << "Podaj nawzisko: ";
    getline(cin, lastName);

    return lastName;
}

string inputPhoneNumber() {
    string phoneNumber;

    cout << "Podaj numer telefonu: ";
    getline(cin, phoneNumber);

    return phoneNumber;
}

string inputEmail() {
    string email;

    cout << "Podaj e-mail: ";
    getline(cin, email);

    return email;
}

string inputAddress() {
    string address;

    cout << "Podaj adres: ";
    getline(cin, address);

    return address;
}

void addPerson(const string filename, list<Person> &persons, int userId) {
    Person person;

    system("cls");
    cout << ">>> DODAJ OSOBE <<<" << endl << endl;
    if (!persons.size()) {
        person.id = 1;
    } else {
        person.id = persons.back().id + 1;
    }
    person.userId = userId;
    person.name = inputName();
    person.lastName = inputLastName();
    person.phoneNumber = inputPhoneNumber();
    person.email = inputEmail();
    person.address = inputAddress();

    persons.push_back(person);
    if (saveToFile(filename, person)) {
        cout << "Dodano nowa osobe!" << endl;
    } else {
        cout << "Ups, cos poszlo nie tak. Blad zapisu do pliku!" << endl;
    }
    pressAnyKey();
}

void saveAllToFile(const string filename, const list<Person> &persons) {
    /*ofstream file;
    file.open(filename);

    for (Person person : persons) {
        if (!saveToFile(filename, person)) {
            cout << "Ups, cos poszlo nie tak. Blad zapisu do pliku!" << endl;
        }
    }
    file.close();*/
}

int inputNumber() {
    int number;

    while (!(cin >> number)) {
        cout << "Niepoprawne dane. Sprobuj jeszcze raz: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.get();
    return number;
}

Person findPersonById(int id, const list<Person> &persons) {
    Person person;

    for (Person p : persons) {
        if (p.id == id) {
            person = p;
            break;
        }
    }
    return person;
}

void removePerson(const string filename, list<Person> &persons) {
    system("cls");
    cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
    cout << "Podaj numer ID osoby, ktora chcesz usunac: ";
    int id = inputNumber();

    Person person = findPersonById(id, persons);
    if (person.id != 0) {
        cout << "Potwierdz naciskajac klawisz 't': ";
        char ch;
        ch = getch();
        if (ch == 't') {
            persons.remove(person);
            cout << "Szukana osoba zostala usunieta" << endl;
            saveAllToFile(filename, persons);
        } else {
            cout << "Anulowano usuwanie!" << endl;
        }
    } else {
        cout << "Nie znaleziono osoby o takim ID!" << endl;
    }
    pressAnyKey();
}

void displayPerson(const Person &person) {
    cout << "ID: " << person.id << endl;
    cout << person.name + " " + person.lastName << endl;
    cout << "Telefon: " + person.phoneNumber << endl;
    cout << "Email: " + person.email << endl;
    cout << "Adres: " + person.address << endl << endl;
}

void findPersonByName(const list<Person> &persons, int userId) {
    string name;
    bool found = false;

    system("cls");
    cout << ">>> WYSZUKIWANIE OSOBY PO IMIENIU <<<" << endl << endl;
    cout << "Podaj imie osoby jaka mamy wyszukac: ";
    getline(cin, name);

    for (Person person : persons) {
        if (person.userId == userId && person.name == name) {
            displayPerson(person);
            found = true;
        }
    }
    if (!found) {
        cout << "Nie znaleziono osob o takim imieniu!" << endl;
    }
    pressAnyKey();
}

void findPersonByLastName(const list<Person> &persons, int userId) {
    string lastName;
    bool found = false;

    system("cls");
    cout << ">>> WYSZUKIWANIE OSOBY PO NAZWISKU <<<" << endl << endl;
    cout << "Podaj nazwisko osoby jaka mamy wyszukac: ";
    getline(cin, lastName);

    for (Person person : persons) {
        if (person.userId == userId && person.lastName == lastName) {
            displayPerson(person);
            found = true;
        }
    }
    if (!found) {
        cout << "Nie znaleziono osob o takim nazwisku!" << endl;
    }
    pressAnyKey();
}

void displayAllPersons(const list<Person> &persons, int userId) {
    system("cls");
    cout << ">>> LISTA OSOB W KSIAZCE ADRESOWEJ <<<" << endl << endl;

    if (!persons.size()) {
        cout << "Baza danych jest pusta!" << endl;
    } else {
        for (Person person : persons) {
            if (person.userId == userId) {
                displayPerson(person);
            }
        }
    }
    pressAnyKey();
}

void displayMenu(const User &loggedUser) {
    system("cls");
    cout << ">>> KSIAZKA ADRESOWA V.0.2 <<<" << endl;
    cout << endl << "Zalogowany jako: " << loggedUser.login << endl << endl;
    cout << "1. Dodaj osobe" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkie osoby" << endl;
    cout << "5. Usun osobe" << endl;
    cout << "6. Edytuj osobe" << endl;
    cout << "7. Zakoncz program" << endl << endl;
    cout << "Podaj numer opcji: " << endl;
}

char selectOption() {
    char ch;

    do {
        ch = getch();
    } while (ch < '1' || ch > '7');

    return ch;
}

bool saveToFile(const string filename, const Person &person) {
    ofstream file;
    file.open(filename, ios_base::app);

    if (file.is_open()) {
        file << person.id << '|';
        file << person.userId << '|';
        file << person.name << '|';
        file << person.lastName << '|';
        file << person.phoneNumber << '|';
        file << person.email << '|';
        file << person.address << '|' << endl;

        file.close();
        return true;
    }
    return false;
}

bool saveToFile(const string filename, const User &user) {
    ofstream file;
    file.open(filename, ios_base::app);

    if (file.is_open()) {
        file << user.id << '|';
        file << user.login << '|';
        file << user.password << '|' << endl;

        file.close();
        return true;
    }
    return false;
}

vector<string> split(string str, char delimiter) {
    stringstream stream(str);
    string segment;
    vector<string> splittedString;

    while (getline(stream, segment, delimiter)) {
       splittedString.push_back(segment);
    }
    return splittedString;
}

void loadFromFile(const string filename, list<Person> &persons) {

    ifstream file;
    file.open(filename);
    string line;
    Person person;
    vector<string> splittedLine;

    if (file.is_open()) {
        while (getline(file, line)) {
            splittedLine = split(line, '|');

            person.id = stoi(splittedLine[0]);
            person.userId = stoi(splittedLine[1]);
            person.name = splittedLine[2];
            person.lastName = splittedLine[3];
            person.phoneNumber = splittedLine[4];
            person.email = splittedLine[5];
            person.address = splittedLine[6];

            persons.push_back(person);
        }
    }
    file.close();
}

void loadFromFile(const string filename, list<User> &users) {
    ifstream file;
    file.open(filename);
    string line;
    User user;
    vector<string> splittedLine;

    if (file.is_open()) {
        while (getline(file, line)) {
            splittedLine = split(line, '|');

            user.id = stoi(splittedLine[0]);
            user.login = splittedLine[1];
            user.password = splittedLine[2];

            users.push_back(user);
        }
    }
    file.close();
}

void displayEditMenu() {
    cout << endl;
    cout << "Wybierz dane do edycji:" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu glownego" << endl << endl;

    cout << "Podaj numer opcji: " << endl;
}

char selectEditOption() {
    char ch;

    do {
        ch = getch();
    } while (ch < '1' || ch > '6');

    return ch;
}

void editPersonData(const string filename, list<Person> &persons) {
    Person person, updatedPerson;

    system("cls");
    cout << ">>> EDYTUJ DANE WYBRANEJ OSOBY <<<" << endl << endl;
    cout << "Podaj numer ID osoby, ktorej dane chcesz edytowac: ";
    int id = inputNumber();

    person = findPersonById(id, persons);
    if (person.id != 0) {
        updatedPerson = person;
        displayEditMenu();
        char option = selectEditOption();

        switch (option) {
        case '1':
            updatedPerson.name = inputName();
            break;
        case '2':
            updatedPerson.lastName = inputLastName();
            break;
        case '3':
            updatedPerson.phoneNumber = inputPhoneNumber();
            break;
        case '4':
            updatedPerson.email = inputEmail();
            break;
        case '5':
            updatedPerson.address = inputAddress();
            break;
        case '6':
            return;
        }
        replace(persons.begin(), persons.end(), person, updatedPerson);
        saveAllToFile(filename, persons);
        cout << "Dane zostaly zmienione!" << endl;
    } else {
        cout << "Nie znaleziono osoby o takim ID!" << endl;
    }
    pressAnyKey();
}

void mainLoop(User &loggedUser) {
    const string FILENAME = "Adresaci.txt";
    list<Person> persons;
    loadFromFile(FILENAME, persons);

    while (1) {
        displayMenu(loggedUser);
        char option = selectOption();

        switch (option) {
        case '1':
            addPerson(FILENAME, persons, loggedUser.id);
            break;
        case '2':
            findPersonByName(persons, loggedUser.id);
            break;
        case '3':
            findPersonByLastName(persons, loggedUser.id);
            break;
        case '4':
            displayAllPersons(persons, loggedUser.id);
            break;
        case '5':
            removePerson(FILENAME, persons);
            break;
        case '6':
            editPersonData(FILENAME, persons);
            break;
        case '7':
            exit(0);
        }
    }
}

//==============================================================================
//=                             MAIN MENU                                      =
//==============================================================================

void displayMainMenu() {
    system("cls");
    cout << ">>> MENU GLOWNE <<<" << endl << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "3. Zakoncz program" << endl << endl;
    cout << "Podaj numer opcji: " << endl;
}

char selectMainMenuOption() {
    char ch;

    do {
        ch = getch();
    } while (ch < '1' || ch > '3');

    return ch;
}
//==============================================================================
//=                     REJESTRACJA UZYTKOWNIKA                                =
//==============================================================================
string inputLogin() {
    string login;

    cout << "Podaj login: ";
    getline(cin, login);

    return login;
}

string inputPassword() {
    string password;

    cout << "Podaj haslo: ";
    getline(cin, password);

    return password;
}

bool isLoginExists(string login, const list<User> &users) {
    for (User user : users) {
        if (login == user.login) {
            return true;
        }
    }
    return false;
}

void addUser(string filename, list<User> &users) {
    User user;

    system("cls");
    cout << ">>> REJESTRACJA NOWEGO UZYTKOWNIKA <<<" << endl << endl;
    if (!users.size()) {
        user.id = 1;
    } else {
        user.id = users.back().id + 1;
    }
    if (isLoginExists(user.login = inputLogin(), users)) {
        cout << "Podany login jest juz zajety" << endl;
        pressAnyKey();
        return;
    }
    user.password = inputPassword();

    users.push_back(user);
    if (saveToFile(filename, user)) {
        cout << "Konto zalozono pomyslnie!" << endl;
    } else {
        cout << "Ups, cos poszlo nie tak. Blad zapisu do pliku!" << endl;
    }
    pressAnyKey();
}

//==============================================================================
//=                     LOGOWANIE UZYTKOWNIKA                                =
//==============================================================================

User getUserByLogin(string login, const list<User> &users) {
    User user;

    for (User u : users) {
        if (login == u.login) {
            user = u;
            break;
        }
    }
    return user;
}

bool validatePassword(string password, const User &user) {
    if (password == user.password) {
        return true;
    }
    return false;
}

void userLogging(const list<User> &users) {
    User user;
    string login;
    const int TRIALS_QUANTITY = 3;

    system("cls");
    cout << ">>> LOGOWANIE UZYTKOWNIKA <<<" << endl << endl;
    if (!isLoginExists(login = inputLogin(), users)) {
        cout << "Podany login nie istnieje!" << endl;
        pressAnyKey();
        return;
    }
    user = getUserByLogin(login, users);
    for (int i = TRIALS_QUANTITY; i >= 1; i--) {
        cout << "Wpisywanie hasla. Pozostalo prob: " << i << endl;
        if (validatePassword(inputPassword(), user)) {
            cout << endl << "Zalogowano pomyslnie!" << endl;
            pressAnyKey();
            mainLoop(user);
        } else {
            cout << "Haslo niepoprawne!" << endl;
            continue;
        }
    }
    pressAnyKey();
    return;
}

int main() {
    const string FILENAME = "Uzytkownicy.txt";
    list<User> users;
    loadFromFile(FILENAME, users);

    while (1) {
        displayMainMenu();
        char mainMenuOption = selectMainMenuOption();

        switch (mainMenuOption) {
        case '1':
            addUser(FILENAME, users);
            break;
        case '2':
            userLogging(users);
            break;
        case '3':
            exit(0);
        }
    }
    return 0;
}
