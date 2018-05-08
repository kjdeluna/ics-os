/*
    Author:
        De Luna, Kobe Jee B.
            kbdeluna@up.edu.ph
*/

typedef struct command_struct {
    struct command_struct *prev;
    char command[256];
    struct command_struct *next;
} COMMAND;

/* Declare global variables here */
COMMAND *cmd_list_head = NULL;
COMMAND *cmd_list_tail = NULL;
int command_list_count = 0;
COMMAND *current_nav_pointer = NULL;

char *get_previous_command() {
    if(current_nav_pointer != cmd_list_head) {
        char *str = current_nav_pointer -> command;
        // printf("%s", str);
        current_nav_pointer = current_nav_pointer -> prev;
        return str;     
    }
    return current_nav_pointer -> command;
}

char *get_next_command() {
    if(current_nav_pointer != cmd_list_tail) {
        current_nav_pointer = current_nav_pointer -> next;
        char *str = current_nav_pointer -> command;
        return str;   
    }
    return current_nav_pointer -> command;
}

void reset_current_nav() {
    current_nav_pointer = cmd_list_tail;
}

void insert_at_tail(COMMAND *node) {
    // If command list is still empty
    if(cmd_list_head == NULL) {
        cmd_list_head = node;
        cmd_list_tail = node;
        current_nav_pointer = cmd_list_tail;
        command_list_count++;
    } else if(strcmp(cmd_list_tail -> command, node -> command) == 0){
        // If command list is not empty, compare the new node to prev command
        //              -> it will not be added to the history
    } else {
        node -> prev = cmd_list_tail;
        cmd_list_tail -> next = node;
        cmd_list_tail = node;
        current_nav_pointer = cmd_list_tail;
        // Increment the command list count
        command_list_count++;
    }
}

void clear_cmd_list() {
    while(cmd_list_head != NULL) {
        COMMAND *freer = cmd_list_head;
        cmd_list_head = cmd_list_head -> next;
        // Isolate node
        freer -> prev = NULL;
        freer -> next = NULL;
        free(freer);
        // Traverse next to the list
    }
    // Reset all variables
    cmd_list_head = NULL;
    cmd_list_tail = NULL;
    current_nav_pointer = NULL;
    command_list_count = 0;
}

void print_cmd_list() {
    int n = 0;
    COMMAND *navigator = cmd_list_head;
    while(navigator != NULL) {
        // Display their corresponding n (based on how they were entered)
        printf("%d\t\t%s\n", (++n)+1000, navigator -> command);
        navigator = navigator -> next;
    }
    /* Uncomment me to print the list in reverse */
    // COMMAND *navigator = cmd_list_tail;
    // while(navigator != NULL) {
    //     printf("%s\n", navigator -> command);
    //     navigator = navigator -> prev;
    // }
}

COMMAND *create_command_node(char *cmd) {
    COMMAND *newNode = (COMMAND *) malloc(sizeof(COMMAND));
    newNode -> prev = NULL;
    strcpy(newNode -> command, cmd);
    newNode -> next = NULL;
    return newNode;
}

void initialize_list() {
    // print_list();
}
