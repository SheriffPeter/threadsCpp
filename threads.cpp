/**
*
*   @file threads.cpp
*   @author SheriffPeter
*
*   @brief small program to start working with threads and condition variable
*
*   @detail This program is gonna create threads on demand. The user will have a menu
*           to interact with the program (create, say hello thread x, kill thread, ...). 
*           This will be done by using threads and condition variable. Note to use 
*           notify_one, notify_all
***/
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include <map>
#include <mutex>
#include <condition_variable>

using namespace std;

enum entryValues {
    QUIT,
    CREATE,
    STOP,
    DEFAULT // Every other choice
};

static mutex myMutex;
static condition_variable myCv; 

static map<string,entryValues> mapEntryValues {
    {"quit", QUIT},
    {"create", CREATE},
    {"stop", STOP}
};

void sayHello(string name, int value)
{
    unique_lock<mutex> lk(myMutex);
    // TODO: implémenter un timeout avec une condition variable pour arrêter le thread
    while(myCv.wait_for(lk, 5000ms) == cv_status::timeout)
    {
    cout << "Hello world " << name << " " << value << endl;

    }
    cout << "Stopping " << name << " " << value << endl;
}

void initializeMapEntryValues()
{
    // On the line work
    
}

int main(int argc, char** argv)
{
    // Thread are started as soons as they are created.
    thread t, t1, t2;

    uint threadCpt = 0;
    
    string entry = "";
    while(entry != "quit")
    {
        cout << "What is it you wanna do?" << endl;
        cin >> entry;
        transform(entry.begin(), entry.end(),entry.begin(), ::tolower);

        switch(mapEntryValues[entry])
        {
            case QUIT:
                myCv.notify_all();
            break;
            case CREATE:
                t = thread(sayHello, "mon piti thread", threadCpt++);
            break;
            case STOP:
                myCv.notify_one();
                t.join();
            break;
            default:
                cout << "Try again bouseux" << endl;   
            break;         
        }


    }

    t.join();
    t1.join();
    t2.join();

    return 0;
}