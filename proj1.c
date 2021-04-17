/*Projeto criado por Tomás Esteves ist 99341*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*CONSTANTS*/

#define TASK_MAX 10001
#define ACTIVITY_MAX 10
#define ACTIVITY_DESCRIPTION 21
#define USER_MAX 51
#define USER_NAME 21
#define TASK_DESCRIPTION 51
#define ZERO 0
#define ONE 1
#define FIRST_ACTIVITIES "TO DO", "IN PROGRESS", "DONE"
#define FIRSTASK "TO DO"
#define DONE "DONE"
#define ERROR1 "too many tasks\n"
#define ERROR2 "duplicate description\n"
#define ERROR3 "invalid duration\n"
#define ERROR4 "%d: no such task\n"
#define ERROR5 "invalid time\n"
#define ERROR6 "user already exists\n"
#define ERROR8 "too many users\n"
#define ERROR9 "no such task\n"
#define ERROR10 "task already started\n"
#define ERROR11 "no such user\n"
#define ERROR12 "no such activity\n"
#define ERROR13 "duplicate activity\n"
#define ERROR14 "invalid description\n"
#define ERROR15 "too many activities\n"
#define ERROR14 "invalid description\n"

/*task strcture*/
typedef struct
{
    char description[TASK_DESCRIPTION];
    char user[USER_NAME];
    char activity[ACTIVITY_DESCRIPTION];
    int expected;
    int started;

} Task;

void read_action();
int new_task(Task all_tasks[TASK_MAX], int ordered_list[TASK_MAX]);
void list_task(Task all_tasks[TASK_MAX], int ordered_list[TASK_MAX],
               int num_of_tasks);
int skip_time(int time);
void new_user(char all_users[][USER_NAME]);
void move_task(Task all_tasks[TASK_MAX], int time, int num_of_tasks,
               char all_users[][USER_NAME],
               char activity[][ACTIVITY_DESCRIPTION], int sorted_time[TASK_MAX]);
void list_activity(Task all_tasks[TASK_MAX], char activity[][ACTIVITY_DESCRIPTION],
                   int sorted_time[TASK_MAX], int ordered_list[TASK_MAX]);
void add_activity(char activity[][ACTIVITY_DESCRIPTION]);
int sort_element(Task all_tasks[TASK_MAX], int ordered_list[TASK_MAX],
                 int elemento_id, int inicial);
void sort_time(int time, int sorted_time[TASK_MAX], int id, Task all_tasks[TASK_MAX]);

/*  starts the program */
int main()
{
    read_action();
    return 0;
}

/* reads the new action, ends when given the q command*/
void read_action()
{
    /*list with the name of all the users*/
    char all_users[USER_MAX][USER_NAME] = {0};
    /*list with the task id  sorted by time*/
    int sorted_time[TASK_MAX] = {0};
    /*list with all the activities*/
    char activity[ACTIVITY_MAX][ACTIVITY_DESCRIPTION] =
        {FIRST_ACTIVITIES};
    /*list with the task id  sorted by name*/
    int ordered_list[TASK_MAX] = {0};
    /*list with all the tasks*/
    Task all_tasks[TASK_MAX] = {0};

    int num_of_tasks = ZERO;
    int time = ZERO;
    int c = ZERO;

    while (c != 'q')
    {
        switch (c = getchar())
        {
        case 't':
            num_of_tasks = new_task(all_tasks, ordered_list);
            break;
        case 'l':
            list_task(all_tasks, ordered_list, num_of_tasks);
            break;
        case 'n':
            time = skip_time(time);
            break;
        case 'u':
            new_user(all_users);
            break;
        case 'm':
            move_task(all_tasks, time, num_of_tasks, all_users, activity, sorted_time);
            break;
        case 'd':
            list_activity(all_tasks, activity, sorted_time, ordered_list);
            break;
        case 'a':
            add_activity(activity);
            break;
        }
    }
}

/*creates new task*/
int new_task(Task all_tasks[TASK_MAX], int ordered_list[TASK_MAX])
{
    int el;
    int j = ZERO;
    char c;

    Task new_task;

    static int num_of_tasks = ONE;

    if (num_of_tasks >= TASK_MAX) /* if there are more than 10000 tasks*/
    {
        printf(ERROR1);

        while ((c = getchar()) != '\n')
            ;

        return num_of_tasks;
    }

    scanf("%d", &new_task.expected); /*read the duration*/

    while ((c = getchar()) == ' ')
        ;

    while (c != '\n') /*read the description*/
    {
        new_task.description[j] = c;
        ++j;
        c = getchar();
    }
    new_task.description[j] = '\0';

    for (el = 1; el < num_of_tasks; ++el) /*compare with every task description*/
    {

        if (!strcmp(all_tasks[el].description, new_task.description)) /* if there is a task with the same description */
        {
            printf(ERROR2);
            return num_of_tasks;
        }
    }
    if (new_task.expected <= 0) /*if duration is less or equal to 0*/
    {
        printf(ERROR3);
        return num_of_tasks;
    }

    strcpy(new_task.activity, FIRSTASK); /*adds "TO DO" to the activity */
    new_task.started = ZERO;             /*sets zero to the started time*/
    all_tasks[num_of_tasks] = new_task;  /*introduces the new task*/

    printf("task %d\n", num_of_tasks);

    /*orders the new task alphabetically */
    num_of_tasks = sort_element(all_tasks, ordered_list, num_of_tasks, 1);

    return num_of_tasks;
}

void list_task(Task all_tasks[TASK_MAX], int ordered_list[TASK_MAX], int num_of_tasks)
{
    int c, num = ZERO;
    Task j;

    if ((c = getchar()) == '\n') /*lists all the tasks in alphabetical order*/
    {
        for (num = 1; num < num_of_tasks; ++num)
        {
            j = all_tasks[ordered_list[num]];
            printf("%d %s #%d %s\n", ordered_list[num], j.activity, j.expected, j.description);
        }
        return;
    }

    else /*lists the given tasks*/
    {
        do
        {
            scanf("%d", &num);
            if (num <= 0) /*if the number is less than zero*/
            {
                printf(ERROR4, num);
            }
            else if (num >= num_of_tasks) /*if the number of the task doens't exist*/
            {
                printf(ERROR4, num);
            }
            else
            {
                j = all_tasks[num];
                printf("%d %s #%d %s\n", num, j.activity, j.expected, j.description);
            }

        } while ((c = getchar()) != '\n'); /*read the term and print it*/

        return;
    }
}

int skip_time(int time)
{
    float num;

    scanf("%f", &num); /*reads the number as a float*/

    if (num < 0 || num != (int)num) /*check if num is less than zero or if it's a float*/
    {
        printf(ERROR5);
    }
    else
    {
        time = time + num; /*adds the number to time and shows it*/
        printf("%d\n", time);
    }
    return time;
}

void new_user(char all_users[][USER_NAME]) /*creates new user or shows all users*/
{
    int c;
    int el;
    char new_user[USER_NAME];

    static int num_of_users = ONE;

    if ((c = getchar()) == '\n') /*lists the users by order of creation*/
    {
        for (el = 1; el < num_of_users; ++el)
            printf("%s\n", all_users[el]);
    }

    else
    {
        scanf("%s", new_user); /*read new user*/

        for (el = 1; el < num_of_users; ++el) /*compares the new user with the rest of them*/
        {

            if (!strcmp(all_users[el], new_user)) /*if there's a user with the new user's name*/
            {
                printf(ERROR6);
                return;
            }
        }

        if (num_of_users >= USER_MAX) /*if there are more than 50 users*/
        {
            printf(ERROR8);
            return;
        }

        strcpy(all_users[num_of_users], new_user); /*adds the new user*/

        ++num_of_users; /*increases the number of users by 1*/
    }
    return;
}

void move_task(Task all_tasks[TASK_MAX],
               int time,
               int num_of_tasks,
               char all_users[][USER_NAME],
               char activity[][ACTIVITY_DESCRIPTION],
               int sorted_time[TASK_MAX])
{
    int id;
    char user[USER_NAME];
    char go_to_activity[ACTIVITY_DESCRIPTION];
    int duration;
    int slack;
    int i = ZERO;
    int c;
    int checkifexists = ONE;

    scanf("%d", &id);  /*scans the task*/
    scanf("%s", user); /*scans the user that will move the task*/
    getchar();

    while ((c = getchar()) != '\n') /*reads the activity to move the task to*/
    {
        go_to_activity[i] = c;
        i++;
    }
    go_to_activity[i] = '\0';

    /*compares to see if the task exists*/
    if (id < num_of_tasks && id > 0)
        checkifexists = ZERO;

    if (checkifexists) /*if it doesn't exist*/
    {
        printf(ERROR9);
        return;
    }

    if (!strcmp(go_to_activity, all_tasks[id].activity)) /*if the task is moving to the same activity*/
    {
        return;
    }

    if (!strcmp(go_to_activity, FIRSTASK)) /*if the task is started and it tries to go TO DO*/
    {
        printf(ERROR10);
        return;
    }

    checkifexists = ONE;

    for (i = 0; i < USER_MAX && checkifexists; ++i) /*compare to see if the user exists*/
        if (!strcmp(user, all_users[i]))
            checkifexists = ZERO;

    if (checkifexists) /*if the user doens't exist*/
    {
        printf(ERROR11);
        return;
    }

    checkifexists = ONE;

    for (i = 0; i < ACTIVITY_MAX && checkifexists; ++i) /*compare to see if the activity exists*/
        if (!strcmp(go_to_activity, activity[i]))
            checkifexists = ZERO;

    if (checkifexists) /*if the activity doens't exist*/
    {
        printf(ERROR12);
        return;
    }

    if (!strcmp(all_tasks[id].activity, FIRSTASK)) /*if the task is from the "TO DO" activity*/
    {
        {
            all_tasks[id].started = time; /*adds the started time to the task*/

            sort_time(time, sorted_time, id, all_tasks); /*sort the task by starting order and alphabetically*/
        }
    }

    if (!strcmp(go_to_activity, DONE)) /*if the task goes to the "DONE" activity*/
    {
        duration = time - all_tasks[id].started;   /*duration = current time - started time*/
        slack = duration - all_tasks[id].expected; /*slack = duration - expected time */

        printf("duration=%d slack=%d\n", duration, slack);
    }

    strcpy(all_tasks[id].activity, go_to_activity); /*changes the current task's activity */
}

void list_activity(Task all_tasks[TASK_MAX],
                   char activity[][ACTIVITY_DESCRIPTION],
                   int sorted_time[TASK_MAX],
                   int ordered_list[TASK_MAX])
{
    int i = ZERO;
    int checkifexists = ONE;
    char activitylist[ACTIVITY_DESCRIPTION];
    int c;

    int a = ONE;

    getchar();

    while ((c = getchar()) != '\n') /*reads the activity*/
    {
        activitylist[i] = c;
        i++;
    }
    activitylist[i] = '\0';

    for (i = 0; i < ACTIVITY_MAX && checkifexists; ++i) /*checks if the activity exists*/
    {
        if (!strcmp(activity[i], activitylist))
            checkifexists = ZERO;
    }
    if (checkifexists)
    { /*if the activity doesn't exist*/
        printf(ERROR12);
        return;
    }
    if (sorted_time[1] == 0) /*if its not sorted by time*/
    {
        for (i = 1; (a = ordered_list[i]) != 0; ++i)
        {
            if (!strcmp(all_tasks[a].activity, activitylist))
                printf("%d %d %s\n", a, all_tasks[a].started, all_tasks[a].description);
        }
    }

    for (i = 1; (a = sorted_time[i]) != 0; ++i) /*prints by starting time and alphabetically*/
    {

        if (!strcmp(all_tasks[a].activity, activitylist))
            printf("%d %d %s\n", a, all_tasks[a].started, all_tasks[a].description);
    }
    return;
}

void add_activity(char activity[][ACTIVITY_DESCRIPTION])
{
    int num, c;
    int j = ZERO;
    int len;
    int tmp;

    char new_activity[ACTIVITY_DESCRIPTION];
    static int num_of_activities = 3;

    c = getchar();

    if (c == '\n') /*shows the list of all the actities*/
        for (num = 0; num < num_of_activities; ++num)
            printf("%s\n", activity[num]);

    else
    {
        while ((c = getchar()) != '\n') /*reads the input*/
        {
            new_activity[j] = c;
            j++;
        }
        new_activity[j] = '\0';

        for (num = ZERO; num < num_of_activities; ++num) /*checks if there's activity with the same name*/

            if (!strcmp(new_activity, activity[num])) /*if there's already an activity with that name*/
            {
                printf(ERROR13);
                return;
            }
        len = j;
        j = ZERO;
        while (j < len) /*checks if the input is accordingly to the rules*/
        {
            tmp = new_activity[j];
            if (tmp >= 'a' && tmp <= 'z')
            {
                printf(ERROR14);
                return;
            }

            ++j;
        }

        if (num_of_activities >= ACTIVITY_MAX) /*if there are more than 10 activities*/
        {
            printf(ERROR15);
            return;
        }

        strcpy(activity[num_of_activities], new_activity); /*adds new activity*/

        ++num_of_activities; /*increases the number of activities by 1*/
    }
}

int sort_element(Task all_tasks[TASK_MAX], int ordered_list[TASK_MAX],
                 int elemento_id, int inicial)
{
    int i;
    int tmp1, tmp2;

    for (i = inicial; i <= elemento_id; ++i) /*check the new descrption of the 2 tasks */
    {
        if (strcmp(all_tasks[elemento_id].description, all_tasks[ordered_list[i]].description) < ZERO) /*if it comes first alphabetically*/
        {
            tmp1 = ordered_list[i];          /*copies the new current element*/
            ordered_list[i++] = elemento_id; /*inserts the new element*/
                                             /*moves to the next entry of the array*/

            while (i <= elemento_id) /*repeats the set of instruction until everything is ordered*/
            {
                tmp2 = ordered_list[i];
                ordered_list[i++] = tmp1;

                tmp1 = ordered_list[i];
                ordered_list[i++] = tmp2;
            }
            return ++elemento_id;
        }
    }
    /*if the new task is the last on the list*/

    ordered_list[i - ONE] = elemento_id;

    return ++elemento_id;
}

void sort_time(int time, int sorted_time[TASK_MAX], int id, Task all_tasks[TASK_MAX])
{
    static int last_time = ZERO;  /*stores the value of the last time this task was called*/
    static int num_sorted = ONE;  /*stores the number of sorted elements by time*/
    static int last_update = ONE; /*stores the number of the array since the last time was changed */

    if (time > last_time) /*if time changed*/
    {
        sorted_time[num_sorted] = id;
        last_update = num_sorted;
        num_sorted++;
        last_time = time;
    }
    else
        num_sorted = sort_element(all_tasks, sorted_time, num_sorted, last_update);
}
