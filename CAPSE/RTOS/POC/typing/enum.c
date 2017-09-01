#ifdef STDOUT
#include <stdio.h>
#endif //STDOUT

typedef enum alarm { Alarm1, Alarm2 } Alarms;
typedef enum event { Event1 = 0x01u,  Event2 = 0x02u, Event3 = 0x04u } Events;
typedef enum task  { Task1, Task2, Task3 } Tasks;


void WaitEvent( Events event) {
#ifdef STDOUT
   printf("Event: %d\n", event);
#endif //STDOUT
}

void ActivateTask( Tasks task) {
#ifdef STDOUT
   printf("Task: %d\n", task);
#endif //STDOUT

}

void SetRelAlarm (Alarms alarm) {
#ifdef STDOUT
   printf("Alarm: %d\n", alarm);
#endif //STDOUT

}

int main(int argc, char* argv[]) {

   WaitEvent(Event1);
   WaitEvent(Event2);
   WaitEvent(Event3);

   ActivateTask(Task1);
   ActivateTask(Task2);
   ActivateTask(Task3);

   SetRelAlarm(Alarm1);
   SetRelAlarm(Alarm2);

#ifdef WRONG
   WaitEvent(Alarm1);
   ActivateTask(Event3);
   SetRelAlarm(Task3);
#endif // WRONG
   return 0;
}
