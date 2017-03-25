#include "agent.h"



Agent::Agent(string filename)
{

	ifstream in;
	in.open(filename.c_str());

	if(in.is_open())
	{

		in>>states;
		in>>actions;
		//cout<<"States " <<states<<endl;
		//cout<<"Actions "<<actions<<endl;
		rewardMatrix=(double ***)malloc(sizeof(double **)*states);
		transistionMatrix=(double ***)malloc(sizeof(double **)*states);
		stateValue=(double *)malloc(sizeof(double)*states);
		policy=(int *)malloc(sizeof(int)*states);
		for(int i=0;i<states;i++)
		{
			rewardMatrix[i]=(double **)malloc(sizeof(double*)*actions);
			transistionMatrix[i]=(double **)malloc(sizeof(double*)*actions);
			for(int j=0;j<actions;j++)
			{
				rewardMatrix[i][j]=(double *)malloc(sizeof(double)*states);
				transistionMatrix[i][j]=(double *)malloc(sizeof(double)*states);
			
			}
		}
		//cout<<"--------------"<<endl;
		for(int i=0;i<states;i++)
			for(int j=0;j<actions;j++)
				for(int k=0;k<states;k++)
					in>>rewardMatrix[i][j][k];
	
		for(int i=0;i<states;i++)
			for(int j=0;j<actions;j++)
				for(int k=0;k<states;k++)
					in>>transistionMatrix[i][j][k];
	
		in>>discount;
		
		for (int i=0;i<states;i++)
			stateValue[i]=0;

	}
	else
	{
		cout<<"Unable to open file"<<endl;
		//throw std::exception("test");
	}
	//exit();
}




double Agent::stateAction(int state,int action)
{
	double value=0;
	for(int i=0;i<states;i++)
		value+=transistionMatrix[state][action][i]* ( rewardMatrix[state][action][i] + discount * stateValue[i] );

	return value;

}


int Agent::getNumberOfStates()
{
	return states;
}


int Agent::getNumberOfActions()
{
	return actions;
}

void Agent::copyStateValue(double tempStateValues[])
{
	for (int i=0;i<states;i++)
		tempStateValues[i]=stateValue[i];
}



void Agent::printPolicy()
{

	for(int i=0;i<states;i++)
		cout<<std::setprecision(6)<<stateValue[i]<<" "<<policy[i]<<endl;
}


bool Agent::stateValueDifference(double tempStateValues[],double errorTolerance)
{
	bool temp=true;
	for (int i = 0; i < states; ++i)
	{
		if(stateValue[i]-tempStateValues[i]<errorTolerance)
			return false;

	}
	return true;
}

void Agent::display()
{

	cout<<"---______________________________________"<<endl;

	cout<<"States " <<states<<endl;
	cout<<"Actions "<<actions<<endl;
	cout<<"RewardMatrix ------------------------- "<<endl;
	for(int i=0;i<states;i++)
		for(int j=0;j<actions;j++)
			for(int k=0;k<states;k++)
				cout<<rewardMatrix[i][j][k]<<" ";

	cout<<"Transisiton Matrix ------------------------- "<<endl;
	
	for(int i=0;i<states;i++)
		for(int j=0;j<actions;j++)
			for(int k=0;k<states;k++)
				cout<<transistionMatrix[i][j][k]<<" ";

	cout<<endl<<endl;
	cout<<"discount "<<discount<<endl;

}
