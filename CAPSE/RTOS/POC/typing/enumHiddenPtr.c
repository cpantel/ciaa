
#ifdef STDOUT
#include <stdio.h>
#endif //STDOUT

typedef enum alarm { eAlarm1, eAlarm2 } Alarms;
typedef enum event {  eEvent1 = 0x01u,  eEvent2 = 0x02u, eEvent3 = 0x04u } Events;
typedef enum task  {  eTask1, eTask2, eTask3 } Tasks;

Alarms aAlarm1 = eAlarm1;
Alarms aAlarm2 = eAlarm2;

Alarms* Alarm1 = &aAlarm1;
Alarms* Alarm2 = &aAlarm2;

Events aEvent1 = eEvent1;
Events aEvent2 = eEvent2;
Events aEvent3 = eEvent3;

Events* Event1 = &aEvent1;
Events* Event2 = &aEvent2;
Events* Event3 = &aEvent3;

Tasks aTask1 = eTask1;
Tasks aTask2 = eTask2;
Tasks aTask3 = eTask3;


Tasks* Task1 = & aTask1;
Tasks* Task2 = & aTask2;
Tasks* Task3 = & aTask3;

void WaitEvent( Events* event) {
#ifdef STDOUT
   printf("Event: %d\n", *event);
#endif //STDOUT
}

void ActivateTask( Tasks* task) {
#ifdef STDOUT
   printf("Task: %d\n", *task);
#endif //STDOUT

}

void SetRelAlarm (Alarms* alarm) {
#ifdef STDOUT
   printf("Alarm: %d\n", *alarm);
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

