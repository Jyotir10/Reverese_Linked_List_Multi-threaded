Reverse a Large Linked List -->
For this, my initial intuition was using iterative method and as I said we can use multi threading with iterative approach. Say we have a LinkedList of size 900000. We can make 5 threads, all of these 5 running in parallel and iteratively reversing a portion of the linked list. When all of these threads will be done we will join the individual answers (individual reversed parts) of each thread and we will get the reversed linked list. I think this would be the most efficient approach to solve this question.

int equal_work = length / 5; // all the threads will reverse this amount of nodes
int extra_work = length % 5; // the first thread will reverse equal_work+extra_work  amount of nodes

I have divided the work among 5 threads and if the number of nodes to be reversed is not divisible by 5 then I give the extra work to the first thread. So if it happens first thread does the extra work.

To compile and run the program do -->
a) gcc -o q1 Linked_List.c -lpthread and then b) ./q1