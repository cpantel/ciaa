typedef enum alarm {  Alarm1, Alarm2 } Alarms;
typedef enum event {  Tec1Pressed = 0x01u,  Tec2Pressed = 0x02u } Events;
typedef enum task  {  Task1, Task2, Task3 } Tasks;


void WaitEvent( Events event) {

}

void ActivateTask( Tasks task) {

}

void SetRelAlarm (Alarms alarm) {

}

int main(int argc, char* argv[]) {
   WaitEvent(Tec1Pressed);
   WaitEvent(Task1);
   WaitEvent(Task3);
   SetRelAlarm(Task3);
   return 0;
}

