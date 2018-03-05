#include <iostream>
#include <vector>

using namespace std;

struct Process
{
    int waitingTime,
        burstTime,
        arrivalTime,
        turnAroundTime,
        responseTime,
        completionTime,
        remainingTime;

    float responseRatio;
    bool isReady;

    string name;
};

// TODO: Change this to show preemptive scheduling
void printFinishedQueue(const vector<Process> &finishedQueue)
{
    cout << "Finished queue: ";
    for (Process p : finishedQueue)
    {
        cout << endl << p.name;
        cout << " " << p.arrivalTime;
        cout << " " << p.burstTime;
        cout << " " << p.responseTime;
        cout << " " << p.completionTime;
        cout << " " << p.turnAroundTime;
    }
}

/*
	Non-preemptive scheduling
		- add burst time to global time
		- assign completion time
		- compute turn around time
		- move process into finsished queue
*/
void executeProcess(int position)
{
    readyQueue.at(position).responseTime = globalTime;
    globalTime++;
    readyQueue.at(position).remainingTime--;

    if(readyQueue.at(position).remainingTime == 0) {
        readyQueue.at(position).completionTime = globalTime;
        readyQueue.at(position).turnAroundTime = globalTime - readyQueue.at(position).arrivalTime;
        finishedQueue.push_back(readyQueue.at(position));
        readyQueue.erase(readyQueue.begin() + position);
    }

    /*
		Calculate waiting time for all processes not being executed
			- Time complexity: 	O(n)
    */
	
    for (size_t i = 0; i < readyQueue.size(); i++)
    {
        if (i != position)
        {
            readyQueue.at(i).waitingTime = readyQueue.at(position).burstTime;
        }
    }
}

int globalTime;
vector<Process> input;
vector<Process> readyQueue;
vector<Process> finishedQueue;

int main()
{
    char choice;

    Process tmp;
    do
    {
        cout << "\n New process";
        cout << "\n Enter process name(one word), arrival time, and burst time: ";
        cin >> tmp.name >> tmp.arrivalTime >> tmp.burstTime;
        tmp.isReady = false;
        input.push_back(tmp);

        cout << "\n Do you want to enter another process? (Y/N) : ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    globalTime = 0;
    while (finishedQueue.size() != input.size())
    {
        /*
			Push process in readyQueue when they arrive
				Time Complexity:	O(n)
				Space Complexity:	O(1)
		*/
        for (Process &process : input)
        {
            if (process.arrivalTime <= globalTime && !process.isReady)
            {
                process.isReady = true;
                process.remainingTime = process.burstTime;
                readyQueue.push_back(process);
            }
        }

        int smallestRemainingTime = readyQueue.at(0).remainingTime,
            smallestRemainingTimeIndex = 0;

        for(size_t i = 0; i < readyQueue.size(); i++) {
            if(readyQueue.at(i).remainingTime < smallestRemainingTime) {
                smallestRemainingTime = readyQueue.at(i).remainingTime;
                smallestRemainingTimeIndex = i;
            }
        }

        executeProcess(smallestRemainingTimeIndex);
    }

    printFinishedQueue(finishedQueue);

    return 0;
}