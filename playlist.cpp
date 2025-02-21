#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

using namespace std;

typedef struct node
{
    char song[100];
    node *fwd;
    node *bwd;
} node;

node *top;
node *temp;
node *top1;
node *ptr;
node *start;

class Playlist
{
public:
    Playlist()
    {
        top = NULL;
    }
    void addNode(node *);
    void deleteNode(node *);
    void countNodes(node *);
    void searchSong(node *);
    void push(char *);
    void display();
    void play(node *);
    void recent();
    void topElement();
    void addPlaylist(node *);
    void deleteMenu(node *);
};


void Playlist ::addNode(node *ptr)
{
    char a[100];
    while (ptr->fwd != NULL)
    {
        ptr = ptr->fwd;
    }
    ptr->fwd = new node;
    ptr->bwd = ptr;
    ptr = ptr->fwd;
    cout << "\nEnter Song name-  ";
    cin >> ws;
    cin.getline(a, 100);
    strcpy(ptr->song, a);
    ptr->fwd = NULL;
}

void printPlaylist(node *ptr)
{
    cout << "\nPlaylist Name- ";
    while (ptr->fwd != NULL)
    {
        cout << ptr->song << endl;
        ptr = ptr->fwd;
    }
    cout << ptr->song;
}

void Playlist ::countNodes(node *ptr)
{
    int i = 0;
    while (ptr->fwd != NULL)
    {
        ptr = ptr->fwd;
        i++;
    }
    i++;
    cout << "\nTotal songs-  " << i - 1 << endl;
    /*int count = 0;
    temp = ptr;
    while(temp != NULL)
    {
            temp = temp -> fwd;
            count++;
    }
    return count - 1;*/
}

node *deletePos(node *pointer, int pos)
{

    node *n1, *bwd1, *temp;
    bwd1 = new node;
    temp = new node;
    int i = 0;
    if (pos == 1)
    {
        temp = pointer;
        pointer = pointer->fwd;
        pointer->bwd = NULL;
        delete temp;
        cout << "\nThe list is updated\nUse the display function to check\n";
        return pointer;
    }
    while (i < pos - 1)
    {
        bwd1 = pointer;
        pointer = pointer->fwd;
        i++;
    }
    if (pointer->fwd == NULL)
    {
        temp = pointer;
        bwd1->fwd->bwd = NULL;
        bwd1->fwd = NULL;
        delete temp;
        cout << "\nThe list is updated\nUse the display function to check\n";
    }
    else
    {
        temp = pointer;
        bwd1->fwd = temp->fwd;
        temp->fwd->bwd = bwd1;
        delete temp;
        cout << "\nThe list is updated\nUse the display function to check\n" << endl;
    }
}

void Playlist ::searchSong(node *ptr)
{
    char song[100];
    cout << "\n\a\a\a\aEnter song To be Searched- ";
    cin >> ws;
    cin >> song;
    int flag = 0;
    while (ptr != NULL)
    {
        if (strcmp(ptr->song, song) == 0)
        {
            cout << "\n\a\a\a\a#Song Found" << endl;
            flag++;
            break;
        }
        else
        {
            ptr = ptr->fwd;
        }
    }
    if (flag == 0)
    {
        cout << "\n\a\a\a\a#Song Not found" << endl;
    }
}

void Playlist ::push(char data[])
{
    if (top == NULL)
    {
        top = new node;
        top->fwd = NULL;
        strcpy(top->song, data);
    }
    else if (strcmp(top->song, data) != 0)
    {
        temp = new node;
        temp->fwd = top;
        strcpy(temp->song, data);
        top = temp;
    }
}

void Playlist ::display()
{
    top1 = top;
    if (top1 == NULL)
    {
        cout << "\n\a\a\a\a=>NO recently played tracks.\n";
        return;
    }
    cout << "\n\a\a\a\a#Recently played tracks-\n";
    while (top1 != NULL)
    {
        cout << top1->song << endl;
        top1 = top1->fwd;
    }
}

void Playlist ::play(node *ptr)
{
    char song[100];
    printPlaylist(ptr);
    cout << "\n\a\a\a\aChoose song you wish to play- ";
    cin >> ws;
    cin >> song;
    int flag = 0;
    while (ptr != NULL)
    {
        if (strcmp(ptr->song, song) == 0)
        {
            cout << "\n\a\a\a\a=>Now Playing......" << song << endl;
            flag++;
            push(song);
            break;
        }
        else
        {
            ptr = ptr->fwd;
        }
    }
    if (flag == 0)
    {
        cout << "\n\a\a\a\a#Song Not found" << endl;
    }
}

void Playlist ::recent()
{
    display();
}

void Playlist ::topElement()
{
    top1 = top;
    if (top1 == NULL)
    {
        cout << "\n\a\a\a\a#NO last played tracks.\n";
        return;
    }
    cout << "\n=>Last Played Song - " << top->song << endl;
}

void deleteSearch(node *start)
{
    char usersong[100];
    printPlaylist(start);
    cout << "\nChoose song you wish to delete- ";
    cin >> ws;
    cin.getline(usersong, 100);
    int flag = 0;
    while (start != NULL)
    {
        if (strcmp(start->song, usersong) == 0)
        {
            cout << "\n\a\a\a\a#Song Found" << endl;
            // node *temp;
            //                      node* temp1 = new node;
            //                     temp1 = start;
            if (start->fwd == NULL)
            {
                //                              cout < "ffffffffffff";
                //                              start = start -> fwd;
                //                              start -> fwd = NULL;
                delete start;
                //                              return;
                flag++;
                break;
            }
            // deleteFile(temp -> song);
            start->bwd->fwd = start->fwd;
            start->fwd->bwd = start->bwd;
            delete start;
            flag++;
            break;
        }
        else
        {
            start = start->fwd;
        }
    }
    if (flag == 0)
    {
        cout << "\n\a\a\a\a#Song Not found" << endl;
    }
}

void Playlist ::deleteMenu(node *start)
{
    int ch;
    cout << "Which way do you wish to delete?\n1.By Song Name\n2.By Position" << endl;
    cin >> ch;
    switch (ch)
    {
    case 1:
        deleteSearch(start);
        break;
    case 2:
        int pos;
        cout << "\nEnter the pos of the song : ";
        cin >> pos;
        deletePos(start, pos - 1);
        break;
    }
}

int main()
{
    int choice, loc;
    char song[100];
    node *start;
    node *temp;
    Playlist obj;
    start = new node;
    cout << "\t\t\t\t\t**PLAYLIST CREATOR**" << endl;
    cout << "Enter your playlist name-  ";
    cin >> ws;
    cin.getline(start->song, 100);
    start->fwd = NULL;
    temp = start;
    // obj.create();
    do
    {
        cout << "\n1. To add a new song\n2. To delete a song\n3. To Display Entered Playlist\n4.To display the total number of songs\n5.To Search for a Song\n6.To play a song\n7.Recent song";
        cout
             << "\nEnter your choice- ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            obj.addNode(start);
            break;
        case 2:
            deleteSearch(start);
            break;
        case 3:
            printPlaylist(start);
            break;
        case 4:
            obj.countNodes(start);
            break;
        case 5:
            obj.searchSong(start);
            break;
        case 6:
            obj.play(start);
            break;
        case 7:
            obj.recent();
            break;
        case 8:
            obj.topElement();
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid choice from 1-11." << endl;
        }
    } while (choice != 11);
}
