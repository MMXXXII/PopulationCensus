//1. программа должна иметь модульную структуру, т.е.должна состоять  +
//из отдельных функций
//2. формирование файла(запись введенных данных в файл); + 
//3. редактирование данных(добавление, удаление, изменение сведений); +
//4. использование отдельного диалога для ввода и проверка корректности всех входных данных;  +
//5. вывод исходных данных(просмотр всех сведений) и реализация всех указанных в задании действий по сортировке и выборке данных; +-
//6. использование главного и контекстного меню; (главное есть, контекстное делаем при среднем возрасте мужчин и женщин)
//7. результаты расчетов и поиска должны быть оформлены в соответствующем виде(с использованием форматированного вывода); +
//8. наличие в главном меню раздела «О программе», в котором указать версию программного продукта, дату внесения последних изменений в программе и координаты автора; + 
//9. наличие в главном меню раздела «Руководство пользователя(Справка)», содержание которого загружается из текстового файла; + 
//10. наличие в главном меню раздела «Задание», содержащего постановку задачи. + 
//_____________________________________________
//11. корректная обработка диалога работы с файлами(например, запрет открытия несуществующего файла, либо запрос на перезапись уже существующего файла, настройка фильтров и др.);+
//12. проверка сохранения сведений в файле при выходе из программы; + 
//13. сортировка выводимой информации по любому из полей записи(критерий сортировки указывается в меню), используя одну процедуру сортировки для всех пунктов меню; + 
//14. по запросу пользователя сохранить результаты поиска и расчетов в новом файле + 
// _______________________________________________
//15.формирование списка ранее открывавшихся файлов;
//16.поиск по любому из полей записи, используя одну функцию для поиска;
//17.предусмотреть возможность поиска по сочетанию первых символов(фамилии на одинаковое сочетание первых букв и т.д. (символы вводятся пользователем));
//18.корректно обрабатывать доступность / недоступность пунктов меню и кнопок
//в зависимости от действий пользователя.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <locale.h>
#include <windows.h>
#include <codecvt>
#include <locale>
#include <map>
#include <regex>


using namespace std;


struct Person
{
	string name_person;
	int years_old;
	string gender;
	string place_life;
	string education_level;
	int count_kids;
	string job;
};

vector<Person> people;
Person person;

bool containsDigit(const string& str) {
	for (char c : str) {
		if (isdigit(c)) {
			return true;
		}
	}
	return false;
}

int countWords(const string& str) {
	stringstream ss(str);
	string word;
	int count = 0;
	while (ss >> word) {
		count++;
	}
	return count;
}

bool containsSpecialCharacters(const std::string& str) {
	for (char c : str) {
		if (!isalnum(c)) { // Проверяем, является ли символ буквой или цифрой
			return true; // Если хотя бы один символ не является буквой или цифрой, возвращаем true
		}
	}
	return false; // Если все символы буквы или цифры, возвращаем false
}

bool fileExists(const string& filename) {
	ifstream file(filename);
	return file.good();
}

void saveToFile(const string& filename, const vector<Person>& people) {
	if (fileExists(filename)) {
		string choice;
		while (true) {
			cout << "Файл с именем " << filename << " уже существует. Желаете перезаписать его (1) или добавить данные (2)? ";
			getline(cin, choice);

			if (choice == "1" || choice == "2") {
				break;
			}
			else {
				cout << "Пожалуйста, введите '1' или '2'." << endl;
			}
		}

		if (choice == "2") {
			ofstream fout(filename, ios::app);
			if (!fout.is_open()) {
				cout << "Ошибка открытия файла!" << endl;
				return;
			}

			for (const Person& person : people) {
				fout << person.name_person << ';';
				fout << person.years_old << ';';
				fout << person.gender << ';';
				fout << person.place_life << ';';
				fout << person.education_level << ';';
				fout << person.count_kids << ';';
				fout << person.job << '\n'; // Добавляем символ новой строки
			}

			fout.close();
			cout << "Данные успешно добавлены в файл." << endl;
			return;
		}
	}

	ofstream fout(filename, ios::trunc);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}

	for (const Person& person : people) {
		fout << person.name_person << ';';
		fout << person.years_old << ';';
		fout << person.gender << ';';
		fout << person.place_life << ';';
		fout << person.education_level << ';';
		fout << person.count_kids << ';';
		fout << person.job << '\n'; // Добавляем символ новой строки
	}

	fout.close();
	cout << "Данные успешно записаны в файл." << endl;
}

string personToString(const Person& person) {
	stringstream ss;
	ss << "ФИО: " << person.name_person << endl;
	ss << "Год рождения: " << person.years_old << endl;
	ss << "Пол: " << person.gender << endl;
	ss << "Место жительства: " << person.place_life << endl;
	ss << "Уровень образования: " << person.education_level << endl;
	ss << "Количество детей: " << person.count_kids << endl;
	ss << "Место работы: " << person.job << endl;
	return ss.str();
}

void capitalizeFirstLetter(string& str) {
	bool makeUpper = true;
	for (char& ch : str) {
		if (makeUpper && islower(ch)) {
			ch = toupper(ch);
			makeUpper = false;
		}
		else if (isspace(ch)) {
			makeUpper = true;
		}
	}
}


void addPerson() {
	Person person;




	cout << "Введите ФИО: ";

	// Считываем ФИО, пропуская последний пробел
	getline(cin >> ws, person.name_person);

	capitalizeFirstLetter(person.name_person);

	// Удаляем пробел в конце, если он есть
	if (!person.name_person.empty() && person.name_person.back() == ' ') {
		person.name_person.pop_back();
	}

	while (true) {
		regex reg("[А-ЯЁ][а-яё]+ +[А-ЯЁ][а-яё]+ +[А-ЯЁ][а-яё]+");
		if (regex_match(person.name_person, reg)) {
			break;
		}
		else {
			cout << "ФИО должно состоять из трех слов, начинаться с заглавных букв и не иметь цифр и специальных символов. Пожалуйста, введите ФИО заново: ";
			getline(cin >> ws, person.name_person);
			capitalizeFirstLetter(person.name_person);
		}
	}




	cout << "Введите год рождения: ";
	string input;
	bool validInput = false;

	while (!validInput) {
		getline(cin, input);

		// Проверяем, содержит ли ввод только цифры
		bool onlyDigits = true;
		for (char c : input) {
			if (!isdigit(c)) {
				onlyDigits = false;
				break;
			}
		}

		// Если ввод содержит только цифры, преобразуем его в int
		if (onlyDigits) {
			person.years_old = stoi(input);
			// Проверяем, чтобы год был в допустимом диапазоне
			if (person.years_old >= 1900 && person.years_old <= 2024) {
				validInput = true;
			}
		}

		if (!validInput) {
			cout << "Год рождения должен быть не ранее 1900 и не позже 2024, а так же иметь цифры или специальные символы. Пожалуйста, введите снова: ";
		}
	}




	cout << "Введите пол (мужской/женский): ";
	do {
		getline(cin, person.gender);
		if (person.gender != "мужской" && person.gender != "женский") {
			cout << "Некорректное значение пола. Пожалуйста, введите снова: ";
		}
	} while (person.gender != "мужской" && person.gender != "женский");



	while (true) {
		regex reg("[А-ЯЁ][-а-яё]*(-[А-ЯЁ][-а-яё]*)?"); // Паттерн для проверки, что первая буква заглавная, а остальные строчные
		cout << "Введите место жительства (город): ";
		getline(cin >> ws, person.place_life);

		if (regex_match(person.place_life, reg)) {
			break; // Введено корректное название города
		}
		else {
			cout << "Город должен начинаться с заглавной буквы. Введите место жительства (город) заново: ";
		}
	}




	// Запрашиваем уровень образования
	cout << "Введите уровень образования (среднее/среднее специальное/высшее): ";
	do {
		getline(cin, person.education_level);
		if (person.education_level != "среднее" && person.education_level != "среднее специальное" && person.education_level != "высшее") {
			cout << "Некорректное значение уровня образования. Пожалуйста, введите снова (среднее/среднее специальное/высшее): ";
		}
	} while (person.education_level != "среднее" && person.education_level != "среднее специальное" && person.education_level != "высшее");



	cout << "Введите количество детей: ";
	string inputStr;
	bool validInputMean = false;

	while (!validInputMean) {
		cin >> inputStr;

		if (!containsSpecialCharacters(inputStr)) {
			person.count_kids = stoi(inputStr);
			if (person.count_kids >= 0 && person.count_kids <= 200) {
				validInputMean = true;
			}
			else {
				cout << "Количество детей должно быть неотрицательным числом и не превышать 200. Пожалуйста, введите снова: ";
			}
		}
		else {
			cout << "Количество детей должно быть целым числом. Пожалуйста, введите снова: ";
		}

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}

	cin.ignore(1000, '\n');



	// Запрашиваем место работы
	cout << "Введите место работы: ";
	getline(cin, person.job);






	cout << " " << endl;
	// Проверяем данные
	string confirmation;
	cout << " " << endl;
	cout << "Проверьте введенные данные:\n" << personToString(person) << "\nДанные введены верно? (да/нет): ";
	getline(cin, confirmation);

	// Повторяем запрос на корректировку, если данные введены неверно
	while (confirmation != "да" && confirmation != "Да") {
		cout << "Что нужно изменить?" << endl;
		cout << "1. ФИО" << endl;
		cout << "2. Год рождения" << endl;
		cout << "3. Пол" << endl;
		cout << "4. Место жительства" << endl;
		cout << "5. Уровень образования" << endl;
		cout << "6. Количество детей" << endl;
		cout << "7. Место работы" << endl;
		cout << "Выберите номер поля для редактирования: ";

		int choice;
		cin >> choice;
		cin.ignore(); // Очищаем буфер ввода после чтения числа

		switch (choice) {
		case 1: {
			cout << "Введите ФИО заново: ";
			getline(cin, person.name_person);
			capitalizeFirstLetter(person.name_person);
			// Удаляем пробел в конце, если он есть
			if (!person.name_person.empty() && person.name_person.back() == ' ') {
				person.name_person.pop_back();
			}
			// Проверяем ввод на соответствие шаблону
			while (true) {
				regex reg("[А-ЯЁ][а-яё]+ +[А-ЯЁ][а-яё]+ +[А-ЯЁ][а-яё]+");
				if (regex_match(person.name_person, reg)) {
					break;
				}
				else {
					cout << "ФИО должно состоять из трех слов, начинаться с заглавных букв и не иметь цифр и специальных символов. Пожалуйста, введите ФИО заново: ";
					getline(cin, person.name_person);
					capitalizeFirstLetter(person.name_person);
				}
			}
			break;
		}
		case 2: {
			cout << "Введите год рождения заново: ";
			string input;
			bool validInput = false;

			while (!validInput) {
				getline(cin, input);

				// Проверяем, содержит ли ввод только цифры
				bool onlyDigits = true;
				for (char c : input) {
					if (!isdigit(c)) {
						onlyDigits = false;
						break;
					}
				}

				// Если ввод содержит только цифры, преобразуем его в int и присваиваем переменной years_old
				if (onlyDigits) {
					person.years_old = stoi(input); // Присваиваем значение года переменной years_old
					// Проверяем, чтобы год был в допустимом диапазоне
					if (person.years_old >= 1900 && person.years_old <= 2024) {
						validInput = true;
					}
				}

				if (!validInput) {
					cout << "Год рождения должен быть не ранее 1900 и не позже 2024, а так же иметь цифры или специальные символы. Пожалуйста, введите снова: ";
				}
			}
			break;
		}

		case 3: {
			cout << "Введите пол (мужской/женский): ";
			do {
				getline(cin, person.gender);
			} while (person.gender != "мужской" && person.gender != "женский");
			break;
		}
		case 4: {
			cout << "Введите место жительства (город): ";
			while (true) {
				regex reg("[А-ЯЁ][-а-яё]*"); // Паттерн для проверки, что первая буква заглавная, а остальные строчные
				getline(cin, person.place_life);

				if (regex_match(person.place_life, reg)) {
					break; // Введено корректное название города
				}
				else {
					cout << "Город должен начинаться с заглавной буквы. Введите место жительства (город) заново: ";
				}
			}
			break;
		}
		case 5: {
			cout << "Введите уровень образования (среднее/среднее специальное/высшее): ";
			do {
				getline(cin, person.education_level);
			} while (person.education_level != "среднее" && person.education_level != "среднее специальное" && person.education_level != "высшее");
			break;
		}
		case 6: {
			cout << "Введите количество детей: ";
			string inputStr;
			bool validInputMean = false;

			while (!validInputMean) {
				cin >> inputStr;

				if (!containsSpecialCharacters(inputStr)) {
					person.count_kids = stoi(inputStr);
					if (person.count_kids >= 0 && person.count_kids <= 200) {
						validInputMean = true;
					}
					else {
						cout << "Количество детей должно быть неотрицательным числом и не превышать 200. Пожалуйста, введите снова: ";
					}
				}
				else {
					cout << "Количество детей должно быть целым числом. Пожалуйста, введите снова: ";
				}

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
				}
			}

			cin.ignore(1000, '\n');
			break;
		}
		case 7: {
			cout << "Введите место работы: ";
			getline(cin, person.job);
			break;
		}
		default:
			cout << "Некорректный выбор. Пожалуйста, выберите номер поля для редактирования от 1 до 7." << endl;
			continue; // Продолжаем цикл, чтобы пользователь мог выбрать снова
		}

		cout << " " << endl;
		// Проверяем данные снова
		cout << "Проверьте введенные данные:\n" << personToString(person) << "\nДанные введены верно? (да/нет): ";
		getline(cin, confirmation);
	}

	// Проверяем и сохраняем отредактированные данные при корректном вводе
	cout << "Данные успешно сохранены!" << endl << endl;
	people.push_back(person);

}


void clearPeople() {

	if (people.empty()) {
		cout << "Пока вы не ввели данные, очистка невозможна" << endl;
		return;
	}

	string confirmation;
	cout << "Вы уверены, что хотите очистить список данных? (да/нет): ";
	getline(cin, confirmation);

	if (confirmation == "да" || confirmation == "Да") {
		people.clear();
		cout << "Список пользователей успешно очищен." << endl;
	}
	else if (confirmation == "нет" || confirmation == "Нет") {
		cout << "Очистка списка данных отменена." << endl;
	}
	else {
		cout << "Некорректный ввод. Очистка списка данных отменена." << endl;
	}
}

void averageYear() {
	if (people.empty()) {
		cout << "Пока вы не ввели данные, очистка невозможна." << endl;
		return;
	}

	string genderChoice;
	cout << "Выберите пол для расчета среднего возраста (мужской/женский): ";
	cin >> genderChoice;

	int sumAge = 0;
	int countPeople = 0;
	const int NOW_YEAR = 2024;

	for (const auto& person : people) {
		if (person.gender == genderChoice) {
			sumAge += (NOW_YEAR - person.years_old);
			countPeople++;
		}
	}

	if (countPeople > 0) {
		int average = sumAge / countPeople;

		cout << "Средний возраст " << genderChoice << ": " << average << " год(а)" << endl;

		cout << "Хотите сохранить средний возраст в файл? (да/нет): ";
		string saveChoice;
		cin >> saveChoice;

		if (saveChoice == "да") {
			string filename;
			cout << "Введите имя файла (без расширения) для сохранения среднего возраста: ";
			cin >> filename;
			filename += ".txt";

			ifstream existingFile(filename);
			if (existingFile.good()) {
				existingFile.close();
				cout << "Файл с именем " << filename << " уже существует. Желаете перезаписать его (1) или добавить данные (2)? ";
				int fileOption;
				cin >> fileOption;

				ofstream outFile;
				if (fileOption == 2) {
					outFile.open(filename, ios_base::app);
				}
				else {
					outFile.open(filename);
				}

				if (outFile.is_open()) {
					outFile << "Средний возраст " << genderChoice << ": " << average << " год(а)" << endl;
					cout << "Результат успешно добавлен в файл." << endl;
					outFile.close();
				}
				else {
					cout << "Ошибка открытия файла для записи." << endl;
				}
			}
			else {
				ofstream outFile(filename);
				if (outFile.is_open()) {
					outFile << "Средний возраст " << genderChoice << ": " << average << " год(а)" << endl;
					cout << "Результат успешно сохранен в файле." << endl;
					outFile.close();
				}
				else {
					cout << "Ошибка открытия файла для записи." << endl;
				}
			}
		}
	}
	else {
		cout << "Нет данных для расчета среднего возраста для выбранного пола." << endl;
	}
}

void printMenu()
{
	cout << " " << endl;
	cout << "1. Добавить запись" << endl;
	cout << "2. Удалить запись" << endl;
	cout << "3. Редактировать запись" << endl;
	cout << "4. Вывод всех данных пользователей" << endl;
	cout << "5. Расчет среднего возраста" << endl;
	cout << "6. Сортировать данные и сохранение результатов в файл" << endl;
	cout << "7. Поиск по ФИО" << endl;
	cout << "8. Сохранить данные в файл" << endl;
	cout << "9. Загрузить данные из файла" << endl;
	cout << "10. Очистить список" << endl;
	cout << "11. Вывод списка всех файлов в рабочей папке" << endl;
	cout << "12. Вывод списка однофамильцев с одинаковыми городами" << endl;
	cout << "13. Расчет процента россиян с высшим образованием" << endl;
	cout << "14. Найти самый населенный город" << endl;
	cout << "15. Руководство пользвателя(справка)" << endl;
	cout << "16. Задание" << endl;
	cout << "17. О программе" << endl;
	cout << "18. Выход" << endl;
}

size_t maxLength(const vector<string>& strings) {
	size_t max_length = 0;
	for (const auto& str : strings) {
		max_length = max(max_length, str.length());
	}
	return max_length;
}

// Функция для печати таблицы с информацией о людях
void printTable(const vector<Person>& people) {
	if (people.empty()) {
		cout << "Вектор данных пуст." << endl;
		return;
	}

	// Определение максимальной длины для каждого столбца на основе заголовков
	size_t max_name_length = 35;  // Минимальная длина для ФИО
	size_t max_year_length = 13;  // Минимальная длина для Года рождения
	size_t max_gender_length = 9; // Минимальная длина для Пола
	size_t max_place_length = 19; // Минимальная длина для Места жительства
	size_t max_education_length = 21; // Минимальная длина для Уровня образования
	size_t max_kids_length = 18; // Минимальная длина для Количества детей
	size_t max_job_length = 15; // Минимальная длина для Места работы

	// Печать заголовка таблицы
	cout << "ID | " << setw(max_name_length) << left << "ФИО" << " | "
		<< setw(max_year_length) << left << "Год рождения" << " | "
		<< setw(max_gender_length) << left << "Пол" << " | "
		<< setw(max_place_length) << left << "Место жительства" << " | "
		<< setw(max_education_length) << left << "Уровень образования" << " | "
		<< setw(max_kids_length) << left << "Количество детей" << " | "
		<< setw(max_job_length) << left << "Место работы" << endl;

	// Печать разделителя
	cout << setfill('-') << setw(4 + max_name_length + max_year_length + max_gender_length
		+ max_place_length + max_education_length + max_kids_length + max_job_length) << "-" << endl;

	// Печать данных о людях
	for (size_t i = 0; i < people.size(); ++i) {
		cout << setfill(' ') << setw(2) << right << i + 1 << " | "
			<< setw(max_name_length) << left << people[i].name_person << " | "
			<< setw(max_year_length) << left << people[i].years_old << " | "
			<< setw(max_gender_length) << left << people[i].gender << " | "
			<< setw(max_place_length) << left << people[i].place_life << " | "
			<< setw(max_education_length) << left << people[i].education_level << " | "
			<< setw(max_kids_length) << left << people[i].count_kids << " | "
			<< setw(max_job_length) << left << people[i].job << endl;
	}
}


// Функция для вывода информации о человеке
void printPerson(const Person& person) {
	cout << "ФИО: " << person.name_person << endl;
	cout << "Год рождения: " << person.years_old << endl;
	cout << "Пол: " << person.gender << endl;
	cout << "Место жительства: " << person.place_life << endl;
	cout << "Уровень образования: " << person.education_level << endl;
	cout << "Количество детей: " << person.count_kids << endl;
	cout << "Место работы: " << person.job << endl;
	cout << endl;
}

void printData(const vector<Person>& people) {
	if (people.empty()) {
		cout << "Вектор данных пуст. Вы не ввели данные для вывода." << endl;
		return;
	}

	for (const auto& person : people) {
		printPerson(person);
	}
}

void deletePerson() {
	if (people.empty()) {
		cout << "Вектор данных пуст. Вы не ввели данные для удаления." << endl;
		return;
	}

	string name;
	cout << "Введите ФИО пользователя, которого хотите удалить, или введите 'отмена' для отмены удаления: ";
	getline(cin, name);

	if (name == "отмена") {
		cout << "Отмена удаления." << endl;
		return;
	}

	if (name.empty()) {
		cout << "Данных для удаления нет." << endl;
		return;
	}

	transform(name.begin(), name.end(), name.begin(), ::tolower); // Преобразуем введенное имя к нижнему регистру

	bool found = false;
	for (auto it = people.begin(); it != people.end(); ++it) {
		// Приведем имя в хранилище к нижнему регистру для сравнения
		string storedName = it->name_person;
		transform(storedName.begin(), storedName.end(), storedName.begin(), ::tolower);

		if (storedName == name) {
			found = true;
			cout << "Вы точно хотите удалить данные данного пользователя? (да/нет): ";
			string confirm;
			getline(cin, confirm);

			// Проверяем корректность ввода
			while (confirm != "да" && confirm != "нет") {
				cout << "Неправильный ввод. Пожалуйста, введите 'да' или 'нет': ";
				getline(cin, confirm);
			}

			if (confirm == "да") {
				people.erase(it);
				cout << "Запись успешно удалена!" << endl;
			}
			else {
				cout << "Удаление отменено." << endl;
			}
			break;
		}
	}

	if (!found) {
		cout << "Запись не найдена." << endl;
	}
}


void editPerson() {

	if (people.empty()) {
		cout << "Вектор данных пуст. Вы не ввели данные для редактирования." << endl;
		return;
	}

	string name;
	cout << "Введите ФИО пользователя, данные которого хотите изменить, или введите 'отмена' для отмены удаления: ";
	getline(cin, name);

	if (name == "отмена") {
		cout << "Отмена редактирования." << endl;
		return;
	}

	// Удаляем пробел в конце ФИО, если он есть
	if (!name.empty() && name.back() == ' ') {
		name.pop_back();
	}

	auto it = find_if(people.begin(), people.end(), [&name](const Person& p) {
		return p.name_person == name;
		});

	if (it != people.end()) {
		Person& person = *it;

		// Ввод нового ФИО с проверкой
		cout << "Введите новое ФИО: ";
		getline(cin, person.name_person);
		while (containsDigit(person.name_person) || countWords(person.name_person) != 3) {
			cout << "Некорректное ФИО. ФИО не должно содержать цифры и должно состоять из трех слов. Пожалуйста, введите снова: ";
			getline(cin, person.name_person);
		}
		stringstream ss(person.name_person);
		string word;
		bool isValid = true;
		while (ss >> word) {
			if (word.length() < 3) {
				isValid = false;
				break;
			}
		}
		if (!isValid) {
			cout << "Каждая часть ФИО (Фамилия, Имя, Отчество) должна содержать не менее трех букв. Пожалуйста, введите снова." << endl;
			editPerson(); // Повторный вызов функции для ввода ФИО
			return;
		}

		// Ввод остальных данных с проверкой
		cout << "Введите новый год рождения: ";
		while (!(cin >> person.years_old) || person.years_old < 1900 || person.years_old > 2024) {
			cout << "Год рождения должен быть не ранее 1900 и не позже 2024. Пожалуйста, введите снова: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cin.ignore();

		cout << "Введите пол (мужской/женский): ";
		do {
			getline(cin, person.gender);
			if (person.gender != "мужской" && person.gender != "женский" && person.gender != "Мужской" && person.gender != "Женский") {
				cout << "Некорректное значение пола. Пожалуйста, введите снова: ";
			}
		} while (person.gender != "мужской" && person.gender != "женский" && person.gender != "Мужской" && person.gender != "Женский");

		cout << "Введите новое место жительства (город): ";
		getline(cin, person.place_life);

		while (containsSpecialCharacters(person.place_life) || containsDigit(person.place_life)) {
			cout << "Место жительства не должно содержать специальные символы и цифры. Пожалуйста, введите снова: ";
			getline(cin, person.place_life);
		}

		cout << "Введите новый уровень образования (среднее/среднее специальное/высшее): ";
		do {
			getline(cin, person.education_level);
			if (person.education_level != "среднее" && person.education_level != "среднее специальное" && person.education_level != "высшее") {
				cout << "Некорректное значение уровня образования. Пожалуйста, введите снова (среднее/среднее специальное/высшее): ";
			}
		} while (person.education_level != "среднее" && person.education_level != "среднее специальное" && person.education_level != "высшее");

		cout << "Введите новое количество детей: ";
		while (!(cin >> person.count_kids) || person.count_kids < 0 || person.count_kids > 200) {
			if (person.count_kids < 0) {
				cout << "Количество детей должно быть неотрицательным числом. Пожалуйста, введите снова: ";
			}
			else {
				cout << "Вы ввели данные, которые невозможны. Количество детей не должно превышать 1000. Пожалуйста, введите снова: ";
			}
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cin.ignore();

		cout << "Введите новое место работы: ";
		getline(cin, person.job);

		cout << "Вы точно хотите изменить данные данного пользователя? (да/нет): ";
		string confirm;
		getline(cin, confirm);
		if (confirm == "да") {
			cout << "Запись успешно отредактирована!" << endl;
		}
		else {
			cout << "Изменение отменено." << endl;
		}
		cout << "Хотите сохранить данные в файл? (да/нет): ";
		getline(cin, confirm);
		if (confirm == "да" || confirm == "Да") {
			cout << "Введите имя файла для сохранения (без расширения): ";
			string filename;
			getline(cin, filename);
			filename += ".txt";
			saveToFile(filename, people); // Save data to file
		}
		else if (confirm == "нет") {
			cout << "Запись не сохранена в файл." << endl << endl;
		}
		else {
			cout << "Некорректный ввод. Запись не сохранена." << endl << endl;
		}
	}
	else {
		cout << "Запись не найдена." << endl;
	}
}


void search(const vector<Person>& people) {
	if (people.empty()) {
		cout << "Вектор данных пуст. Вы не ввели данные для поиска." << endl;
		return;
	}

	cout << "Выберите метод поиска:" << endl;
	cout << "1. По данным (фамилия, год рождения, пол)" << endl;
	cout << "2. По началу фамилии" << endl;

	int choice;
	cout << "Ваш выбор: ";
	cin >> choice;
	cin.ignore();

	if (choice == 1) {
		string surname;
		cout << "Введите фамилию пользователя, данные которого хотите найти: ";
		getline(cin, surname);

		int birthYear;
		cout << "Введите год рождения пользователя, данные которого хотите найти: ";
		cin >> birthYear;
		cin.ignore();

		string gender;
		cout << "Введите пол пользователя (мужской/женский): ";
		getline(cin, gender);

		cout << endl;

		// Создаем временный вектор для хранения найденных людей
		vector<Person> foundPeople;

		// Проверяем каждого человека в векторе
		for (const auto& person : people) {
			// Проверяем, соответствуют ли данные введенным критериям
			if (person.name_person == surname && person.years_old == birthYear && person.gender == gender) {
				// Добавляем найденного человека во временный вектор
				foundPeople.push_back(person);
			}
		}

		// Выводим результаты поиска в виде таблицы
		printTable(foundPeople);

		// Спрашиваем пользователя, хочет ли он сохранить результаты поиска в файл
		cout << "Хотите сохранить результаты поиска в файл? (да/нет): ";
		string saveChoice;
		getline(cin, saveChoice);

		if (saveChoice == "да") {
			string filename;
			cout << "Введите название файла (без расширения '.txt'): ";
			getline(cin, filename);
			filename += ".txt";

			// Сохраняем результаты поиска в файл
			saveToFile(filename, foundPeople);
		}
		else if (saveChoice == "нет") {
			cout << "Результаты поиска не сохранены." << endl;
		}
		else {
			cout << "Некорректный выбор. Результаты поиска не сохранены." << endl;
		}
	}
	else if (choice == 2) {
		string surname;
		cout << "Введите начало фамилии пользователя, данные которого хотите найти: ";
		getline(cin, surname);

		cout << endl;

		// Создаем временный вектор для хранения найденных людей
		vector<Person> foundPeople;

		// Проверяем каждого человека в векторе
		for (const auto& person : people) {
			// Проверяем, содержится ли указанная последовательность символов в фамилии
			if (person.name_person.find(surname) != string::npos) {
				// Добавляем найденного человека во временный вектор
				foundPeople.push_back(person);
			}
		}

		// Проверяем, были ли найдены какие-либо результаты
		if (foundPeople.empty()) {
			cout << "По вашему запросу ничего не найдено." << endl;
		}
		else {
			// Выводим результаты поиска в виде таблицы
			printTable(foundPeople);

			// Спрашиваем пользователя, хочет ли он сохранить результаты поиска в файл
			cout << "Хотите сохранить результаты поиска в файл? (да/нет): ";
			string saveChoice;
			getline(cin, saveChoice);

			if (saveChoice == "да") {
				string filename;
				cout << "Введите название файла (без расширения '.txt'): ";
				getline(cin, filename);
				filename += ".txt";

				// Сохраняем результаты поиска в файл
				saveToFile(filename, foundPeople);
			}
			else if (saveChoice == "нет") {
				cout << "Результаты поиска не сохранены." << endl;
			}
			else {
				cout << "Некорректный выбор. Результаты поиска не сохранены." << endl;
			}
		}
	}
	else {
		cout << "Некорректный выбор. Пожалуйста, выберите 1 или 2." << endl;
	}
}

void loadFromFile(vector<Person>& people) {
	string filename;
	cout << "Введите имя файла для загрузки данных (с расширением, *.txt) или введите 'отмена' для выхода в главное меню: ";
	getline(cin, filename);

	if (filename == "отмена") {
		cout << "Возвращение в главное меню..." << endl;
		return;
	}

	ifstream fin;
	fin.open(filename);

	if (!fin.is_open()) {
		cout << "Данный файл не существует" << endl;
	}
	else {
		string line;
		while (getline(fin, line)) {
			stringstream ss(line);
			string name, birthYear, gender, city, education, children, job;
			getline(ss, name, ';');
			getline(ss, birthYear, ';');
			getline(ss, gender, ';');
			getline(ss, city, ';');
			getline(ss, education, ';');
			getline(ss, children, ';');
			getline(ss, job, ';');

			Person person;
			person.name_person = name;
			person.years_old = stoi(birthYear);
			person.gender = gender;
			person.place_life = city;
			person.education_level = education;
			person.count_kids = stoi(children);
			person.job = job;
			people.push_back(person);
		}
		fin.close();
		cout << "Данные успешно импортированы" << endl;
	}
}


void AboutProgram()
{
	system(" cls ");
	cout << "Программа создана студентом Иркутского Национального Исследовательского Технического Университета группы ИСТб-23-2 Серёгиным Семёном" << endl;
	cout << "Версия программного продукта: v1.1.7" << endl;
	cout << "Дата последних изменений - 08.05.2024" << endl;
	cout << "Связь с автором: " << endl;
	cout << "TG: https://t.me/MMXXXII" << endl;
	cout << "VK: https://vk.com/mmxxxii" << endl;
}

void ReadMe() {
	wifstream inputFile("Руководство пользователя.txt");
	if (inputFile.is_open()) {
		inputFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8
		wstring line;
		while (getline(inputFile, line)) {
			wcout << line << endl;
		}
		inputFile.close();
	}
	else {
		cout << "Не удалось открыть файл." << endl;
	}
}

void task()
{
	cout << "Результаты переписи населения хранятся в файле, имеющем следующую структуру: Ф.И.О. жителя, его год рождения, пол, адрес места жительства"
		"(город), образование, количество детей, место работы. Написать программу, "
		"обрабатывающую эти сведения и позволяющую определить: средний возраст "
		"жителей(мужчины, женщины); процент россиян, имеющих высшее образование; самый населенный город. Сформировать списки однофамильцев, проживающих в одном городе. Организовать поиск сведений о человеке по его фамилии и году рождения." << endl;

}

bool comparePeople(const Person& person1, const Person& person2, const string& criterion) {
	string field1, field2;

	if (criterion == "name") {
		field1 = person1.name_person;
		field2 = person2.name_person;
	}
	else if (criterion == "years") {
		return person1.years_old < person2.years_old;
	}
	else if (criterion == "gender") {
		field1 = person1.gender;
		field2 = person2.gender;
	}
	else if (criterion == "place") {
		field1 = person1.place_life;
		field2 = person2.place_life;
	}
	else if (criterion == "education") {
		field1 = person1.education_level;
		field2 = person2.education_level;
	}
	else if (criterion == "kids") {
		return person1.count_kids < person2.count_kids;
	}
	else if (criterion == "job") {
		field1 = person1.job;
		field2 = person2.job;
	}
	else {
		// Если критерий сортировки указан некорректно, считаем объекты равными
		return false;
	}

	// Преобразование к нижнему регистру для регистронезависимой сортировки
	transform(field1.begin(), field1.end(), field1.begin(), ::tolower);
	transform(field2.begin(), field2.end(), field2.begin(), ::tolower);

	return field1 < field2;
}

void sortData(const string& criterion) {

	sort(people.begin(), people.end(), [criterion](const Person& person1, const Person& person2) {
		return comparePeople(person1, person2, criterion);
		});

	printTable(people);
}


void printData(const string& criterion, const string& filename) {
	// Проверяем, существует ли уже файл с таким именем
	if (fileExists(filename)) {
		string choice;
		while (true) {
			cout << "Файл с именем " << filename << " уже существует. Хотите перезаписать его? (да/нет): ";
			getline(cin, choice);

			// Преобразуем ввод пользователя в нижний регистр
			transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

			if (choice == "да") {
				break;
			}
			else if (choice == "нет") {
				cout << "Сохранение в файл отменено." << endl;
				return;
			}
			else {
				cout << "Пожалуйста, введите 'да' или 'нет'." << endl;
			}
		}
	}

	sortData(criterion);

	// Открываем файл для записи
	ofstream outputFile(filename);
	if (!outputFile.is_open()) {
		cout << "Ошибка открытия файла для записи." << endl;
		return;
	}

	// Записываем отсортированные данные в файл
	for (const auto& person : people) {
		outputFile << "ФИО: " << person.name_person << endl;
		outputFile << "Год рождения: " << person.years_old << endl;
		outputFile << "Пол: " << person.gender << endl;
		outputFile << "Город: " << person.place_life << endl;
		outputFile << "Уровень образования: " << person.education_level << endl;
		outputFile << "Количество детей: " << person.count_kids << endl;
		outputFile << "Место работы: " << person.job << endl;
		outputFile << endl;
	}

	outputFile.close(); // Закрываем файл
}

void percentWithHigherEducation() {
	int totalPeople = people.size();
	int countWithHigherEducation = 0;

	// Подсчет количества людей с высшим образованием
	for (const auto& person : people) {
		if (person.education_level == "высшее") {
			countWithHigherEducation++;
		}
	}

	// Если есть хотя бы один человек в базе
	if (totalPeople > 0) {
		// Расчет процента людей с высшим образованием
		double percent = (static_cast<double>(countWithHigherEducation) / totalPeople) * 100;

		// Вывод результата на экран
		cout << "Процент россиян с высшим образованием: " << fixed << setprecision(2) << percent << "%" << endl;

		// Меню для сохранения результатов в файл
		cout << "Хотите сохранить результаты в файл? (да/нет): ";
		string choice;
		cin >> choice;

		if (choice == "да") {
			// Пользователь решил сохранить результаты
			cout << "Введите имя файла (без расширения) для сохранения: ";
			string filename;
			cin >> filename;

			// Добавляем расширение .txt к имени файла
			filename += ".txt";

			// Проверяем существует ли файл
			ifstream existingFile(filename);
			if (existingFile.good()) {
				existingFile.close();
				// Файл уже существует
				cout << "Файл с именем " << filename << " уже существует. Желаете перезаписать его (1) или добавить данные (2)? ";
				int fileOption;
				cin >> fileOption;

				// Проверяем выбор пользователя
				if (fileOption == 2) {
					// Открываем файл для добавления
					ofstream outFile(filename, ios_base::app);
					outFile << "Процент россиян с высшим образованием: " << fixed << setprecision(2) << percent << "%" << endl;
					cout << "Результаты успешно добавлены в файл." << endl;
					outFile.close();
				}
				else {
					// Открываем файл для перезаписи
					ofstream outFile(filename);
					outFile << "Процент россиян с высшим образованием: " << fixed << setprecision(2) << percent << "%" << endl;
					cout << "Результаты успешно перезаписаны в файл." << endl;
					outFile.close();
				}
			}
			else {
				// Файла с таким именем нет, просто записываем результаты
				ofstream outFile(filename);
				outFile << "Процент россиян с высшим образованием: " << fixed << setprecision(2) << percent << "%" << endl;
				cout << "Результаты успешно сохранены в файле." << endl;
				outFile.close();
			}
		}
	}
	else {
		// Если нет людей в базе, выводим сообщение об этом
		cout << "Нет информации о людях для подсчета процента с высшим образованием." << endl;
	}
}

void mostPopulatedCity() {
	map<string, int> cityPopulation;

	// Подсчет количества жителей в каждом городе
	for (const auto& person : people) {
		cityPopulation[person.place_life]++;
	}

	// Поиск города с наибольшим количеством жителей
	int maxPopulation = 0;
	string mostPopulatedCity;

	for (const auto& pair : cityPopulation) {
		if (pair.second > maxPopulation) {
			maxPopulation = pair.second;
			mostPopulatedCity = pair.first;
		}
	}

	if (!mostPopulatedCity.empty()) {
		cout << "Самый населенный город: " << mostPopulatedCity << ", количество жителей: " << maxPopulation << endl;
	}
	else {
		cout << "Нет данных для определения самого населенного города." << endl;
	}
}

void listSameSurnamesInCity() {
	map<pair<string, string>, vector<string>> surnameLists;

	// Заполняем карту данными
	for (const auto& person : people) {
		string surname = person.name_person.substr(0, person.name_person.find(' ')); // Получаем фамилию
		string city = person.place_life;

		// Добавляем имя в список для соответствующей фамилии и города
		surnameLists[{city, surname}].push_back(person.name_person);
	}

	// Выводим списки однофамильцев
	bool hasSameSurnames = false;
	for (const auto& pair : surnameLists) {
		if (pair.second.size() > 1) { // Если в городе больше одного однофамильца
			hasSameSurnames = true;
			break;
		}
	}

	// Выводим списки однофамильцев
	if (hasSameSurnames) {
		cout << left << setw(30) << "Город" << " | " << "Однофамильцы" << endl;
		for (const auto& pair : surnameLists) {
			if (pair.second.size() > 1) { // Если в городе больше одного однофамильца
				for (const auto& name : pair.second) {
					cout << setw(30) << pair.first.second + " " + pair.first.first << " | " << name << endl;
				}
			}
		}
	}
	else {
		cout << "Нет городов с однофамильцами." << endl;
	}
}

void saveOrExit() {

	if (people.empty()) {
		cout << "Никаких изменений не было, сохранять нечего." << endl;
		exit(0);
	}

	string choice;
	do {
		cout << "Хотите сохранить данные перед выходом? (да/нет): ";
		cin >> choice;
		if (choice == "да" || choice == "Да") {
			string saveFilename;
			cout << "Введите имя файла для сохранения (без расширения): ";
			cin >> saveFilename;
			saveFilename += ".txt";
			saveToFile(saveFilename, people);
			return; // Возвращаемся из функции, так как пользователь сделал правильный выбор
		}
		else if (choice == "нет" || choice == "Нет") {
			return; // Возвращаемся из функции, так как пользователь сделал правильный выбор
		}
		else {
			cout << "Неправильный выбор. Пожалуйста, введите 'да' или 'нет'." << endl;
		}
	} while (true); // Повторяем, пока пользователь не сделает правильный выбор
}

//считывает информацию с файлов и выводит ее
//void readTxtFilesFromCurrentDirectory() {
//	WIN32_FIND_DATA findData;
//	HANDLE hFind = FindFirstFile(L"*.txt", &findData);
//
//	if (hFind != INVALID_HANDLE_VALUE) {
//		do {
//			// Преобразование WCHAR в char
//			char filename[260];
//			WideCharToMultiByte(CP_ACP, 0, findData.cFileName, -1, filename, 260, NULL, NULL);
//
//			cout << "Reading file: " << filename << endl;
//
//			// Открываем файл для чтения
//			ifstream file(filename);
//			if (file.is_open()) {
//				string line;
//				// Считываем и выводим содержимое файла построчно
//				while (getline(file, line)) {
//					cout << line << endl;
//				}
//				file.close();
//			}
//			else {
//				cerr << "Error opening file: " << filename << endl;
//			}
//		} while (FindNextFile(hFind, &findData) != 0);
//		FindClose(hFind);
//	}
//	else {
//		cerr << "No .txt files found in the current directory." << endl;
//	}
//}

void readTxtFilesFromCurrentDirectory() {
	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFile(L"*.txt", &findData);
	int fileCount = 0;

	if (hFind != INVALID_HANDLE_VALUE) {
		// Считаем количество файлов
		do {
			fileCount++;
		} while (FindNextFile(hFind, &findData) != 0);
		FindClose(hFind);
	
		if (fileCount < 5)
		{
			cout << "Найдено " << fileCount << " файла:" << endl;
		}

		if (fileCount > 4)
		{
			cout << "Найдено " << fileCount << " файлов:" << endl;
		} 

		// Теперь проходим по файлам снова, чтобы вывести их имена
		hFind = FindFirstFile(L"*.txt", &findData);
		int currentFileCount = 0;
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				char filename[260];
				WideCharToMultiByte(CP_ACP, 0, findData.cFileName, -1, filename, 260, NULL, NULL);
				cout << ++currentFileCount << ". " << filename << endl;
			} while (FindNextFile(hFind, &findData) != 0);
			FindClose(hFind);
		}
	}
	else {
		cerr << "В текущей папке не найдены файлы с расширением .txt" << endl;
	}
}

vector<string> readPreviousFiles(const string& filename) {
	vector<string> fileList;
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		fileList.push_back(line);
	}
	return fileList;
}


int main()
{
	int choice;
	setlocale(LC_ALL, "Russian_Russia.1251");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	cout << "Формирование бинарного файла	Вариант 6" << endl;
	do {
		printMenu();
		cout << "Выберите действие: ";
		if (!(cin >> choice)) {
			cout << "Ошибка: неправильный ввод. Пожалуйста, введите число от 1 до 18." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		cout << " " << endl;
		cin.ignore();

		switch (choice)
		{
		case 1:
			addPerson();
			break;
		case 2:
			deletePerson();
			break;
		case 3:
			editPerson();
			break;
		case 4:
			printTable(people);
			break;
		case 5:
			averageYear();
			break;
		case 6:
		{
			if (people.empty()) {
				cout << "Вектор данных пуст. Вы не ввели данные для сортировки." << endl;
				break;
			}

			string criterion;
			cout << "Выберите критерий сортировки (name/years/gender/place/education/kids/job) или введите 'отмена' для выхода в главное меню: ";
			getline(cin, criterion);
			if (criterion == "отмена") {
				cout << "Сортировка отменена." << endl;
				break;
			}

			sortData(criterion);

			string filename;
			cout << " " << endl;
			cout << "Введите имя файла (без расширения) для сохранения результатов сортировки или введите 'отмена' для отмены: ";
			getline(cin, filename);
			if (filename == "отмена") {
				cout << "Сохранение в файл отменено." << endl;
				break;
			}
			filename += ".txt";
			cout << "Результаты сортировки сохранены в файле." << endl;
			break;
		}

		case 7:
			search(people);
			break;
		case 8:
		{
			string saveFilename;
			cout << "Введите имя файла для сохранения (без расширения): ";
			getline(cin, saveFilename);

			saveFilename += ".txt";

			saveToFile(saveFilename, people);
		}
		break;
		case 9:
		{
			loadFromFile(people);
		}
		break;

		case 10:
		{
			clearPeople();
			break;
		}

		case 11:
		{
			readTxtFilesFromCurrentDirectory();
			break;
		}

		case 12:
		{
			listSameSurnamesInCity();
			break;
		}

		case 13:
		{
			percentWithHigherEducation();
			break;
		}

		case 14:
		{
			mostPopulatedCity();
			break;
		}

		case 15:
		{
			ReadMe();
			break;
		}
		case 16:
		{
			task();
			break;
		}
		case 17:
		{
			AboutProgram();
			break;
		}
		case 18:
		{
			saveOrExit();
		}
		}
	} while (choice != 18);

	return 0;
}


//рассчет сред возраста мужчин  +
//проверка на введенные данные пользователя +
//сделать выбор сохранения в файл среднего возраста  +
//сортировка не работает  +
//на выходе есть ошибка писать английским нет(ytn)


//08.05.24

//добавление отмены в пунктах меню
//удаление данных о человеке переделано
//добавлены подтверждение 
//переработаны edit и delete


//найдены n файлов сделать