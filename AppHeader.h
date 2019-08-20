#ifndef APPHEADER_H_INCLUDED
#define APPHEADER_H_INCLUDED


#define SIZE 26   /// dimensiuhne tabel
#define max_words 10000  /// dimensiune maxima text
#define LENGTH 45 /// dimensiune maxima cuvant
#define no_accounts 6 /// Nr. conturi

#include <conio.h>
#include <stdio.h>


struct node
{
    char word[46];
    node *next;
};

class List
{

   public:

    node *head;

    List();
    ~List();

    int get_List_Index(char *word);
    void Create();
    void Delete();
    void Insert_Node(char *word);
    void Out();
};

List::List(void)
{
    //std::cout << "New object has been created..." << '\n';
}

List::~List(void)
{
    //std::cout << "Object has been deleted" << '\n';
}

void List::Create()
{
    head = NULL;
}

void List::Delete()
{
    node *index = head;

    while(index != NULL)
    {
        node *aux = index;
        index = index->next;
        delete(aux);
    }
}

int List::get_List_Index(char *word)
{
    node *index = head;
    while(index != NULL)
    {
        if(strcmp(index->word, word) == 0)return 1;
        index = index->next;
    }

    return 0;
}

void List::Insert_Node(char *word)
{
    node *new_node = new node;
    strcpy(new_node->word, word);

    new_node->next = head;
    head = new_node;

}


struct Account
{
    char username[20];
    char password[10];
}User[no_accounts];


   /// PROTOTIPURI

bool unload_dictionary(List table[]);
void initialize(List table[]);
unsigned int Hash(char c);
void Intro();
void Log_window(bool &k);





   /// Definitiile subprogramelor

void Intro()
{
    for(int i = 0; i < 10; i++) std::cout << '\n';
    for(int j = 0; j < 30; j++) std::cout << " ";

    int consoleWidth = 50;

    std::cout << std::setw(consoleWidth / 2) << "MISTAKEN WORD FINDER" << '\n' << '\n' << '\n';
    for(int j = 0; j < 35 ; j++) std::cout << " ";
    std::cout << std::setw(3*consoleWidth / 8) << "WELCOME !!!" << '\n' << '\n' << '\n';

    std::cout << "         >>>  " << "Press 'E' and then ENTER to log in" << '\n';
    std::cout << "         >>>  " << "Press other key and then ENTER to exit" << '\n' << '\n' << '\n';
}

 void Log_window(bool &k,int &index)
{
    int ok = 2, flag = 0, k1 = 0, user_attempts_remaining = 3, password_attempts_remaining = 3;
    char u[20],p[10];

    while(ok != 1 && user_attempts_remaining > 0)
    {
        std::cout <<  "   Username :  "; std::cin.get(u, 20); std::cin.get();

        for(int i = 0; i < no_accounts; i++)
            if(strcmp(u, User[i].username) == 0)
            {
                flag = 1;
                ok--;
                index = i;
                break;
            }

        user_attempts_remaining --;
        if(flag != 1) std::cout << "   Invalid username ... Attempts remaining : " << user_attempts_remaining << '\n';

    }


    if(ok == 1)
    {
        while(ok != 0 && password_attempts_remaining > 0)
        {
            std::cout <<  "   Password :  ";
            while((p[k1] = getch()) != '\r')
            {
                if(p[k1] != 0x08)
                {
                    std::cout << '*';
                    k1++;
                }
                else{
                    k1--;
                    std::cout <<"\b \b";
                }
            }
            p[k1]= '\0';

            password_attempts_remaining --;

            if(strcmp(p ,User[index].password) == 0)ok--;
            else
            {
                std::cout << "   Wrong password ... Attempts remaining : " << password_attempts_remaining << '\n';
                k1 = 0;
            }

        }
    }

    if(ok == 0)
    {
        std::cout << '\n' << '\n' << '\n' << '\n' << "   Log in succesful !!" << '\n' << '\n';
        std::cout << "   Welcome " << User[index].username << " !" << '\n' <<'\n' << '\n' << '\n';
        k = true;
    }
    else{
        std::cout <<'\n' << "   Failed to log in" << '\n' << '\n';
        k = false;
    }

}


bool unload_dictionary(List table[])
{
    int err = SIZE;
    for(int i = 0; i < SIZE; i++)
    {
        table[i].Delete();
        err --;
    }

    if(err == 0) return true;

    return false;
}


void initialize(List table[])
{
    for(int i = 0; i < 26; i++)
        table[i].Create();
}



unsigned int Hash(char c)
{
    switch (c)
    {
        case 'a':
        case 'A':
            return 0;
        case 'b':
        case 'B':
            return 1;
        case 'c':
        case 'C':
            return 2;
        case 'd':
        case 'D':
            return 3;
        case 'e':
        case 'E':
            return 4;
        case 'f':
        case 'F':
            return 5;
        case 'g':
        case 'G':
            return 6;
        case 'h':
        case 'H':
            return 7;
        case 'i':
        case 'I':
            return 8;
        case 'j':
        case 'J':
            return 9;
        case 'k':
        case 'K':
            return 10;
        case 'l':
        case 'L':
            return 11;
        case 'm':
        case 'M':
            return 12;
        case 'n':
        case 'N':
            return 13;
        case 'o':
        case 'O':
            return 14;
        case 'p':
        case 'P':
            return 15;
        case 'q':
        case 'Q':
            return 16;
        case 'r':
        case 'R':
            return 17;
        case 's':
        case 'S':
            return 18;
        case 't':
        case 'T':
            return 19;
        case 'u':
        case 'U':
            return 20;
        case 'v':
        case 'V':
            return 21;
        case 'w':
        case 'W':
            return 22;
        case 'x':
        case 'X':
            return 23;
        case 'y':
        case 'Y':
            return 24;
        case 'z':
        case 'Z':
            return 25;

        default: return -1;
    }
}



#endif // APPHEADER_H_INCLUDED
