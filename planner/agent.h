#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;



class Agent{

private:
int  states;
int actions;

//double transistionMatrix[30][100][100];
//double rewardMatrix[30][100][100];

double ***transistionMatrix;
double ***rewardMatrix;
double discount;


public:
double *stateValue;
int *policy;

int getNumberOfStates();

int getNumberOfActions();

void copyStateValue(double tempstateValue[]);
Agent(string filename);
double stateAction(int state,int action);

bool stateValueDifference(double tempStateValue[],double errorTolerance);

void display();
void printPolicy();
};

