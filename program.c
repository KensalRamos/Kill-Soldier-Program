/*
 *
 * COP 3502C Midterm Assignment Two
 * This program is written by: Kensal J. Ramos 
 * 
 * TLDR:
 * 1) Make a circular doubly linked list in reverse. Ex: 5,4,3,2,1
 * 2) Print.
 * 3) Reverse circular doubly linked list. So now: 1,2,3,4,5
 * 4) Print.
 * 5) Perform kill() skipping k amount of soldiers every iteration.
 * 6) Print survivor.
 */

// Pre-processor directives
#include <stdio.h>
#include <stdlib.h>

// Struct
typedef struct node {

    int info;
    struct node *prev, *next;

} soldier;

// Function prototypes
soldier* createSoldier(int sequence);
soldier* createReverseCircle(int n);
soldier* rearrangeCircle(soldier* head);
void display(soldier* head);
int kill(soldier* head, int n, int k);
void insertFirst(int pos);
void deleteNode(soldier *t);

int main(void) {

    soldier *t;
    soldier *head;
    int n, k;

    printf("Enter an n value followed by a k value (Ex: 1 2): ");
    scanf("%d %d", &n, &k);

    // Descending order
    head = createReverseCircle(n);
    printf("\nList: ");
    display(head);

    // Ascending order
    head = rearrangeCircle(head);
    printf("\nReversed: ");
    display(head);

    // Kill
    printf("\nSurvivor is: %d\n", kill(head, n, k));

    return 0;
}

/*
 *
 * Parameters: int pos - the desired position of soldier node
 * Description: This function will insert a node to the beginning of linked list.
 * Keep in mind that this is a circular list.
 * Head->prev = last_element
 * 
 *
void insertFirst(int info) {

    soldier *temp;
    soldier *roam; // Only used for "roaming"/traversing the array
    temp = (soldier *) malloc(sizeof(soldier));
    temp->info = info;
    temp->next = NULL;
    temp->prev = NULL;

    if (head == NULL) {
        head = temp;

        // We need to get the last element in order to set the head->prev
        head->prev = temp;
        head->next = temp;
    }
    else {
        
        temp->next = head;
        head->prev = temp;
        // Get the last element so we can get the prev node. Last nodes' next has to be temp.
        // temp->prev = last_node
        // last_node->next = temp
        roam = head;
        while(roam->next != head)
            roam = roam->next;
        
        temp->prev = roam;
        roam->next = temp;
        head = temp;

    }
    
}*/

/*
 * Parameters: int sequence - position of the soldier node being created
 * Description: Simple function that creates a soldier node and returns it.
 * 
 */
soldier* createSoldier(int sequence) {

    soldier *temp;
    temp = (soldier *) malloc(sizeof(soldier));

    temp->info = sequence;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;

}

/*
 * Parameters: int n - Represents the number of soldiers in my linked list.
 * 
 * Description: This will create a linked list in descending order.
 * Ex: 5->4->3->2->1
 * 
 */
soldier* createReverseCircle(int n) {

    soldier *temp;
    soldier *t;
    soldier *head;
    head = NULL;

    int i;

    /*
     * We start this for loop at zero because the logic inside for loop for inserting a
     * soldier node is using logic for inserting at the beginning of a linked list.
     */
    for (i = 1; i <= n; i++) {
        
        temp = (soldier *) malloc(sizeof(soldier));
        temp = createSoldier(i);

        if (head == NULL) {

            head = temp;
            head->next = temp;
            head->prev = temp;

        }
        else {

            temp->next = head;
            head->prev = temp;
            
            t = head;
            while(t->next != head) // Get the last item in linked list.
                t = t->next;

            temp->prev = t;
            t->next = temp;
            head = temp;

        }

    }

    return head;

} 

/*
 * Parameters: soldier *head - This is the head of our linked list
 * Description: This function reverses the order of the linked list.
 * Ex. Before: 3->2->1->NULL
 *     After:  1->2->3->NULL
 */
soldier* rearrangeCircle(soldier *head) {

    soldier *t;
    int i = 1;

    t = head;

    while(t->next != head) {
        t->info = i;
        t = t->next;
        i++;
    }

    t->info = i;
    t = t->next;
    return t;

}

void display(soldier *head) {

    soldier *t;

    t = head;
    while(t->next != head){
        printf("%d ", t->info);
        t = t->next;
    }
    printf("%d", t->info);

}

/*
 *
 * Parameters: 
 *      soldier *head - This points to the head of the linked list
 *      int n - This represents the number of soldiers given
 *      int k - This represents the amount of soldiers skipped for killing
 * 
 * Description: This function kills the soldiers according to the value of k. It returns 
 * the sequence value of the survivor
 * For example: If n = 5, k = 2. The survivor is 3.
 * 1->2->3->4->5
 */
int kill(soldier *head, int n, int k) {

    soldier *t;
    soldier *temp;
    int i = 0, j = 0;
    t = head;

    // This will repeate n-1 amount of times because one survivor is left
    for (i = 0; i < (n - 1); i++) {
        
        // This will cycle through K soldiers and eliminate each one cycled
        for (j = 0; j < k; j++) {
            temp = t;
            t = t->next;

            if (t->next != t) 
                deleteNode(temp);
        }  

        // Skips soldier at k
        if (n % 2 == 1)
            t = t->next;
        else if (i > 0)
        {
            t = t->next;
        }
        
    }

    return (t->info);
}

void deleteNode(soldier *t) {

    (t->next)->prev = t->prev;
    (t->prev)->next = t->next;

    free(t);

}