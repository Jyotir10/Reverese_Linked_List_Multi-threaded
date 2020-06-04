#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>

struct Node* starting_pts[5]; // contains the starting point of each section of the linked list
struct Node* returned_pts[5]; // the points returned by rev function

struct Node {
    int data;
    struct Node* next;
};// struct for my Linked List node

typedef struct{
    int count,arr_pos;
    struct Node* start;
}nodeds_t;

void push (struct Node** ref, int val){
    struct Node* new_node = (struct Node*) malloc(sizeof (struct Node)); // make a new node
    new_node->data = val; // set the value of node to the given value
    new_node->next = *ref; // link it to the node that is currently the head
    *ref = new_node; // make the head pointer point to the new node
}// push into a linked list

void printList(struct Node* head){
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
    printf("\n");
} // to print a list

void get_length(struct Node* head, int* len){
    struct Node* temp = head;
    int len_val = 0;
    while (temp != NULL) {
        len_val += 1;
        temp = temp->next;
    }
    *len = len_val;
}

void *reverse(void* a)
{
    nodeds_t* info = (nodeds_t*)a;
    struct Node* current = info->start;
    int stop_check = info->count;
    int i = info->arr_pos;
    int tracker = 0;
    
    struct Node* prev = NULL;
//    struct Node* current = *head_ref;
    struct Node* next = NULL;
    while (current != NULL) {
        // Store next
        next = current->next;

        // Reverse current node's pointer
        current->next = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
        tracker += 1;
        if(tracker==stop_check){
            break;
        }
    }
//    *head_ref = prev;
    returned_pts[i] = prev;
    return (0);
}

void get_all_ponts(struct Node* head,int l,int equal_work,int extra_work){
    int stop_two = equal_work + extra_work; //4
    int stop_three = stop_two + equal_work; // 6
    int stop_four = stop_three + equal_work;//8
    int stop_five = stop_four + equal_work;//10
    
    struct Node* temp = head;
    int len_val = 0;
    while (temp != NULL) {
        len_val += 1;
        temp = temp->next;
        if(len_val == stop_two){
            starting_pts[1] = temp;
        }
        else if(len_val == stop_three){
            starting_pts[2] = temp;
        }
        else if(len_val == stop_four){
            starting_pts[3] = temp;
        }
        else if(len_val == stop_five){
            starting_pts[4] = temp;
        }
    }
}

int main() {
    struct Node* head = NULL;
    int length = 0;
    
    for(int i=0;i<100000000;i++){
        push(&head,i+1);
    } // creating threads (more than 10 threads!) This implementation is for reversing a large number of nodes
    
    printf("Linked List before Reversing\n");
    //printList(head);
    
    // I will divide the linked list into 5 sections
    starting_pts[0] = head; // get the starting point of each head
    get_length(head,&length); // get the length of the linked list created
    int equal_work = length / 5; // all the threads will reverse this amount of nodes
    int extra_work = length % 5; // the first thread will reverse equal_work+extra_work  amount of nodes
    
    get_all_ponts(head,length,equal_work,extra_work);
    
    int vo = 9; // make 5 threads and 1st thread will do the extra work
    
    pthread_t t1,t2,t3,t4,t5;
    struct Node* loc1 = starting_pts[0];
    struct Node* loc2 = starting_pts[1];
    struct Node* loc3 = starting_pts[2];
    struct Node* loc4 = starting_pts[3];
    struct Node* loc5 = starting_pts[4];
    
    
    nodeds_t first = {equal_work+extra_work,0,loc1};
    nodeds_t sec = {equal_work,1,loc2};
    nodeds_t third = {equal_work,2,loc3};
    nodeds_t fourth = {equal_work,3,loc4};
    nodeds_t fifth = {equal_work,4,loc5};
    
    
//    printf("%d %d %d %d %d\n",loc1->data,loc2->data,loc3->data,loc4->data,loc5->data);
    pthread_create(&t1,0,reverse,&first);
    pthread_create(&t2,0,reverse,&sec);
    pthread_create(&t3,0,reverse,&third);
    pthread_create(&t4,0,reverse,&fourth);
    pthread_create(&t5,0,reverse,&fifth);
    
    //printf("le  is --> %d\n",length);
    pthread_join(t1,0);
    pthread_join(t2,0);
    pthread_join(t3,0);
    pthread_join(t4,0);
    pthread_join(t5,0);
    
    struct Node* link1 = returned_pts[0];
    struct Node* link2 = returned_pts[1];
    struct Node* link3 = returned_pts[2];
    struct Node* link4 = returned_pts[3];
    struct Node* link5 = returned_pts[4];
    
    loc2->next = link1;
    loc3->next = link2;
    loc4->next = link3;
    loc5->next = link4;
    
    printf("Given linked list after reverseing\n");
    //printList(link5);
    return(0);
}
