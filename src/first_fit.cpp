#include <iostream>
#include <vector>
using namespace std;

struct Process {
    string name;
    int memory;
    size_t assignedTo;
    bool isAssigned;
};
vector<Process> input;

struct MemoryBlock {
    int size;
    bool used;
};
vector<MemoryBlock> memory;

void firstFit() {
    for(Process &proc: input) {
        for(size_t j = 0; j < memory.size(); j++) {
            if(proc.memory <= memory.at(j).size && !memory.at(j).used) {
                proc.isAssigned = true;
                proc.assignedTo = j;
                memory.at(j).used = true;
                break;
            }
        }
    }
}

void printResult() {
    cout << "process\tsize\tblock\tfragmentation\n";
    for(Process proc: input) {
        cout << proc.name << "\t" << proc.memory << "\t";
        if(proc.isAssigned) {
                cout << memory.at(proc.assignedTo).size << "\t" <<
                memory.at(proc.assignedTo).size - proc.memory << endl;
        }
        else {
            cout << "N/A\tN/A\n";
        }
    }
}

int main() {
    char choice;

    // Enter available blocks in memory
    cout << "Enter available memory blocks\n";
    MemoryBlock memTmp;
    do {
        cout << "Enter size of memory block: ";
        cin >>  memTmp.size;
        memTmp.used = false;
        memory.push_back(memTmp);
        cout << "Do you want to insert another memory block? (Y/N): ";
        cin >> choice;
    } while(toupper(choice) == 'Y');
    
    // Enter processes
    cout << "\n Enter processes to assign to memory\n";
    Process tmp;
    do {
        cout << "Enter process name and memory required: ";
        cin >> tmp.name >> tmp.memory;
        tmp.isAssigned = false;
        input.push_back(tmp);

        cout << "Do you want to enter another process? (Y/N): ";
        cin >> choice;
    } while(toupper(choice) == 'Y');

    // execute first fit algo
    firstFit();

    // print the results
    printResult();

    return 0;
}
