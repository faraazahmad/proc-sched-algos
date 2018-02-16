#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int arrivalTime,
        burstTime,
        turnAroundTime,
        completionTime,
        responseTime;
    
    string name;
};

int globalTime = 0;
vector<Process> readyQueue,
                finishedQueue;

void executeProcess(int readyQueueIndex) {
    globalTime += readyQueue.at(readyQueueIndex).burstTime;
    readyQueue.at(readyQueueIndex).completionTime = globalTime;
    finishedQueue.push_back(readyQueue.at(readyQueueIndex));
    readyQueue.erase(readyQueue.begin() + readyQueueIndex);
}

void printFinishedQueue() {
    for(int i = 0; i < finishedQueue.size(); i++) {
        cout << "\n " << finishedQueue.at(i).name;
        cout << " " << finishedQueue.at(i).arrivalTime;
        cout << " " << finishedQueue.at(i).burstTime;
        cout << " " << finishedQueue.at(i).completionTime;
    }
}

void printReadyQueue() {
    for (int i = 0; i < readyQueue.size(); i++)
    {
        cout << "\n " << readyQueue.at(i).name;
        cout << " " << readyQueue.at(i).arrivalTime;
        cout << " " << readyQueue.at(i).burstTime;
    }
    cout << endl;
}

int main() {
    vector<Process> input;
    Process tmp;
    char choice;
    int numProcesses;

    do {
        cout << "\n Enter name, arrival time and burst time of process: ";
        cin >> tmp.name >> tmp.arrivalTime >> tmp.burstTime;
        input.push_back(tmp);

        cout << "\n Do you want to input another process? (Y/N): ";
        cin >> choice;
    } while(toupper(choice) == 'Y');
    numProcesses = input.size();

    while( finishedQueue.size() != numProcesses ) {

        /*
            push processes in the readyqueue when they arrive
                Time complexity: O(n)
                Space Complexity: O(1)
        */
        for (int i = 0; i < input.size(); i++)
        {
            if (input.at(i).arrivalTime <= globalTime)
            {
                readyQueue.push_back(input.at(i));
                input.erase(input.begin() + i);
            }
        }

        cout << "\n Global Time = " << globalTime;
        printReadyQueue();

        /*
            search for process with shortest burst time
            Time complexity: O(n)
            Space Complexity: O(1)
        */
        int shortestBurstTime = readyQueue.at(0).burstTime, shortestBurstTimeIndex = 0;
        for (int i = 0; i < readyQueue.size(); i++)
        {
            if (readyQueue.at(i).burstTime < shortestBurstTime)
            {
                shortestBurstTime = readyQueue.at(i).burstTime;
                shortestBurstTimeIndex = i;
            }
        }

        // execute the shortest Job
        executeProcess(shortestBurstTimeIndex);
    }

    cout << endl << "Finished Queue" << endl;
    printFinishedQueue();

    return 0;
}