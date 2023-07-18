#include <iostream>

using ProcessId = int;
using std::cin, std::cout, std::endl;

struct Process {
    Process* previousProcess = nullptr;
    Process* nextProcess = nullptr;
    ProcessId id;
};

class Scheduler {
    Process* head = nullptr;

public:
    Process* add_process(ProcessId pid) {
        Process* newProcess = new Process;
        newProcess->id = pid;

        if (head == nullptr) {
            head = newProcess;
        } else {
            Process* current = head;
            while (current->nextProcess != nullptr) {
                current = current->nextProcess;
            }
            current->nextProcess = newProcess;
            newProcess->previousProcess = current;
        }

        return newProcess;
    }

    void delete_process(ProcessId pid) {
        if (head == nullptr) {
            return;
        }

        Process* current = head;
        while (current != nullptr) {
            if (current->id == pid) {
                if (current->previousProcess != nullptr) {
                    current->previousProcess->nextProcess = current->nextProcess;
                } else {
                    head = current->nextProcess;
                }

                if (current->nextProcess != nullptr) {
                    current->nextProcess->previousProcess = current->previousProcess;
                }

                delete current;
                return;
            }
            current = current->nextProcess;
        }
    }

    Process* fork(ProcessId parentId, ProcessId newId) {
        Process* newProcess = new Process;
        newProcess->id = newId;

        Process* current = head;
        while (current != nullptr) {
            if (current->id == parentId) {
                newProcess->nextProcess = current->nextProcess;
                if (current->nextProcess != nullptr) {
                    current->nextProcess->previousProcess = newProcess;
                }
                current->nextProcess = newProcess;
                newProcess->previousProcess = current;
                return newProcess;
            }
            current = current->nextProcess;
        }

        delete newProcess;
        return nullptr;
    }

    void print_schedule() {
        Process* current = head;
        while (current != nullptr) {
            cout << current->id << " ";
            current = current->nextProcess;
        }
        cout << endl;
    }
};

enum Operations {
    ADD_PROCESS,
    DELETE_PROCESS,
    FORK,
    PRINT_SCHEDULE,
};

int main() {
    Scheduler s;
    int n;
    cin >> n;

    while (n--) {
        int operationInput;
        cin >> operationInput;

        Operations opId = static_cast<Operations>(operationInput);

        if (opId == ADD_PROCESS) {
            ProcessId newPid;
            cin >> newPid;
            s.add_process(newPid);
        } else if (opId == DELETE_PROCESS) {
            ProcessId toBeDeletedPid;
            cin >> toBeDeletedPid;
            s.delete_process(toBeDeletedPid);
        } else if (opId == FORK) {
            ProcessId pidToBeForked;
            ProcessId newPid;
            cin >> pidToBeForked;
            cin >> newPid;
            s.fork(pidToBeForked, newPid);
        } else if (opId == PRINT_SCHEDULE) {
            s.print_schedule();
        }
    }

    return 0;
}
