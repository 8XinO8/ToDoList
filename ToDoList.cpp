#include <iostream>;
#include <fstream>;
#include <sstream>;
#include <vector>;
#include<windows.h>
using namespace std;

struct ToDoList
{
	int ID;
	string title;
	string description;
	bool completion_status;
	vector<ToDoList> queues;
};

void mainMenu(ToDoList);
void deleteRecent(ToDoList main_object);
void deleteAtPos(ToDoList main_object);
bool validateInput(string user_input);
void fullView(ToDoList main_object);
void quickView(ToDoList main_object);
void viewListMenu(ToDoList main_object);
void loadFile(ToDoList main_object) {
	main_object.queues.clear();
	ifstream file;
	string user_input;
	int line_counter = 0;
	int queue_counter = 0;
	cout << endl << "Какое имя файла?" << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;
	file.open(user_input);
	cin.clear();
	cin.ignore();
	if (file.is_open()) {
		string line;
		ToDoList tempObj = main_object;

		while (getline(file, line))
		{
			switch (line_counter)
			{
			case 0:
				tempObj.title = line;
				line_counter++;
				break;
			case 1:
				tempObj.description = line;
				line_counter++;
				break;
			case 2:
				main_object.queues.push_back(tempObj);
				line_counter = 0;
				queue_counter++;
				break;
			}
		}
	}
	else {
		cout << "Ошибка: Не удалось открыть файл" << user_input << endl;
		mainMenu(main_object);
	}

	cout << "Фаил загружен успешно" << endl << endl;
	mainMenu(main_object);
}
void saveToFile(ToDoList main_object) {
	string user_input;
	cout << endl << "Какое имя файла?" << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;

	while (true)
	{
		ofstream file(user_input);

		if (file) {

			for (int i = 0; i < main_object.queues.size(); i++)
			{
				file << main_object.queues[i].title << endl;
				file << main_object.queues[i].description << endl << endl;
			}
			file.close();

			cout << "Файл успешно сохранен." << endl << endl;
			mainMenu(main_object);
			break;
		}
		else
		{
			cout << "Файл не найден, повторите попытку " << endl << endl;
			mainMenu(main_object);
		}
	}
}


void newItemMenu(ToDoList main_object) {
	string user_input;
	string title = "";
	string description = "";
	ToDoList newList = main_object;

	cout << endl << "Чтобы добавить новый список, заполните название и описание (необязательно)." << endl << endl;
	while (true)
	{
		cout << "Пожалуйста, введите заголовок: " << endl;
		getline(cin >> ws, title);
		cout << endl;

		if (title != "") {
			cout << "Пожалуйста, введите описание: " << endl;
			getline(cin >> ws, description);
			cout << endl;
			break;
		}

		continue;
	}
	newList.title = title;
	newList.description = description;
	main_object.queues.push_back(newList);
	while (true) {
		string retry;
		cout << "Хотите добавить еще один? (Y или N)" << endl;
		cin >> retry;
		cout << endl;

		cin.clear();
		cin.ignore();

		if (retry == "Y" || retry == "N") {
			if (retry == "Y") {
				newItemMenu(main_object);
				return;
			}
			else {
				mainMenu(main_object);
				return;
			}
		}
		else {
			cout << "Ошибка: Неверный выбор." << endl << endl;
			continue;
		}
	}

}

void deleteItemMenu(ToDoList main_object) {
	string user_input;
	int int_user_input;
	cout << " Меню удаления: " << endl << endl;
	cout << " 1. Удалить новейшую задачу." << endl;
	cout << " 2. Удалить конкретную задачу" << endl;
	cout << " 3. Назад" << endl << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;
	cin.clear();
	cin.ignore();
	if (validateInput(user_input)) {
		stringstream ss(user_input);
		ss >> int_user_input;
	}
	else {
		cout << "Ошибка: Неверный выбор." << endl << endl;
		deleteItemMenu(main_object);
	}

	switch (int_user_input)
	{
	case 1:
		deleteRecent(main_object);
		break;
	case 2:
		deleteAtPos(main_object);
		break;
	case 3:
		mainMenu(main_object);
		break;
	default:
		cout << "Ошибка: Неверный выбор. " << endl << endl;
		deleteItemMenu(main_object);
		break;
	}

	return;
}
void deleteRecent(ToDoList main_object) {

	if (main_object.queues.size() > 0) {
		main_object.queues.pop_back();
		cout << "Задача удалена." << endl << endl;
	}
	else {
		cout << "Нет задачи для удаления." << endl << endl;
	}

	deleteItemMenu(main_object);
}
void deleteAtPos(ToDoList main_object) {
	string user_input;
	int int_user_input;
	cout << "Как называется задача?" << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;

	for (int i = 0; i < main_object.queues.size(); i++)
	{
		if (!(user_input == main_object.queues[i].title)) {
			continue;
		}
		else {
			main_object.queues.erase(main_object.queues.begin() + i);
			cout << "Задача с названием ( " << user_input << " ) был удален." << endl << endl;
			deleteItemMenu(main_object);
		}
	}

	cout << "Задача с названием( " << user_input << " ) не был найден." << endl << endl;
	deleteItemMenu(main_object);
}
void quickView(ToDoList main_object) {

	vector<ToDoList> temp = main_object.queues;

	cout << "Задачи по названию: " << endl;

	if (temp.size() == 0) {
		cout << "Ни одна задача не требует внимания!" << endl;
	}
	else {
		for (int i = 0; i < temp.size(); i++)
		{
			cout << " " << temp[i].title << endl;
		}
	}
	cout << endl;

	main_object.queues = temp;

	viewListMenu(main_object);
}
void fullView(ToDoList main_object) {
	string user_input;
	cout << "Как называется задача?" << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;
	for (int i = 0; i < main_object.queues.size(); i++)
	{
		if (!(user_input == main_object.queues[i].title)) {
			continue;
		}
		else {
			cout << "Заголовок: \n" << main_object.queues[i].title << endl << endl;
			cout << "Описание: \n" << main_object.queues[i].description << endl << endl;
			viewListMenu(main_object);
		}
	}

	cout << "Задача с названием( " << user_input << " ) не был найден." << endl << endl;

	cin.clear();
	cin.ignore();

	viewListMenu(main_object);
}

void viewListMenu(ToDoList main_object) {

	string user_input;
	int int_user_input;
	cout << " Меню просмотров: " << endl << endl;
	cout << " 1. Быстрый просмотр" << endl;
	cout << " 2. Полный просмотр" << endl;
	cout << " 3. Назад" << endl;

	cout << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;
	if (validateInput(user_input)) {
		stringstream ss(user_input);
		ss >> int_user_input;
	}
	else {
		deleteItemMenu(main_object);
	}

	switch (int_user_input)
	{
	case 1:
		quickView(main_object);
	case 2:
		fullView(main_object);
	case 3:
		mainMenu(main_object);
	default:
		cout << " Ошибка: Неверный выбор. ";
		viewListMenu(main_object);
	}
}

bool validateInput(string user_input) {
	bool inputValid = false;
	int int_user_input;
	stringstream ss(user_input);
	if (ss >> int_user_input) {
		return true;
	}
	else {
		ss.clear();
		return false;
	}
}
void mainMenu(ToDoList main_object) {
	int int_user_input;
	string user_input;
	cout << "Главное меню: " << endl << endl;
	cout << " 1. Добавьте новый элемент" << endl;
	cout << " 2. Удалить элемент" << endl;
	cout << " 3. Просмотр списков" << endl;
	cout << " 4. Сохранить в файл" << endl;
	cout << " 5. Загрузить из файла" << endl;
	cout << " 6. Выход" << endl << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;
	cin.clear();
	cin.ignore();
	if (validateInput(user_input)) {
		stringstream ss(user_input);
		ss >> int_user_input;
	}
	else {
		cout << "Ошибка: Неверный выбор." << endl << endl;
		mainMenu(main_object);
	}
	switch (int_user_input)
	{
	case 1:
		newItemMenu(main_object);
		break;
	case 2:
		deleteItemMenu(main_object);
		break;
	case 3:
		viewListMenu(main_object);
		break;
	case 4:
		saveToFile(main_object);
	case 5:
		loadFile(main_object);
		break;
	case 6:
		exit(99);
		break;
	default:
		cout << "Ошибка: Неверный выбор." << endl << endl;
		mainMenu(main_object);
	}
	return;
}
void driver() {
	ToDoList main_object;
	mainMenu(main_object);
};
int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
		driver();
}