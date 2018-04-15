#include <iostream>
#include <vector>
#include <algorithm>
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

    bool isReady;

    string name;
};

bool longestRemainingTime(Process p1, Process p2) {
    return p1.remainingTime < p2.remainingTime;
}

int globalTime;
vector<Process> input;
vector<Process> readyQueue;
vector<Process> finishedQueue;

/*
	Preemptive scheduling
		- execute process from readyqueue for one time unit
        - increment globalTime for one time unit
        - put that process back in readyqueue
        - execute next process from readyqueue
*/
void executeProcess()
{
    // sort ready queue by longest remaining time
    sort(readyQueue.begin(), readyQueue.end(), longestRemainingTime);
    // choose process with the most remaining time
    Process &current_process = readyQueue.front();
    // print statement for Gantt chart
    cout << globalTime << " " << current_process.name << " ";
    // execute process
    globalTime++;
    current_process.remainingTime--;
    /*
		Increment waiting time for all processes not being executed
			- Time complexity: 	O(n)
    */
    for(size_t i = 1; i < readyQueue.size(); i++) {
        readyQueue.at(i).waitingTime++;
    }

    if(current_process.remainingTime == 0) {
        current_process.completionTime = globalTime;
        current_process.turnAroundTime = globalTime - current_process.arrivalTime;
        finishedQueue.push_back(current_process);
        readyQueue.erase(readyQueue.begin() + 0);
    }
}

void printResults() {
    cout << "\nName\tA.T.\tB.T.\tC.T.\tR.T.\tT.A.T\n";
    for(Process p : finishedQueue) {
        cout << p.name << "\t";
        cout << p.arrivalTime << "\t";
        cout << p.burstTime << "\t";
        cout << p.completionTime << "\t";
        cout << p.responseTime << "\t";
        cout << p.turnAroundTime << "\t";
        cout << endl;
    }
}

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

        executeProcess();
    }

    cout << globalTime << endl;
    printResults();

    return 0;
}