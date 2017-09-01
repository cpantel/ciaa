#ifdef STDOUT
#include <stdio.h>
#endif //STDOUT

typedef enum alarm { eAlarm1, eAlarm2 } Alarms;
typedef enum event {  eEvent1 = 0x01u,  eEvent2 = 0x02u, eEvent3 = 0x04u } Events;
typedef enum task  {  eTask1, eTask2, eTask3 } Tasks;

Alarms Alarm1 = eAlarm1;
Alarms Alarm2 = eAlarm2;

Events Event1 = eEvent1;
Events Event2 = eEvent2;
Events Event3 = eEvent3;

Tasks Task1 = eTask1;
Tasks Task2 = eTask2;
Tasks Task3 = eTask3;

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

   WaitEvent(&Event1);
   WaitEvent(&Event2);
   WaitEvent(&Event3);

   ActivateTask(&Task1);
   ActivateTask(&Task2);
   ActivateTask(&Task3);

   SetRelAlarm(&Alarm1);
   SetRelAlarm(&Alarm2);

#ifdef WRONG
   WaitEvent(&Alarm1);
   ActivateTask(&Event3);
   SetRelAlarm(&Task3);
#endif // WRONG
   return 0;
}

