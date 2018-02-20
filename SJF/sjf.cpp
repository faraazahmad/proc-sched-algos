#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int arrivalTime,
        burstTime,
        turnAroundTime,
        completionTime,
        responseTime;
    
    bool isReady;

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
    for(Process& process: finishedQueue) {
        cout << "\n " << process.name;
        cout << " " << process.arrivalTime;
        cout << " " << process.burstTime;
        cout << " " << process.completionTime;
    }
}

int main() {
    vector<Process> input;
    Process tmp;
    char choice;

    do {
        cout << "\n Enter name, arrival time and burst time of process: ";
        cin >> tmp.name >> tmp.arrivalTime >> tmp.burstTime;
        tmp.isReady = false;
        input.push_back(tmp);

        cout << "\n Do you want to input another process? (Y/N): ";
        cin >> choice;
    } while(toupper(choice) == 'Y');

    while( finishedQueue.size() != input.size() ) {

        /*
            push processes in the readyqueue when they arrive
                Time complexity: O(n)
                Space Complexity: O(1)
        */
        for(Process& process: input) {
            if(process.arrivalTime <= globalTime && !process.isReady) {
                process.isReady = true;
                readyQueue.push_back(process);
            }
        }

        /*
            Search for process with shortest burst time
            Time complexity: O(n)
            Space Complexity: O(1)
        */
        int shortestBurstTime = readyQueue.at(0).burstTime, shortestBurstTimeIndex = 0;
        for (size_t i = 1; i < readyQueue.size(); i++)
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

    cout << endl << "Finished Queue";
    printFinishedQueue();

    return 0;
}