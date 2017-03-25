#include "agent.h"

using namespace std;

#define ERROR_TOLERANCE 0.0000000001

int main(int argv,char **args)
{
	//char a[]="fname";
	if(argv!=2)
	{
		cout<<"Invalid number of Arguments"<<endl;
		return(0);
	}
	//Agent agent("/home/ankith/learning/ReinforcementLearning/assignments/cs747-a2015-assign2-v1/data/MDP-2_2.txt");
	Agent agent(args[1]);
	double *tempStateValue;//[120]={0};
	
	long long int itr=0;
	int states=agent.getNumberOfStates();
	int actions=agent.getNumberOfActions();
	tempStateValue=(double *)malloc(sizeof(double)*states);
	do {

		agent.copyStateValue(tempStateValue);
		for(int i=0;i<states;i++)
		{	
			for (int j = 0; j < actions;j++)
			{
				double temp=agent.stateAction(i,j);
				if(temp>agent.stateValue[i])
				{
					agent.policy[i]=j;
					agent.stateValue[i]=temp;
				}
			}
		}
		itr++;
	}while(agent.stateValueDifference(tempStateValue,ERROR_TOLERANCE));
	
	agent.printPolicy();
	return 0;
}
