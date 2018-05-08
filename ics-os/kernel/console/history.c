typedef struct command_struct {
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
        printf("1");
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
}

COMMAND *create_command_node(char *cmd) {
    COMMAND *newNode = (COMMAND *) malloc(sizeof(COMMAND));
    strcpy(newNode -> command, cmd);
    newNode -> next = NULL;
    return newNode;
}

void initialize_list() {
    print_list();
}
