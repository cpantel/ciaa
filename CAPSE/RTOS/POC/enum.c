typedef enum event {  Tec1Pressed,  Tec2Pressed } Events;
typedef enum task  {  Task1, Task2, Task3 } Tasks;


void WaitEvent( Events event) {

}

void ActivateTask( Tasks task) {

}


int main(int argc, char* argv[]) {
   WaitEvent(Tec1Pressed);
   WaitEvent(Task1);
   WaitEvent(Task3);
   return 0;
}

