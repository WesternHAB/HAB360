/* Tasks */
    // Serial task
    #define SERIAL_TASK_PERIOD              1               // ms
    #define SERIAL_TASK_STACK_SIZE          100             // Words (1 word = 2 bytes) (64 or so leads to problems)

    // Commands task
    #define COMMANDS_TASK_PERIOD            1             // ms
    #define COMMANDS_TASK_STACK_SIZE        64           // Words (1 word = 2 bytes)

    // Temperature task
	//#define TEMPERATURE_TASK_PERIOD       1000          // ms
