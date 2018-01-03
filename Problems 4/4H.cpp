#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

class QuackVM
{
	queue<int> Queue;
	vector<int> Registers;
	vector<string> Program;
	int Line;
	map<string, int> JumpMap;
	stringstream Output;
	const int ModConst = 65536, CharConst = 256;

	bool ProceedCommand(string &Command);
	void Add();
	void Subtract();
	void Multiply();
	void Divide();
	void Modulo();
	void SetReg(char Reg);
	void GetReg(char Reg);
	void Print(char Reg = 0);
	void PrintChar(char Reg = 0);
	void Jump(string &Label);
	void JumpIfZero(char Reg, string &Label);
	void JumpIfEqual(char Reg1, char Reg2, string &Label);
	void JumpIfGreater(char Reg1, char Reg2, string &Label);
public:
	QuackVM();
	void LoadProgram(ifstream &Input);
	void RunProgram();
	string GetOutput();
};

QuackVM::QuackVM()
{
	Registers.resize(26);
}

void QuackVM::LoadProgram(ifstream &Input)
{
	string Command;
	Line = 0;
	while (Input >> Command)
	{
		if (Command[0] == ':')
			JumpMap.insert(make_pair(Command.substr(1), Line));
		Program.push_back(Command);
		++Line;
	}
}

string QuackVM::GetOutput()
{
	return Output.str();
}

void QuackVM::RunProgram()
{
	Line = 0;
	while (Line != Program.size())
	{
		if (!ProceedCommand(Program[Line]))
			break;
		++Line;
	}
}

bool QuackVM::ProceedCommand(string &Command)
{
	switch (Command[0])
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		Queue.push(atoi(Command.c_str()));
		break;
	case '+':
		Add();
		break;
	case '-':
		Subtract();
		break;
	case '*':
		Multiply();
		break;
	case '/':
		Divide();
		break;
	case '%':
		Modulo();
		break;
	case '>':
		SetReg(Command[1]);
		break;
	case '<':
		GetReg(Command[1]);
		break;
	case 'P':
		if (Command.size() == 1)
			Print();
		else
			Print(Command[1]);
		break;
	case 'C':
		if (Command.size() == 1)
			PrintChar();
		else
			PrintChar(Command[1]);
		break;
	case ':':
		break;
	case 'J':
		Jump(Command.substr(1));
		break;
	case 'Z':
		JumpIfZero(Command[1], Command.substr(2));
		break;
	case 'E':
		JumpIfEqual(Command[1], Command[2], Command.substr(3));
		break;
	case 'G':
		JumpIfGreater(Command[1], Command[2], Command.substr(3));
		break;
	case 'Q':
		return false;
	}
	return true;
}

void QuackVM::Add()
{
	if (Queue.size() < 2)
		return;
	int x = Queue.front();
	Queue.pop();
	int y = Queue.front();
	Queue.pop();
	int r = (x + y) % ModConst;
	if (r < 0) r += ModConst;
	Queue.push(r);
}

void QuackVM::Subtract()
{
	if (Queue.size() < 2)
		return;
	int x = Queue.front();
	Queue.pop();
	int y = Queue.front();
	Queue.pop();
	int r = (x - y) % ModConst;
	if (r < 0) r += ModConst;
	Queue.push(r);
}

void QuackVM::Multiply()
{
	if (Queue.size() < 2)
		return;
	int x = Queue.front();
	Queue.pop();
	int y = Queue.front();
	Queue.pop();
	int r = (x * y) % ModConst;
	if (r < 0) r += ModConst;
	Queue.push(r);
}

void QuackVM::Divide()
{
	if (Queue.size() < 2)
		return;
	int x = Queue.front();
	Queue.pop();
	int y = Queue.front();
	Queue.pop();
	int r;
	if (y == 0)
		r = 0;
	else
		r = x / y;
	Queue.push(r);
}

void QuackVM::Modulo()
{
	if (Queue.size() < 2)
		return;
	int x = Queue.front();
	Queue.pop();
	int y = Queue.front();
	Queue.pop();
	int r;
	if (y == 0)
		r = 0;
	else
		r = x % y;
	Queue.push(r);
}

void QuackVM::SetReg(char Reg)
{
	if (Queue.size() < 1)
		return;
	Registers[Reg - 'a'] = Queue.front();
	Queue.pop();
}

void QuackVM::GetReg(char Reg)
{
	Queue.push(Registers[Reg - 'a']);
}

void QuackVM::Print(char Reg)
{
	if (Reg == 0)
	{
		if (Queue.size() < 1)
			return;
		Output << Queue.front() << '\n';
		Queue.pop();
	}
	else
		Output << Registers[Reg - 'a'] << '\n';
}

void QuackVM::PrintChar(char Reg)
{
	if (Reg == 0)
	{
		if (Queue.size() < 1)
			return;
		Output << (char)(Queue.front() % CharConst);
		Queue.pop();
	}
	else
		Output << (char)(Registers[Reg - 'a'] % CharConst);
}

void QuackVM::Jump(string &Label)
{
	Line = JumpMap[Label];
}

void QuackVM::JumpIfZero(char Reg, string &Label)
{
	if (Registers[Reg - 'a'] == 0)
		Line = JumpMap[Label];
}

void QuackVM::JumpIfEqual(char Reg1, char Reg2, string &Label)
{
	if (Registers[Reg1 - 'a'] == Registers[Reg2 - 'a'])
		Line = JumpMap[Label];
}

void QuackVM::JumpIfGreater(char Reg1, char Reg2, string &Label)
{
	if (Registers[Reg1 - 'a'] > Registers[Reg2 - 'a'])
		Line = JumpMap[Label];
}

int main()
{
	ifstream FIn("quack.in");
	ofstream FOut("quack.out");
	QuackVM VM;
	VM.LoadProgram(FIn);
	VM.RunProgram();
	FOut << VM.GetOutput();
	return 0;
}