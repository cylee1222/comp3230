#include "../include/production.h"
#include "../include/utils.h"
#include "../include/scheduler.h"
#include "../include/robot.h"

static int num_cars;
static int num_spaces;
static int num_typeA;
static int num_typeB;
static int num_typeC;
static int total_num_robots;

void startProduction(){
  /* Init robots */
  Robot* robotsA = calloc(num_typeA, sizeof(Robot_t));
  Robot* robotsB = calloc(num_typeB, sizeof(Robot_t));
  Robot* robotsC = calloc(num_typeC, sizeof(Robot_t));
  /* Init robots end*/

  /* Prepare task */
  Task task = calloc(1, sizeof(Task_t));
  task->jobQ = queueCreate(num_cars * 17);
  sem_init(&task->sem_A, 0, num_typeA);
  sem_init(&task->sem_B, 0, num_typeB);
  sem_init(&task->sem_C, 0, num_typeC);
  sem_init(&task->sem, 0, 0);
  for (int k = 0; k < num_cars; k++){

    //Store raw materials of body
    int i = 6;
    queueEnqueue(task->jobQ, &i);
    for(int j = 0; j < 3; ++j){
      queueEnqueue(task->jobQ, &j);
    }

    //Store raw materials of car
    i = 7;
    queueEnqueue(task->jobQ, &i);
    for(int j = 3; j < 6; ++j){
      if(j == WINDOW) {
        for(int l = 0; l < 7; l++) queueEnqueue(task->jobQ, &j);
      } else if(j == TIRE) {
        for(int l = 0; l < 4; l++) queueEnqueue(task->jobQ, &j);
      } else queueEnqueue(task->jobQ, &j);
    }
  }
  /* Prepare task end*/

  /* Production start */
  // Create robot, assign task, and start to work
  for (int i = 0; i < num_typeA; ++i) {
    robotsA[i] = createRobot(TypeA);
    robotsA[i]->task = task;
    pthread_create(&robotsA[i]->pthread, NULL, revisedSimpleRobotRoutine, robotsA[i]);
  }
  // TODO: create typeB and typeC robots
  for (int i = 0; i < num_typeB; ++i) {
    robotsB[i] = createRobot(TypeB);
    robotsB[i]->task = task;
    pthread_create(&robotsB[i]->pthread, NULL, revisedSimpleRobotRoutine, robotsB[i]);
  }
  for (int i = 0; i < num_typeC; ++i) {
    robotsC[i] = createRobot(TypeC);
    robotsC[i]->task = task;
    pthread_create(&robotsC[i]->pthread, NULL, revisedSimpleRobotRoutine, robotsC[i]);
  }
  
  // wait until work done
  for (int i = 0; i < num_typeA; ++i) {
    pthread_join(robotsA[i]->pthread, NULL);
  }
  // TODO: join typeB and typeC robot threads
    for (int i = 0; i < num_typeB; ++i) {
    pthread_join(robotsB[i]->pthread, NULL);
  }
  for (int i = 0; i < num_typeC; ++i) {
    pthread_join(robotsC[i]->pthread, NULL);
  }

  /* Production end */

  /* Release memory */
  for (int i = 0; i < num_typeA; ++i) releaseRobot(robotsA[i]);
  for (int i = 0; i < num_typeB; ++i) releaseRobot(robotsB[i]);
  for (int i = 0; i < num_typeC; ++i) releaseRobot(robotsC[i]);
  queueDestroy(task->jobQ);
  sem_destroy(&task->sem_A);
  sem_destroy(&task->sem_B);
  sem_destroy(&task->sem_C);
  sem_destroy(&task->sem);
  free(task);
  free(robotsA);
  free(robotsB);
  free(robotsC);
}

int main(int argc, char *argv[]) {
  if (argc < 6) {
    printf("Usage: %s <number of cars> <number of spaces> <number of typeA robot> <number of typeB robot> <number of typeC robot>\n", argv[0]);
    return EXIT_SUCCESS;
  }
  // Change to your name and university ID
  printf("Name: Lee Chun Yin\t UID: 3035556046\n");
  /* Initialization */
  num_cars   = atoi(argv[1]);
  num_spaces = atoi(argv[2]);
  num_typeA  = atoi(argv[3]);
  num_typeB  = atoi(argv[4]);
  num_typeC  = atoi(argv[5]);
  total_num_robots = num_typeA + num_typeB + num_typeC;
  printf("Production goal: %d, num space: %d, num typeA: %d, num typeB: %d, num typeC: %d\n",
      num_cars, num_spaces, num_typeA, num_typeB, num_typeC);
  initProduction(num_cars, num_spaces);
  initNumRobot(num_typeA, num_typeB, num_typeC);
  /* Initialization end */

  double timer = getCurrentTime();
  startProduction();
  timer = getCurrentTime() - timer;
  
  printf("====Final Report====\n");
  printProductionProgress();
  printf("Production time: %lf\n", timer);
  return 0;
}
