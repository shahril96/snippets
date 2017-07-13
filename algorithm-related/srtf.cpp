#include <iostream>

using namespace std;

int SIZE_STRUCT;

int choose_process(struct process Process[], int running[], int size_running);
int get_total_burst_time(struct process Process[]);
int check_if_exist(int running[], int size_running, int check);
void add_running_process(struct process Process[], int running[], int &size_running, int i);

struct process
{
    char ID;
    int arrival_time, burst_time;
};

/*

input:

4
C 2 4
A 0 6
D 2 2
B 1 3

output:

A B D C A

*/

int main()
{
    struct process Process[50];
    cin >> SIZE_STRUCT;

    for(int i = 0; i < SIZE_STRUCT; i++) // input
    {
        cin >> Process[i].ID >> Process[i].arrival_time >> Process[i].burst_time;
    }

    int total_burst_time = get_total_burst_time(Process);
    int running[SIZE_STRUCT], size_running = 0;
    char previous_id = 0;

    for(int i = 0; i < total_burst_time; i++)
    {
        add_running_process(Process, running, size_running, i);
        int get_process = choose_process(Process, running, size_running);

        Process[get_process].burst_time--;

        if(previous_id != Process[get_process].ID)
            cout << Process[get_process].ID << ' ';

        previous_id = Process[get_process].ID;
    }

    cout << endl;
}

void add_running_process(struct process Process[], int running[], int &size_running, int i)
{
    // add running process bila dh smpai arrival time
    for(int z = 0; z < SIZE_STRUCT; z++)
    {
        if(Process[z].arrival_time == i)
        {
            running[size_running] = z;
            size_running++;
        }
    }
}

int choose_process(struct process Process[], int running[], int size_running)
{
    int choose[SIZE_STRUCT], size = 0;

    // check mana process yng burst time still lagi x cecah zero
    for(int i = 0; i < size_running; i++)
    {
        if(Process[running[i]].burst_time > 0)
        {
            choose[size] = running[i];
            size++;
        }
    }

    if(size > 1) // klau running process yng x cecah zero lebih dari 1, then cri yg mna ada shortest burst time
    {
        int shortest = 9999, id_short;

        for(int i = 0; i < size; i++)
        {
            if(Process[choose[i]].burst_time < shortest)
            {
                shortest = Process[choose[i]].burst_time;
                id_short = choose[i];
            }
        }

        return id_short;
    }

    return choose[0];
}

int get_total_burst_time(struct process Process[])
{
    int total = 0;

    // ambik total burst time
    for(int i = 0; i < SIZE_STRUCT; i++)
        total += Process[i].burst_time;

    return total;
}
