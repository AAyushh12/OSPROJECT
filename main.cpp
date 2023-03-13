void execute_level1() {
    Process* current_process = nullptr;
    Node* current_node = queue_level1;
    Node* previous_node = nullptr;
    
    // Find the highest priority process
    while (current_node != nullptr) {
        Process* process = current_node->process;
        if (current_process == nullptr || process->priority < current_process->priority) {
            current_process = process;
            previous_node = previous_node;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }
    
    // Execute the highest priority process
    if (current_process != nullptr) {
        int time_to_execute = min(current_process->remaining_time, 2); // execute for 2 units of time
        current_process->remaining_time -= time_to_execute;
        current_process->executed_time += time_to_execute;
        
        // If process is completed, print the output and remove from queue
        if (current_process->remaining_time == 0) {
            int turnaround_time = current_process->executed_time - current_process->arrival_time;
            int waiting_time = turnaround_time - current_process->burst_time;
            cout << "Process " << current_process->pid << " completed. Turnaround time = " << turnaround_time << ", Waiting time = " << waiting_time << endl;
            if (previous_node == nullptr) {
                queue_level1 = current_node->next;
            } else {
                previous_node->next = current_node->next;
            }
            delete current_node;
        } else { // Move the process to the level 2 queue
            if (previous_node == nullptr) {
                queue_level1 = current_node->next;
            } else {
                previous_node->next = current_node->next;
            }
            current_process->priority++; // Lower the priority
            Node* new_node = new Node;
            new_node->process = current_process;
            new_node->next = queue_level2;
            queue_level2 = new_node;
        }
    }
}