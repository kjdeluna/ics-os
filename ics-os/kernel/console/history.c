typedef struct command_struct {
    struct command_struct *prev;
    char command[256];
    struct command_struct *next;
} COMMAND;

COMMAND *cmd_list_head = NULL;
COMMAND *cmd_list_tail = NULL;

void insert_at_tail(COMMAND *node) {
    // If command list is still empty
    if(cmd_list_head == NULL) {
        cmd_list_head = node;
        cmd_list_tail = node;
    } else {
        node -> prev = cmd_list_tail;
        cmd_list_tail -> next = node;
        cmd_list_tail = node;
    }
}

void print_list() {
    COMMAND *navigator = cmd_list_head;
    while(navigator != NULL) {
        printf("%s\n", navigator -> command);
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
    print_list();
}
