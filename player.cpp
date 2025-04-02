#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
//using fstream lib which require char array for compatibility not the string
using namespace std;

struct node
{
    string song;
    struct node *next;
    struct node *prev;
}*top,*temp,*top1;

// Playlist structure
struct Playlist {
    string name;  // Stores the playlist name
    node* head;   // Points to the first song in the list
    Playlist(string pname) : name(pname), head(nullptr) {}
};

Playlist* createPlaylist() {
    string pname;
    cout << "Enter your playlist name: ";
    getline(cin, pname);

    Playlist* myPlaylist = new Playlist(pname);  // Create a playlist
    cout << "Playlist '" << myPlaylist->name << "' created successfully!\n";
    return myPlaylist;
}

// Pointer->	Purpose
// top->	Points to the top of a stack used for recently played songs.
// temp	->  A temporary pointer used for operations (like adding/deleting nodes).
// top1	->  Used for traversing the recently played song list.mtlb stack ko traverse karne ke liye
// void tofile(string song)
// {
//     ofstream f1;  ///append mode
//     f1.open("playlist.txt");
//     f1<<song<<endl;
//     f1.close();
// }

void tofile(const string& song_name) {
    ofstream file("playlist.txt", ios::app); // Open in append mode
    if (!file) {  // Check if file opened successfully
        cout << "Error: Unable to open playlist file.\n";
        return;
    }
    file << song_name << endl;
    file.close();
    cout << "DEBUG: Song written to file -> " << song_name << endl;
}



// void add_node(struct node *first){

//     while (first->next != nullptr) {
//         first = first->next;
//     }

//     // Allocate new node using `new` instead of `malloc`
//     node * newsong=new node();
//     string song;
//     cout << "\nEnter Song name: ";
//     cin.ignore();

//     // When you use std::cin >> to take input, it leaves a newline character (\n) in the input buffer. If you then use std::getline(std::cin, str_variable);, it immediately stops reading because it sees the leftover \n.

//     getline(cin, song);  // Read full song name
//     newsong->song = song;
//     newsong->next=nullptr; 
//     first->next = newsong;
//     newsong->prev=first;
    

//     tofile(song);  // Save song to file

//     // first->next = nullptr;
// }

void add_node(struct node *&start) {
    string song_name;
    cout << "\nEnter Song Name: ";
    cin.ignore();  // Clear input buffer
    getline(cin, song_name);  // Take full song name with spaces

    struct node *new_song = new node();
    new_song->song = song_name;
    new_song->next = nullptr;

    if (start == nullptr) {  // If list is empty, make new_song the start
        start = new_song;
    } else {
        struct node *temp = start;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_song;
        new_song->prev = temp;
    }
    tofile(song_name);
    cout << "Song added successfully!\n";
}


void add_node_file(struct node *first,string a)
    {
    while(first->next!=NULL)
    {
        first=first->next;
    }
    first->next=new node();
    first->prev=first;
    first=first->next;
    first->song = a;
    // strcpy(first->song,a.c_str());
    first->next=NULL;
}

void delete_file(string song)
{
    ifstream f1;
    ofstream f2;
    string line;
    f1.open("playlist.txt");
    // ,ios::in|ios::out   ---> use with fstream for read and write simultaneously
    f2.open("temp.txt");
    if(!f1 || !f2) {  // Check if files opened successfully
        cout<< "Error opening files!" <<endl;
        return;
    }

    bool found = false;

    while (getline(f1, line)) {
        if (line != song) {
            f2 << line << endl;  // Copy other songs
        } 
        else {
            found = true;  // Song found and skipped
        }
    }

    f1.close();
    f2.close();

    if (found) {
        remove("playlist.txt");
        rename("temp.txt", "playlist.txt");
        cout << "Song has been deleted." << endl;
    } 
    else {
        remove("temp.txt");  // Clean up
        cout << "There is no song with the name you entered." << endl;
    }
}


void del_node(struct node *first)
{   // for deleting last song isme last node ko delete kar rahe hai
    if(first==nullptr){
        cout<<"\nPlaylist is empty\n";
        return;
    }
    else if(first->next==nullptr){
        delete first;
        cout<<"\nDeleted Last Song\n";
        return;
    }
    while((first->next)->next!=NULL)
    {
        first=first->next;
    }

    struct node *temp;
    temp=(first->next)->next;
    first->next=NULL;
    delete temp;
    cout<<"Deleted"<<endl;
}

void printlist(struct node *first)
{   
    // the parameter first is passed by value, but since it is a pointer (struct node *first), it allows modifying the data it points to.
    cout<<"\nPlaylist Name- ";
    while(first->next!=NULL)
    {
        cout<<first->song<<endl;
        first=first->next;
    }
    cout<<first->song<<endl;
}

int count_nodes(struct node *first)
{   // to count total songs
    int i=0;
    while (first->next!=NULL)
    {
        first=first->next;
        i++;
    }
    i++;
    cout<<"\nTotal songs-  "<<i<<endl;
    return i;
}


// struct node *del_pos(struct node *pointer, int pos)
// {
//            struct node *prev1,*temp;
//            prev1=new struct node;
//            if (pointer == nullptr) {
//             cout << "List is empty.\n";
//             return nullptr;
//             }
//            int tot_song= count_nodes(pointer);
//            if(pos>tot_song){
//                 cout<<"\nInvalid position\n";
//                 return pointer;
//             }
//            else if(pos==1)
//            {    
//                 struct node*temp=pointer;
//                 delete_file(temp->song);  //song ko file se delete kar diya

//                 pointer=pointer->next;
//                 if (pointer != nullptr)
//                     pointer->prev = nullptr;
//                 delete temp;
//                 cout<<"\nThe list is updated\nUse the display function to check"<<endl;
//                 return pointer;
//            }
//            else if(pos==tot_song){
//                 //last song
//                 struct node *new_first=pointer;
//                 while (pointer->next != nullptr) {
//                     pointer = pointer->next;
//                 }
                
//                 delete_file(pointer->song); // Remove from file
            
//                 if (pointer->prev != nullptr) {
//                     pointer->prev->next = nullptr; // Unlink last node from the list
//                 }
            
//                 delete pointer; // Free memory
            
//                 pointer = nullptr; // Avoid dangling pointer
//                 return new_first;   // Return pointer
//            }
//            else{
//                 // any middle position;
//                 struct node *new_first=pointer;
//                 int i=1;
//                 while(i<pos && pointer!=nullptr){
//                     pointer=pointer->next;
//                     i++;
//                 }
//                 delete_file(pointer->song);
//                 pointer->prev->next=pointer->next;
//                 pointer->next->prev=pointer->prev;
//                 delete pointer;
//                 cout<<"\nThe list is updated\nUse the display function to check\n";
//                 return new_first;
                
//            }
           
// }

struct node *del_pos(struct node *pointer, int pos)
{
    if (pointer == nullptr) {
        cout << "List is empty.\n";
        return nullptr;
    }

    int tot_song = count_nodes(pointer);
    if (pos > tot_song || pos < 1) {
        cout << "\nInvalid position\n";
        return pointer;
    }

    struct node *temp = pointer;

    // Case 1: Deleting the first node
    if (pos == 1)
    {    
        delete_file(temp->song);  
        pointer = pointer->next;
        if (pointer != nullptr)
            pointer->prev = nullptr;
        delete temp;
        cout<<"\nThe list is updated. Use the display function to check."<<endl;
        return pointer;
    }

    // Traverse to the node to be deleted
    for (int i = 1; temp != nullptr && i < pos; i++)
    {
        temp = temp->next;
    }

    // Case 2: Deleting the last node
    if (temp->next == nullptr)
    {
        delete_file(temp->song);
        temp->prev->next = nullptr;
        delete temp;
        cout<<"\nThe list is updated. Use the display function to check."<<endl;
        return pointer;
    }

    // Case 3: Deleting a middle node
    delete_file(temp->song);
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;

    cout<<"\nThe list is updated. Use the display function to check."<<endl;
    return pointer;
}

void search1(struct node *first)
{
    string song;
    cout<<"\n\a\a\a\aEnter song To be Searched- ";
    cin.ignore();
    getline(cin, song);  // Allows spaces in input
    int flag=0;

    while(first!=nullptr)
    {
        if(first->song==song)
        {
            cout<<"\n\a\a\a\a#Song Found"<<endl;
            flag++;
            break;
        }
        else
        {
            first=first->next;
        }
    }
    
    if(flag==0)
    {
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }
}

void create()
{
    top = NULL;
}

void push(string data)
{   //top is maintained as stack
    if (top == nullptr)
    {
        top =new node();
        top->next = nullptr;
        // strcpy(top->song,data);
        top->song=data;
    }
    else if (top->song!=data)
    {
        temp =new node();
        temp->next = top;
        temp->song=data;
        top = temp;
    }
}

void display()
{   //dispaying all recent playback
    top1 = top;
    if (top1 == NULL)
    {
        cout<<"\n...NO recently played tracks..."<<endl;
        return;
    }
    cout<<"\nRecently played tracks-\n";
    while (top1 != NULL)
    {
        cout<<top1->song<<endl;
        top1 = top1->next;
    }
 }
void recent(){
    display();
}

void play(struct node *first)
{
    string song;
    printlist(first);
    cout<<"\n\a\a\a\aChoose song you wish to play- ";
    cin.ignore();
    getline(cin, song);  // Allows spaces in input
    bool flag=0;

    while(first!=nullptr)
    {
        if(first->song==song)
        {
            cout<<"\n\a\a\a\a=>Now Playing......"<<song<<endl;
            flag=1;
            push(song);
            break;
        }
        else
        {
            first=first->next;
        }
    }
    if(flag==0)
    {
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }
}



void topelement()
{
    
    if(top==NULL)
    {
        cout<<"\n\a\a\a\a#NO last played tracks.\n";
        return;
    }
    cout<<"\n=>Last Played Song - "<<top->song<<endl;
}


// void sort( node *&pointer)
// {

// struct node *a = NULL;
// struct node *b = NULL;
// struct node *c = NULL;
// struct node *e = NULL;
// struct node *tmp = NULL;
// while(e != pointer->next)
// {
//     c = a = pointer;
//     b = a->next;
//     while(a != e)
//         {
//             if(strcmp(a->song,a->song))
//             {
//                 if(a == pointer)
//                 {
//                     tmp = b -> next;
//                     b->next = a;
//                     a->next = tmp;
//                     pointer = b;
//                     c = b;
//                 }
//             else
//             {
//                 tmp = b->next;
//                 b->next = a;
//                 a->next = tmp;
//                 c->next = b;
//                 c = b;
//             }
//         }
//         else
//         {
//             c = a;
//             a = a->next;
//         }
//         b = a->next;
//         if(b == e)
//             e = a;
//         }
//     }
// }
void addplaylist(struct node *start)
{
    ifstream f1;
    f1.open("playlist.txt");       //This line opens the file "playlist.txt" in read mode (ios::in) using an fstream object (f1).
    if (!f1) {  // Check if the file exists or can be opened
        cout << "Error: Unable to open playlist.txt" << endl;
        return;
    }

    string line;
    while (getline(f1, line))  // Reads line only if valid
    {
        add_node_file(start, line); // Adds song to the linked list
    }
    cout<<"Playback added successfully enjoy the music"<<endl;
    
    
}

void del_search(struct node *&start)
{
    
    if(count_nodes(start) == 0){
        cout<<"\n...No songs in the playlist..."<<endl;
        return;
    }

    string song;
    printlist(start);
    cout<<"\nChoose song you wish to delete: ";
    cin.ignore();
    getline(cin, song);  // Allows spaces in input

    struct node *ptr = start;
    int pos = 1;
    while(ptr != nullptr)
    {
        if(ptr->song == song)
        {
            cout<<"\n#Song Found"<<endl;
            start = del_pos(start, pos);  // Correctly update head pointer
            return; // Exit after deletion
        }
        ptr = ptr->next;
        pos++;
    }
    cout<<"\n#Song Not Found"<<endl;
}



void deletemenu(struct node *&start)
{
    int c;
    cout<<"Which type of delete do you want?\n1.By Search\n2.By Position"<<endl;
    cin>>c;
    if(c==1){
        del_search(start);
    }
    else{
        int pos=0;
        cin>>pos;
        start=del_pos(start, pos);
    }
    
}

main()
{
    int choice=0;
    string song="";
    struct node *start,*hold;
    start=new node();
    cout<<"**Welcome to Our Music Player**"<<endl<<endl;
    cout<<"*******Follow the guideline for smooth playback *******"<<endl<<endl;
    cout<<"***please use '_' for space.***"<<endl<<endl;
    cout<<"Enter your playlist name-  ";
    cin.ignore();
    getline(cin,start->song);
    start->next=nullptr;
    hold=start;
    create();
    int playlist_count=0;
    
    // do{
    //     cout<<"\nChoose an option to play"<<endl;
    //     cout<<"1.Choose a playlist.  2.Create a new playlist."<<endl;
    //     cin>>playlist_count;

        
    // }
    do{
        cout<<"\n1.Add  New Song\n2.Delete Song\n3.Display Entered Playlist\n4.Total Songs\n5.Search Song\n6.Play Song\n7.Recently Played List\n8.Last Played\n9.Add From File\n10.Exit"<<endl;
        cout<<("\n\a\a\a\aEnter your choice- ");
        cin>>choice;
        
        switch(choice)
        {
            case 1:add_node(start);
            break;
            case 2:deletemenu(start);
            break;
            case 3:printlist(start);
            break;
            case 4:count_nodes(hold);
            break;
            case 5:search1(start);
            break;
            case 6:play(start);
            break;
            case 7:recent();
            break;
            case 8:topelement();
            break;
            case 9:addplaylist(start);
            break;
            case 10:exit(0);
        }
    }while(choice!=10);

    
}