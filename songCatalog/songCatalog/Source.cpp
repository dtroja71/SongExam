#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <stdlib.h>

#define CLS system("cls")

using namespace std;

struct Song {
	string name;
	string author;
	string text;
	int year;
};

int length = 0;
Song* songs;
ofstream file;
ifstream file_;
string filename = "data.txt";


void addToEnd(Song*& arr, int& length, Song value) //ccылка на размер будет изменена по адресу , а указатель на ссылку получает адресс массива
{
	Song* newArray = new Song[length + 1];//выделяем память
	for (int i = 0; i < length; i++)
	{
		newArray[i] = arr[i];
	}
	newArray[length] = value;
	delete[]arr; //удалить старый массив но указатель остается
	arr = newArray; //присвоить старій указатель новому массиву
	length++;
}

void addSongByKeyboard()
{
	Song tempSong;
	cout << "Введите название страны: ";
	cin >> tempSong.name;
	cout << "Введите автора: ";
	cin >> tempSong.author;
	cout << "Введите text: ";
	cin >> tempSong.text;
	cout << "Введите год: ";
	cin >> tempSong.year;

	addToEnd(songs, length, tempSong);
}

void addSongByFile()
{
	Song tempSong;
	string filename;
	ifstream fileIn;    //read
	while (true)
	{
		cout << "Введите имя файла:";
		cin >> filename;
		filename += ".txt";
		fileIn.open(filename);
		if (fileIn.fail())
		{
			cout << "Error opening file!\a";
			CLS;
			continue;
		}

		getline(fileIn, tempSong.name);
		getline(fileIn, tempSong.author);
		string year;
		getline(fileIn, year);
		tempSong.year = atoi(year.c_str());

		while (!fileIn.eof())
		{
			string line;
			getline(fileIn, line);
			tempSong.text += line + "\n";
		}
		fileIn.close();
		addToEnd(songs, length, tempSong);
		break;
	}
}

void deleteToPlace(Song*& arr, int& length, int placeIndex) //ccылка на размер будет изменена по адресу , а указатель на ссылку получает адресс массива
{
	Song* newArray = new Song[length--];//выделяем память
	for (int i = 0, j = 0; i < length; i++, j++)
	{
		if (placeIndex == i)
		{
			j++;
		}
		newArray[i] = arr[j];
	}
	delete[]arr; //удалить старый массив но указатель остается
	arr = newArray; //присвоить старій указатель новому массиву
}

int searchIndexByName(const Song* const arr, const int const length, const string const name)
{
	for (size_t i = 0; i < length; i++)
	{
		if (arr[i].name == name) return i;
	}
	return -1;
}// poisk slofa

void printSongsText(const Song* const arr, const int const length, const string const name)
{
	int index = searchIndexByName(arr, length, name);
	cout << arr[index].text;
}

void printSongsTextByWords(const Song* const arr, const int const length, const string const searchWord)
{
	int index = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (arr[i].text == searchWord) index = i - 1;
			
	}
	cout << arr[index].text;
}

void changeSongsText(Song* arr, const int const length, const string const name)
{
	int index = searchIndexByName(arr, length, name);
	cout << "Старый текст: \n\n";
	cout << arr[index].text;
	cout << "\n\nВведите новый текст: \n";
	cin >> arr[index].text;
}

void saveSongs()
{
	cout << "Если вы жилаете сохранить в стандартный каталог нажмите 0,"
		"иначе введите имя нового каталога: ";
	string inputText;
	cin >> inputText;
	if (inputText != "0") {
		filename = inputText + ".txt";
	}
	file.open(filename);
	for (size_t i = 0; i < length; i++)
	{
		file << songs[i].name << endl;
		file << songs[i].author << endl;
		file << songs[i].year << endl;
		file << songs[i].text << endl;
		file << "\n";
		if (i == length - 1)
		{
			file << "***";
		}
		else {
			file << "***\n";
		}
	}
	file.close();
	CLS;
	cout << "Песни успешно сохранены";
}

void openSongs(Song*& arr, int& length)
{
	cout << "Если вы жилаете открыть стандартный каталог нажмите 0 или введите имя каталога: ";
	string inputText;
	cin >> inputText;
	if (inputText != "0")
	{
		filename = inputText + ".txt";
	}
	file_.open(filename);

	length = 0;
	arr = new Song[length];//обнулить старый массив

	while (!file_.eof())
	{
		Song tempSong;
		string line;
		string text;
		getline(file_, line);
		tempSong.name = line;
		getline(file_, line);
		tempSong.author = line;
		getline(file_, line);
		tempSong.year = atoi(line.c_str());
		while (line != "***")
		{
			getline(file_, line);
			tempSong.text += line + "\n";
		}
		addToEnd(arr, length, tempSong);
	}
	file.close();
}

void printAllCatalog() {
	for (size_t i = 0; i < length; i++)
	{
		cout << songs[i].name << endl;
		cout << songs[i].author << endl;
		cout << songs[i].year << endl;
		cout << songs[i].text << endl;
	}
}

void printMenu()
{
	string country;
	int mainMenuIndex;
	int indexToSearch;
	string word;

	cout << "---Каталог гимнов стран---\n\n";
	cout << "1. Добавление текста песни;" << endl;
	cout << "2. Удаление текста песни;" << endl;
	cout << "3. Изменение текста песни;" << endl;
	cout << "4. Отображение текста песни;" << endl;
	cout << "5. Сохранение каталога песен;" << endl;
	cout << "6. Открытие каталога песен;" << endl;
	cout << "7. Поиск и отображение всех песен, содержащих слово, указанное пользователем;" << endl;
	cout << "8. Показать весь каталог песен;" << endl;
	cout << "9. Выход\n" << endl;
	cout << "Выберите пункт меню: ";
	cin >> mainMenuIndex;

	switch (mainMenuIndex)
	{
	case 1:
		cout << "1. Добавление текста песни c клавиатуры" << endl;
		cout << "2. Добавление текста песни c файла\n" << endl;
		cout << "Выберите пункт меню: ";
		int j;
		cin >> j;
		switch (j)
		{
		case 1:
			addSongByKeyboard();
			CLS;
			break;
		case 2:
			addSongByFile();
			CLS;
			break;
		default:
			cout << "---Ошибка выбора!---Повторите выбор" << endl;;
			Sleep(1000);
			CLS;
			break;
		}
		break;

	case 2:
		cout << "Удаление текста песни" << endl;
		cout << "Введите название страны для удаления: ";
		cin >> country;
		indexToSearch = searchIndexByName(songs, length, country);
		deleteToPlace(songs, length, indexToSearch);
		CLS;
		break;
	case 3:
		cout << "Изменение текста песни" << endl;
		cout << "Введите название страны для изменения: ";
		cin >> country;
		changeSongsText(songs, length, country);
		system("pause");
		CLS;
		break;
	case 4:
		cout << "Отображение текста песни" << endl;
		cout << "Введите название страны для отображения: ";
		cin >> country;
		printSongsText(songs, length, country);
		system("pause");
		CLS;
		break;
	case 5:
		saveSongs();
		system("pause");
		CLS;
		break;
	case 6:
		openSongs(songs, length);
		system("pause");
		CLS;
		break;
	case 7:
		cout << "Поиск и отображение всех песен, содержащих слово, указанное пользователем" << endl;
		cout << "Введите слово: ";
		cin >> word;
		printSongsTextByWords(songs, length, word);
		system("pause");
		CLS;
		break;
	case 8:
		printAllCatalog();
		system("pause");
		CLS;
	case 9:
		exit(3);
		system("pause");
		CLS;
		break;

	default:
		cout << "---Ошибка выбора!---Повторите выбор---" << endl;
		Sleep(1000);
		CLS;
		break;
	}
}



int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		printMenu();
		
		

		system("pause");
	}



	return 0;
}


//Создайте приложение «Каталог текстов песен».
//Приложение должно иметь следующие возможности :
//■■ Добавление текста песни :
//• Текст песни :
//ӽӽ может быть введен с клавиатуры;
//ӽӽ загружен из файла.
//Для каждой песни нужно указывать название песни, автора текста и
//год создания песни(если он известен).
//■■ Удаление текста песни.
//■■ Изменение текста песни.
//■■ Отображение текста песни на экран.
//■■ Сохранение текста песни в файл.
//■■ Поиск и отображение всех песен одного автора.
//■■ Поиск и отображение всех песен, содержащих слово, указанное пользова -
//телем.


