//
// Приложение для Windows.
// 1.	Предложить свой алгоритм формирования цифровой подписи для данных .
// 2.	Подпись должна быть индивидуальна  с достаточно высокой вероятностью.Как минимум возможность формирования 1024 варианта подписи.
//
// ----------------------------------------------------------------------------------
// 1.	Приложение читает данные из файла, указанного при запуске или запрошенного от пользователя .
// 2.	Проверяет наличие цифровой подписи этого файла данных.
// 3.	О наличии / отсутствии подписи сообщает.
// 4.	Предлагает убрать / добавить подпись.
// 5.	Результат писать в другой файл.Имя его получать при запуске  или формировать автоматически.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void printWelcome() {
    cout << "+---------------------------+" << endl;
    cout << "|    Welcome to program     |" << endl;
    cout << "+---------------------------+" << endl;
}

bool userChoose(char& userAnswer) {
    int userTries = 1;

    while (userTries < 3) {
        cin >> userAnswer;

        switch (userAnswer) {
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            cout << "Sorry, I don't understand that." << endl;
            cout << "Please try again." << endl;
            userTries = userTries + 1;
        }
    }
    return false;
}

int main() {

    printWelcome();

    while (true) {
        char userAnswer;
        bool choose;

        cout << "Do you want select the file (y or n) ?" << endl;
        choose = userChoose(userAnswer);

        string filePath;
        if (choose) {
            cout << "Please write the path to the file:" << endl;
            cin >> filePath;
        }
        else
        {
            cout << "The default file is chosen" << endl;
            filePath = "..\\test_1.txt";
        }

        int data;
        int signing = 0;

        ifstream fin(filePath);

        if (!fin.is_open()) {
            cout << "Sorry, cannot open the file" << endl;
            continue;
        }

        fin >> data;
        fin >> signing;
        fin.close();

        cout << "Data: " << data << endl;
        if (signing == data % 1024) {
            cout << "The digital signature is: " << signing << endl;
            cout << "Do you want to delete Signing (y or n) ?" << endl;

            choose = userChoose(userAnswer);
            if (choose) {
                filePath = "..\\test_" + to_string(data % 1024) + ".txt";
                ofstream fout(filePath);
                if (!fout.is_open()) {
                    cout << "Sorry, cannot open the file" << endl;
                    continue;
                }

                fout << data << endl;
                fout.close();
                cout << "The signature was successfully deleted" << endl;
            }
        }
        else {
            cout << "The digital signature has not been detected." << endl;
            cout << "Do you want to add Signing (y or n) ?" << endl;

            choose = userChoose(userAnswer);
            if (choose) {
                filePath = "..\\test_" + to_string(data % 1024) + ".txt";
                ofstream fout(filePath);
                if (!fout.is_open()) {
                    cout << "Sorry, cannot open the file" << endl;
                    continue;
                }

                fout << data << endl;
                fout << data % 1024;
                fout.close();
                cout << "The signature was successfully recorded" << endl;
            }
        }
    }
    return 0;
}