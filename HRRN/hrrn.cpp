#include <iostream>
#include <vector>

using namespace std;

struct Process {
	int waitingTime,
		burstTime,
		arrivalTime,
		turnAroundTime,
		responseTime,
		completionTime;

	float responseRatio;
	bool isReady;

	string name;
};

void printFinishedQueue(const vector<Process>& finishedQueue) {
	cout << "Finished queue: ";
	for (Process p: finishedQueue) {
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
void executeProcess(int position, int& globalTime, vector<Process>& readyQueue, vector<Process>& finishedQueue) {
	readyQueue.at(position).responseTime = globalTime;
	globalTime += readyQueue.at(position).burstTime;
	readyQueue.at(position).completionTime = globalTime;
	readyQueue.at(position).turnAroundTime = globalTime - readyQueue.at(position).arrivalTime;

	/*
		Calculate waiting time for all processes not being executed
			- Time complexity: 	O(n)
	*/
	for(size_t i = 0; i < readyQueue.size(); i++) {
		if(i != position) {
			readyQueue.at(i).waitingTime = readyQueue.at(position).burstTime;
		}
	}

	finishedQueue.push_back(readyQueue.at(position));
	readyQueue.erase(readyQueue.begin() + position);
}

int main() {
	int globalTime;
	char choice;
	vector<Process> input;
	vector<Process> readyQueue;
	vector<Process> finishedQueue;

	Process tmp;
	do {
		cout << "\n New process";
		cout << "\n Enter process name(one word), arrival time, and burst time: ";
		cin >> tmp.name >> tmp.arrivalTime >> tmp.burstTime;
		tmp.isReady = false;
		input.push_back(tmp);

		cout << "\n Do you want to enter another process? (Y/N) : ";
		cin >> choice;
	} while(toupper(choice) == 'Y');

	globalTime = 0;
	while ( finishedQueue.size() != input.size() ) {
		/*
			Push process in readyQueue when they arrive
				Time Complexity:	O(n)
				Space Complexity:	O(1)
		*/
		for(Process& process: input) {
			if(process.arrivalTime <= globalTime && !process.isReady) {
				process.isReady = true;
				readyQueue.push_back(process);
			}			
		}

		if (readyQueue.size() == 1) {
			executeProcess(0, globalTime, readyQueue, finishedQueue);
		}
		else {
			/*
				Calculate response ratio of all processes in readyQueue
					Time Complexity: 	O(n)
					Space complexity: 	O(1)
			*/
			for (Process& process: readyQueue) {
				process.waitingTime = globalTime - process.arrivalTime;
				process.responseRatio = 1.0 + float(process.waitingTime) / float(process.burstTime);
			}

			float highestRatio = 1.0;
			int highestRatioIndex = 0;
			// search for process with highest responseRatio in readyQueue
			for(size_t i = 0; i < readyQueue.size(); i++) {
				if(readyQueue.at(i).responseRatio > highestRatio) {
					highestRatio = readyQueue.at(i).responseRatio;
					highestRatioIndex = i;
				}
			}
			executeProcess(highestRatioIndex, globalTime, readyQueue, finishedQueue);
		}
	}

	printFinishedQueue(finishedQueue);

	return 0;
}