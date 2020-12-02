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
  int num_A = robot->task->num_A;
  int num_B = robot->task->num_B;
  int num_C = robot->task->num_C;
  Task task = robot->task;
#ifdef DEBUG
    debug_printf(__func__, "Robot%c[%d] starts...\n", 
        RobotTypeToChar(robot->robotType), robot->id);
#endif 
  int jobID;
  while (!queueIsEmpty(task->jobQ)) {
    jobID = *queueFront(task->jobQ);
    switch (jobID) {
    case SKELETON:
      if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case ENGINE:
      if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case CHASSIS:
      if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;   
    case BATTERY:
      if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case WINDOW:
      if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case TIRE:
      if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case BODY:
      if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    case CAR:
      if(num_C > 0){
        if(type == 'C'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_B > 0){
        if(type == 'B'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);


        }
      }else if(num_A > 0){
        if(type == 'A'){

            queueDequeueFront(task->jobQ, &jobID);
#ifdef DEBUG
            debug_printf(__func__, "Robot%c[%d]: working on job %d...\n", 
                RobotTypeToChar(robot->robotType), robot->id, jobID);
#endif
            simpleWork(jobID, robot);

          
        }
      }else{
        err_printf(__func__, __LINE__, "Error!! Invalid number of robots\n");
      }
      break;
    default:
      err_printf(__func__, __LINE__, "Error!! Robot%c[%d] gets invalid jobID %d\n", 
        RobotTypeToChar(robot->robotType), robot->id, jobID);
      break;  
    }

  }

  pthread_exit(NULL);
}
