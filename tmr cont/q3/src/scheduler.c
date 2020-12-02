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
  while (!queueIsEmpty(task->jobQ)) {
    queueDequeueFront(task->jobQ, &jobID);
    switch (jobID) {
    case SKELETON:
      if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case ENGINE:
      if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case CHASSIS:
      if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;  
    case BATTERY:
      if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case WINDOW:
      if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case TIRE:
      if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case BODY:
      if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case CAR:
            if(sem_trywait(&robot->task->sem_C) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_C);
      }else if(sem_trywait(&robot->task->sem_B) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_B);
      }else if(sem_trywait(&robot->task->sem_A) == 0){
#ifdef DEBUG
      debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
          RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
      simpleWork(jobID, robot);
      sem_post(&robot->task->sem_A);
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    }

  }

  pthread_exit(NULL);
}
