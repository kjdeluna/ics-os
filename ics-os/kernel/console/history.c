/*
    Author:
        De Luna, Kobe Jee B.
            kbdeluna@up.edu.ph
        Saulo, Marc Enrico C.
            mcsaulo@up.edu.ph
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

COMMAND *create_command_node(char *cmd) {
    COMMAND *newNode = (COMMAND *) malloc(sizeof(COMMAND));
    newNode -> prev = NULL;
    strcpy(newNode -> command, cmd);
    newNode -> next = NULL;
    return newNode;
}

char *get_previous_command() {
    if(current_nav_pointer != cmd_list_head) {
        char *str = current_nav_pointer -> command;
        // printf("%s", str);
        current_nav_pointer = current_nav_pointer -> prev;
        return str;     
    }
    return current_nav_pointer -> command;
}

/*This command is used to append the whole history list to the history file*/
void append_history_to_file(){ 
   char str[256];
   char *u;
   file_PCB *fp;
   COMMAND *navigator = cmd_list_head;
   COMMAND *temp_nav = NULL;

   /*read the history file first*/
   fp=openfilex("history.txt",FILE_READ);
   while(fgets(str, 256, fp) != NULL) {
        u = strtok(str, "\n");
        strcpy(str,u);
        if(temp_nav == NULL) {
            temp_nav = create_command_node(str);
        } else {
            temp_nav->next = create_command_node(str);
            temp_nav->next->prev = temp_nav;
        }
   }
   /*Then do the append for the one in the history file*/
   fp=openfilex("history.txt",FILE_WRITE); //opens the history.txt
    while(temp_nav != NULL) {    //traverse the whole history list
        fwrite(temp_nav->command,strlen(temp_nav->command),1,fp);
        fwrite("\n",1,1,fp);
        temp_nav = temp_nav->next; //move to the next node
    }
    /*Then append the ones in the history list*/
    while(navigator != NULL) {
        fwrite(navigator->command, strlen(navigator->command),1,fp);
        fwrite("\n",1,1,fp);
        navigator = navigator->next;
    }   
   fclose(fp); //close the file
}

/*Same as append*/
void write_history_to_file(){
   file_PCB *fp;
   COMMAND *navigator = cmd_list_head;

   fp=openfilex("history.txt",FILE_WRITE);
    while(navigator != NULL) {  
        fwrite(navigator->command,strlen(navigator->command),1,fp);
        fwrite("\n",1,1,fp);
        navigator = navigator->next;
    }   
   fclose(fp);
}

/*
    - Counts the history lines in the history file
    - This is used at the -n subcommand

*/
int count_history_file_content() {
   file_PCB *fp;
   char str[256];
   int counter = 0;

   fp=openfilex("history.txt",FILE_READ);
   while(fgets(str, 256, fp) != NULL) {
    counter++; //increase counter every time we encounter a line in the file
   } fclose(fp);
   return counter; //return the counter 
}

/*Reads/prints the lines from the history list that are not in the history file*/
void read_lines_not_in_file() {
    int count = count_history_file_content();
    int counter_list = 0;
    int print_counter = 1000;
    COMMAND *navigator = cmd_list_head;

    // if(count == 0) {
    while(counter_list < count) {
        navigator = navigator->next;
        counter_list;
    }
    while(navigator != NULL) {
        printf("%i\t\t%s\n", ++print_counter,navigator->command);
        navigator = navigator->next;
    }
}

/*Appends the current history to the history list*/
void append_to_history_list() {
   char str[256];
   char *u;
   COMMAND *navigator = cmd_list_head;
   COMMAND *tail = cmd_list_tail;

   while(navigator->prev != tail) {
     strcpy(str,navigator->command);
     insert_at_tail(create_command_node(str));
     navigator = navigator->next;
   }
}

/*Gets all the input/line in the history file and places them in the history line*/
void get_from_history_file() {
   int count = 1000;
   char str[256];
   char *u;
   file_PCB *fp;
   COMMAND *navigator = cmd_list_head;
   COMMAND *temp = NULL;

   fp=openfilex("history.txt",FILE_READ);
   while(fgets(str, 256, fp) != NULL) {
        u = strtok(str, "\n");
        strcpy(str,u);
        printf("%i\t\t%s\n", ++count,str);
        insert_at_tail(create_command_node(str));
   }
   fclose(fp);
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
// TODO: ignore `empty` inputs
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

void delete_cmd_offset(int offset) {
    printf("%i\n", offset);
    int n = 1001;
    COMMAND *navigator = cmd_list_head;
    while((n != offset) && (navigator->next != NULL)) {
        navigator = navigator -> next;
        n++;
    } 
    if(navigator->prev == NULL) {
        cmd_list_head = navigator->next;
        navigator->next->prev = NULL;
        free(navigator);
    } else if(navigator->next == NULL) {
        cmd_list_tail = navigator->prev;
        navigator->prev->next = NULL;
        free(navigator);
    } else if((navigator->next != NULL) && (navigator->prev != NULL)){
        navigator->next->prev = navigator->prev;
        navigator->prev->next = navigator->next;
        navigator->prev = NULL;
        navigator->next = NULL;
        free(navigator);
    }
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


void initialize_list() {
    // print_list();
}
