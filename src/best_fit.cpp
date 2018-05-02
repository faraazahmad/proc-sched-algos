#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    string name;
    int memory;
    size_t assignedTo;
    bool isAssigned;
};
vector<Process> input;

struct MemoryBlock
{
    int size;
    bool used;
};
vector<MemoryBlock> memory;

void bestFit()
{
  	/*
    	Get the smallest memory block that fits
  	*/
  	size_t smallestIndex;
  	for(Process& proc : input) {
  		// intitalise smallestIndex with the first memory
  		// block that fits
  		for(size_t j = 0; j < memory.size(); j++) {
  			if(memory.at(j).size >= proc.memory && !memory.at(j).used) {
  				smallestIndex = j;
  				break;
  			}
  		}

  		// find the smallest block
    	for(size_t j = 0; j < memory.size(); j++) {
    		if (memory.at(j).size < memory.at(smallestIndex).size 
    			&& !memory.at(j).used
    			&& memory.at(j).size >= proc.memory)
    				smallestIndex = j;
    	}

    	// assign the process to the smallest block
    	proc.isAssigned = true;
    	proc.assignedTo = memory.at(smallestIndex).size;
    	memory.at(smallestIndex).used = true;
  	}
}

void printResult()
{
    cout << "process\tsize\tblock\tfragmentation\n";
    for (Process proc : input)
    {
        cout << proc.name << "\t" << proc.memory << "\t";
        if (proc.isAssigned)
        {
            cout << memory.at(proc.assignedTo).size << "\t" << memory.at(proc.assignedTo).size - proc.memory << endl;
        }
        else
        {
            cout << "N/A\tN/A\n";
        }
    }
}

int main()
{
    char choice;

    // Enter available blocks in memory
    cout << "Enter available memory blocks\n";
    MemoryBlock memTmp;
    do
    {
        cout << "Enter size of memory block: ";
        cin >> memTmp.size;
        memTmp.used = false;
        memory.push_back(memTmp);
        cout << "Do you want to insert another memory block? (Y/N): ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    // Enter processes
    cout << "\n Enter processes to assign to memory\n";
    Process tmp;
    do
    {
        cout << "Enter process name and memory required: ";
        cin >> tmp.name >> tmp.memory;
        tmp.isAssigned = false;
        input.push_back(tmp);

        cout << "Do you want to enter another process? (Y/N): ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    // execute first fit algo
    worstFit();

    // print the results
    printResult();

    return 0;
}
