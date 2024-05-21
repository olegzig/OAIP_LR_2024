#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

struct Date {
    int day;
    int month;
    int year;
};

struct Project {
    std::string name;
    std::vector<std::string> developers;
    Date startDate;
    std::string status;
};

std::vector<Project> projects;

void addProject() {
    Project project;
    std::string developer;
    int numDevelopers;

    std::cout << "Введите название проекта: ";
    std::cin.ignore();
    std::getline(std::cin, project.name);

    std::cout << "Введите количество разработчиков: ";
    std::cin >> numDevelopers;
    std::cin.ignore();

    for (int i = 0; i < numDevelopers; ++i) {
        std::cout << "Введите имя разработчика " << i + 1 << ": ";
        std::getline(std::cin, developer);
        project.developers.push_back(developer);
    }

    std::cout << "Введите дату начала (день месяц год): ";
    std::cin >> project.startDate.day >> project.startDate.month >> project.startDate.year;

    std::cout << "Введите статус проекта (укажите \"completed\" для завершённого проекта!): ";
    std::cin.ignore();
    std::getline(std::cin, project.status);

    projects.push_back(project);
}

void clearProjects() {
    projects.clear();
    std::cout << "Массив проектов очищен.\n";
}

void saveProjectsToFile(const std::string& filename) {
    std::ofstream file(filename);

    for (const auto& project : projects) {
        file << project.name << '\n';
        file << project.developers.size() << '\n';
        for (const auto& developer : project.developers) {
            file << developer << '\n';
        }
        file << project.startDate.day << ' ' << project.startDate.month << ' ' << project.startDate.year << '\n';
        file << project.status << '\n';
    }

    file.close();
    std::cout << "Проекты сохранены в файл " << filename << ".\n";
}

void loadProjectsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << ".\n";
        return;
    }

    projects.clear();
    Project project;
    int numDevelopers;

    while (file >> project.name) {
        file >> numDevelopers;
        file.ignore();
        project.developers.clear();
        project.developers.reserve(numDevelopers);
        for (int i = 0; i < numDevelopers; ++i) {
            std::string developer;
            std::getline(file, developer);
            project.developers.push_back(developer);
        }
        file >> project.startDate.day >> project.startDate.month >> project.startDate.year;
        file.ignore();
        std::getline(file, project.status);
        projects.push_back(project);
    }

    file.close();
    std::cout << "Проекты загружены из файла " << filename << ".\n";
}

void displayProjects() {
    for (const auto& project : projects) {
        std::cout << "Название: " << project.name << '\n';
        std::cout << "Разработчики: ";
        for (const auto& developer : project.developers) {
            std::cout << developer << ' ';
        }
        std::cout << "\nДата начала: " << project.startDate.day << '.' << project.startDate.month << '.' << project.startDate.year << '\n';
        std::cout << "Статус: " << project.status << "\n\n";
    }
}

void displayProjectsByStatus(const std::string& status) {
    std::vector<Project> filteredProjects;

    for (const auto& project : projects) {
        if (project.status == status) {
            filteredProjects.push_back(project);
        }
    }

    std::sort(filteredProjects.begin(), filteredProjects.end(), [](const Project& a, const Project& b) {
        if (a.startDate.year != b.startDate.year)
            return a.startDate.year < b.startDate.year;
        if (a.startDate.month != b.startDate.month)
            return a.startDate.month < b.startDate.month;
        return a.startDate.day < b.startDate.day;
        });

    for (const auto& project : filteredProjects) {
        std::cout << "Название: " << project.name << '\n';
        std::cout << "Разработчики: ";
        for (const auto& developer : project.developers) {
            std::cout << developer << ' ';
        }
        std::cout << "\nДата начала: " << project.startDate.day << '.' << project.startDate.month << '.' << project.startDate.year << '\n';
        std::cout << "Статус: " << project.status << "\n";
    }
}

void displayTopDeveloper() {
    std::map<std::string, int> developerProjectCount;

    for (const auto& project : projects) {
        if (project.status == "completed") {
            for (const auto& developer : project.developers) {
                developerProjectCount[developer]++;
            }
        }
    }

    auto topDeveloper = std::max_element(developerProjectCount.begin(), developerProjectCount.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second;
        });

    if (topDeveloper != developerProjectCount.end()) {
        std::cout << "Разработчик с наибольшим количеством завершённых проектов: " << topDeveloper->first
            << " (" << topDeveloper->second << " проектов)\n";
    }
    else {
        std::cout << "\nНет завершённых проектов.\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    std::string filename = "projects.txt";

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить новый проект\n";
        std::cout << "2. Очистить массив проектов\n";
        std::cout << "3. Сохранить проекты в файл\n";
        std::cout << "4. Загрузить проекты из файла\n";
        std::cout << "5. Вывести все проекты\n";
        std::cout << "6. Вывести проекты по статусу\n";
        std::cout << "7. Вывести разработчика с наибольшим количеством завершённых проектов\n";
        std::cout << "8. Завершить работу\n";
        std::cout << "Выберите пункт меню: ";
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            addProject();
            break;
        case 2:
            clearProjects();
            break;
        case 3:
            saveProjectsToFile(filename);
            break;
        case 4:
            loadProjectsFromFile(filename);
            break;
        case 5:
            displayProjects();
            break;
        case 6: {
            std::string status;
            std::cout << "Введите статус: ";
            std::cin.ignore();
            std::getline(std::cin, status);
            displayProjectsByStatus(status);
            break;
        }
        case 7:
            displayTopDeveloper();
            break;
        case 8:
            std::cout << "Завершение работы программы.\n";
            break;
        default:
            std::cout << "\nНеверный пункт меню.\n\n";
            break;
        }
    } while (choice != 8);

    return 0;
}
