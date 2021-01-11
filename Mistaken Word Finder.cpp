#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>
#include <ctype.h>
#include "AppHeader.h"


using namespace std;


ifstream load("dictionary.in");
ifstream f("accounts.txt");
ofstream out("report.txt");


int main() {

    system("Color 27");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 47);

    /// Reading accounts list
    char aux[50];
    for (int i = 0; i < no_accounts; i++) {
        f.get(aux, 50);
        strcpy(User[i].username, aux);
        f.get();
        f.get(aux, 50);
        strcpy(User[i].password, aux);
        f.get();
    }

    Intro();

    char c;
    cin >> c;
    cin.get();
    bool ok;
    int index, nr_file = 1, report_header = 0;
    char answer = 'y';

    if (c == 'E' || c == 'e') {
        Log_window(ok, index);
        if (ok) {
            int word_cnt = 0;
            List hashtable[SIZE];

            // Initialisation
            initialize(hashtable);

            // Dictionary Loading
            while (!load.eof() && word_cnt < 143100) {
                char word[46];
                load.get(word, 46);
                load.get();
                unsigned int i = Hash(word[0]);
                hashtable[i].Insert_Node(word);
                word_cnt++;
            }
            word_cnt -= (load.eof() == 1);

            cout << '\n';
            cout << "    >>> Dictionary succesfully loaded ... Application ready to use     " << '\n' << '\n';

            while (answer == 'y') {
                // Reading input text
                char file[20], aux[4];
                int cnt, sign, k;
                int x = 0;
                while (x != 1) {
                    k = 0;
                    sign = 0;
                    cnt = 0;

                    cout << "    >>> Enter the file name ( Format : file.txt ) : ";
                    cin.get(file, 20);
                    cin.get();

                    int n = strlen(file);
                    for (int i = 0; i < n; i++)
                        if (file[i] == '.' && i != 0)cnt++;

                    if (cnt == 1) {
                        for (int i = 2; i < n; i++) {
                            if (file[i - 1] == '.') sign = 1;
                            if (sign == 1)aux[k++] = file[i];
                        }

                        aux[k] = '\0';
                        if (strcmp(aux, "txt") == 0)x = 1;
                    }
                }
                ifstream in(file);
                char text[max_words];
                char text_copy[max_words];
                in.get(text, max_words);
                strcpy(text_copy, text);

                if (strlen(text) != 0) {
                    cout << '\n' << '\n' << '\n' << "   >>>  File (" << nr_file
                         << ") succesfully processed ! Here is your text : " << '\n' << '\n' << '\n';
                    cout << "       ";
                    // Text processing
                    char *p;
                    int mistaken_words = 0, nr_words = 0, upper_case = 0, space = 0, first_word = 0;

                    p = strtok(text, " .,-?/!(){}[]<>");

                    while (p != NULL) {
                        nr_words++;
                        unsigned int i = Hash(p[0]);
                        if (isupper(p[0])) {
                            p[0] = tolower(p[0]);
                            upper_case = 1;
                        }
                        if (hashtable[i].get_List_Index(p) == 0) {
                            mistaken_words++;
                            SetConsoleTextAttribute(hConsole, 36);
                            if (space % 10 == 0) cout << '\n' << "     ";
                            if (first_word == 0) {
                                cout << "  ";
                                first_word++;
                            }
                            if (upper_case == 1) {
                                p[0] = toupper(p[0]);
                                if (first_word > 1 && space % 10 != 0)cout << '.';
                                else if (first_word <= 1) cout << " ";
                            } else if (space % 10 != 0) cout << " ";
                            cout << p;
                            space++;
                            first_word++;
                        } else {
                            SetConsoleTextAttribute(hConsole, 43);
                            if (space % 10 == 0) cout << '\n' << "     ";
                            if (first_word == 0) {
                                cout << "  ";
                                first_word++;
                            }
                            if (upper_case == 1) {
                                p[0] = toupper(p[0]);
                                if (first_word > 1 && space % 10 != 0)cout << '.';
                                else if (first_word <= 1) cout << " ";
                            } else if (space % 10 != 0) cout << " ";
                            cout << p;
                            space++;
                            first_word++;
                        }
                        p = strtok(NULL, " .,-?/!(){}[]<>");
                        upper_case = 0;
                    }
                    cout << '.';
                    double percentage = (1 - double(((mistaken_words / 1.00) / (nr_words / 1.00)))) * 100;
                    if (report_header == 0) {
                        out << '\n' << "         TEXT ANALYSIS REPORT" << '\n' << '\n' << '\n';
                        report_header = 1;
                    }
                    out << '\n' << "  User : " << User[index].username << '\n' << '\n';
                    out << '\n' << "    -> File number : " << nr_file << '\n';
                    out << '\n' << "    -> File name : " << file << '\n';
                    out << '\n' << "    -> Text : " << text_copy << '\n';
                    out << '\n' << "    -> Number of words in dictionary : " << word_cnt << '\n';
                    out << '\n' << "    -> Number of words in text : " << nr_words << " " << '\n';
                    out << '\n' << "    -> Mistaken words : " << mistaken_words << " " << '\n';
                    out << '\n' << "    -> Percentage of correctness : " << percentage << '%' << '\n';
                    out << '\n' << '\n' << '\n';

                    // Success
                    cout << '\n' << '\n';
                    cout << "   ";
                    SetConsoleTextAttribute(hConsole, 233);
                    cout << ">>> View the complete report in report.txt" << '\n' << '\n';
                    SetConsoleTextAttribute(hConsole, 47);
                    nr_file++;
                } else cout << '\n' << '\n' << '\n' << "           >>>  File not found or empty" << '\n' << '\n';

                cout << '\n' << '\n';
                cout << "   >>> Press 'y' and then ENTER to analyse another file";
                cout << '\n' << '\n';
                cout << "   >>> Press 'n' and then ENTER to log out";
                cin >> answer;
                cout << '\n' << '\n';

                cin.get();
                cout << '\n' << '\n' << '\n' << '\n';

                in.close();
            }
            cout << '\n' << '\n';
            cout << "   >>> Log out successful" << '\n' << '\n';

            // Free the allocated dynamic memory
            cout << '\n' << '\n' << '\n';
            cout << "   >>> APPLICATION REPORT : " << '\n' << '\n';
            if (unload_dictionary(hashtable))
                cout << "       -> Application succesful ... No memory leaks detected" << '\n' << '\n';
            else cout << "       -> Application error ... Memory leaks detected" << '\n' << '\n';

            char exit;
            cout << '\n' << '\n' << '\n' << "   >>> Press 'A' and then ENTER to exit ";
            cin >> exit;

            if (exit == 'a' || exit == 'A') return 0;
        }

        // Closing all file handlers
        out.close();
        load.close();
        f.close();

        char exit1;
        cout << '\n' << '\n' << '\n' << "   >>> Press 'A' and then ENTER to exit ";
        cin >> exit1;
        if (exit1 == 'a' || exit1 == 'A') return 0;
    } else cout << '\n' << '\n' << "Exit succesful !" << '\n' << '\n';

    out.close();
    load.close();
    f.close();

    return 0;
}
