#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday 
{	
	int month;
	int day;
	int year;
    char *name;
    struct list_head list;
};

/**
 * The following defines and initializes a list_head object named birthday_list
 */
static LIST_HEAD(birthday_list);

int part3_init(void)
{
   
    printk(KERN_INFO "***Loading Proejct1 Part3 Module***\n");

    /* Create a linked list containing five struct birthday elements*/
    
    /* NOTE:THE NAME OF FIRST STRUCT BIRTHDAY SHOULD BE YOUR OWN NAME */
     
    ///////////Add your codes here......
     
    struct birthday *person;
    
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->day = 29;
    person->month = 3;
    person->year = 2002;
    person->name = "Guranggad";
    INIT_LIST_HEAD(&person->list);
    
    list_add_tail(&person->list, &birthday_list);
    
    struct birthday *person1;
    
    person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
    person1->day = 12;
    person1->month = 2;
    person1->year = 1809;
    person1->name = "Abraham";
    INIT_LIST_HEAD(&person1->list);
    
    list_add_tail(&person1->list, &birthday_list);
    
    struct birthday *person2;
    
    person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
    person2->day = 29;
    person2->month = 5;
    person2->year = 1917;
    person2->name = "John";
    INIT_LIST_HEAD(&person2->list);
    
    list_add_tail(&person2->list, &birthday_list);
    
    struct birthday *person3;
    
    person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
    person3->day = 27;
    person3->month = 8;
    person3->year = 1858;
    person3->name = "Theodore";
    INIT_LIST_HEAD(&person3->list);
    
    list_add_tail(&person3->list, &birthday_list);
    
    struct birthday *person4;
    
    person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
    person4->day = 22;
    person4->month = 2;
    person4->year = 1732;
    person4->name = "George";
    INIT_LIST_HEAD(&person4->list);
    
    list_add_tail(&person4->list, &birthday_list);
    
    /* Traverse the linked list  */
    
    //Add codes here......
    
    
    struct birthday *ptr;
    
    list_for_each_entry(ptr, &birthday_list, list) {
    	printk(KERN_INFO "Name: %s Birthday: Month: %d Day: %d Year: %d", ptr->name, ptr->month, ptr->day, ptr->year);
    }
    
    return 0;
}

void part3_exit(void) {
    
    printk(KERN_INFO "***Removing Project1 Part3 Module***\n");

    /* Remove the elements from the linked list and return the free memory back to the kernel */
    
    //////////Add your codes here....
    
    struct birthday *ptr, *next;
    
    list_for_each_entry_safe(ptr, next, &birthday_list, list){
    	printk(KERN_INFO "Removing %s %d %d %d", ptr->name, ptr->month, ptr->day, ptr->year);
    	list_del(&ptr->list);
    	kfree(ptr);
    }
        
}

module_init( part3_init );
module_exit( part3_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Proejct1 Part3");
MODULE_AUTHOR("GSU_CSC4320_6320_TH_Spring2023");

