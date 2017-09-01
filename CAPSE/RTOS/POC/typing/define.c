#ifdef STDOUT
#include <stdio.h>
#endif //STDOUT

#define Alarm1 0
#define Alarm2 1

#define Event1 0x01u
#define Event2 0x02u
#define Event3 0x04u

#define Task1 0
#define Task2 1
#define Task3 2

typedef unsigned int EventMaskType;
typedef unsigned char TaskType;
typedef unsigned char AlarmType;

void WaitEvent(EventMaskType event) {
#ifdef STDOUT
   printf("Event: %d\n", event);
#endif //STDOUT
}

void ActivateTask( TaskType task) {
#ifdef STDOUT
   printf("Task: %d\n", task);
#endif //STDOUT

}

void SetRelAlarm (AlarmType alarm) {
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
