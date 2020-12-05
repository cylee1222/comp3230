#include "../include/scheduler.h"

void *simpleRobotRoutine(void *arg) {
  Robot robot = (Robot)arg;
  Task task = robot->task;
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] starts...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
#endif 
  int jobID;
  while (!queueIsEmpty(task->jobQ)) {
    queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
        RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
    simpleWork(jobID, robot);
  }

  pthread_exit(NULL);
}

void simpleWork(int jobID, Robot robot) {
  double timer = getCurrentTime();
  switch (jobID) {
  case SKELETON:
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] making skeleton...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
    fflush(stdout);
#endif
    makeSkeleton(robot);
    break;
  case ENGINE:
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] making engine...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
    fflush(stdout);
#endif
    makeEngine(robot);
    break;
  case CHASSIS:
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] making chassis...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
    fflush(stdout);
#endif
    makeChassis(robot);
    break;
  case BODY:
    makeBody(robot);
    break;
  case WINDOW:
    makeWindow(robot);
    break;
  case TIRE:
    makeTire(robot);
    break;
  case BATTERY:
    makeBattery(robot);
    break;
  case CAR:
    makeCar(robot);
    break;
  default:
    err_printf(__func__, __LINE__, "Error!! Robot%c[%d] gets invalid jobID %d\n", 
        RobotTypeToChar(robot->robotType), robot->id, jobID);
    break;
  }
  timer = getCurrentTime() - timer;
#ifdef DEBUG
  debug_printf(__func__, "Robot%c[%d] job %d done! Time: %lf\n", 
      RobotTypeToChar(robot->robotType), robot->id, jobID, timer);
#endif

}

void *revisedSimpleRobotRoutine(void *arg) {
  Robot robot = (Robot)arg;
  char type = RobotTypeToChar(robot->robotType);
  Task task = robot->task;
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] starts...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
#endif 
  int jobID;
  int numA;
  int numB;
  int numC;
  int head;
  while (!queueIsEmpty(task->jobQ)) {
    sem_wait(&task->sem);
    if(queueIsEmpty(task->jobQ)){
      sem_post(&task->sem);
      continue;
    }
    sem_getvalue(&task->semA, &numA);
    sem_getvalue(&task->semB, &numB);
    sem_getvalue(&task->semC, &numC);

    head = *queueFront(task->jobQ);
    if(type == 'A'){
      if(head == 2 || head == 3 || head == 4 || numB == 0 || numC == 0){
        sem_wait(&task->semA);
        queueDequeueFront(task->jobQ, &jobID);
        sem_post(&task->sem);
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
        RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
        revisedSimpleWork(jobID, robot);
        sem_post(&task->semA);        
      }else{
        sem_post(&task->sem);
      }
    }else if(type == 'B'){
      if(head == 6 || numA == 0 || numC == 0){
        sem_wait(&task->semB);
        queueDequeueFront(task->jobQ, &jobID);
        sem_post(&task->sem);
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
        RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
        revisedSimpleWork(jobID, robot);
        sem_post(&task->semB);        
      }else{
        sem_post(&task->sem);
      }
    }else{
      if(head == 0 || head == 1 || head == 5 || head == 7 || numA == 0 || numB == 0){
        sem_wait(&task->semC);
        queueDequeueFront(task->jobQ, &jobID);
        sem_post(&task->sem);
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
        RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
        revisedSimpleWork(jobID, robot);
        sem_post(&task->semC);        
      }else{
        sem_post(&task->sem);
      }
    }

  }

  pthread_exit(NULL);
}

void revisedSimpleWork(int jobID, Robot robot){
  Task task = robot->task;
  double timer = getCurrentTime();
  switch (jobID) {
  case SKELETON:
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] making skeleton...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
    fflush(stdout);
#endif
    sem_wait(&task->sem0);
    sem_wait(&task->sem_body);
    makeSkeleton(robot);
    sem_post(&task->sem_body);
    break;
  case ENGINE:
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] making engine...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
    fflush(stdout);
#endif
    sem_wait(&task->sem1);
    sem_wait(&task->sem_body);
    makeEngine(robot);
    sem_post(&task->sem_body);
    break;
  case CHASSIS:
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] making chassis...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
    fflush(stdout);
#endif
    sem_wait(&task->sem2);
    sem_wait(&task->sem_body);
    makeChassis(robot);
    sem_post(&task->sem_body);
    break;
  case BODY:
    sem_wait(&task->sem6);
    sem_post(&task->sem0);
    sem_post(&task->sem1);
    sem_post(&task->sem2);
    makeBody(robot);
    break;
  case WINDOW:
    sem_wait(&task->sem4);
    makeWindow(robot);
    break;
  case TIRE:
    sem_wait(&task->sem5);
    makeTire(robot);
    break;
  case BATTERY:
    sem_wait(&task->sem3);
    makeBattery(robot);
    break;
  case CAR:
    sem_wait(&task->sem3);
    for(int i = 0; i < 7; ++i){
      sem_wait(&task->sem4);
    }
    for(int i = 0; i < 4; ++i){
      sem_wait(&task->sem5);
    }   
    makeCar(robot);
    sem_post(&task->sem6);
    break;
  default:
    err_printf(__func__, __LINE__, "Error!! Robot%c[%d] gets invalid jobID %d\n", 
        RobotTypeToChar(robot->robotType), robot->id, jobID);
    break;
  }
  timer = getCurrentTime() - timer;
#ifdef DEBUG
  debug_printf(__func__, "Robot%c[%d] job %d done! Time: %lf\n", 
      RobotTypeToChar(robot->robotType), robot->id, jobID, timer);
#endif

}
