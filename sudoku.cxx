#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;


bool same(vector< vector<int> > S, vector<vector<int> > tmp)//this checks, if the two tables are the same or not
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(S[i][j]!=tmp[i][j])
			{
				return false;
			}
		}
	}
	return true;
}


void readin(ifstream &in, vector<vector<int> > &S)//reads in the Sudoku table from a file
{
	int a;
	for(int i=0;i<9;i++)
	{
		vector<int> row;
		for(int j=0;j<9;j++)
		{
			in>>a;
			row.push_back(a);
		}
		S.push_back(row);
	}
}

void writeout(ofstream &out, vector<vector<int> > &S)//writes out the Sudok table to a file
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			out<<S[i][j]<<" ";
		}
		out<<endl;
	}
}

void print(vector< vector<int> > S)//writes out Sudoku table to the terminal
{
	for(unsigned i=0;i<S.size();i++)
	{
		for(unsigned j=0;j<S[i].size();j++)
		{
			cout<<S[i][j]<<" ";
		}
		cout<<endl;
	}
}



void base(vector<vector<int> > &S)//Simple algorithm, that guesses numbers based on excluding numbers
{
	for(int num=1;num<=9;num++)
	{
		vector<int> row;
		for(int i=0;i<9;i++)
		{
			row.push_back(0);
		}
		vector<vector<int> > M;
		for(int i=0;i<9;i++)
		{
			M.push_back(row);
		}
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				if(S[i][j]!=0)
				{
					M[i][j]=-1;
				}
			}
		}
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				if(S[i][j]==num)
				{
					for(int k=0;k<9;k++)
					{
						M[i][k]=-1;
						M[k][j]=-1;
					}
					for(int k=0;k<3;k++)
					{
						for(int l=0;l<3;l++)
						{
							M[3*(i/3)+k][3*(j/3)+l]=-1;
						}
					}
				}
			}
		}

		
		for(int i=0;i<9;i++)
		{
			int s=0;
			for(int j=0;j<9;j++)
			{
				if(M[i][j]==-1)
				{
					s++;
				}
			}
			if(s==8)
			{
				for(int j=0;j<9;j++)
				{
					if(M[i][j]==0)
					{
						S[i][j]=num;
						for(int k=0;k<9;k++)
						{
								M[i][k]=-1;
								M[k][j]=-1;
						}
						for(int n=0;n<3;n++)
						{
							for(int m=0;m<3;m++)
							{
								M[3*(i/3)+n][3*(j/3)+m]=-1;
							}
						}
					}
				}
			}
		}
		
		
		
		
		for(int i=0;i<9;i++)
		{
			int s=0;
			for(int j=0;j<9;j++)
			{
				if(M[j][i]==-1)
				{
					s++;
				}
			}
			if(s==8)
			{
				for(int j=0;j<9;j++)
				{
					if(M[j][i]==0)
					{
						S[j][i]=num;
						for(int k=0;k<9;k++)
						{
								M[j][k]=-1;
								M[k][i]=-1;
						}
						for(int n=0;n<3;n++)
						{
							for(int m=0;m<3;m++)
							{
								M[3*(j/3)+n][3*(i/3)+m]=-1;
							}
						}
					}
				}
			}
		}

		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				int s=0;
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{
						if(M[i*3+k][j*3+l]==-1)
						{
							s++;
						}
					}
				}
				if(s==8)
				{
					for(int k=0;k<3;k++)
					{
						for(int l=0;l<3;l++)
						{
							if(M[i*3+k][j*3+l]==0)
							{
								S[i*3+k][j*3+l]=num;
								for(int n=0;n<3;n++)
								{
									for(int m=0;m<3;m++)
									{
										M[i*3+n][j*3+m]=-1;
									}
								}
								for(int n=0;n<9;n++)
								{
										M[n][j*3+l]=-1;
										M[i*3+k][n]=-1;
								}
							}
						}
					}
				}
			}
		}

		
	}
}


bool check(vector<vector<int> > &S,int  I,int  J,int a)//checks if number 'a' can be written in the place I,J
{
	for(int i=0;i<9;i++)
	{
		if((S[I][i]==a)||(S[i][J]==a))
		{
			return false;
		}
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(S[3*(I/3)+i][3*(J/3)+j]==a)
			{
				return false;
			}
		}
	}
	return true;
}

bool isgood(vector<vector<int> > S)
{
	for(int num=1;num<=9;num++)
	{
		
		for(int i=0;i<9;i++)
		{
			int s=0;
			for(int j=0;j<9;j++)
			{
				if(S[i][j]==num)
				{
					s++;
				}
			}
			if(s!=1)
			{
				return false;
			}
		}
		for(int i=0;i<9;i++)
		{
			int s=0;
			for(int j=0;j<9;j++)
			{
				if(S[j][i]==num)
				{
					s++;
				}
			}
			if(s!=1)
			{
				return false;
			}
		}
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				int s=0;
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{
						if(S[i*3+k][j*3+l]==num)
						{
							s++;
						}
					}
				}
				if(s!=1)
				{
					return false;
				}
			}
		}
	}
	return true;
}

/*
The upcoming guess function simply guesses a number to the place, where the smallest is the number of possibilities
*/
void guess(vector<vector<int> > &S, int &length)
{
	//cout<<length<<endl;
	if(length>=20)
	{
		return;
	}
	vector<vector<int> > L;
	vector<int> row;
	for(int i=0;i<9;i++)
	{
		row.push_back(0);
	}
	for(int i=0;i<9;i++)
	{
		L.push_back(row);
	}
	for(int num=1;num<=9;num++)
	{
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				if((S[i][j]==0)&&(check(S,i,j,num)))
				{
					L[i][j]++;
				}
			}
		}
	}

	int sz=9;
	int A,B;
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if((L[i][j]<sz)&&(L[i][j]>0))
			{
				sz=L[i][j];
				A=i;
				B=j;
			}
		}
	}
	vector<int> possible;
	for(int i=1;i<10;i++)
	{
		if(check(S,A,B,i))
		{
			possible.push_back(i);
		}
	}

	for(unsigned i=0;i<possible.size();i++)
	{
		length++;
		vector<vector<int> > tmp=S;
		vector<vector<int> > tmp2;
		S[A][B]=possible[i];
		do
		{
			tmp2=S;
			base(S);
		}
		while((!isgood(S))&&(!same(S,tmp2)));
		if(!isgood(S))
		{
			guess(S,length);
		}
		else
		{
			length=8128;
			return;
		}
		if(!isgood(S))
		{
			S=tmp;
		}
		else
		{
			return;
		}
		length--;
		
	}
	
	
	
}





int main(int argc, char **argv)
{
	clock_t begin = clock();
	int length=0;
	vector<vector<int> > S,tmp;
	ifstream in;
	in.open("s.txt");//name of the file
	readin(in,S);
	in.close();
	/******************************************************************/
	/*while(!isgood(S)&&i<30)
	{
		base(S);
		i++;
	}*/
	do
	{
		tmp=S;
		base(S);
	}
	while((!isgood(S))&&(!same(S,tmp)));
	if(!isgood(S))
	{
		guess(S,length);
	}
	print(S);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout<<"Elapsed time (s)="<<elapsed_secs<<endl;
}

