/***********
 * A simple ACC computer made to be what I remember
 * of COFAC (Craven's Old Fashoned Acc Computer). It's been 4 years
 * or so since I've used COFAC
 * so I probably didn't get everything right
 * ********/
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

//REGISTERS
int IP;
int ACC;
int MEM[1000];

//SYSTEM VARS
int opcode;
int location;
bool running;

//EMU VARS
bool debug;	//when ==true it will be stupidly verbose in calling out
		//what opcodes are being called 

void DecodeOP()
{
	opcode = (int)(MEM[IP]/1000);
	location = MEM[IP]%1000;
	//cout << "opcode " << opcode << " MEM[IP] " << MEM[IP] << endl;
}

void DoOp()
{
	switch(opcode)
	{
		case 0://load
			{
				if(debug)	
				{
					cout << "load";
				}
				ACC = MEM[location];
				if(debug)
				{
					cout << " ACC = " << ACC << endl;
				}
				break;
			}
		case 5://store
			{
				if(debug)
				{
					cout << "store";
				}
				MEM[location] = ACC;
				if(debug)
				{
					cout << " MEM[" << location << "] = " << MEM[location] << endl;
				}
				break;
			}
		case 10://add
			{
				if(debug)
				{
					cout << "add";
				}
				ACC = ACC + MEM[location];
				if(debug)
				{
					cout << " ACC = " << ACC << endl;
				}
				break;
			}
		case 15://sub
			{
				if(debug)
				{
					cout << "sub";
				}
				ACC = ACC - MEM[location];
				if(debug)
				{
					cout << " ACC = " << ACC << endl;
				}
				break;
			}
		case 20://jump
			{
				if(debug)
				{
					cout << "jump";
				}
				IP = location-1;
				if(debug)
				{
					cout << " IP = " << IP << endl;
				}
				break;
			}
		case 25://jump0
			{
				if(debug)
				{
					cout << "jump0";
				}
				if(ACC == 0)
				{
					IP = location-1;
				}
				if(debug)
				{
					cout << " IP = " << IP << endl;
				}
				break;
			}
		case 30://jumpn
			{
				if(debug)
				{
					cout << "jumpn";
				}
				if(ACC != 0)
				{
					IP = location-1;
				}
				if(debug)
				{
					cout << " IP = " << IP << endl;
				}
				break;
			}
		case 99://end
			{
				if(debug)
				{
					cout << "end" << endl;
				}
				running = false;
				break;
			}
	}
}

void ProcessorCycle()
{
	DecodeOP();
	DoOp();
	IP++;
}

void CoreDump()
{
	cout << "IP: " << IP << endl;
	cout << "ACC: " << ACC << endl;
//	cout << "MEM: " << endl;

	/*for(int i=0;i<1000;i++)
	{
		cout << "[" << i << "]=" << MEM[i] << endl;
	}*/
}

//Loads a file into memory. See INPUTFORMAT for more
void Load(string file)
{
	string inputline;
	char* pch;
	ifstream in;

	int location, num;

	in.open(file.c_str());
	getline(in, inputline);
	
	while(in)
	{	
		pch = strtok((char*)inputline.c_str(), ":");
		location = atoi(pch);
		pch = strtok(NULL, ":");
		num = atoi(pch);

		MEM[location] = num;
		
		getline(in, inputline);
	}

	in.close();
}

int main(int argc, char* argv[])
{
	running = true;

	IP = 0;
	ACC = 0;

	if(argc<2)
	{
		cout << "Usage: gofac infile" << endl;
		return 1;
	}

	Load(argv[1]);
	while(running)
	{
		ProcessorCycle();
	}
	CoreDump();
	return 0;
}
