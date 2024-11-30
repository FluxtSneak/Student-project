#include "queue_tab.h"
#include "queue_list.h"

int main(){
    queue_lst Q= queue_create_lst();
    for (int i=0; i<10; i++){
        queue_insert_lst(&Q,i );
    }
    print_queue_lst(Q);

    T tmp=queue_extract_lst(&Q);
    printf("tmp = %d \n",tmp);
    print_queue_lst(Q);
    
    queue_destroy_lst(&Q);
    
    
    
    
    
    return 0;


}