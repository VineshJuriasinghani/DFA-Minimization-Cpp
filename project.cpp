#include<iostream>
#include <fstream>
using namespace std;

struct node
{
int state;
node *p1,*p2;
char transition;
int sign;
int partition_no;	
};

class DFA
{

node *N,*S;
public:
static int partitions;
DFA(int size)
{
	N=new node[size];
	S=new node[size*2];
	for(int i=0;i<size;i++)
	{
		N[i].p1=NULL;
		N[i].p2=NULL;
		N[i].state=0;   // Initial = -1   , Final =1   ,  no state =0  , Both initial & Final =2
        S[i].p1=NULL;
        S[i].state=0;
        S[i].transition='\0';
	    N[i].sign=i;
	    N[i].partition_no=-1;
	}
}
void Connect_nodes(int size,ifstream &in)
{
	int input; 
	for(int i=0,j=0;i<size;i++,j=j+2)
	{
		in>>input;
		in>>S[j].transition;
		cout<<"node's first connection : "<<i<<" -> "<<" "<<S[j].transition<<" -> "<<input<<endl;
		N[i].p1=&S[j];
		S[j].p1=&N[input];

		in>>input;
		in>>S[j+1].transition;
		cout<<"node's second connection : "<<i<<" -> "<<" "<<S[j+1].transition<<" -> "<<input<<endl;
		N[i].p2=&S[j+1];
		S[j+1].p2=&N[input];
	}
}
	
void set_states(ifstream &in)
{
	int input;
	char input1;
  	in>>input;
  	cout<< input <<": node is your initial state  "<<endl;
  	N[input].state=-1;
  	while(1)
  	{
  		
  	cout<<"Enter b to break else press any key to continue "<<endl;
	in>>input1;
	fflush(stdin);
	if(input1=='b')
	{
	break;
	}  	
	in>>input;
	cout<<input<<": node is your final state "<<endl;
	if(N[input].state==-1)
	N[input].state=2;  
    else
    N[input].state=1;

	}
  	
}	

void print_DFA(int size,ofstream &out)
{
	system("CLS");
	cout<<"\t\t\t\t\t\t PRINTING DFA : "<<endl<<endl;
	cout<<"______________________________________________________________________________________________________________________"<<endl;
	 out<<"\t\t\t\t\t\t PRINTING DFA : "<<endl<<endl;
	 out<<"_________________________________________________________________________________________________________________________________________"<<endl;
	    for(int i=0;i<size;i++)
		{
			cout<<" Node : "<<i<<endl<<endl;
			cout<<"First : ";
			cout<<N[i].sign<<" -> "<<N[i].p1->transition<<" -> "<<N[i].p1->p1->sign<<"\t";
		    cout<<"Second : ";
		    cout<<N[i].sign<<" -> "<<N[i].p2->transition<<" -> "<<N[i].p2->p2->sign<<endl<<endl;
		    out<<" Node : "<<i<<endl<<endl;
			out<<"First : ";
			out<<N[i].sign<<" -> "<<N[i].p1->transition<<" -> "<<N[i].p1->p1->sign<<"\t";
		    out<<"Second : ";
		    out<<N[i].sign<<" -> "<<N[i].p2->transition<<" -> "<<N[i].p2->p2->sign<<endl<<endl;
		}
		
}

void print_partitions(int *temp,int size,int no,ofstream &out)
{
	
		cout<<" Partition # : "<<no<<" "<<endl<<endl;
		out<<" Partition # : "<<no<<" "<<endl<<endl;
		for(int i=0;i<size;i++)
		{
		  	cout<<"First: ";
			cout<<N[temp[i]].sign<<" -> "<<N[temp[i]].p1->transition<<" -> "<<N[temp[i]].p1->p1->sign<<"partition = "<<N[temp[i]].p1->p1->partition_no<<"  "<<"\t";
		    cout<<"Second: ";
		    cout<<N[temp[i]].p2->transition<<" -> "<<N[temp[i]].p2->p2->sign<<"partition = "<<N[temp[i]].p2->p2->partition_no<<"  "<<endl<<endl;
			out<<"First: ";
			out<<N[temp[i]].sign<<" -> "<<N[temp[i]].p1->transition<<" -> "<<N[temp[i]].p1->p1->sign<<"partition = "<<N[temp[i]].p1->p1->partition_no<<"  "<<"\t";
		    out<<"Second: ";
		    out<<N[temp[i]].p2->transition<<" -> "<<N[temp[i]].p2->p2->sign<<"partition = "<<N[temp[i]].p2->p2->partition_no<<"  "<<endl<<endl;
		}
}

void divide_in(int size)
{
	
for(int i=0;i<size;i++)
{
if(N[i].state==1||N[i].state==2)
	N[i].partition_no=1;                   // Dividing Final & Non final states
else
	N[i].partition_no=0;
}
Update_partitions(size);	

}



void set_partitions(int size)
{
	
int *mem;

	for(int j=0,k=0;j<=partitions;j++)
	{	
		k=0;
		for(int i=0;i<size;i++)
		{
			
			if(N[i].partition_no == j)
			{
				k++;
			}
		
		}

		mem= new int [k];
	
		k=0;
		for(int i=0;i<size;i++)
		{		
			if(N[i].partition_no == j)
			{
				mem[k++]=i;
			}
		}

	 	shift_in_new(k,mem,size,j);	
		delete mem;
	}
	return;
}

int & Reset_partition(int size,int j)
{

    int *mem;
		
		int k=0;
		for(int i=0;i<size;i++)
		{
			
			if(N[i].partition_no == j)
			{
				k++;
			}
		
		}

		mem= new int [k];
	
		k=0;
		for(int i=0;i<size;i++)
		{		
			if(N[i].partition_no == j)
			{
				mem[k++]=i;
			}
		}
	return *mem;
}

void Reset_print_partition(int size,int j,ofstream &out)
{

    int *mem;
		
		int k=0;
		for(int i=0;i<size;i++)
		{
			
			if(N[i].partition_no == j)
			{
				k++;
			}
		
		}

		mem= new int [k];
	
		k=0;
		for(int i=0;i<size;i++)
		{		
			if(N[i].partition_no == j)
			{
				mem[k++]=i;
			}
		}
			
	print_partitions(mem,k,j,out);
	
}

void shift_in_new(int k , int *mem , int size , int j)
{
	int count =0;
	int *temp[k], *index , temp1 , temp2 ;
	
	index = new int [k];
	
		for(int i=0 ; i<k ; i++)
		{
			count =0;
			 
			for(int l=0 ; l<k ; l++)
			{
				if( (N[mem[i]].p1->p1->partition_no == N[mem[l]].p1->p1->partition_no) && (N[mem[i]].p2->p2->partition_no == N[mem[l]].p2->p2->partition_no) )
				{
					count++;
				}
			}
			
			if(count == k)
			{
				return;
			}
			
			temp [i] = new int [count];
			index[i]=count;
			for(int l=0,p=0;l<k;l++)
			{
				if( (N[mem[i]].p1->p1->partition_no == N[mem[l]].p1->p1->partition_no) && (N[mem[i]].p2->p2->partition_no == N[mem[l]].p2->p2->partition_no) )
				{
					temp[i][p++]=mem[l];
				}
			}
	    }
	    temp1 = index[0];
	    temp2=0;
	    for(int v=1;v<k;v++)
	    {
			if(temp1 >= index[v])
			{
				temp1 = index[v]; 
				temp2 = v;
			}
		}
		
		for(int F=0; F<index[temp2]; F++)
	    shift(k,size,temp[temp2][F],j);
	    
		set_partitions(size);		
	return ;
}

		
void shift(int k , int size , int j, int p)
{
		if(k>1)
		{
			CreateNew_partition();
			N[j].partition_no=partitions;
			Update_partitions(size);
			Reset_partition(size,p);
		}
		return;
}

void CreateNew_partition()
{
	partitions++;
	return;
}


void Update_partitions(int size)
{
	
for(int i=0;i<size;i++)
{
	for(int j=0;j<size;j++)
	{
		if(N[i].p1->p1->sign==N[j].sign)
		{
			N[i].p1->p1->partition_no=N[j].partition_no;
		}
		if(N[i].p2->p2->sign==N[j].sign)
		{
			N[i].p2->p2->partition_no=N[j].partition_no;
		}
	
    }
}

return;	
}

};
int DFA::partitions =1;




int main()
{
int size;
ifstream in;
ofstream out;
in.open("test3.txt");                // Write test file name here to run the input
out.open("output.txt",ios::out);    
cout<<"Enter no of nodes in DFA after removing unreachable nodes"<<endl;
in>>size;	
DFA fa(size);
fa.Connect_nodes(size,in);
fa.set_states(in);
fa.divide_in(size);
fa.set_partitions(size);
fa.print_DFA(size,out);
in.close();
cout<<"\t\t\t\t\t PRINTING MINIMIZED PARTITIONS :"<<endl<<endl;
cout<<"______________________________________________________________________________________________________________________"<<endl;
cout<<"TOTAL PARTITIONS : "<<DFA::partitions+1<<endl<<endl;
out<<"\t\t\t\t\t PRINTING MINIMIZED PARTITIONS :"<<endl<<endl<<endl;
out<<"_________________________________________________________________________________________________________________________________________"<<endl;
out<<"TOTAL PARTITIONS : "<<DFA::partitions+1<<endl<<endl;
for(int p=0;p<=DFA::partitions;p++)
fa.Reset_print_partition(size,p,out);

out.close();
}
