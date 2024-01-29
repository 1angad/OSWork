#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/* This function is called when the module is loaded. */
int part2_init(void)
{
       printk(KERN_INFO "Loading Project1 Part2 Module\n");

       return 0;
}

/* This function is called when the module is removed. */
void part2_exit(void) {
	printk(KERN_INFO "Removing Project1 Part2 Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( part2_init );
module_exit( part2_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Project1 Part2");
MODULE_AUTHOR("GSU_CSC4320_6320_TH_Spring2023");

