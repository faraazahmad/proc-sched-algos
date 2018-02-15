#include <iostream>
#include <vector>

using namespace std;

struct Process {
	int waitingTime,
		burstTime,
		arrivalTime,
		turnAroundTime,
		responseTime;

	float responseRatio;

	string name;
};

void printFinishedQueue(const vector<Process>& finishedQueue) {
	cout << "Finished queue is: ";
	for (const Process& p: finishedQueue)
		cout << p.name << ", ";
	cout << "\b\b \n";
}

void executeProcess(int position, int& globalTime, vector<Process>& readyQueue, vector<Process>& finishedQueue) {
	globalTime += readyQueue.at(position).burstTime;
	readyQueue.at(position).responseTime = globalTime;
	finishedQueue.push_back(readyQueue.at(position));
	readyQueue.erase(readyQueue.begin() + position);
	printFinishedQueue(finishedQueue);
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
		input.push_back(tmp);

		cout << "\n Do you want to enter another process? (Y/N) : ";
		cin >> choice;
	} while(toupper(choice) == 'Y');

	cout << "\n\nDebugging\n\n";

	globalTime = 0;
	while (!input.empty()) {
		for (size_t i = 0; i < input.size(); i++) {
			if (input.at(i).arrivalTime <= globalTime) {
				readyQueue.push_back(input.at(i));
				cout << "Inserted process " << input.at(i).name << " in readyQueue\n";
				input.erase(input.begin() + i);
			}
		}

		if (readyQueue.size() == 1) {
			cout << "Executing process " << readyQueue.at(0).name << " from readyQueue\n";
			executeProcess(0, globalTime, readyQueue, finishedQueue);
		}
		else {
			//  calculate response ratio of all processes in readyQueue
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
			cout << "Executing process " << readyQueue.at(highestRatioIndex).name << " with highest response ratio of " << highestRatio << " from readyQueue\n";
			executeProcess(highestRatioIndex, globalTime, readyQueue, finishedQueue);
		}
	}

	for(Process& process: finishedQueue) {
		cout << process.name << " ";
		cout << process.arrivalTime << " ";
		cout << process.burstTime << " ";
		cout << process.responseTime << endl;
	}

	return 0;
}