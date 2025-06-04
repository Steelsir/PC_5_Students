#include <iostream>
#include <limits> 
#include <windows.h>
#include <string>
#include <map>
#ifdef max, min
#undef max, min
#endif
using namespace std;

class Student {
private:
    static int nextId;
    int StId;
    string name;
    int age;
    double assessment;

public:
    Student(const string& name, int age, int assessment) :
        StId(nextId++),
        name(name),
        age(age),
        assessment(assessment) {}

    int getStId() const { return StId; }
    string getName() const { return name; }
    int getAge() const { return age; }
    int getAssessment() const { return assessment; }

    void setName(const string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setAssessment(int newAssessment) { assessment = newAssessment; }

    void assess() const {
        if (assessment > 100) {
            cout << " Ошибка введённых данных" << endl;
        }
        else if (assessment >= 90) {
            cout << " Оценка: Отлично!" << endl;
        }
        else if (assessment >= 70) {
            cout << " Оценка: Хорошо." << endl;
        }
        else if (assessment >= 50) {
            cout << " Оценка: Удовлетворительно" << endl;
        }
        else {
            cout << " Оценка: Неудовлетворительно" << endl;
        }
    }

    void show() const {
        cout << "№ учащегося: " << StId << " Имя: " << name
            << " Возраст: " << age << " Оценка: " << assessment;
        assess();
    }
};

int Student::nextId = 1;

void addStudent(map<int, Student*>& studentsMap,
    const string& name, int age, int assessment) {
    Student* newStudent = new Student(name, age, assessment);
    studentsMap[newStudent->getStId()] = newStudent;
}

void showAllStudents(const map<int, Student*>& studentsMap) {
    for (const auto& pair : studentsMap) {
        pair.second->show();
        cout << endl;
    }
}

void numCheck(int num, int min, int max){
    cin >> num;
    if (!(num <= max && num >= min)) {
        cin.clear(); // очистка потока ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n Ошибка! Требуется ввести число от " << min << " до " << max;
    }
}

// Функция для изменения данных студента
void changeStudent(map<int, Student*>& studentsMap) {
    string propertyToChange, newName;
    int studentId, currentId;

    cout << "\nВведите номер студента для изменения: ";
    cin >> currentId;

    // Поиск студента по id
    for (const auto& pair : studentsMap) {
        if (pair.second->getStId() == currentId) {
            studentId = pair.second->getStId();
            break;
        }
    }

    if (studentId == 0) {
        cout << "\nСтудент не найден" << endl;
        cin.get();
        return;
    }

    cout << "\nЧто хотите изменить? (Имя/Возраст/Оценка): ";
    cin >> propertyToChange;
    for (int i = 0; i < propertyToChange.length(); i++) {
        propertyToChange[i] = tolower(propertyToChange[i]);
    }

    if (propertyToChange == "имя") {
        cout << "\nВведите новое имя: ";
        cin >> newName;
        studentsMap[studentId]->setName(newName);
    }
    else if (propertyToChange == "возраст") {
        int newAge;
        cout << "\nВведите новый возраст: ";
        numCheck(newAge, 17, 200);
        studentsMap[studentId]->setAge(newAge);   
    }
    else if (propertyToChange == "оценка") {
        int newAssessment;
        cout << "\nВведите новую оценку: ";
        numCheck(newAssessment, 1, 100);
        studentsMap[studentId]->setAssessment(newAssessment);      
    }
}

// Функция для добавления нового студента.
void addNewStudent(map<int, Student*>& studentsMap) {
    string name;
    int age;
    int assessment;
    cout << "\nВведите имя нового студента: ";
    cin>>name;    
    cout << "\nВведите возраст: ";
    numCheck(age,17,200);
    cout << "\nВведите оценку: ";
    numCheck(assessment,1,100);
    addStudent(studentsMap, name, age, assessment);
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    map<int, Student*> studentsMap;

    addStudent(studentsMap, "Мария", 21, 79);
    addStudent(studentsMap, "Владислав", 22, 90);
    addStudent(studentsMap, "Руслан", 23, 100);
    addStudent(studentsMap, "Иван", 21, 65);
    addStudent(studentsMap, "Антон", 21, 49);

    // Пример изменения данных
    studentsMap[3]->setName("Роман");
    studentsMap[5]->setAssessment(65);
    studentsMap[4]->setAge(42);

    cout << "Нажмите enter, чтобы продолжить";
    
    string command;

    // Основной цикл программы
    cin.get(); 
    do {
        cin.clear();
        showAllStudents(studentsMap);
        cout << "Доступные команды: Добавить/Изменить/Выход\n";
        cout << "Введите команду: ";
        getline(cin, command);// помогло исправить непредвиденную ошибку

        // Приведение к нижнему регистру
        for (size_t i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        }

        if (command == "добавить") {
            addNewStudent(studentsMap);
            cin.get();
        }
        else if (command == "изменить") {
            changeStudent(studentsMap);
            cin.get();
        }
        else if (command == "выход") {
            break;
        }
        else {
            cout << "Ошибка ввода\n";
            cin.get();
        }        
    } while (command != "выход");

    // Освобождение памяти
    for (auto& pair : studentsMap) {
        delete pair.second;
    }

    return 0;
}
