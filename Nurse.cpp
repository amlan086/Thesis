#include<algorithm>
#include<initializer_list>
#include<numeric>
#include<system_error>
#include<array>
#include<iomanip>
#include<ostream>
#include<thread>
#include<atomic>
#include<ios>
#include<queue>
#include<tuple>
#include<bitset>
#include<iosfwd>
#include<random>
#include<type_traits>
#include<chrono>
#include<iostream>
#include<ratio>
#include<typeindex>
#include<codecvt>
#include<istream>
#include<regex>
#include<typeinfo>
#include<complex>
#include<iterator>
#include<scoped_allocator>
#include<unordered_map>
#include<condition_variable>
#include<limits>
#include<set>
#include<unordered_set>
#include<deque>
#include<list>
#include<sstream>
#include<utility>
#include<exception>
#include<locale>
#include<stack>
#include<valarray>
#include<forward_list>
#include<map>
#include<stdexcept>
#include<vector>
#include<fstream>
#include<memory>
#include<streambuf>
#include<functional>
#include<mutex>
#include<string>
#include<future>
#include<new>
#include<strstream>
#include <cstdlib>
#include <cstring>
using namespace std;

bool vailidator();
int better_vailidator();


ifstream in;
ofstream out;

string history_f, scinario, week_data_f[4];
int no_weeks, no_skills, no_shift_types, no_contracts, no_nurses;
vector<string>skills;



int total_contact_minimum = 0;



vector<int>nurse_from_skill[120];

int solution[400][400][200];
int sol_ant_mat[400][400][200];
int sol[400][400][200];

int prev_solution[400][400][200];
int see_sol = 0;
//map<string, pair <int, int> >shift_types; //min max consecutive shifts

string days[7] = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };
map< string, int> skills_point;
map<string, int> shift_type_point;
map<string, int> contracts_point;
map<string, int> nurses_point;
int nurse_check_per_day[120][120];

int requirements_minimum[120][120][120];
int requirements_optimal[120][120][120];
int requirements_fulfil[120][120][120];
int requirements_optimal_fulfil[120][120][120];
int requirements_remain[120][120][120];

int requirements_per_day[120][120];

vector< pair< string, int > >shift_off_req[120];



int best_result = 10000000;

class History {
public:
	int numberOfAssignments,
		numberOfWorkingWeekends,
		numberOfConsecutiveAssignments,
		numberOfConsecutiveWorkingDays,
		numberOfConsecutiveDaysOff;
	string lastAssignedShiftType;

};


class ShiftType {
public:
	string id;
	int minimumNumberOfConsecutiveAssignments,
		maximumNumberOfConsecutiveAssignments;

	vector<string> forbiddenSucceedingShiftTypes;
	vector<int> previousforbiddenSucceedingShiftTypes;
	vector<int> afterforbiddenSucceedingShiftTypes;
};


class Contract {
public:
	string id;
	int minimumNumberOfAssignments,
		maximumNumberOfAssignments,
		minimumNumberOfConsecutiveWorkingDays,
		maximumNumberOfConsecutiveWorkingDays,
		minimumNumberOfConsecutiveDaysOff,
		maximumNumberOfConsecutiveDaysOff,
		maximumNumberOfWorkingWeekends;
	bool completeWeekends;
};


class Nurse {
public:
	string id, contract;
	vector<string> skills;
	History history;
};


class NRP {
public:
	int nurse_sol[500];

};
NRP nrp_nurse[400];





class Particle {
public:
	int sequence[4000][2];

	int pbest[4000][2];
	int sequence_val;
	int pbest_val;
	bool feasible = 0;


};
Particle particle[200];

int solution_no = 0;
multimap<float, pair< int, vector<int>>>nurse_sol[400];



History histories[120];
Nurse nurses[120];
ShiftType shift_type[120];
Contract contracts[120];


vector<int>nurse_space[120];

vector<int>shifts_problem[120];

int no_particle = -1;


int gbest[4000][2];

int gbest_val = 1000000;



int hard_validator1();

int hard_validator2();

int hard_validator3();

int hard_validator4();

int soft_validator1();
int soft_validator2();
int soft_validator3();
int soft_validator4();
int soft_validator5();
int soft_validator6();
int soft_validator7();
int soft_validator1();
int s_n = 0;

void random_initialization();

bool repair1();
void repair2();
void repair3();
void repair4();
void repair5();







void input(string file, string h, string w1, string w2, string w3, string w4) {



	//file += ".txt";

	history_f = "H0-" + file + "-" + h + ".txt";
	scinario = "Sc-" + file + ".txt";

	week_data_f[0] = "WD-" + file + "-" + w1 + ".txt";
	week_data_f[1] = "WD-" + file + "-" + w2 + ".txt";
	week_data_f[2] = "WD-" + file + "-" + w3 + ".txt";
	week_data_f[3] = "WD-" + file + "-" + w4 + ".txt";



	string file1 = "./input/" + file + "/" + scinario;


	//freopen(file1.c_str(), "r", stdin);

	in.open(file1);

	//scenario
	if (!in)
	{
		out << "unable to open " << file1 << endl;

	}
	string null;
	getline(in, null);
	in >> null;
	in >> null;
	in >> no_weeks;
	in >> null >> null;
	in >> no_skills;


	//out << no_weeks << " " << no_skills<<endl;

	for (int i = 0;i < no_skills;i++)
	{
		string s;
		in >> s;
		skills.push_back(s);
		skills_point[s] = i;

		//out << i << " " << s << endl;
	}
	in >> null >> null;
	//shift types
	in >> no_shift_types;

	//out << no_shift_types << endl;
	for (int i = 0;i < no_shift_types;i++)
	{
		string s;
		in >> s;
		cout << s << endl;
		shift_type_point[s] = i;
		shift_type[i].id = s;
		char cc;
		while (in >> cc && cc != '(')
		{

		}
		int a, b;
		in >> a;

		in >> cc;
		in >> b;

		in >> cc;
		shift_type[i].minimumNumberOfConsecutiveAssignments = a;
		shift_type[i].maximumNumberOfConsecutiveAssignments = b;

		//out << shift_type[i].id << " " << shift_type[i].minimumNumberOfConsecutiveAssignments << " " << shift_type[i].maximumNumberOfConsecutiveAssignments << endl;

	}


	//forbidden succession
	in >> null;

	for (int i = 0;i < no_shift_types;i++)
	{
		string s;
		in >> s;
		cout << s;
		int n;
		in >> n;
		int key = shift_type_point.find(s)->second;
		for (int j = 0;j < n;j++)
		{
			string ss;
			in >> ss;
			shift_type[key].forbiddenSucceedingShiftTypes.push_back(ss);
			int kkk = shift_type_point.find(ss)->second;
			shift_type[kkk].previousforbiddenSucceedingShiftTypes.push_back(key);
			shift_type[key].afterforbiddenSucceedingShiftTypes.push_back(kkk);

		}

	}
	//contracts
	in >> null;
	in >> null;
	in >> no_contracts;

	for (int i = 0;i < no_contracts;i++)
	{
		string s;
		in >> s;
		cout << s;
		contracts_point[s] = i;
		contracts[i].id = s;

		char cc;
		int a, b;
		while (in >> cc && cc != '(')
		{

		}

		in >> a;

		in >> cc;
		in >> b;

		in >> cc;

		contracts[i].minimumNumberOfAssignments = a;
		contracts[i].maximumNumberOfAssignments = b;
		total_contact_minimum += a;
		while (in >> cc && cc != '(')
		{

		}

		in >> a;

		in >> cc;
		in >> b;

		in >> cc;
		contracts[i].minimumNumberOfConsecutiveWorkingDays = a;
		contracts[i].maximumNumberOfConsecutiveWorkingDays = b;

		while (in >> cc && cc != '(')
		{

		}

		in >> a;

		in >> cc;
		in >> b;
		in >> cc;
		contracts[i].minimumNumberOfConsecutiveDaysOff = a;
		contracts[i].maximumNumberOfConsecutiveDaysOff = b;
		in >> contracts[i].maximumNumberOfWorkingWeekends;
		in >> contracts[i].completeWeekends;


	}

	//nurses
	in >> null >> null;


	in >> no_nurses;

	for (int i = 0;i < no_nurses;i++)
	{
		string id, contract;
		vector<string> skills;

		string s;
		in >> s;
		cout << s << endl;
		nurses_point[s] = i;
		//int key1 = nurses_point.find(s)->second;
		//out << s << " " << i << key1<<endl;

		nurses[i].id = s;
		in >> s;
		nurses[i].contract = s;

		int n;
		in >> n;
		for (int j = 0;j < n;j++)
		{
			string ss;
			in >> ss;
			nurses[i].skills.push_back(ss);
			int key = skills_point.find(ss)->second;
			nurse_from_skill[key].push_back(i);


		}


	}



	cout << 1;

	in.close();






	//history


	string file2 = "./input/" + file + "/" + history_f;
	//freopen(file2.c_str(), "r", stdin);
	in.open(file2);
	if (!in)
	{
		out << "unable to open " << file2 << endl;

	}

	int n;
	in >> null;
	in >> n;
	in >> null;
	in >> null;
	//out << n;
	cout << n;
	for (int i = 0;i < no_nurses;i++)
	{


		string ss;
		in >> ss;
		cout << ss;
		/*map<string, int>::iterator it;
		it = nurses_point.find(ss);*/
		int key = nurses_point.find(ss)->second;

		in >> histories[key].numberOfAssignments
			>> histories[key].numberOfWorkingWeekends
			>> histories[key].lastAssignedShiftType
			>> histories[key].numberOfConsecutiveAssignments
			>> histories[key].numberOfConsecutiveWorkingDays
			>> histories[key].numberOfConsecutiveDaysOff;

		nurses[key].history = histories[key];
	}




	/*


	//weekdata1
	in.close();
	string file3 = "./input/" + file + "/" + week_data_f[0];
	//freopen(file3.c_str(), "r", stdin);
	in.open(file3);
	if (!in)
	{
		out << "unable to open " << file3 << endl;

	}
	in >> null >> null >> null;

	for (int i = 0; i < no_shift_types*no_skills;i++)
	{

		string shift, skill;
		in >> shift >> skill;
		int key1 = shift_type_point.find(shift)->second;
		int key2 = skills_point.find(skill)->second;
		//cout << key1 << " " << key2 << " " << endl;
		for (int j = 0;j < 7;j++)
		{
			char cc;
			int a, b;
			while (in >> cc && cc != '(')
			{

			}

			in >> a;
			//cout << a;
			in >> cc;
			in >> b;
			//cout << b;
			in >> cc;

			requirements_minimum[j][key1][key2] = a;
			requirements_optimal[j][key1][key2] = b;
			requirements_remain[j][key1][key2] = a;
			requirements_per_day[j][key2] += a;
		}





	}

	in >> null >> null;
	int nn;
	in >> nn;
	for (int i = 0;i < nn;i++)
	{
		string s;
		in >> s;
		int key1 = nurses_point.find(s)->second;

		string shift, day;
		int d_n;
		in >> shift >> day;

		for (int i = 0;i < 7;i++)
		{
			if (days[i] == day)
			{
				d_n = i;
				break;
			}
		}
		//cout << shift<<endl;
		//int s_n = shift_type_point.find(shift)->second;

		shift_off_req[key1].push_back(make_pair(shift, d_n));

		//out << key1 << " " << nurses[key1].id << " ";
			//out<<   shift_off_req[key1][0].first << " " << shift_off_req[key1][0].second<< endl;
	}



	*/


	string file3;

	//weekdata1

	for (int w = 0;w < no_weeks;w++)
	{
		in.close();
		file3 = "./input/" + file + "/" + week_data_f[w];
		//freopen(file3.c_str(), "r", stdin);
		in.open(file3);
		if (!in)
		{
			out << "unable to open " << file3 << endl;

		}
		in >> null >> null >> null;

		for (int i = 0; i < no_shift_types*no_skills;i++)
		{

			string shift, skill;
			in >> shift >> skill;
			int key1 = shift_type_point.find(shift)->second;
			int key2 = skills_point.find(skill)->second;
			//cout << key1 << " " << key2 << " " << endl;
			for (int j = w * 7 + 0;j < w * 7 + 7;j++)
			{
				char cc;
				int a, b;
				while (in >> cc && cc != '(')
				{

				}

				in >> a;
				//cout << a;
				in >> cc;
				in >> b;
				//cout << b;
				in >> cc;

				requirements_minimum[j][key1][key2] = a;
				requirements_optimal[j][key1][key2] = b;
				requirements_remain[j][key1][key2] = a;
				requirements_per_day[j][key2] += a;
			}





		}

		in >> null >> null;
		int nn;
		in >> nn;
		for (int i = 0;i < nn;i++)
		{
			string s;
			in >> s;
			int key1 = nurses_point.find(s)->second;

			string shift, day;
			int d_n;
			in >> shift >> day;

			for (int i = 0;i < 7;i++)
			{
				if (days[i] == day)
				{
					d_n = w * 7 + i;
					break;
				}
			}
			//cout << shift<<endl;
			//int s_n = shift_type_point.find(shift)->second;

			shift_off_req[key1].push_back(make_pair(shift, d_n));

			//out << key1 << " " << nurses[key1].id << " ";
				//out<<   shift_off_req[key1][0].first << " " << shift_off_req[key1][0].second<< endl;
		}







	}








}
int myrandom(int i) { return std::rand() % i; }

void show_solution()
{

	out << "	";

	for (int j = 0; j < no_weeks * 7;j++)
	{
		out << "	" << days[j % 7] << "		";

		out << "	";
	}
	out << endl;




	for (int i = 0;i < no_nurses;i++)
	{
		out << nurses[i].id << "	";

		for (int j = 0; j < no_weeks * 7;j++)
		{
			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] < 0)
					out << 0 << "	";
				else
					out << solution[i][j][k] << "	";
			}
			out << "	";
		}
		out << endl;
	}
	out << endl;


	/*


		for (int i = 0;i < no_nurses;i++)
		{


			for (int j = 0; j < no_weeks * 7;j++)
			{
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] < 0)
						out << 0 << "";
					else
						out << solution[i][j][k] << "";
				}
				out << " ";
			}
			out << endl;
		}
		out << endl;
		*/
}




vector<int>skill_nurse[100][100];

void nurse_skill()
{

	for (int i = 0;i < no_nurses;i++)
	{


		int cnt_skill = nurses[i].skills.size();
		int cnt_type = contracts_point.find(nurses[i].contract)->second;


		if (cnt_skill == 1)
		{
			string k = nurses[i].skills[0];
			int kk = skills_point.find(k)->second;

			skill_nurse[1][kk].push_back(i);
		}
		if (cnt_skill == 2)
		{
			string k = nurses[i].skills[0];
			int kk = skills_point.find(k)->second;
			skill_nurse[2][kk].push_back(i);

			k = nurses[i].skills[1];
			kk = skills_point.find(k)->second;
			skill_nurse[2][kk].push_back(i);


		}
	}


}




void withdraw(int nur, int d, int st)
{
	int prv = -1, aft = -1;

	for (int i = 0;i < no_shift_types;i++)
	{
		if (d > 0 && solution[nur][d - 1][i] > 0)
			aft = i;
		if (solution[nur][d + 1][i] > 0)
			prv = i;
	}


	bool flag = 0;

	shifts_problem[nur].clear();


	/*
	int j = aft;
	cout << j << " " << shift_type[j].afterforbiddenSucceedingShiftTypes.size() << endl;;
		for (int i = 0;i < shift_type[j].afterforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[j].afterforbiddenSucceedingShiftTypes[i];

			cout << "----" << j<< " " << s << endl;




		}

	*/
	if (aft != -1)
	{
		for (int i = 0;i < shift_type[aft].afterforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[aft].afterforbiddenSucceedingShiftTypes[i];
			shifts_problem[nur].push_back(s);
			shifts_problem[nur].push_back(d - 1);
			shifts_problem[nur].push_back(aft);

			solution[nur][d - 1][aft] = 0;
			//cout << "------" << aft << " " << s << endl;
			if (s == st)
				flag = 1;
		}
	}
	if (prv != -1)
	{
		for (int i = 0;i < shift_type[prv].previousforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[prv].previousforbiddenSucceedingShiftTypes[i];
			shifts_problem[nur].push_back(s);
			shifts_problem[nur].push_back(d + 1);
			shifts_problem[nur].push_back(prv);

			solution[nur][d + 1][prv] = 0;
			if (s == st)
				flag = 1;
			//cout << "------" << s << " " << prv << endl;
		}
	}
	//cout << flag;

}

















int conflict_check_prev(int nur, int d, int st)
{
	int prv = -1, aft = -1;



	if (d == 0 && nurses[nur].history.lastAssignedShiftType != "None")
	{
		aft = shift_type_point.find(nurses[nur].history.lastAssignedShiftType)->second;
	}

	for (int i = 0;i < no_shift_types;i++)
	{
		if (d > 0 && solution[nur][d - 1][i] > 0)
			aft = i;
		if (solution[nur][d + 1][i] > 0)
			prv = i;
	}


	int flag = 0;
	bool flag_p = 0, flag_a = 0;



	shifts_problem[nur].clear();


	/*
	int j = aft;
	cout << j << " " << shift_type[j].afterforbiddenSucceedingShiftTypes.size() << endl;;
		for (int i = 0;i < shift_type[j].afterforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[j].afterforbiddenSucceedingShiftTypes[i];

			cout << "----" << j<< " " << s << endl;




		}

	*/
	if (aft != -1)
	{
		for (int i = 0;i < shift_type[aft].afterforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[aft].afterforbiddenSucceedingShiftTypes[i];
			shifts_problem[nur].push_back(s);
			shifts_problem[nur].push_back(d - 1);
			shifts_problem[nur].push_back(aft);

			//cout << "------" << aft << " " << s << endl;
			if (s == st)
				flag_p = 1;
		}
	}
	
	//cout << flag;

	
		return flag_p;
}









int conflict_check_post(int nur, int d, int st)
{
	int prv = -1, aft = -1;



	if (d == 0 && nurses[nur].history.lastAssignedShiftType != "None")
	{
		aft = shift_type_point.find(nurses[nur].history.lastAssignedShiftType)->second;
	}

	for (int i = 0;i < no_shift_types;i++)
	{
		if (d > 0 && solution[nur][d - 1][i] > 0)
			aft = i;
		if (solution[nur][d + 1][i] > 0)
			prv = i;
	}


	int flag = 0;
	bool flag_p = 0, flag_a = 0;
	


	shifts_problem[nur].clear();


	/*
	int j = aft;
	cout << j << " " << shift_type[j].afterforbiddenSucceedingShiftTypes.size() << endl;;
		for (int i = 0;i < shift_type[j].afterforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[j].afterforbiddenSucceedingShiftTypes[i];

			cout << "----" << j<< " " << s << endl;




		}

	*/
	
	if (prv != -1)
	{
		for (int i = 0;i < shift_type[prv].previousforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[prv].previousforbiddenSucceedingShiftTypes[i];
			shifts_problem[nur].push_back(s);
			shifts_problem[nur].push_back(d + 1);
			shifts_problem[nur].push_back(prv);
			if (s == st)
				flag_a = 1;
			//cout << "------" << s << " " << prv << endl;
		}
	}
	//cout << flag;


	return flag_a;
}



bool conflict_check(int nur, int d, int st)
{
	int prv = -1, aft = -1;

	if(st==-1)
		return 0;


	if (d == 0 && nurses[nur].history.lastAssignedShiftType != "None")
	{
		aft = shift_type_point.find(nurses[nur].history.lastAssignedShiftType)->second;
	}

	for (int i = 0;i < no_shift_types;i++)
	{
		if (d > 0 && solution[nur][d - 1][i] > 0)
			aft = i;
		if ( d< no_weeks*7 && solution[nur][d + 1][i] > 0)
			prv = i;
	}


	bool flag = 0;
	for (int i = 0;i < no_shift_types;i++)
	{
		if (i == st)
			continue;
		if (solution[nur][d][i] > 0)
			flag = 1;

	}
	

	shifts_problem[nur].clear();


	/*
	int j = aft;
	cout << j << " " << shift_type[j].afterforbiddenSucceedingShiftTypes.size() << endl;;
		for (int i = 0;i < shift_type[j].afterforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[j].afterforbiddenSucceedingShiftTypes[i];

			cout << "----" << j<< " " << s << endl;




		}

	*/
	if (aft != -1)
	{
		for (int i = 0;i < shift_type[aft].afterforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[aft].afterforbiddenSucceedingShiftTypes[i];
			shifts_problem[nur].push_back(s);
			shifts_problem[nur].push_back(d - 1);
			shifts_problem[nur].push_back(aft);

			//cout << "------" << aft << " " << s << endl;
			if (s == st)
				flag = 1;
		}
	}
	if (prv != -1)
	{
		for (int i = 0;i < shift_type[prv].previousforbiddenSucceedingShiftTypes.size();i++)
		{
			int s = shift_type[prv].previousforbiddenSucceedingShiftTypes[i];
			shifts_problem[nur].push_back(s);
			shifts_problem[nur].push_back(d + 1);
			shifts_problem[nur].push_back(prv);
			if (s == st)
				flag = 1;
			//cout << "------" << s << " " << prv << endl;
		}
	}
	//cout << flag;
	return flag;
}


void constraint()
{


	for (int i = 0;i < no_nurses;i++)
	{
		/*for (int j = 0;j < shift_off_req[i].size();j++)
		{
			int d = shift_off_req[i][j].second;
			string shift=shift_off_req[i][j].first;

			if (shift == "Any")
			{pkk
				for (int k = 0;k < no_shift_types;k++)
					solution[i][d][k] = -1;
			}
			else
			{

				int s = shift_type_point.find(shift)->second;
				solution[i][d][s] = -1;
			}

		}
		*/


		string lastAssignedShift = nurses[i].history.lastAssignedShiftType;
		//cout << lastAssignedShift;


		if (lastAssignedShift != "None")
		{
			int shift_id = shift_type_point.find(lastAssignedShift)->second;

			//cout << shift_id;



			for (int j = 0;j < shift_type[shift_id].forbiddenSucceedingShiftTypes.size();j++)
			{
				string ss = shift_type[shift_id].forbiddenSucceedingShiftTypes[j];

				//cout << ss;
				int forbid_id = shift_type_point.find(ss)->second;
				//cout << forbid_id;
				solution[i][0][forbid_id] = -1;

			}
		}

	}

	//show_solution();

}
bool check(int i, int j, int k)
{

	if (solution[i][j][k] > 0 || solution[i][j][k] < 0)
		return 0;
	else
		return 1;


}

void update(int n, int d, int s)
{

	for (int i = 0;i < no_shift_types;i++)
	{
		if (i != s)
			solution[n][d][i] = -2;
	}

	for (int j = 0;j < shift_type[s].forbiddenSucceedingShiftTypes.size();j++)
	{
		string ss = shift_type[s].forbiddenSucceedingShiftTypes[j];

		//cout << ss;
		int forbid_id = shift_type_point.find(ss)->second;
		//cout << forbid_id;
		solution[n][d + 1][forbid_id] = -3;

	}
}
int aa[100][100][100];
int check_req()
{
	int flag = 0;
	memset(aa, 0, sizeof aa);
	for (int j = 0;j < no_weeks * 7;j++)
	{


		for (int k = 0;k < no_shift_types;k++)
		{

			for (int i = 0;i < no_nurses;i++)
			{
				if (solution[i][j][k] > 0)
				{

					int ll = solution[i][j][k] - 1;
					aa[j][k][ll]++;
				}


			}
		}
	}

	for (int i = 0;i < no_weeks * 7;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{

			for (int k = 0;k < no_skills;k++)
			{

				if (aa[i][j][k] < requirements_minimum[i][j][k])
				{
					flag = 1;
					goto A;
				}

			}
		}
	}



	//cout << flag << endl;
A:
	return flag;

}
vector< pair <int, pair <int, int> > >random_keep;
void build_the_vector()
{
	for (int i = 0;i < no_weeks * 7;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{

			for (int k = 0;k < no_skills;k++)
			{

				if (requirements_minimum[i][j][k] > 0)
				{
					random_keep.push_back(make_pair(i, make_pair(j, k)));
				}

			}
		}
	}

}

void create_req()
{

	for (int i = 0;i < no_weeks * 7;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				requirements_remain[i][j][k] = requirements_minimum[i][j][k];
			}

		}

	}


}



vector<int>update_nurse_space[100];


void nurse_space_update(int d)
{

	for (int i = 0;i < 100;i++)
	{
		update_nurse_space[i].clear();

	}


	for (int i = 0;i < no_nurses;i++)
	{
		int cn = contracts_point.find(nurses[i].contract)->second;

		int compliment_no_of_skills = no_skills - nurses[i].skills.size() + 1;

		int tt = 0;
		for (int j = 0;j < no_shift_types;j++)
		{
			if (solution[i][d - 1][j] > 0)
				tt++;
			if (solution[i][d + 1][j] > 0)
				tt++;

		}





		int tot_push = contracts[cn].maximumNumberOfAssignments *(10 * tt + 1);



		for (int k = 0; k < nurses[i].skills.size();k++)
		{
			int l = skills_point.find(nurses[i].skills[k])->second;

			for (int j = 0;j < tot_push;j++)
			{
				update_nurse_space[l].push_back(i);

			}
		}


	}







}




















int nurse_no[10];

void nurse_space_create()
{

	for (int i = 0;i < 100;i++)
	{
		nurse_space[i].clear();

	}

	memset(nurse_no, 0, sizeof nurse_no);

	for (int i = 0;i < no_nurses;i++)
	{
		int cn = contracts_point.find(nurses[i].contract)->second;

		int compliment_no_of_skills = no_skills - nurses[i].skills.size() + 1;
		int tot_push = contracts[cn].maximumNumberOfAssignments * compliment_no_of_skills;

		for (int k = 0; k < nurses[i].skills.size();k++)
		{
			int l = skills_point.find(nurses[i].skills[k])->second;
			nurse_no[l]++;
			for (int j = 0;j < tot_push;j++)
			{
				nurse_space[l].push_back(i);

			}
		}


	}







}

int req[100];
void random_init()
{

	memset(nurse_check_per_day, -1, sizeof nurse_check_per_day);
	vector<int>ds;

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		ds.push_back(i);
	}




	while (ds.size() != 0)
	{

		int rnd = rand() % ds.size();
		//out << ds[rnd]<<" "<<ds.size()<<endl;


		int r_d = ds[rnd];


		//out << r_d << " " << r_sft << " ";
		int r_t = 0;


		memset(req, 0, sizeof req);
		vector<pair<int, int>>r_n_s;

		for (int k = 0;k < no_shift_types;k++)
		{


			for (int i = 0;i < no_skills;i++)
			{

				int cnt = 0;
				for (int l = 0;l < no_nurses;l++)
				{
					if (i == solution[l][r_d][k] - 1)
						cnt++;
				}

				req[i] += max(requirements_minimum[r_d][k][i] - cnt, 0);
				//out << req << " ";

				r_t += max(requirements_minimum[r_d][k][i] - cnt, 0);
				for (int j = 0;j < requirements_minimum[r_d][k][i] - cnt;j++)
					r_n_s.push_back(make_pair(i, k));


			}
		}

		//cout << 1;
		int nurse_day[100];
		memset(nurse_day, -1, sizeof nurse_day);
		vector<int>variable;
		set<int>chosen;
		int itr = 0;
		while (r_n_s.size() > 0 && itr < 500)
		{
			//vailidator();
			//cout << ds.size() << " " << r_n_s.size() << endl;
			itr++;
			int rnd_ind = rand() % r_n_s.size();
			int skl = r_n_s[rnd_ind].first;
			int sft = r_n_s[rnd_ind].second;

			bool flag = 1;
			int iter = 0;
			nurse_space_update(r_d);

			while (flag && iter < 1000)
			{
				iter++;


				int rnd_nur_ind = rand() % update_nurse_space[skl].size();
				int nur = update_nurse_space[skl][rnd_nur_ind];
				if (chosen.find(update_nurse_space[skl][rnd_nur_ind]) == chosen.end() && solution[update_nurse_space[skl][rnd_nur_ind]][r_d][sft] == 0 && conflict_check(nur, r_d, sft) == 0)
				{
					chosen.insert(update_nurse_space[skl][rnd_nur_ind]);

					solution[nur][r_d][sft] = skl + 1;
					if (nurses[nur].skills.size() > 0)
					{
						variable.push_back(nur);

					}

					r_n_s.erase(r_n_s.begin() + rnd_ind);
					flag = 0;
					iter = 0;
				}

				if (iter > 500 && flag == 1)
				{

					auto it = find(variable.begin(), variable.end(), nur);
					if (it != variable.end() && conflict_check(nur, r_d, sft) == 0)
					{
						for (int k = 0;k < no_shift_types;k++)
						{
							if (solution[nur][r_d][k] > 0)
							{
								r_n_s.push_back(make_pair(solution[nur][r_d][k] - 1, k));
								solution[nur][r_d][k] = 0;
							}

						}
						solution[nur][r_d][sft] = skl + 1;
						r_n_s.erase(r_n_s.begin() + rnd_ind);
						flag = 0;
						iter = 0;
					}


				}
				if (iter > 800 && flag == 1)
				{
					withdraw(nur, r_d, sft);
					if (conflict_check(nur, r_d, sft) == 0 && solution[update_nurse_space[skl][rnd_nur_ind]][r_d][sft] == 0)
					{
						solution[nur][r_d][sft] = skl + 1;
						r_n_s.erase(r_n_s.begin() + rnd_ind);
						flag = 0;
						iter = 0;
					}

				}




			}





		}





		//show_solution();
		//vailidator();
		//out << endl << endl;

		ds.erase(ds.begin() + rnd);

	}


	//show_solution();
	//vailidator();










}


bool nurse_have_skill(int i, int skl)
{
	
	for (int j = 0;j < nurses[i].skills.size();j++)
	{
		int skil = skills_point.find(nurses[i].skills[j])->second;
		if (skl == skil)
			return 1;

	}

	return 0;
}



void repair4()
{



	for (int j = 0;j < no_weeks * 7;j++)
	{

		for (int k = 0;k < no_shift_types;k++)
		{
			int skl[100];
			vector < pair<int, int>>skil_need;
			vector<pair<int, int>>var_nurse;
			memset(skl, 0, sizeof skl);
			//memset(skl_need, 0, sizeof skl_need);
			vector<int>serial;
			for (int i = 0; i < no_nurses; ++i) serial.push_back(i);
			random_shuffle(serial.begin(), serial.end());
			random_shuffle(serial.begin(), serial.end(), myrandom);



			for (std::vector<int>::iterator it = serial.begin(); it != serial.end(); ++it)
			{
				int i = *it;
				if (solution[i][j][k] > 0)
				{
					int sk = solution[i][j][k];
					if (nurses[i].skills.size() > 1)
					{
						var_nurse.push_back(make_pair(nurses[i].skills.size(), i));
					}
					else
						skl[sk - 1]++;

				}
			}
			//sort(var_nurse.begin(), var_nurse.end());



			for (int i = 0;i < no_skills;i++)
			{
				skil_need.push_back(make_pair(skl[i] - requirements_minimum[j][k][i], i));

			}

			sort(skil_need.begin(), skil_need.end());

			for (int i = 0;i < skil_need.size();i++)
			{
				int iter = 0;
				while (skil_need[i].first < 0 && iter < -1 * skil_need[i].first * 5)
				{
					iter++;
					int skl = skil_need[i].second;
					vector<pair<int, int>>nur_select;
					bool f = 0;
					for (int l = 0;l < var_nurse.size();l++)
					{
						int nur = var_nurse[l].second;
						if (nurse_have_skill(nur, skl))
						{
							nur_select.push_back(make_pair(l, nur));
							f = 1;

						}
					}

					if (f == 1)
					{
						int a = rand() % nur_select.size();
						int nur = nur_select[a].second;
						int l = nur_select[a].first;
						solution[nur][j][k] = skl + 1;
						skil_need[i].first++;
						var_nurse.erase(var_nurse.begin() + l);
					}
				}
			}
		}
	}

}



void repair3()
{



	for (int j = 0;j < no_weeks * 7;j++)
	{
		vector < pair<int, int>> day_var;
		for (int k = 0;k < no_shift_types;k++)
		{
			int skl[100];
			vector < pair<int, int>>skil_need;
			vector<pair<int, int>>var_nurse;
			memset(skl, 0, sizeof skl);
			//memset(skl_need, 0, sizeof skl_need);
			vector<int>serial;
			for (int i = 0; i < no_nurses; ++i) serial.push_back(i);
			random_shuffle(serial.begin(), serial.end());
			random_shuffle(serial.begin(), serial.end(), myrandom);



			for (std::vector<int>::iterator it = serial.begin(); it != serial.end(); ++it)
			{
				int i = *it;
				if (solution[i][j][k] > 0)
				{
					int sk = solution[i][j][k];
					if (nurses[i].skills.size() > 1)
					{
						var_nurse.push_back(make_pair(nurses[i].skills.size(), i));
					}
					else
						skl[sk - 1]++;

				}
			}
			sort(var_nurse.begin(), var_nurse.end());



			for (int i = 0;i < no_skills;i++)
			{
				skil_need.push_back(make_pair(skl[i] - requirements_minimum[j][k][i], i));

			}

			sort(skil_need.begin(), skil_need.end());

			for (int i = 0;i < skil_need.size();i++)
			{
				int iter = 0;
				while (skil_need[i].first < 0 && iter < -1 * skil_need[i].first * 5)
				{
					iter++;
					int skl = skil_need[i].second;
					bool f = 0;
					for (int l = 0;l < var_nurse.size();l++)
					{
						int nur = var_nurse[l].second;
						if (nurse_have_skill(nur, skl))
						{

							solution[nur][j][k] = skl + 1;
							skil_need[i].first++;
							var_nurse.erase(var_nurse.begin() + l);

						}
					}


				}



			}
			for (int i = 0;i < var_nurse.size();i++)
			{
				//int skl_cnt = var_nurse[i].first;
				int nur = var_nurse[i].second;
				int sft = k;
				day_var.push_back(make_pair(nur, sft));
				solution[nur][j][k] = 0;
			}




		}



		vector<pair<int, int>>r_n_s;

		for (int k = 0;k < no_shift_types;k++)
		{


			for (int i = 0;i < no_skills;i++)
			{

				int cnt = 0;
				for (int l = 0;l < no_nurses;l++)
				{
					if (i == solution[l][j][k] - 1)
						cnt++;
				}

				//req[i] += max(requirements_minimum[j][k][i] - cnt, 0);
				//out << req << " ";

				//r_t += max(requirements_minimum[r_d][k][i] - cnt, 0);
				for (int j = 0;j < requirements_minimum[j][k][i] - cnt;j++)
					r_n_s.push_back(make_pair(i, k));


			}
		}
		int itr = 0;
		while (r_n_s.size() > 0 && itr < 500)
		{
			//vailidator();
			//cout << ds.size() << " " << r_n_s.size() << endl;
			itr++;
			int rnd_ind = rand() % r_n_s.size();
			int skl = r_n_s[rnd_ind].first;
			int sft = r_n_s[rnd_ind].second;

			bool flag = 1;
			int iter = 0;
			vector<int>chose;
			for (int i = 0;i < day_var.size();i++)
			{
				if (nurse_have_skill(day_var[i].first, skl) && conflict_check(day_var[i].first, j, sft) == 0)
					chose.push_back(i);
			}

			if (chose.size() > 0)
			{
				int ind = chose[rand() % chose.size()];

				solution[day_var[ind].first][j][sft] = skl + 1;
				r_n_s.erase(r_n_s.begin() + rnd_ind);
				day_var.erase(day_var.begin() + ind);

			}



		}






	}





}






void repair5()
{

	memset(nurse_check_per_day, -1, sizeof nurse_check_per_day);
	vector<int>ds;

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		ds.push_back(i);
	}




	while (ds.size() != 0)
	{

		int rnd = rand() % ds.size();
		//out << ds[rnd]<<" "<<ds.size()<<endl;


		int r_d = ds[rnd];


		//out << r_d << " " << r_sft << " ";
		int r_t = 0;


		memset(req, 0, sizeof req);
		vector<pair<int, int>>r_n_s;

		for (int k = 0;k < no_shift_types;k++)
		{


			for (int i = 0;i < no_skills;i++)
			{

				int cnt = 0;
				for (int l = 0;l < no_nurses;l++)
				{
					if (i == solution[l][r_d][k] - 1)
						cnt++;
				}

				req[i] += max(requirements_minimum[r_d][k][i] - cnt, 0);
				//out << req << " ";

				r_t += max(requirements_minimum[r_d][k][i] - cnt, 0);
				for (int j = 0;j < requirements_minimum[r_d][k][i] - cnt;j++)
					r_n_s.push_back(make_pair(i, k));


			}
		}

		//cout << 1;
		int nurse_day[100];
		memset(nurse_day, -1, sizeof nurse_day);
		vector<int>variable;
		set<int>chosen;
		int itr = 0;
		nurse_space_create();
		while (r_n_s.size() > 0 && itr < 50)
		{
			//vailidator();
			//cout << ds.size() << " " << r_n_s.size() << endl;
			itr++;
			int rnd_ind = rand() % r_n_s.size();
			int skl = r_n_s[rnd_ind].first;
			int sft = r_n_s[rnd_ind].second;

			bool flag = 1;
			int iter = 0;
		

			while (flag && iter < 500)
			{
				iter++;


				int rnd_nur_ind = rand() % nurse_space[skl].size();
				int nur = nurse_space[skl][rnd_nur_ind];



				auto it = find(variable.begin(), variable.end(), nur);
				if (it != variable.end() && conflict_check(nur, r_d, sft) == 0)
				{
					for (int k = 0;k < no_shift_types;k++)
					{
						if (solution[nur][r_d][k] > 0)
						{
							r_n_s.push_back(make_pair(solution[nur][r_d][k] - 1, k));
							solution[nur][r_d][k] = 0;
						}

					}
					solution[nur][r_d][sft] = skl + 1;
					r_n_s.erase(r_n_s.begin() + rnd_ind);
					flag = 0;
					iter = 0;
				}





				if (iter > 250 && flag == 1)
				{

					if (chosen.find(nurse_space[skl][rnd_nur_ind]) == chosen.end() && solution[nurse_space[skl][rnd_nur_ind]][r_d][sft] == 0 && conflict_check(nur, r_d, sft) == 0)
					{
						chosen.insert(nurse_space[skl][rnd_nur_ind]);

						solution[nur][r_d][sft] = skl + 1;
						if (nurses[nur].skills.size() > 0)
						{
							variable.push_back(nur);

						}

						r_n_s.erase(r_n_s.begin() + rnd_ind);
						flag = 0;
						iter = 0;
					}



				}
				if (iter > 400 && flag == 1)
				{
					withdraw(nur, r_d, sft);
					if (conflict_check(nur, r_d, sft) == 0 && solution[nurse_space[skl][rnd_nur_ind]][r_d][sft] == 0)
					{
						solution[nur][r_d][sft] = skl + 1;
						r_n_s.erase(r_n_s.begin() + rnd_ind);
						flag = 0;
						iter = 0;
					}

				}




			}





		}





		//show_solution();
		//vailidator();
		//out << endl << endl;

		ds.erase(ds.begin() + rnd);

	}


	//show_solution();
	//vailidator();










}









void optimalition()
{

	memset(nurse_check_per_day, -1, sizeof nurse_check_per_day);
	vector<int>ds;

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		ds.push_back(i);
	}




	while (ds.size() != 0)
	{

		int rnd = rand() % ds.size();
		//out << ds[rnd]<<" "<<ds.size()<<endl;


		int r_d = ds[rnd];


		//out << r_d << " " << r_sft << " ";
		int r_t = 0;


		memset(req, 0, sizeof req);
		vector<pair<int, int>>r_n_s;

		for (int k = 0;k < no_shift_types;k++)
		{


			for (int i = 0;i < no_skills;i++)
			{

				int cnt = 0;
				for (int l = 0;l < no_nurses;l++)
				{
					if (i == solution[l][r_d][k] - 1)
						cnt++;
				}

				req[i] += max(requirements_optimal[r_d][k][i] - cnt, 0);
				//out << req << " ";

				r_t += max(requirements_optimal[r_d][k][i] - cnt, 0);
				for (int j = 0;j < requirements_optimal[r_d][k][i] - cnt;j++)
					r_n_s.push_back(make_pair(i, k));


			}
		}

		//cout << 1;
		int nurse_day[100];
		memset(nurse_day, -1, sizeof nurse_day);
		vector<int>variable;
		set<int>chosen;
		int itr = 0;
		while (r_n_s.size() > 0 && itr < 1)
		{
			//vailidator();
			//cout << "opti"<<ds.size() << " " << r_n_s.size() << endl;
			itr++;
			int rnd_ind = rand() % r_n_s.size();
			int skl = r_n_s[rnd_ind].first;
			int sft = r_n_s[rnd_ind].second;

			bool flag = 1;
			int iter = 0;
			nurse_space_update(r_d);
			while (flag && iter < 2)
			{
				iter++;


				int rnd_nur_ind = rand() % update_nurse_space[skl].size();
				int nur = update_nurse_space[skl][rnd_nur_ind];
				if (chosen.find(update_nurse_space[skl][rnd_nur_ind]) == chosen.end() && solution[update_nurse_space[skl][rnd_nur_ind]][r_d][sft] == 0 && conflict_check(nur, r_d, sft) == 0)
				{
					chosen.insert(update_nurse_space[skl][rnd_nur_ind]);


					solution[nur][r_d][sft] = skl + 1;
					if (nurses[nur].skills.size() > 0)
					{
						variable.push_back(nur);

					}

					r_n_s.erase(r_n_s.begin() + rnd_ind);
					flag = 0;
					iter = 0;
				}

				if (iter > 2 && flag == 1)
				{

					auto it = find(variable.begin(), variable.end(), nur);
					if (it != variable.end() && conflict_check(nur, r_d, sft) == 0)
					{
						for (int k = 0;k < no_shift_types;k++)
						{
							if (solution[nur][r_d][k] > 0)
							{
								r_n_s.push_back(make_pair(solution[nur][r_d][k] - 1, k));
								solution[nur][r_d][k] = 0;
							}

						}
						solution[nur][r_d][sft] = skl + 1;
						r_n_s.erase(r_n_s.begin() + rnd_ind);
						flag = 0;
						iter = 0;
					}


				}





			}





		}





		//show_solution();
		//vailidator();
		//out << endl << endl;

		ds.erase(ds.begin() + rnd);

	}


	//show_solution();
	//vailidator();










}


















int hard_validator1()
{
	int flag = 0;
	for (int i = 0;i < no_nurses;i++)
	{

		for (int j = 0;j < no_weeks * 7;j++)
		{
			bool f = 0;

			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					if (f == 1)
					{
						flag++;
						//break;
					}

					f = 1;

				}

			}
		}

	}
	return flag;
}

void print_req_minimum()
{
	for (int i = 0;i < no_weeks * 7;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				out << requirements_minimum[i][j][k] << " ";
			}
			out << " ";
		}
		out << endl << endl;
	}


}


void print_req_fulfil()
{
	for (int i = 0;i < no_weeks * 7;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				out << requirements_fulfil[i][j][k] << " ";
			}
			out << " ";
		}
		out << endl << endl;
	}
}

int hard_validator2()
{

	int total = 0;

	memset(requirements_fulfil, 0, sizeof requirements_fulfil);

	for (int i = 0;i < no_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{

			int t = 0, tt = 0;
			for (int k = 0;k < no_skills;k++)
			{
				t += requirements_minimum[i][j][k];
			}

			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
					tt++;
			}

			if (t > tt)
				total += t - tt;

		}


	}




	return total;

}


int evoluation()
{
	//out << "h1" << endl;
	int h1 = hard_validator1();
	//show_solution();
	int h2 = hard_validator2();
	int h4 = hard_validator4();
	//show_solution();
	int h3 = hard_validator3();
	//show_solution();
	//out << "s1" << endl;
	int s1 = soft_validator1();
	//show_solution();
	//out << "s2" << endl;
	int s2 = soft_validator2();
	//show_solution();

	//out << "s3" << endl;
	int s3 = soft_validator3();
	//show_solution();
	//out << "s4" << endl;
	int s4 = soft_validator4();
	//show_solution();
	//out << "s5" << endl;
	int s5 = soft_validator5();
	//show_solution();
	int s6 = soft_validator6();
	//show_solution();
	int s7 = soft_validator7();
	//show_solution();
	out << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s6 << " " << s7 << endl;
	return s1 + s2 + s3 + s4 + s5 + s6 + s7;
}


void save_prev()
{


	for (int i = 0;i < no_nurses;i++)
	{
		for (int j = 0;j < no_weeks * 7;j++)
		{
			for (int k = 0;k < no_shift_types;k++)
			{
				prev_solution[i][j][k] = solution[i][j][k];
			}
		}
	}

}

void back_to_prev()
{

	for (int i = 0;i < no_nurses;i++)
	{
		for (int j = 0;j < no_weeks * 7;j++)
		{
			for (int k = 0;k < no_shift_types;k++)
			{
				solution[i][j][k] = prev_solution[i][j][k];
			}
		}
	}






}



void print_particle()
{
	for (int ind = 0;ind <= no_particle;ind++)
	{
		out << ind << endl;
		for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
		{
			out << particle[ind].sequence[i][0] << particle[ind].sequence[i][0] << " ";


		}
		out << endl;
	}
}

void print_gbest()
{

	out << "gbest" << endl;

	for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
	{
		out << gbest[i][0] << gbest[i][0] << " ";


	}
	out << endl;

}




void gbest_update(int ind)
{

	for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
	{
		gbest[i][0] = particle[ind].pbest[i][0];
		gbest[i][1] = particle[ind].pbest[i][1];

	}
	gbest_val = particle[ind].pbest_val;


}

void pbest_update(int ind)
{


	for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
	{
		particle[ind].pbest[i][0] = particle[ind].sequence[i][0];
		particle[ind].pbest[i][1] = particle[ind].sequence[i][1];

	}
	particle[ind].pbest_val = particle[ind].sequence_val;
	//out << "seq_val --" << particle[ind].sequence_val << " " << particle[ind].pbest_val << endl;


}
int g_bset_ind=-1;

void particle_create(int sum)
{
	++no_particle;
	int ind = 0;
	//out << "evo"<<sum << endl;
	particle[no_particle].sequence_val = sum;
	//out <<"seq_val"<<particle[no_particle].sequence_val << endl;
	for (int i = 0;i < no_nurses;i++)
	{
		for (int j = 0;j < no_weeks * 7;j++)
		{
			int skill = 0;
			int sft = -1;
			for (int k = 0;k < no_shift_types;k++)
			{

				if (solution[i][j][k] > 0)
				{
					skill = solution[i][j][k];
					sft = k;
					break;
				}

			}
			particle[no_particle].sequence[ind][0] = sft;
			particle[no_particle].sequence[ind][1] = skill;
			ind++;

		}
	}
	//out << "seq_val" << particle[no_particle].sequence_val << endl;
	pbest_update(no_particle);

	//out << "-------" << no_particle << "---------" << endl;
	print_particle();
	//out << "pp" << endl;
	//out << particle[no_particle].pbest_val << endl;
//	out << "pp" << endl;
	if (sum <= gbest_val)
	{
		//	out << "pp" << endl;
		gbest_update(no_particle);
		g_bset_ind = no_particle;
		//print_gbest();
		//out <<"val"<< gbest_val << endl << endl;
	}




	out << endl;



}



void solution_to_particle(int ind)
{
	//particle[ind].sequence[ind].clear();
	//particle[ind].sequence_val = sum;
	//out <<"seq_val"<<particle[no_particle].sequence_val << endl;

	int d = -1;
	for (int i = 0;i < no_nurses;i++)
	{
		for (int j = 0;j < no_weeks * 7;j++)
		{
			int skill = 0;
			int sft = -1;
			++d;
			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					skill = solution[i][j][k];
					sft = k;
					break;
				}
			}
			particle[ind].sequence[d][0] = sft;
			particle[ind].sequence[d][1] = skill;
	

		}
	}
	//out << "seq_val" << particle[no_particle].sequence_val << endl;




	//out << endl;



}



vector< pair< int, pair<int, int>>>swap_seq_p;
vector< pair< int, pair<int, int>>>swap_seq_g;
void swap_sequence_pbst(int ind)
{
	swap_seq_p.clear();

	for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
	{
		if (particle[ind].pbest[i][0] != particle[ind].sequence[i][0] || particle[ind].pbest[i][1] != particle[ind].sequence[i][1])
		{

			//int a = pbest[i][0], b = pbest[i][1];
			//swap_seq.push_back(make_pair(i, make_pair(i,)));

			swap_seq_p.push_back(make_pair(i, make_pair(particle[ind].pbest[i][0] - particle[ind].sequence[i][0], particle[ind].pbest[i][1] - particle[ind].sequence[i][1])));
		}

	}







}
void swap_sequence_gbst(int ind)
{
	//cout << ind << endl;
	swap_seq_g.clear();

	for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
	{
		//cout << i << endl;
		//cout << gbest[i][0] << " " << particle[ind].sequence[i][0] << "      " << gbest[i][1] << " " << particle[ind].sequence[i][1]<<endl;
		if (gbest[i][0] != particle[ind].sequence[i][0] || gbest[i][1] != particle[ind].sequence[i][1])
		{
			//	out << "-=-=-" << endl;
				//int a = pbest[i][0], b = pbest[i][1];
				//swap_seq.push_back(make_pair(i, make_pair(i,)));

			swap_seq_g.push_back(make_pair(i, make_pair(gbest[i][0] - particle[ind].sequence[i][0], gbest[i][1] - particle[ind].sequence[i][1])));
		}

	}







}


void gbest_to_solution()
{

	for (int j = 0;j < no_nurses + 1;j++)
	{
		for (int k = 0;k < no_weeks * 7 + 1;k++)
		{
			memset(solution[j][k], 0, sizeof solution[j][k]);
			memset(sol[j][k], 0, sizeof sol[j][k]);
		}
	}

	int i = 0;



	for (int j = 0;j < no_nurses;j++)
	{
		for (int k = 0;k < no_weeks * 7;k++)
		{

			int sft = gbest[i][0];
			int skl = gbest[i][1];
			if (sft != -1)
				solution[j][k][sft] = skl;
			else
				solution[j][k][sft] = 0;
			i++;
		}
	}

}







void particle_to_solution(int ind)
{

	for (int j = 0;j < no_nurses + 1;j++)
	{
		for (int k = 0;k < no_weeks * 7 + 1;k++)
		{
			memset(solution[j][k], 0, sizeof solution[j][k]);
			memset(sol[j][k], 0, sizeof sol[j][k]);
		}
	}

	int i = 0;



	for (int j = 0;j < no_nurses;j++)
	{
		for (int k = 0;k < no_weeks * 7;k++)
		{

			int sft = particle[ind].sequence[i][0];
			int skl = particle[ind].sequence[i][1];
			if (sft != -1)
				solution[j][k][sft] = skl;
			else
				solution[j][k][sft] = 0;
			i++;
		}
	}

}


void swap(int ind)
{
	out << "index" << ind << endl;
	particle_to_solution(ind);

	save_prev();

                      
	

	swap_sequence_pbst(ind);


	out << "prev" << evoluation() << " " << hard_validator1() << " " << hard_validator2() << " " << hard_validator3() << " " << hard_validator4() << endl;

	//out << "---" << swap_seq_p.size() << " ";

	for (int i = 0;i < swap_seq_p.size();i++)
	{

		int d = swap_seq_p[i].first;
		int sft = swap_seq_p[i].second.first;
		int skl = swap_seq_p[i].second.second;

		//out << d << " " << sft << " " << skl << endl;
		int r = rand() % 10;
		if (r < 5)
			continue;

		particle_to_solution(ind);

		int nr = floor(d /(no_weeks * 7));
		int dd = d % (no_weeks * 7);
		if (conflict_check(nr, dd, particle[ind].sequence[d][0] + sft) == 0)
		{
			particle[ind].sequence[d][0] = particle[ind].sequence[d][0] + sft;
			particle[ind].sequence[d][1] = particle[ind].sequence[d][1] + skl;
		}



	}
	//out << "^5^^^" << endl;

	swap_sequence_gbst(ind);
	out << swap_seq_g.size() << endl;
	for (int i = 0;i < swap_seq_g.size();i++)
	{
		int d = swap_seq_g[i].first;
		int sft = swap_seq_g[i].second.first;
		int skl = swap_seq_g[i].second.second;



		//out << d << " " << sft << " " << skl << endl;
		int r = rand() % 10;
		if (r < 5)
			continue;




		particle_to_solution(ind);

		int nr = floor(d / (no_weeks * 7));
		int dd = d % (no_weeks * 7);

		if (conflict_check(nr, dd, particle[ind].sequence[d][0] + sft) == 0)
		{
			particle[ind].sequence[d][0] = particle[ind].sequence[d][0] + sft;
			particle[ind].sequence[d][1] = particle[ind].sequence[d][1] + skl;
		}




	}
	//out << "^^^^" << endl;
	particle_to_solution(ind);



	int h1 = hard_validator1();
	int h2 = hard_validator2();
	int h4 = hard_validator4();
	int h3 = hard_validator3();
	out << "aftr" << evoluation() << " " << hard_validator1() << " " << hard_validator2() << " " << hard_validator3() << " " << hard_validator4() << endl;
	//show_solution();
	int trial = 0;

	while ((h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0) && trial < 5)
	{
		trial++;
		repair5();
	}

	 h1 = hard_validator1();
	h2 = hard_validator2();
	 h4 = hard_validator4();
	 h3 = hard_validator3();

	 out << "aftr repair" << evoluation() << " " << h1 << " " << h2 << " " << h3 << " " << h4 << endl;
	 show_solution();



	if((h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0) )
	 {
		 back_to_prev();


	 }


	h1 = hard_validator1();
	h2 = hard_validator2();
	h4 = hard_validator4();
	h3 = hard_validator3();

	out << "final" << evoluation() << " " << h1 << " " << h2 << " " << h3 << " " << h4 << endl;


	int sum = evoluation();
	particle[ind].sequence_val = sum;	

	solution_to_particle(ind);

	if (sum < particle[ind].pbest_val)
	{
		pbest_update(ind);


	}




}


void pso()
{
	out << "~~~~~~~~~~~~~~~~~~~~~~~~~~PSO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	//print_particle();
	//print_gbest();

	






	for (int iter = 0;iter < 50;iter++)
	{

		out << "~~~~~~~PSO~~~~~~~~~~  " <<iter<< endl;
		cout << "~~~~~~~PSO~~~~~~~~~~  " << iter << endl;
		for (int i = 0;i <= no_particle;i++)
		{

			swap(i);




		}

		for (int i = 0;i < no_particle;i++)
		{

			if (particle[i].pbest_val < gbest_val)
			{
				gbest_val = particle[i].pbest_val;
				gbest_update(i);
				particle_to_solution(i);

				out << "------------------------" << endl;
				show_solution();

				out << evoluation() << endl;

			}



		}

	}



}

vector<int>skill_group[20][20];



void skil_group()
{
	for (int i = 0;i < no_skills;i++)
	{

		for (int j = 0;j < no_skills;j++)
		{
			

			for (int k = 0;k < no_nurses;k++)
			{
				if (nurse_have_skill(k, i) && nurse_have_skill(k, j))
				{
					skill_group[i][j].push_back(k);
					skill_group[j][i].push_back(k);

				}
			}

		}


	}






}



vector <pair<int,  int> > swapsp,swapsg;



void swap_sequence_pbst1(int ind)
{

	

	for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
	{
		if (particle[ind].pbest[i][0] != particle[ind].sequence[i][0] || particle[ind].pbest[i][1] != particle[ind].sequence[i][1])
		{
			int pbest_skill = particle[ind].pbest[i][1];
			int particle_skill = particle[ind].sequence[i][1];
			int particle_sft= particle[ind].sequence[i][0];
			int pbest_sft = particle[ind].pbest[i][0];
			int f = 0;
			for (int j = 0;j < no_nurses;j++)
			{
				int nur = floor(i / (no_weeks * 7));
				if (j == nur)
					continue;
				//	int in = j * no_weeks * 7 + i % (no_weeks * 7);
				

				int rnd = rand() % 10;


				if (particle[ind].sequence[j*no_weeks * 7 + (i % (no_weeks * 7))][0] == particle[ind].pbest[i][0] && particle[ind].pbest[i][1]== particle[ind].sequence[j*no_weeks * 7 + (i % (no_weeks * 7))][1] && nurse_have_skill(j, particle_skill - 1) && rnd>5
					&& conflict_check(nur,i%7*no_weeks, pbest_sft)==0 && conflict_check(j, i% 7*no_weeks, particle_sft)==0)
				{
					particle[ind].sequence[i][0] = particle[ind].pbest[i][0];
					particle[ind].sequence[i][1] = particle[ind].pbest[i][1];


					//if (nurse_have_skill(j, particle_skill - 1))
					//{
						particle[ind].sequence[j*no_weeks * 7 +( i % (no_weeks * 7))][0] = particle_sft;
						particle[ind].sequence[j*no_weeks * 7 + (i % (no_weeks * 7))][1] = particle_skill;
						//swapsp.push_back(make_pair(i, j*no_weeks * 7 + (i % (no_weeks * 7))));
					





						



						f = 1;
						particle_to_solution(ind);

						int x = i % (7 * no_weeks) - 1;
						//int y = (j * no_weeks * 7 + (i % (no_weeks * 7))) % (7 * no_weeks);





						int particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
						int particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

						int particle_skill_j = particle[ind].sequence[j*no_weeks * 7 + x][1];
						int particle_sft_j = particle[ind].sequence[j*no_weeks * 7 + x][0];



						while ((conflict_check(nur, x, particle_sft_nur) == 1 || conflict_check(j, x, particle_sft_j) == 1) && x >= 0)
						{

							particle[ind].sequence[x + (nur*no_weeks * 7)][0] = particle_sft_j;
							particle[ind].sequence[x + (nur*no_weeks * 7)][1] = particle_skill_j;


							//if (nurse_have_skill(j, particle_skill - 1))
							//{
							particle[ind].sequence[j*no_weeks * 7 + x][0] = particle_sft_nur;
							particle[ind].sequence[j*no_weeks * 7 + x][1] = particle_skill_nur;


							
								particle_to_solution(ind);
								if ((conflict_check(nur, x, particle_sft_j) == 1) || (conflict_check(j, x, particle_sft_nur) == 1))
								{
									if ((conflict_check(nur, x, particle_sft_j) == 1))
									{
										particle[ind].sequence[x + (nur*no_weeks * 7)][0] = -1;
										particle[ind].sequence[x + (nur*no_weeks * 7)][1] = 0;
									}

									if ((conflict_check(j, x, particle_sft_nur) == 1))
									{
										particle[ind].sequence[x + (j*no_weeks * 7)][0] = -1;
										particle[ind].sequence[x + (j*no_weeks * 7)][1] = 0;

									}

									break;
								}
							


							x--;
							if (x < 0)
								continue;

						
							particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
							particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

							particle_skill_j = particle[ind].sequence[j*no_weeks * 7 + x][1];
							particle_sft_j = particle[ind].sequence[j*no_weeks * 7 + x][0];

							particle_to_solution(ind);
							f = 1;



							//  swapsg.push_back(make_pair(i, j*no_weeks * 7 + (i % (no_weeks * 7))));



						}




						particle_to_solution(ind);
						x = i % (7 * no_weeks) + 1;
						//int y = (j * no_weeks * 7 + (i % (no_weeks * 7))) % (7 * no_weeks);





						particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
						particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

						particle_skill_j = particle[ind].sequence[j*no_weeks * 7 + x][1];
						particle_sft_j = particle[ind].sequence[j*no_weeks * 7 + x][0];

						while ((conflict_check(nur, x, particle_sft_nur) == 1 || conflict_check(j, x, particle_sft_j) == 1) && x < no_weeks * 7)
						{

							particle[ind].sequence[x + (nur*no_weeks * 7)][0] = particle_sft_j;
							particle[ind].sequence[x + (nur*no_weeks * 7)][1] = particle_skill_j;


							//if (nurse_have_skill(j, particle_skill - 1))
							//{
							particle[ind].sequence[j*no_weeks * 7 + x][0] = particle_sft_nur;
							particle[ind].sequence[j*no_weeks * 7 + x][1] = particle_skill_nur;


							particle_to_solution(ind);
							if ((conflict_check(nur, x, particle_sft_j) == 1) || (conflict_check(j, x, particle_sft_nur) == 1))
							{
								if ((conflict_check(nur, x, particle_sft_j) == 1))
								{
									particle[ind].sequence[x + (nur*no_weeks * 7)][0] = -1;
									particle[ind].sequence[x + (nur*no_weeks * 7)][1] = 0;
								}

								if ((conflict_check(j, x, particle_sft_nur) == 1))
								{
									particle[ind].sequence[x + (j*no_weeks * 7)][0] = -1;
									particle[ind].sequence[x + (j*no_weeks * 7)][1] = 0;

								}

								break;
							}
							x++;
							if (x >= no_weeks * 7)
								continue;
							particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
							particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

							particle_skill_j = particle[ind].sequence[j*no_weeks * 7 + x][1];
							particle_sft_j = particle[ind].sequence[j*no_weeks * 7 + x][0];

							particle_to_solution(ind);
							f = 1;



							//  swapsg.push_back(make_pair(i, j*no_weeks * 7 + (i % (no_weeks * 7))));



						}

						if (f == 1)
							break;

				}




			}
		



			//swap_seq_p.push_back(make_pair(i, make_pair(particle[ind].pbest[i][0] - particle[ind].sequence[i][0], particle[ind].pbest[i][1] - particle[ind].sequence[i][1])));
		
		}

	}


	//for (int i = 0;i < 5;i++)
	//	repair5();

}



void swap_sequence_gbst1(int ind)
{



	for (int i = 0;i < no_weeks * 7 * no_nurses;i++)
	{
		if (gbest[i][0] != particle[ind].sequence[i][0] || gbest[i][1] != particle[ind].sequence[i][1])
		{
			int pbest_skill = gbest[i][1];
			int pbest_sft = gbest[i][0];
			int particle_skill = particle[ind].sequence[i][1];
			int particle_sft = particle[ind].sequence[i][0];

			int da = i % (7 * no_weeks);

			int f = 0;


			for (int j = 0;j < no_nurses;j++)
			{
				int nur = floor(i / (no_weeks * 7));
				if (j == nur)
					continue;
			//	int in = j * no_weeks * 7 + i % (no_weeks * 7);

				int rnd = rand() % 10;

				if (particle[ind].sequence[j*no_weeks * 7 + (i%(no_weeks * 7))][0] == gbest[i][0] && gbest[i][1] == particle[ind].sequence[j*no_weeks * 7 +( i%(no_weeks * 7))][1] && nurse_have_skill(j, particle_skill - 1) && rnd>5
					&& conflict_check(nur, i % 7 * no_weeks, pbest_sft)==0 && conflict_check(j, i % 7 * no_weeks, particle_sft)==0)
				{
					
					
					particle[ind].sequence[i][0] = gbest[i][0];
					particle[ind].sequence[i][1] = gbest[i][1];


					//if (nurse_have_skill(j, particle_skill - 1))
					//{
					particle[ind].sequence[j*no_weeks * 7 + i % (no_weeks * 7)][0] = particle_sft;
					particle[ind].sequence[j*no_weeks * 7 + i % (no_weeks * 7)][1] = particle_skill;

					f = 1;
					particle_to_solution(ind);

					int x= i % (7 * no_weeks)-1;
					//int y = (j * no_weeks * 7 + (i % (no_weeks * 7))) % (7 * no_weeks);

					

					
					
					int particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
					int particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

					int particle_skill_j = particle[ind].sequence[j*no_weeks * 7+x ][1];
					int particle_sft_j = particle[ind].sequence[j*no_weeks * 7+x ][0];
					


					while((conflict_check(nur, x, particle_sft_nur)==1 || conflict_check(j,x, particle_sft_j) == 1 ) &&  x>=0 )
					{
						
						particle[ind].sequence[x + (nur*no_weeks * 7)][0] = particle_sft_j;
						particle[ind].sequence[x + (nur*no_weeks * 7)][1] = particle_skill_j;


					//if (nurse_have_skill(j, particle_skill - 1))
					//{
						particle[ind].sequence[j*no_weeks * 7 + x][0] = particle_sft_nur;
						particle[ind].sequence[j*no_weeks * 7 + x][1] = particle_skill_nur;

						particle_to_solution(ind);
						if ((conflict_check(nur, x, particle_sft_j) == 1) || (conflict_check(j, x, particle_sft_nur) == 1))
						{
							if ((conflict_check(nur, x, particle_sft_j) == 1))
							{
								particle[ind].sequence[x + (nur*no_weeks * 7)][0] = -1;
								particle[ind].sequence[x + (nur*no_weeks * 7)][1] = 0;
							}

							if ((conflict_check(j, x, particle_sft_nur) == 1))
							{
								particle[ind].sequence[x + (j*no_weeks * 7)][0] = -1;
								particle[ind].sequence[x + (j*no_weeks * 7)][1] = 0;

							}

							break;
						}

						


						x--;
						if (x < 0)
							continue;
						 particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
						 particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

						 particle_skill_j = particle[ind].sequence[j*no_weeks * 7 + x][1];
					    particle_sft_j = particle[ind].sequence[j*no_weeks * 7 + x][0];

						particle_to_solution(ind);
						f = 1;
				


					  //  swapsg.push_back(make_pair(i, j*no_weeks * 7 + (i % (no_weeks * 7))));
						
					

					}




					particle_to_solution(ind);
					 x = i % (7 * no_weeks) + 1;
					//int y = (j * no_weeks * 7 + (i % (no_weeks * 7))) % (7 * no_weeks);





					particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
			        particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

					 particle_skill_j = particle[ind].sequence[j*no_weeks * 7 + x][1];
					 particle_sft_j = particle[ind].sequence[j*no_weeks * 7 + x][0];

					 while ((conflict_check(nur, x, particle_sft_nur) == 1 || conflict_check(j, x, particle_sft_j) == 1) && x <no_weeks*7)
					 {

						 particle[ind].sequence[x + (nur*no_weeks * 7)][0] = particle_sft_j;
						 particle[ind].sequence[x + (nur*no_weeks * 7)][1] = particle_skill_j;


						 //if (nurse_have_skill(j, particle_skill - 1))
						 //{
						 particle[ind].sequence[j*no_weeks * 7 + x][0] = particle_sft_nur;
						 particle[ind].sequence[j*no_weeks * 7 + x][1] = particle_skill_nur;


						 particle_to_solution(ind);
						 if ((conflict_check(nur, x, particle_sft_j) == 1) || (conflict_check(j, x, particle_sft_nur) == 1))
						 {
							 if ((conflict_check(nur, x, particle_sft_j) == 1) )
							 {
								 particle[ind].sequence[x + (nur*no_weeks * 7)][0] = -1;
								 particle[ind].sequence[x + (nur*no_weeks * 7)][1] = 0;
							 }

							 if ((conflict_check(j, x, particle_sft_nur) == 1))
							 {
								 particle[ind].sequence[x + (j*no_weeks * 7)][0] = -1;
								 particle[ind].sequence[x + (j*no_weeks * 7)][1] = 0;

							 }

							 break;
						 }

						 

						 x++;
						 if (x >= no_weeks*7)
							 continue;
						 particle_skill_nur = particle[ind].sequence[nur*no_weeks * 7 + x][1];
						 particle_sft_nur = particle[ind].sequence[nur*no_weeks * 7 + x][0];

						 particle_skill_j = particle[ind].sequence[j*no_weeks * 7 + x][1];
						 particle_sft_j = particle[ind].sequence[j*no_weeks * 7 + x][0];

						 particle_to_solution(ind);
						 f = 1;



						 //  swapsg.push_back(make_pair(i, j*no_weeks * 7 + (i % (no_weeks * 7))));



					 }

					if (f == 1)
						break;

					}

			}




			//swap_seq_p.push_back(make_pair(i, make_pair(particle[ind].pbest[i][0] - particle[ind].sequence[i][0], particle[ind].pbest[i][1] - particle[ind].sequence[i][1])));

		}

	}
	//for (int i = 0;i < 5;i++)
	//	repair5();


}

void swap1(int ind)
{
	out << "index" << ind << endl;
	particle_to_solution(ind);

	save_prev();



	//

	swap_sequence_pbst1(ind);
	particle_to_solution(ind);
	out << "p_best" << evoluation() << " " << hard_validator1() << " " << hard_validator2() << " " << hard_validator3() << " " << hard_validator4() << endl;

	
	swap_sequence_gbst1(ind);


/*
	for (int kk = 0;kk < swapsp.size();kk++)
	{
		
			int ii = swapsp[kk].first;
			int jj = swapsp[kk].second;
			int particle_sft = particle[ind].sequence[ii][0];
			int particle_skill = particle[ind].sequence[ii][1];
			particle[ind].sequence[ii][0] = particle[ind].pbest[ii][0];
			particle[ind].sequence[ii][1] = particle[ind].pbest[ii][1];


			//if (nurse_have_skill(j, particle_skill - 1))
			//{
			particle[ind].sequence[jj][0] = particle_sft;
			particle[ind].sequence[jj][1] = particle_skill;
			//}


		
	}


	for (int kk = 0;kk < swapsg.size();kk++)
	{
		
			int ii = swapsg[kk].first;
			int jj = swapsg[kk].second;
			int particle_sft = particle[ind].sequence[ii][0];
			int particle_skill = particle[ind].sequence[ii][1];
			particle[ind].sequence[ii][0] = gbest[ii][0];
			particle[ind].sequence[ii][1] = gbest[ii][1];


			//if (nurse_have_skill(j, particle_skill - 1))
			//{
			particle[ind].sequence[jj][0] = particle_sft;
			particle[ind].sequence[jj][1] = particle_skill;
			//}


		
	}

*/
	particle_to_solution(ind);
	out << "g_best" << evoluation() << " " << hard_validator1() << " " << hard_validator2() << " " << hard_validator3() << " " << hard_validator4() << endl;

	//out << "---" << swap_seq_p.size() << " ";


	show_solution();
	out << endl << endl;
	
	//out << "^^^^" << endl;
	


	int trial = 0;

	int h1 = hard_validator1();
	int h2 = hard_validator2();
	int h4 = hard_validator4();
	int h3 = hard_validator3();

	while ((h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0) && trial < 2)
	{
		trial++;
		//repair5();
	}

	

	//out << "aftr repair" << evoluation() << " " << h1 << " " << h2 << " " << h3 << " " << h4 << endl;
	//show_solution();

	 h1 = hard_validator1();
	 h2 = hard_validator2();
	 h4 = hard_validator4();
	h3 = hard_validator3();

	if ((h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0))
	{
		//back_to_prev();


	}


	h1 = hard_validator1();
	h2 = hard_validator2();
	h4 = hard_validator4();
	h3 = hard_validator3();

	int sum = evoluation();

	out << "final" << sum << " " << h1 << " " << h2 << " " << h3 << " " << h4 << endl;
	

	
	particle[ind].sequence_val = sum;	
	solution_to_particle(ind);


	if (sum < particle[ind].pbest_val)
	{
		pbest_update(ind);


	}




}





void pso1()
{

	out << "=============================Pso==================================" << endl;


	for (int iter = 0;iter < 50;iter++)
	{

		cout << "======Pso========== " <<iter<< endl;
		for (int i = 0;i <= no_particle;i++)
		{

			swap1(i);


			

		}

		for (int i = 0;i < no_particle;i++)
		{

			if (particle[i].pbest_val < gbest_val)
			{
				gbest_val = particle[i].pbest_val;
				gbest_update(i);
				particle_to_solution(i);

				out << "------------------------" << endl;
				show_solution();

				out << evoluation() << endl;

			}



		}

	}






}


int hard_validator4()
{

	int flag = 0;

	memset(requirements_fulfil, 0, sizeof requirements_fulfil);

	for (int i = 0;i < no_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
				{
					int sk = solution[k][i][j] - 1;
					requirements_fulfil[i][j][sk]++;


				}

			}



		}


	}

	for (int i = 0;i < no_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_skills;k++)
			{
				if (requirements_fulfil[i][j][k] < requirements_minimum[i][j][k])
				{
					flag++;

				}

			}



		}


	}



	return flag;

}



int hard_validator3()
{

	int flag = 0;
	for (int i = 0;i < no_nurses;i++)
	{

		string sss = nurses[i].history.lastAssignedShiftType;
		if (sss != "None") {
			int key = shift_type_point.find(sss)->second;

			for (int l = 0;l < shift_type[key].forbiddenSucceedingShiftTypes.size();l++)
			{
				string ss = shift_type[key].forbiddenSucceedingShiftTypes[l];

				//cout << ss;
				int forbid_id = shift_type_point.find(ss)->second;
				//cout << forbid_id;
				if (solution[i][0][forbid_id] > 0)
				{
					//out << i<<" "<<j+1<<" "<<<< endl;
					flag++;
				}

			}

		}


		for (int j = 0;j < no_weeks * 7;j++)
		{
			bool f = 0;

			for (int k = 0;k < no_shift_types;k++)
			{
				if ((solution[i][j][k] > 0))
				{



					for (int l = 0;l < shift_type[k].forbiddenSucceedingShiftTypes.size();l++)
					{
						string ss = shift_type[k].forbiddenSucceedingShiftTypes[l];

						//cout << ss;
						int forbid_id = shift_type_point.find(ss)->second;
						//cout << forbid_id;
						if (solution[i][j + 1][forbid_id] > 0)
						{
							//out << i<<" "<<j+1<<" "<<<< endl;
							flag++;
						}

					}





				}

			}


		}
	}

	return flag;
}
int soft_validator1()
{

	int flag = 0;
	int total = 0;

	memset(requirements_fulfil, 0, sizeof requirements_fulfil);

	for (int i = 0;i < no_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{
			bool f = 0;

			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
				{
					int sk = solution[k][i][j];
					requirements_fulfil[i][j][sk]++;

				}

			}



		}


	}


	for (int i = 0;i < no_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_skills;k++)
			{
				int cnt = 0;
				for (int l = 0;l < no_nurses;l++)
				{
					if (k == solution[l][i][j] - 1)
						cnt++;
				}


				if (requirements_optimal[i][j][k] > cnt)
					total += (requirements_optimal[i][j][k] - cnt) * 30;

			}



		}


	}



	return total;

}
int soft_validator2()
{
	//minimumNumberOfConsecutiveWorkingDays,
		//maximumNumberOfConsecutiveWorkingDays,4
	int mn_v = 0, mx_v = 0;
	int total = 0;

	for (int i = 0;i < no_nurses;i++)
	{
		//out << "full" << total << endl;
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfConsecutiveWorkingDays;
		int mx = contracts[key].maximumNumberOfConsecutiveWorkingDays;
		//out << "--------------------------" << endl;

		int cons_day = nurses[i].history.numberOfConsecutiveWorkingDays;

		if (cons_day >= mx)
			cons_day = mx;

		for (int m = 0;m < no_weeks;m++)
		{

			bool start = 0;
			if (cons_day > 0)
				start = 1;

			for (int j = m * 7 + 0;j < m * 7 + 7;j++)
			{
				bool f = 0;

				for (int k = 0;k < no_shift_types;k++)
				{

					if (solution[i][j][k] > 0)
					{
						f = 1;
						start = 1;

					}




				}

				if (f == 1)
				{
					cons_day++;

				}

				if ((f == 0 || j == no_weeks * 7 - 1) && start == 1)
				{
					//out << j << " " << cons_day << endl;
					if (cons_day > mx)
					{
						total += (cons_day - mx) * 30;
						cons_day = 0;
						start = 0;
					}
					else if (cons_day < mn && j != no_weeks * 7 - 1)
					{
						total += (mn - cons_day) * 30;
						cons_day = 0;
						start = 0;
					}
					else if (cons_day >= mn && cons_day <= mx)
					{
						cons_day = 0;
						start = 0;
					}
				}

			}

		}
		//out << endl;



		//out << "half" << total << endl;







		//out << "@@" << mn << " " << mx << endl;
		string ss = nurses[i].history.lastAssignedShiftType;
		int lst = -1;
		if (ss != "None")
			lst = shift_type_point.find(ss)->second;






		for (int k = 0;k < no_shift_types;k++)
		{
			bool start = 0;
			int cons_sft = 0;
			mn = shift_type[k].minimumNumberOfConsecutiveAssignments;
			mx = shift_type[k].maximumNumberOfConsecutiveAssignments;

			bool f = 0;
			if (k == lst)
			{
				cons_sft = nurses[i].history.numberOfConsecutiveAssignments;

				if (cons_sft >= mx)
					cons_sft = mx;
				if (cons_sft > 0)
					start = 1;

			}

			for (int j = 0;j < no_weeks * 7;j++)
			{

				if (solution[i][j][k] > 0)
				{
					f = 1;
					start = 1;
					cons_sft++;

				}
				else
				{
					f = 0;
				}

				if ((f == 0 || j == no_weeks * 7 - 1) && start == 1)
				{

					if (cons_sft > mx)
					{
						//out <<1<<" "<< j << " " << cons_sft << endl;
						total += (cons_sft - mx) * 15;
						cons_sft = 0;
						start = 0;
					}
					else if (cons_sft < mn && j != no_weeks * 7 - 1)
					{
						//out <<2<<" "<< j << " " << cons_sft << endl;
						total += (mn - cons_sft) * 15;
						cons_sft = 0;
						start = 0;
					}
					else if (cons_sft >= mn && cons_sft <= mx)
					{
						cons_sft = 0;
						start = 0;
					}
				}




			}
		}

	}

	return total;
}
int soft_validator3()
{
	int mn_v = 0, mx_v = 0;
	int res = 0;

	for (int i = 0;i < no_nurses;i++)
	{
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfConsecutiveDaysOff;
		int mx = contracts[key].maximumNumberOfConsecutiveDaysOff;

		//out << mn << " " << mx << endl;


		int cons_dayof = nurses[i].history.numberOfConsecutiveDaysOff;
		//out << "cons_dayof"<<cons_dayof << endl;


		for (int j = 0;j < no_weeks * 7;j++)
		{
			//out << "j"<<j << endl;


			if (j < (no_weeks * 7) - 1)
			{
				bool f = 1;
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						f = 0;
					}
					//out << "k" << k << endl;
				}
				if (f == 1)
				{
					//out << "f1cons_dayof" << cons_dayof << endl;

					cons_dayof++;
					//out << "res" << res << endl;

				}
				if (f == 0)
				{
					//out << "f0" << endl;
					if (cons_dayof != 0)
					{
						//out << "f0cons_dayof" << cons_dayof << endl;
						if (cons_dayof > mx)
						{
							res += cons_dayof - mx;
							//cons_dayof = 0;
							//out << "res" << res << endl;


						}
						if (cons_dayof < mn)
						{
							res += mn - cons_dayof;
							//cons_dayof = 0;
								//out << "res" << res << endl;
						}
						cons_dayof = 0;
						//out << "cons_dayof" << cons_dayof << endl;
						//out << "res" << res << endl;
					}

				}

			}
			else
			{
				bool f = 1;
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						f = 0;
					}
					//out << "k" << k << endl;

				}
				if (f == 1)
				{
					//out << "f1cons_dayof" << cons_dayof << endl;

					cons_dayof++;
					if (cons_dayof > mx)
					{
						res += cons_dayof - mx;
						//cons_dayof = 0;
						//out << "res" << res << endl;


					}
					/*if (cons_dayof < mn)
					{
						res += mn - cons_dayof;
						//cons_dayof = 0;
						//out << "res" << res << endl;
					}*/
					cons_dayof = 0;
					//out << "res" << res << endl;

				}
				if (f == 0)
				{
					if (cons_dayof != 0)
					{
						//out << "f0cons_dayof" << cons_dayof << endl;
						if (cons_dayof > mx)
						{
							res += cons_dayof - mx;
							//cons_dayof = 0;
							//out << "res" << res << endl;


						}
						if (cons_dayof < mn)
						{
							res += mn - cons_dayof;
							//cons_dayof = 0;
							//out << "res" << res << endl;
						}
						cons_dayof = 0;
						//out << "cons_dayof" << cons_dayof << endl;
						//out << "res" << res << endl;
					}

				}





			}

		}
		//out <<"rws"<< res << endl;
	}
	//out <<"res"<< res << endl;


	return (res) * 30;

}
int soft_validator4()
{
	int flag = 0;
	for (int i = 0;i < no_nurses;i++)
	{

		for (int j = 0;j < shift_off_req[i].size();j++)
		{
			int d = shift_off_req[i][j].second;
			string shift = shift_off_req[i][j].first;

			if (shift == "Any")
			{
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][d][k] > 0)
					{
						//solution[i][d][k] = 500;


						//out << endl << i << " " << d << " " << k << endl;
						flag++;
					}

				}
			}

			else
			{

				int s = shift_type_point.find(shift)->second;

				if (solution[i][d][s] > 0)
				{
					//solution[i][d][s] = 500;
					//out << endl << i << " " << d << " " << s << endl;
					flag++;
				}
			}

		}
	}
	return flag * 10;
}
int soft_validator5()
{
	int flag = 0;
	int total = 0;
	for (int i = 0;i < no_nurses;i++)
	{

		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].completeWeekends;


		if (mn == 1)
		{
			for (int j = 5;j < no_weeks * 7;j += 7)
			{
				//out << days[j % 7];

				int flag5 = 0;
				int flag6 = 0;


				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						//solution[i][j][k] = 1000;
						flag5 = 1;
						//out << "f5" << flag5 << endl;

					}
					if (solution[i][j + 1][k] > 0)
					{
						//solution[i][j][k] = 1000;
						flag6 = 1;
						//out << "f6" << flag6 << endl;

					}
				}
				if (flag5 != flag6)
					total += 30;


			}
		}
	}
	return total;
}

int soft_validator6()
{
	int mn_v = 0, mx_v = 0;

	int total = 0;
	for (int i = 0;i < no_nurses;i++)
	{
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfAssignments;
		int mx = contracts[key].maximumNumberOfAssignments;


		int cons_assign = nurses[i].history.numberOfAssignments;
		int total_assign = 0;

		for (int j = 0;j < no_weeks * 7;j++)
		{
			bool f = 1;

			for (int k = 0;k < no_shift_types;k++)
			{

				if (solution[i][j][k] > 0)
					total_assign++;




			}



		}
		if (total_assign < mn)
			total += (mn - total_assign) * 20;
		else if (total_assign > mx)
			total += (total_assign - mx) * 20;




	}


	return total;
}
int soft_validator7()
{

	int total = 0;
	for (int i = 0;i < no_nurses;i++)
	{
		int f = 0;
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mx = contracts[key].maximumNumberOfWorkingWeekends;


		int working_week_end = nurses[i].history.numberOfWorkingWeekends;
		int cnt = 0;
		bool flg = 0;
		for (int j = 5;j < no_weeks * 7;j += 7)
		{
			//out << days[j % 7];

			flg = 0;



			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flg = 1;
					//out << "f5" << flag5 << endl;
					//out << j << days[j % 7] << k<<" " ;

				}
				if (solution[i][j + 1][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flg = 1;
					//out << "f6" << flag6 << endl;
					//out << j+1 << days[(j+1) % 7] << k<<" "  ;

				}




			}
			if (flg == 1)
				cnt++;

		}
		//cout << endl;

		//out <<i<<" "<< cnt << endl;
		if (cnt > mx)
			total += (cnt - mx) * 30;





	}
	return total;

}

int sol_cnt = 0;



void print_sol_nurse()
{


	for (int i = 0;i < no_nurses;i++)
	{
		out << i << endl;


		for (auto it = nurse_sol[i].begin(); it != nurse_sol[i].end(); ++it)
		{
			out << '\t' << it->first << "	";
			for (int j = 0; j < it->second.second.size();j++)
			{
				out << it->second.second[j] << " ";
			}
			out << endl;
		}
		out << endl;

	}


}




int two_week_val(int start, int week) {
	int nom_weeks;
	int flag = 0;
	cout << "I am in two val" << endl;

	out << "I am in two val" << endl;

	if (start > week)
	{
		cout << "I am in two start" << endl;
		nom_weeks = start;

		for (int i = 0;i < no_nurses;i++)
		{

			string sss = nurses[i].history.lastAssignedShiftType;
			if (sss != "None") {
				int key = shift_type_point.find(sss)->second;
				for (int l = 0;l < shift_type[key].forbiddenSucceedingShiftTypes.size();l++)
				{
					string ss = shift_type[key].forbiddenSucceedingShiftTypes[l];

					cout << ss << endl;
					int forbid_id = shift_type_point.find(ss)->second;
					cout << forbid_id << endl;
					if (solution[i][0][forbid_id] > 0)
					{
						///out << i<<" "<<j+1<<" "<< endl;
						flag++;
					}

				}

			}


			for (int j = week * 7;j < start * 7 + 7;j++)
			{
				bool f = 0;

				for (int k = 0;k < no_shift_types;k++)
				{
					if ((solution[i][j][k] > 0))
					{



						for (int l = 0;l < shift_type[k].forbiddenSucceedingShiftTypes.size();l++)
						{
							string ss = shift_type[k].forbiddenSucceedingShiftTypes[l];

							cout << ss << endl;
							int forbid_id = shift_type_point.find(ss)->second;
							cout << forbid_id << endl;
							if (solution[i][j + 1][forbid_id] > 0)
							{
								out << i << " " << j + 1 << " " << endl;
								flag++;
							}

						}





					}

				}


			}
		}

		//return flag;
	}
	else if (week > start)
	{
		cout << "I am in two start333" << endl;
		nom_weeks = week;

		for (int i = 0;i < no_nurses;i++)
		{

			string sss = nurses[i].history.lastAssignedShiftType;
			if (sss != "None") {
				int key = shift_type_point.find(sss)->second;

				for (int l = 0;l < shift_type[key].forbiddenSucceedingShiftTypes.size();l++)
				{
					string ss = shift_type[key].forbiddenSucceedingShiftTypes[l];

					cout << ss << endl;
					int forbid_id = shift_type_point.find(ss)->second;
					cout << forbid_id << endl;
					if (solution[i][0][forbid_id] > 0)
					{
						//out << i<<" "<<j+1<<" "<< endl;
						flag++;
					}

				}

			}


			for (int j = start * 7;j < week * 7 + 7;j++)
			{
				bool f = 0;

				for (int k = 0;k < no_shift_types;k++)
				{
					if ((solution[i][j][k] > 0))
					{



						for (int l = 0;l < shift_type[k].forbiddenSucceedingShiftTypes.size();l++)
						{
							string ss = shift_type[k].forbiddenSucceedingShiftTypes[l];

							cout << ss << endl;
							int forbid_id = shift_type_point.find(ss)->second;
							cout << forbid_id << endl;
							if (solution[i][j + 1][forbid_id] > 0)
							{
								out << i << " " << j + 1 << " " << endl;
								flag++;
							}

						}





					}

				}


			}
		}
		cout << "Flag" << flag;
		//return flag;

	}

	return flag;

}

class Week_sol {
public:
	int sol[100][10][10];
	float distance;
	float visibility;
	float trail;


}week_sol[17][500];


vector< pair <float, int>>week_sol_point[20];


int path[20][20];
void solution_push(int i, vector<int>v)
{
	for (int k = 0;k < no_weeks * 7;k++)
	{
		memset(solution[i][k], 0, sizeof solution[i][k]);

	}
	int ind = 0;
	for (int j = 0;j < no_weeks * 7;j++)
	{
		for (int k = 0;k < no_shift_types;k++)
		{
			solution[i][j][k] = v[ind];
			ind++;
		}
	}




}

void selection()
{

	for (int j = 0;j < no_nurses + 1;j++)
	{
		for (int k = 0;k < no_weeks * 7 + 1;k++)
		{
			memset(solution[j][k], 0, sizeof solution[j][k]);
			//	memset(sol[j][k], 0, sizeof sol[j][k]);
		}
	}


	/*int rndd = 2;
	while (rndd--)
	{*/
	//cout << rndd << endl;
	std::srand(unsigned(std::time(0)));
	vector<int>serial;

	for (int i = 0; i < no_nurses; ++i) serial.push_back(i);
	random_shuffle(serial.begin(), serial.end());
	random_shuffle(serial.begin(), serial.end(), myrandom);

	for (int i = 0; i < no_nurses; ++i)
		//out << serial[i] << " ";
		out << endl;


	for (std::vector<int>::iterator it = serial.begin(); it != serial.end(); ++it)
	{
		int nur = *it;
		if (nurse_sol[nur].size() > 0)
		{

			multimap<float, pair< int, vector<int>>> ::iterator itr = nurse_sol[nur].begin();

			//int kk = rand() % 2;
			//if (kk == 0)
				//nurse_sol[nur].erase(nurse_sol[nur].begin());
			out << nur << " " << itr->first << endl;

			solution_push(nur, itr->second.second);

		}


	}
	out << "----------------------------------------------------------------------------" << endl;
	show_solution();
	vailidator();

	out << "----------------------------------------------------------------------------" << endl;
	repair3();
	for (int i = 0;i < 10;i++)
	{
		out << "repair" << i << endl;
		cout << "repair" << i << " ";
		repair5();
		vailidator();
		random_init();
		vailidator();

	}

	/*for (int i = 0;i < 10;i++)
	{
		int aaa = repair1();
		if (aaa)
			break;

	}
	*/

	optimalition();
	show_solution();
	vailidator();



	//}


}

int week_sol_soft_validator1(int t)
{


	int flag = 0;
	int total = 0;
	int nom_weeks = t + 1;
	memset(requirements_fulfil, 0, sizeof requirements_fulfil);

	for (int i = t * 7;i < nom_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{
			bool f = 0;

			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
				{
					int sk = solution[k][i][j];
					requirements_fulfil[i][j][sk]++;

				}

			}



		}


	}


	for (int i = t * 7;i < nom_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_skills;k++)
			{
				int cnt = 0;
				for (int l = 0;l < no_nurses;l++)
				{
					if (k == solution[l][i][j] - 1)
						cnt++;
				}


				if (requirements_optimal[i][j][k] > cnt)
					total += (requirements_optimal[i][j][k] - cnt) * 30;

			}



		}


	}



	return total;

}
int week_sol_soft_validator2(int t)
{
	//minimumNumberOfConsecutiveWorkingDays,
		//maximumNumberOfConsecutiveWorkingDays,4
	int mn_v = 0, mx_v = 0;
	int total = 0;
	int nom_weeks = t + 1;



	for (int i = 0;i < no_nurses;i++)
	{
		//out << "full" << total << endl;
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfConsecutiveWorkingDays;
		int mx = contracts[key].maximumNumberOfConsecutiveWorkingDays;
		//out << "--------------------------" << endl;

		int cons_day = nurses[i].history.numberOfConsecutiveWorkingDays;

		if (cons_day >= mx)
			cons_day = mx;

		for (int m = 0;m < t + 1;m++)
		{

			bool start = 0;
			if (cons_day > 0)
				start = 1;

			for (int j = m * 7 + 0;j < m * 7 + 7;j++)
			{
				bool f = 0;

				for (int k = 0;k < no_shift_types;k++)
				{

					if (solution[i][j][k] > 0)
					{
						f = 1;
						start = 1;

					}




				}

				if (f == 1)
				{
					cons_day++;

				}

				if ((f == 0 || j == nom_weeks * 7 - 1) && start == 1)
				{
					//out << j << " " << cons_day << endl;
					if (cons_day > mx)
					{
						total += (cons_day - mx) * 30;
						cons_day = 0;
						start = 0;
					}
					else if (cons_day < mn && j != nom_weeks * 7 - 1)
					{
						total += (mn - cons_day) * 30;
						cons_day = 0;
						start = 0;
					}
					else if (cons_day >= mn && cons_day <= mx)
					{
						cons_day = 0;
						start = 0;
					}
				}

			}

		}
		//out << endl;



		//out << "half" << total << endl;







		//out << "@@" << mn << " " << mx << endl;
		string ss = nurses[i].history.lastAssignedShiftType;
		int lst = -1;
		if (ss != "None")
			lst = shift_type_point.find(ss)->second;






		for (int k = 0;k < no_shift_types;k++)
		{
			bool start = 0;
			int cons_sft = 0;
			mn = shift_type[k].minimumNumberOfConsecutiveAssignments;
			mx = shift_type[k].maximumNumberOfConsecutiveAssignments;

			bool f = 0;
			if (k == lst)
			{
				cons_sft = nurses[i].history.numberOfConsecutiveAssignments;

				if (cons_sft >= mx)
					cons_sft = mx;
				if (cons_sft > 0)
					start = 1;

			}

			for (int j = t * 7;j < nom_weeks * 7;j++)
			{

				if (solution[i][j][k] > 0)
				{
					f = 1;
					start = 1;
					cons_sft++;

				}
				else
				{
					f = 0;
				}

				if ((f == 0 || j == nom_weeks * 7 - 1) && start == 1)
				{

					if (cons_sft > mx)
					{
						//out <<1<<" "<< j << " " << cons_sft << endl;
						total += (cons_sft - mx) * 15;
						cons_sft = 0;
						start = 0;
					}
					else if (cons_sft < mn && j != nom_weeks * 7 - 1)
					{
						//out <<2<<" "<< j << " " << cons_sft << endl;
						total += (mn - cons_sft) * 15;
						cons_sft = 0;
						start = 0;
					}
					else if (cons_sft >= mn && cons_sft <= mx)
					{
						cons_sft = 0;
						start = 0;
					}
				}




			}
		}

	}

	return total;
}
int week_sol_soft_validator3(int t)
{
	int mn_v = 0, mx_v = 0;
	int res = 0;
	int nom_weeks = t + 1;

	for (int i = 0;i < no_nurses;i++)
	{
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfConsecutiveDaysOff;
		int mx = contracts[key].maximumNumberOfConsecutiveDaysOff;

		//out << mn << " " << mx << endl;


		int cons_dayof = nurses[i].history.numberOfConsecutiveDaysOff;
		//out << "cons_dayof"<<cons_dayof << endl;


		for (int j = t * 7;j < nom_weeks * 7;j++)
		{
			//out << "j"<<j << endl;


			if (j < (nom_weeks * 7) - 1)
			{
				bool f = 1;
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						f = 0;
					}
					//out << "k" << k << endl;
				}
				if (f == 1)
				{
					//out << "f1cons_dayof" << cons_dayof << endl;

					cons_dayof++;
					//out << "res" << res << endl;

				}
				if (f == 0)
				{
					//out << "f0" << endl;
					if (cons_dayof != 0)
					{
						//out << "f0cons_dayof" << cons_dayof << endl;
						if (cons_dayof > mx)
						{
							res += cons_dayof - mx;
							//cons_dayof = 0;
							//out << "res" << res << endl;


						}
						if (cons_dayof < mn)
						{
							res += mn - cons_dayof;
							//cons_dayof = 0;
								//out << "res" << res << endl;
						}
						cons_dayof = 0;
						//out << "cons_dayof" << cons_dayof << endl;
						//out << "res" << res << endl;
					}

				}

			}
			else
			{
				bool f = 1;
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						f = 0;
					}
					//out << "k" << k << endl;

				}
				if (f == 1)
				{
					//out << "f1cons_dayof" << cons_dayof << endl;

					cons_dayof++;
					if (cons_dayof > mx)
					{
						res += cons_dayof - mx;
						//cons_dayof = 0;
						//out << "res" << res << endl;


					}
					/*if (cons_dayof < mn)
					{
						res += mn - cons_dayof;
						//cons_dayof = 0;
						//out << "res" << res << endl;
					}*/
					cons_dayof = 0;
					//out << "res" << res << endl;

				}
				if (f == 0)
				{
					if (cons_dayof != 0)
					{
						//out << "f0cons_dayof" << cons_dayof << endl;
						if (cons_dayof > mx)
						{
							res += cons_dayof - mx;
							//cons_dayof = 0;
							//out << "res" << res << endl;


						}
						if (cons_dayof < mn)
						{
							res += mn - cons_dayof;
							//cons_dayof = 0;
							//out << "res" << res << endl;
						}
						cons_dayof = 0;
						//out << "cons_dayof" << cons_dayof << endl;
						//out << "res" << res << endl;
					}

				}





			}

		}
		//out <<"rws"<< res << endl;
	}
	//out <<"res"<< res << endl;


	return (res) * 30;

}
int week_sol_soft_validator4(int t)
{
	int flag = 0;
	int nom_weeks = t + 1;
	for (int i = 0;i < no_nurses;i++)
	{

		for (int j = 0;j < shift_off_req[i].size();j++)
		{
			int d = shift_off_req[i][j].second;
			string shift = shift_off_req[i][j].first;

			if (shift == "Any")
			{
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][d][k] > 0)
					{
						//solution[i][d][k] = 500;


						//out << endl << i << " " << d << " " << k << endl;
						flag++;
					}

				}
			}

			else
			{

				int s = shift_type_point.find(shift)->second;

				if (solution[i][d][s] > 0)
				{
					//solution[i][d][s] = 500;
					//out << endl << i << " " << d << " " << s << endl;
					flag++;
				}
			}

		}
	}
	return flag * 10;
}
int week_sol_soft_validator5(int t)
{
	int flag = 0;
	int total = 0;
	int nom_weeks = t + 1;
	for (int i = 0;i < no_nurses;i++)
	{

		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].completeWeekends;


		if (mn == 1)
		{
			for (int j = 5;j < nom_weeks * 7;j += 7)
			{
				//out << days[j % 7];

				int flag5 = 0;
				int flag6 = 0;


				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						//solution[i][j][k] = 1000;
						flag5 = 1;
						//out << "f5" << flag5 << endl;

					}
					if (solution[i][j + 1][k] > 0)
					{
						//solution[i][j][k] = 1000;
						flag6 = 1;
						//out << "f6" << flag6 << endl;

					}
				}
				if (flag5 != flag6)
					total += 30;


			}
		}
	}
	return total;
}

int week_sol_soft_validator6(int t)
{
	int mn_v = 0, mx_v = 0;

	int total = 0;
	int nom_weeks = t + 1;
	for (int i = 0;i < no_nurses;i++)
	{
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfAssignments;
		int mx = contracts[key].maximumNumberOfAssignments;


		int cons_assign = nurses[i].history.numberOfAssignments;
		int total_assign = 0;

		for (int j = 0;j < nom_weeks * 7;j++)
		{
			bool f = 1;

			for (int k = 0;k < no_shift_types;k++)
			{

				if (solution[i][j][k] > 0)
					total_assign++;




			}



		}
		if (total_assign < mn)
			total += (mn - total_assign) * 20;
		else if (total_assign > mx)
			total += (total_assign - mx) * 20;




	}


	return total;
}
int week_sol_soft_validator7(int t)
{

	int total = 0;
	int nom_weeks = t + 1;
	for (int i = 0;i < no_nurses;i++)
	{
		int f = 0;
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mx = contracts[key].maximumNumberOfWorkingWeekends;


		int working_week_end = nurses[i].history.numberOfWorkingWeekends;
		int cnt = 0;
		bool flg = 0;
		for (int j = 5;j < nom_weeks * 7;j += 7)
		{
			//out << days[j % 7];

			flg = 0;



			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flg = 1;
					//out << "f5" << flag5 << endl;
					//out << j << days[j % 7] << k<<" " ;

				}
				if (solution[i][j + 1][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flg = 1;
					//out << "f6" << flag6 << endl;
					//out << j+1 << days[(j+1) % 7] << k<<" "  ;

				}




			}
			if (flg == 1)
				cnt++;

		}
		//cout << endl;

		//out <<i<<" "<< cnt << endl;
		if (cnt > mx)
			total += (cnt - mx) * 30;





	}
	return total;

}
int week_validator(int i)
{
	//out << "s1" << endl;
	int s1 = week_sol_soft_validator1(i);
	//show_solution();
	//out << "s2" << endl;
	int s2 = week_sol_soft_validator2(i);
	//show_solution();

	//out << "s3" << endl;
	int s3 = week_sol_soft_validator3(i);
	//show_solution();
	//out << "s4" << endl;
	int s4 = week_sol_soft_validator4(i);
	//show_solution();
	//out << "s5" << endl;
	int s5 = week_sol_soft_validator5(i);
	//show_solution();
	int s6 = week_sol_soft_validator6(i);
	//show_solution();
	int s7 = week_sol_soft_validator7(i);
	//show_solution();
	int result = s1 + s2 + s3 + s4 + s5 + s6 + s7;
	//out << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s6 << " " << s7 << "   " << s1 + s2 + s3 + s4 + s5 + s6 + s7 << endl;

	return result;


}
bool fill_week[100];
int bmin = 9999999999;
int prev_path[20][20];
int path_cost[100];

vector<pair<int, int>>feromen;

void ACO_1()
{
	for (int i = 0;i < no_weeks;i++)
		sort(week_sol_point[i].begin(), week_sol_point[i].end());
	for (int i = 0;i < no_weeks;i++)

	{
		out << week_sol_point[i][0].first << " " << week_sol_point[i][0].second << endl;
	}



}










int taken_week[20];

void ACO() {

	int l;

	//int sol_ant_mat[100][100][100];

	cout << "Here in aco" << endl;

	for (int i = 0;i < no_weeks;i++)
		sort(week_sol_point[i].rbegin(), week_sol_point[i].rend());


	out << "week_best" << endl;
	for (int i = 0;i < no_weeks;i++)

	{
		out << week_sol_point[i][0].first << " " << week_sol_point[i][0].second << endl;
	}





	cout << "Here in ant ago" << endl;

	bool flg_end = 1;
	while (1)
	{
		for (int ant = 0;ant < no_weeks;ant++)
			memset(path[ant], -1, sizeof path[ant]);

		for (int ant = 0;ant < no_weeks;ant++)
		{


			int check = 0;
			int p = 0;
			out << "ant---------" << ant << endl;

			vector<int>taken;
			for (int i = 0;i < no_weeks;i++)
			{
				if (i != ant)
					taken.push_back(i);
			}

			//pat.push_back(week_sol_point[ant][0].second);
			//p.push_back( week_sol_point[ant][0].second);




			int mn = 100000000;
			int mn_ind = -1;

			vector<pair<int, pair<int, int >> >srt;
			for (int j = 0;j < taken.size();j++)
			{
				int i = taken[j];
				srt.push_back(make_pair(week_sol_point[i][0].first, make_pair(i, week_sol_point[i][0].second)));



			}





			//show_solution();

			sort(srt.rbegin(), srt.rend());
			for (int i = 0;i < no_nurses;i++)
			{
				for (int j = 0;j < no_weeks * 7;j++)
				{
					memset(solution[i][j], 0, sizeof solution[i][j]);

				}

			}
			for (int i = 0;i < no_nurses;i++)
			{
				cout << "i---------" << i << endl;
				//out << "i---------" << i << endl;

				for (int j = ant * 7;j < ant * 7 + 7;j++)
				{
					for (int k = 0;k < no_shift_types;k++)
					{
						int ii = week_sol_point[ant][0].second;
						solution[i][j][k] = week_sol[ant][ii].sol[i][j][k];
						//out<< solution[i][j][k]<<endl;

					}


				}
			}

			path[ant][ant] = week_sol_point[ant][0].second;
			fill_week[ant] = 1;
			out << "ant  " << ant << endl;
			out << "after ant" << endl;
			show_solution();
			out << "end ant" << endl;
			int val_evu = 0;


			l = taken.size();


			while (l > 0)
			{
				//cout << "taken---------" << l << endl;
				out << "taken---------" << l << endl;
				int twval1 = 0;
				int twval = 0;
				int twval2 = 0;

				int week = srt[0].second.first;
				int ind = srt[0].second.second;
				//out << "week : "<<week << " " << ind << endl;

				//path[ant] = week_sol_point[week][ind].second;

				//cout << "Week:" << week << endl;

				out << "+++++++++++++++++++++++++++" << endl;
				out << "Week:" << week << endl;
				//cout << "ind:" << ind << endl;
				out << "ind:" << ind << endl;

				if (week == ant + 1 || week == ant - 1)
				{
					cout << "I am in if" << endl;
					out << "I am in if" << endl;

					for (int i = 0;i < no_nurses;i++)
					{
						for (int j = week * 7;j < week * 7 + 7;j++)
						{
							for (int k = 0;k < no_shift_types;k++)
							{
								int p = week_sol[week][ind].sol[i][j][k];
								//out << p << endl;

								solution[i][j][k] = p;


							}


						}
					}

					out << "after inserting a week" << endl;
					show_solution();

					twval = two_week_val(ant, week);
					//cout << "twval-----" << twval << endl;
					out << "twval-----" << twval << endl;


					if (twval != 0)
					{
						cout << "twval " << twval << "twval1 " << twval1 << endl;
						out << "twval " << twval << "twval1 " << twval1 << endl;

						for (int i = 0;i < no_nurses;i++)
						{
							for (int j = week * 7;j < week * 7 + 7;j++)
							{
								for (int k = 0;k < no_shift_types;k++)
								{
									solution[i][j][k] = 0;

								}


							}

						}
						//repeat[i].erase(repeat[i].begin() + rnd);
						srt.erase(srt.begin() + 0);

						taken_week[week]++;


						srt.push_back(make_pair(week_sol_point[week][taken_week[week]].first, make_pair(week, week_sol_point[week][taken_week[week]].second)));
						//srt.push_back(make_pair(week_sol_point[week][taken_week[week]].distance*week_sol[week][taken_week[week]].trail, make_pair(week, taken_week[week])));

						sort(srt.rbegin(), srt.rend());





						cout << "srt_first" << srt[0].first << endl;
						out << "srt_first" << srt[0].first << endl;



					}
					else
					{
						check = 0;
						srt.erase(srt.begin() + 0);
						l = l - 1;
						fill_week[week] = 1;
						path[ant][week] = ind;
						//p++;
						//pat.push_back(week_sol_point[week][ind].second);
						cout << "taken_size" << l << endl;
						//out << "Not valid pre sol:" << endl;
						//cout << "Not valid pre sol:" << endl;
						show_solution();
						//out << "Not valid after sol:" << endl;
						//cout << "Not valid after sol:" << endl;

					}


				}
				else
				{
					cout << "I am in else" << endl;
					out << "I am in else" << endl;
					for (int i = 0;i < no_nurses;i++)
					{
						for (int j = week * 7;j < week * 7 + 7;j++)
						{
							for (int k = 0;k < no_shift_types;k++)
							{

								solution[i][j][k] = week_sol[week][ind].sol[i][j][k];
								//show_solution();

							}


						}
					}
					if ((fill_week[max(week - 1, 0)] == 1 && week > 0))
					{
						twval1 = two_week_val(week - 1, week);
						cout << "twval1" << twval1 << endl;
						out << "twval1" << twval1 << endl;

					}

					if ((fill_week[min(week + 1, no_weeks)] == 1 && week < no_weeks - 1))
					{
						twval2 = two_week_val(week, week + 1);
						cout << "twval2" << twval2 << endl;
						out << "twval2" << twval2 << endl;
					}

					if (twval1 != 0 || twval2 != 0)
					{
						cout << "twval1" << twval1 << " teval2" << twval2 << endl;
						out << "twval1 " << twval1 << " teval 2" << twval2 << endl;
						for (int i = 0;i < no_nurses;i++)
						{
							for (int j = week * 7;j < week * 7 + 7;j++)
							{
								for (int k = 0;k < no_shift_types;k++)
								{
									solution[i][j][k] = 0;

								}


							}

						}

						srt.erase(srt.begin() + 0);

						taken_week[week]++;

						//srt.push_back(make_pair(week_sol[week][taken_week[week]].distance*week_sol[week][taken_week[week]].trail, make_pair(week, taken_week[week])));
						srt.push_back(make_pair(week_sol_point[week][taken_week[week]].first, make_pair(week, week_sol_point[week][taken_week[week]].second)));
						sort(srt.rbegin(), srt.rend());


					}
					else
					{
						check = 0;
						srt.erase(srt.begin() + 0);
						l = l - 1;
						fill_week[week] = 1;
						path[ant][week] = ind;
						//p++;
						//pat.push_back(week_sol_point[week][ind].second);
						cout << "taken_size" << l << endl;
						//out << "Not valid pre sol:" << endl;
						//cout << "Not valid pre sol:" << endl;
						show_solution();

					}








				}


			}










			out << "Aco:   " << ant << endl;

			out << "path  " << endl;

			for (int kk = 0;kk < no_weeks;kk++)
				out << path[ant][kk] << " ";

			out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			show_solution();
			//vailidator();

			int h1 = hard_validator1();
			int h2 = hard_validator2();
			int h3 = hard_validator3();
			int h4 = hard_validator4();

			out << "h111 " << h1 << "h22222 " << h2 << "h3 " << h3 << "h44  " << h4 << endl;



			int s1 = soft_validator1();
			int s2 = soft_validator2();
			int s3 = soft_validator3();
			int s4 = soft_validator4();
			int s5 = soft_validator5();
			int s6 = soft_validator6();
			int s7 = soft_validator7();


			val_evu = s1 + s2 + s3 + s4 + s5 + s6 + s7;
			out << "val_evy  " << val_evu << endl;


			path_cost[ant] = val_evu;

			if (val_evu < bmin)
			{
				bmin = val_evu;
				for (int i = 0;i < no_nurses;i++)
				{
					for (int j = 0; j < no_weeks * 7;j++)
					{

						for (int sft = 0;sft < no_shift_types;sft++)
						{

							sol_ant_mat[i][j][sft] = solution[i][j][sft];
						}

					}

				}

			}
			//show_solution();
			//out << "Heeeeeee" << endl;
















		}

		for (int i = 0;i < no_weeks;i++)
			week_sol_point[i].clear();

		for (int j = 0;j < no_weeks;j++)
		{
			for (int i = 0;i < s_n + 1;i++)
			{

				week_sol[j][i].trail = week_sol[j][i].trail *.7;



			}
		}
		for (int ant = 0;ant < no_weeks;ant++)
		{
			for (int j = 0;j < no_weeks;j++)
			{
				week_sol[j][path[ant][j]].trail += (1 / path_cost[ant]);

			}
		}



		for (int j = 0;j < no_weeks;j++)
		{
			for (int i = 0;i < s_n + 1;i++)
			{

				week_sol_point[j].push_back(make_pair(week_sol[j][i].visibility + week_sol[j][i].trail, i));



			}
		}




		for (int i = 0;i < no_weeks;i++)
			sort(week_sol_point[i].rbegin(), week_sol_point[i].rend());

















		flg_end = 1;
		for (int ant = 0;ant < no_weeks - 1;ant++)
		{
			for (int j = 0;j < no_weeks;j++)
				if (path[ant][j] != path[ant + 1][j])
				{
					flg_end = 0;

				}
		}
		if (flg_end == 1)
			break;
	}





	out << "bmax" << bmin << endl;

	int evul = 0;

	for (int i = 0;i < no_weeks;i++) {




		for (int nur = 0;nur < no_nurses;nur++)
		{
			for (int j = i * 7; j < i * 7 + 7;j++)
			{

				for (int sft = 0;sft < no_shift_types;sft++)
				{

					week_sol[i][solution_no].sol[nur][j][sft] = sol_ant_mat[nur][j][sft];
				}

			}

		}

		/*week_sol[i][solution_no].distance = bmin;
		int evu = week_validator(i);
		//out << "Week_Validator " << i << " " << evu << endl;
		evul += evu;



		int quality = (week_sol[i][solution_no].distance) * .3 + evu * .2;

		week_sol_point[i].push_back(make_pair(quality, solution_no));
		//solution_no++;

		*/



	}







	//out << "weeek evullll    " << evul << endl;
















}


























int single_nur_vali2(int i)
{

	int mn_v = 0, mx_v = 0;
	int total = 0;

	//out << "full" << total << endl;
	string s = nurses[i].contract;
	int key = contracts_point.find(s)->second;
	int mn = contracts[key].minimumNumberOfConsecutiveWorkingDays;
	int mx = contracts[key].maximumNumberOfConsecutiveWorkingDays;
	//out << "--------------------------" << endl;

	int cons_day = nurses[i].history.numberOfConsecutiveWorkingDays;

	if (cons_day >= mx)
		cons_day = mx;

	for (int m = 0;m < no_weeks;m++)
	{

		bool start = 0;
		if (cons_day > 0)
			start = 1;

		for (int j = m * 7 + 0;j < m * 7 + 7;j++)
		{
			bool f = 0;

			for (int k = 0;k < no_shift_types;k++)
			{

				if (solution[i][j][k] > 0)
				{
					f = 1;
					start = 1;

				}




			}

			if (f == 1)
			{
				cons_day++;

			}

			if ((f == 0 || j == no_weeks * 7 - 1) && start == 1)
			{
				//out << j << " " << cons_day << endl;
				if (cons_day > mx)
				{
					total += (cons_day - mx) * 30;
					cons_day = 0;
					start = 0;
				}
				else if (cons_day < mn && j != no_weeks * 7 - 1)
				{
					total += (mn - cons_day) * 30;
					cons_day = 0;
					start = 0;
				}
				else if (cons_day >= mn && cons_day <= mx)
				{
					cons_day = 0;
					start = 0;
				}
			}

		}

	}
	//out << endl;



	//out << "half" << total << endl;







	//out << "@@" << mn << " " << mx << endl;
	string ss = nurses[i].history.lastAssignedShiftType;
	int lst = -1;
	if (ss != "None")
		lst = shift_type_point.find(ss)->second;






	for (int k = 0;k < no_shift_types;k++)
	{
		bool start = 0;
		int cons_sft = 0;
		mn = shift_type[k].minimumNumberOfConsecutiveAssignments;
		mx = shift_type[k].maximumNumberOfConsecutiveAssignments;

		bool f = 0;
		if (k == lst)
		{
			cons_sft = nurses[i].history.numberOfConsecutiveAssignments;

			if (cons_sft >= mx)
				cons_sft = mx;
			if (cons_sft > 0)
				start = 1;

		}

		for (int j = 0;j < no_weeks * 7;j++)
		{

			if (solution[i][j][k] > 0)
			{
				f = 1;
				start = 1;
				cons_sft++;

			}
			else
			{
				f = 0;
			}

			if ((f == 0 || j == no_weeks * 7 - 1) && start == 1)
			{

				if (cons_sft > mx)
				{
					//out <<1<<" "<< j << " " << cons_sft << endl;
					total += (cons_sft - mx) * 15;
					cons_sft = 0;
					start = 0;
				}
				else if (cons_sft < mn && j != no_weeks * 7 - 1)
				{
					//out <<2<<" "<< j << " " << cons_sft << endl;
					total += (mn - cons_sft) * 15;
					cons_sft = 0;
					start = 0;
				}
				else if (cons_sft >= mn && cons_sft <= mx)
				{
					cons_sft = 0;
					start = 0;
				}
			}




		}
	}



	return total;

}

int single_nur_vali3(int i)
{

	int mn_v = 0, mx_v = 0;
	int res = 0;

	string s = nurses[i].contract;
	int key = contracts_point.find(s)->second;
	int mn = contracts[key].minimumNumberOfConsecutiveDaysOff;
	int mx = contracts[key].maximumNumberOfConsecutiveDaysOff;

	//out << mn << " " << mx << endl;


	int cons_dayof = nurses[i].history.numberOfConsecutiveDaysOff;
	//out << "cons_dayof"<<cons_dayof << endl;


	for (int j = 0;j < no_weeks * 7;j++)
	{
		//out << "j"<<j << endl;


		if (j < (no_weeks * 7) - 1)
		{
			bool f = 1;
			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					f = 0;
				}
				//out << "k" << k << endl;
			}
			if (f == 1)
			{
				//out << "f1cons_dayof" << cons_dayof << endl;

				cons_dayof++;
				//out << "res" << res << endl;

			}
			if (f == 0)
			{
				//out << "f0" << endl;
				if (cons_dayof != 0)
				{
					//out << "f0cons_dayof" << cons_dayof << endl;
					if (cons_dayof > mx)
					{
						res += cons_dayof - mx;
						//cons_dayof = 0;
						//out << "res" << res << endl;


					}
					if (cons_dayof < mn)
					{
						res += mn - cons_dayof;
						//cons_dayof = 0;
							//out << "res" << res << endl;
					}
					cons_dayof = 0;
					//out << "cons_dayof" << cons_dayof << endl;
					//out << "res" << res << endl;
				}

			}

		}
		else
		{
			bool f = 1;
			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					f = 0;
				}
				//out << "k" << k << endl;

			}
			if (f == 1)
			{
				//out << "f1cons_dayof" << cons_dayof << endl;

				cons_dayof++;
				if (cons_dayof > mx)
				{
					res += cons_dayof - mx;
					//cons_dayof = 0;
					//out << "res" << res << endl;


				}
				/*if (cons_dayof < mn)
				{
					res += mn - cons_dayof;
					//cons_dayof = 0;
					//out << "res" << res << endl;
				}*/
				cons_dayof = 0;
				//out << "res" << res << endl;

			}
			if (f == 0)
			{
				if (cons_dayof != 0)
				{
					//out << "f0cons_dayof" << cons_dayof << endl;
					if (cons_dayof > mx)
					{
						res += cons_dayof - mx;
						//cons_dayof = 0;
						//out << "res" << res << endl;


					}
					if (cons_dayof < mn)
					{
						res += mn - cons_dayof;
						//cons_dayof = 0;
						//out << "res" << res << endl;
					}
					cons_dayof = 0;
					//out << "cons_dayof" << cons_dayof << endl;
					//out << "res" << res << endl;
				}

			}





		}

	}
	//out <<"rws"<< res << endl;

//out <<"res"<< res << endl;


	return (res) * 30;

}

int single_nur_vali4(int i)
{
	int flag = 0;

	for (int j = 0;j < shift_off_req[i].size();j++)
	{
		int d = shift_off_req[i][j].second;
		string shift = shift_off_req[i][j].first;

		if (shift == "Any")
		{
			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][d][k] > 0)
				{
					//solution[i][d][k] = 500;


					//out << endl << i << " " << d << " " << k << endl;
					flag++;
				}

			}
		}

		else
		{

			int s = shift_type_point.find(shift)->second;

			if (solution[i][d][s] > 0)
			{
				//solution[i][d][s] = 500;
				//out << endl << i << " " << d << " " << s << endl;
				flag++;
			}
		}

	}

	return flag * 10;


}

int single_nur_vali5(int i)
{


	int flag = 0;
	int total = 0;


	string s = nurses[i].contract;
	int key = contracts_point.find(s)->second;
	int mn = contracts[key].completeWeekends;


	if (mn == 1)
	{
		for (int j = 5;j < no_weeks * 7;j += 7)
		{
			//out << days[j % 7];

			int flag5 = 0;
			int flag6 = 0;


			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flag5 = 1;
					//out << "f5" << flag5 << endl;

				}
				if (solution[i][j + 1][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flag6 = 1;
					//out << "f6" << flag6 << endl;

				}
			}
			if (flag5 != flag6)
				total += 30;


		}
	}

	return total;


}
int single_nur_vali6(int i)
{
	int mn_v = 0, mx_v = 0;

	int total = 0;

	string s = nurses[i].contract;
	int key = contracts_point.find(s)->second;
	int mn = contracts[key].minimumNumberOfAssignments;
	int mx = contracts[key].maximumNumberOfAssignments;


	int cons_assign = nurses[i].history.numberOfAssignments;
	int total_assign = 0;

	for (int j = 0;j < no_weeks * 7;j++)
	{
		bool f = 1;

		for (int k = 0;k < no_shift_types;k++)
		{

			if (solution[i][j][k] > 0)
				total_assign++;




		}



	}
	if (total_assign < mn)
		total += (mn - total_assign) * 20;
	else if (total_assign > mx)
		total += (total_assign - mx) * 20;







	return total;

}

int single_nur_vali7(int i)
{
	int total = 0;

	int f = 0;
	string s = nurses[i].contract;
	int key = contracts_point.find(s)->second;
	int mx = contracts[key].maximumNumberOfWorkingWeekends;


	int working_week_end = nurses[i].history.numberOfWorkingWeekends;
	int cnt = 0;
	bool flg = 0;
	for (int j = 5;j < no_weeks * 7;j += 7)
	{
		//out << days[j % 7];

		flg = 0;



		for (int k = 0;k < no_shift_types;k++)
		{
			if (solution[i][j][k] > 0)
			{
				//solution[i][j][k] = 1000;
				flg = 1;
				//out << "f5" << flag5 << endl;
				//out << j << days[j % 7] << k<<" " ;

			}
			if (solution[i][j + 1][k] > 0)
			{
				//solution[i][j][k] = 1000;
				flg = 1;
				//out << "f6" << flag6 << endl;
				//out << j+1 << days[(j+1) % 7] << k<<" "  ;

			}




		}
		if (flg == 1)
			cnt++;

	}
	//cout << endl;

	//out <<i<<" "<< cnt << endl;
	if (cnt > mx)
		total += (cnt - mx) * 30;






	return total;


}


void sol_nurse(int evoluation)
{



	for (int i = 0;i < no_nurses;i++)
	{
		vector<int>v;
		int single_nur_vali = 0;

		for (int j = 0;j < no_weeks * 7;j++)
		{

			for (int k = 0;k < no_shift_types;k++)
			{

				v.push_back(solution[i][j][k]);
				//cout << solution[i][j][k] << endl;


			}

		}

		int single2 = single_nur_vali2(i);
		int single3 = single_nur_vali3(i);
		int single4 = single_nur_vali4(i);
		int single5 = single_nur_vali5(i);
		int single6 = single_nur_vali6(i);
		int single7 = single_nur_vali7(i);

		single_nur_vali = single2 + single3 + single4 + single5 + single6 + single7;
		//out <<i<<"--->"<< single2 << " " << single3 << " " << single4 << " " << single5 << " " << single6 << " " << single7 <<" "<< single_nur_vali <<endl;
		//int rndd = rand() % 1000;
		//out << rndd << endl;

		int quality = single_nur_vali * .8 + evoluation * .2;
		//nurse_sol[i].insert(make_pair(quality, v));





		bool ins = 1;

		for (auto it = nurse_sol[i].begin();it != nurse_sol[i].end();it++)
		{
			bool same = 0;
			if (it->first == single_nur_vali)
			{
				same = 1;
				vector<int>value = it->second.second;

				for (int ii = 0;ii < value.size();ii++)
				{
					if (value[ii] != v[ii])
					{
						same = 0;
						break;
					}

				}

			}
			if (same == 1)
			{
				ins = 0;
				break;
			}
		}



		if (ins == 1)
		{
			nurse_sol[i].insert(make_pair(quality, make_pair(solution_no, v)));

		}
	}


}












vector<pair<int, int>>req_s;
void initial_sol()
{


	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			memset(requirements_fulfil, 0, sizeof requirements_fulfil);
		}
	}

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];


			}
		}
	}


	vector<int>ds;

	for (int i = 0;i < no_nurses;i++)
	{
		ds.push_back(i);
	}


	while (ds.size() != 0)
	{






		int rnd = rand() % ds.size();

		//out << ds[rnd]<<" "<<ds.size()<<endl;


		int ii = ds[rnd];

		int nur = ii;

		/*int max_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfAssignments;
		int min_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfAssignments;
		int max_con_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfConsecutiveWorkingDays;
		int min_con_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfConsecutiveWorkingDays;
		int max_con_off = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfConsecutiveDaysOff;
		int min_con_off = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfConsecutiveDaysOff;
		bool com_weekend = contracts[contracts_point.find(nurses[ii].contract)->second].completeWeekends;

		int last_assign_sft = shift_type_point[nurses[ii].history.lastAssignedShiftType];
		int last_assign_cons_sft = nurses[ii].history.numberOfConsecutiveAssignments;
		int last_cons = nurses[ii].history.numberOfConsecutiveWorkingDays;
		int last_con_off = nurses[ii].history.numberOfConsecutiveDaysOff;


		*/


		//	int assignment = 0, con_assignment = last_cons, con_off = last_con_off, con_sft = last_assign_cons_sft;




			//for (int j = 0;j < no_weeks * 7;j++)
			//	memset(solution[i][j], 0, sizeof solution[i][j]);

		int req[10];
		int last_cons = nurses[ii].history.numberOfConsecutiveWorkingDays;
		int last_con_off = nurses[ii].history.numberOfConsecutiveDaysOff;
		//int max_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfAssignments;
		//int min_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfAssignments;
		int max_con_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfConsecutiveWorkingDays;
		int min_con_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfConsecutiveWorkingDays;
		int max_con_off = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfConsecutiveDaysOff;
		int min_con_off = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfConsecutiveDaysOff;
		//int last_assign_sft = shift_type_point[nurses[ii].history.lastAssignedShiftType];
		//int last_assign_cons_sft = nurses[ii].history.numberOfConsecutiveAssignments;
		int key1 = contracts_point.find(nurses[ii].contract)->second;
		int max_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfAssignments;
		int min_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfAssignments;
		bool com_weekend = contracts[contracts_point.find(nurses[ii].contract)->second].completeWeekends;

		string nurse_type = nurses[ii].contract;


		int s = 0, r = 0, f = 0;
		memset(req, 0, sizeof req);
		int cnt = last_cons, cnt_off = last_con_off, break1 = 0;



		for (int d = 0;d < 7 * no_weeks;d = d + r + s)
		{




			cnt += r;
			/*r = floor(max_assignment / no_weeks);


				if (r > max_con_assignment )
				{
					r = rand()%2 +max_con_assignment;
				}
				else if (r < min_con_assignment)
				{
					r = min_con_assignment;
				}



*/
/*r = rand() % (max_con_assignment - min_con_assignment + 2) + min_con_assignment;
s = rand() % (min_con_off + (max_con_off - min_con_off));
//r = max_con_assignment;

//r = rand() % (max_con_assignment - min_con_assignment + 1) + min_con_assignment;
//s = rand() % max_con_off +(no_weeks - r);

if (nurse_type == "FullTime")
{
	s = rand() % min_con_off + (min_con_off - 1);
}
else
{
	if (s > max_con_off)
	{
		s = max_con_off;
	}
	else if (s < min_con_off)
	{
		s = min_con_off ;
	}

}
*/


			r = rand() % (max_con_assignment - min_con_assignment + 1) + min_con_assignment;
			s = rand() % (min_con_off + (max_con_off - min_con_off));
			//r = rand() % 2 + max_con_assignment;
			//s = rand() % 2 +min_con_off;

			if (s > 0)
			{
				cnt_off += s;

				if (cnt_off >= max_con_off)
					s = 0;

			}



			if (s == 0)
				cnt += r;
			else
				cnt = 0;

			if (cnt >= max_con_assignment)
				s = min_con_off;

			f = d + s + r;




			if (d + s >= no_weeks * 7)
			{
				break;
			}
			if (f > 7 * no_weeks)
			{
				f = 7 * no_weeks;
			}

			for (int k = 0;k < nurses[nur].skills.size();k++)
			{
				int sk = skills_point[nurses[nur].skills[k]];
				for (int i = d + s;i < f;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						req[j] += max(0, requirements_fulfil[i][j][sk]);

					}
				}

			}


			int max_sft = -1, mx = 0;

			req_s.clear();
			for (int i = 0;i < no_shift_types;i++)
			{
				req_s.push_back(make_pair(req[i], i));
			}


			/*for (int i = 0;i < no_shift_types;i++)
			{
				if (req[i] > mx)
				{
					mx = req[i];
					max_sft = i;

				}
				if (req[i] == mx)
				{
					int r = rand() % 2;
					if (r == 1)
					{
						mx = req[i];
						max_sft = i;

					}



				}
			}*/
			int ind = 0;
			sort(req_s.rbegin(), req_s.rend());
			max_sft = req_s[ind].second;
			if (conflict_check(nur, d + s, max_sft) == 0)
			{


				for (int i = d + s;i < d + s + r;i++)
				{

					int mx = -1, mx_skl = -1;
					for (int k = 0;k < nurses[nur].skills.size();k++)
					{
						int sk = skills_point[nurses[nur].skills[k]];
						if (mx < requirements_fulfil[i][max_sft][sk])
						{
							mx = requirements_fulfil[i][max_sft][sk];
							mx_skl = sk;
						}





					}

					solution[nur][i][max_sft] = mx_skl + 1;
					requirements_fulfil[i][max_sft][mx_skl] = max(requirements_fulfil[i][max_sft][mx_skl] - 1, 0);
					//rand_assign--;

				}



			}

			else
			{



				if (req_s[ind].second == req_s[ind + 1].second && conflict_check(nur, d + s, req_s[ind + 1].second) == 0)
				{

					int max_sft1 = req_s[ind + 1].second;


					for (int i = d + s;i < d + s + r;i++)
					{

						int mx = -1, mx_skl = -1;
						for (int k = 0;k < nurses[nur].skills.size();k++)
						{
							int sk = skills_point[nurses[nur].skills[k]];
							if (mx < requirements_fulfil[i][max_sft1][sk])
							{
								mx = requirements_fulfil[i][max_sft1][sk];
								mx_skl = sk;
							}






						}

						solution[nur][i][max_sft1] = mx_skl + 1;
						requirements_fulfil[i][max_sft1][mx_skl] = max(requirements_fulfil[i][max_sft1][mx_skl] - 1, 0);
						//rand_assign--;

					}



					continue;
				}


				int prev_skl = 0;
				int prev_sft = -1;

				for (int ss = 0;ss < no_shift_types;ss++)
				{
					if (solution[nur][d - 1][ss] > 0)
					{
						prev_sft = ss;
						prev_skl = solution[nur][d - 1][ss];
					}
				}

				int mx = -1, mx_skl = -1;
				for (int k = 0;k < nurses[nur].skills.size();k++)
				{
					int sk = skills_point[nurses[nur].skills[k]];
					if (mx < requirements_fulfil[d][max_sft][sk])
					{
						mx = requirements_fulfil[d][max_sft][sk];
						mx_skl = sk;
					}


				}

				if (requirements_fulfil[d - 1][prev_sft][prev_skl] >= requirements_fulfil[d][max_sft][mx_skl] || d + s - 1 == 0)
				{
					for (int i = d + s + 1;i < f;i++)
					{
						cnt = r - 2;
						int mx = -1, mx_skl = -1;
						for (int k = 0;k < nurses[nur].skills.size();k++)
						{
							int sk = skills_point[nurses[nur].skills[k]];
							if (mx < requirements_fulfil[i][max_sft][sk])
							{
								mx = requirements_fulfil[i][max_sft][sk];
								mx_skl = sk;
							}



						}
						if (conflict_check(nur, i, max_sft) == 0)
						{

							solution[nur][i][max_sft] = mx_skl + 1;
							requirements_fulfil[i][max_sft][mx_skl] = max(requirements_fulfil[i][max_sft][mx_skl] - 1, 0);
							//rand_assign--;

						}

					}

				}



				else
				{
					solution[nur][d + s - 1][prev_sft] = 0;
					requirements_fulfil[d + s - 1][prev_sft][prev_skl]++;

					for (int i = d + s;i < f;i++)
					{
						int mx = -1, mx_skl = -1;
						for (int k = 0;k < nurses[nur].skills.size();k++)
						{
							int sk = skills_point[nurses[nur].skills[k]];
							if (mx < requirements_fulfil[i][max_sft][sk])
							{
								mx = requirements_fulfil[i][max_sft][sk];
								mx_skl = sk;
							}



						}
						if (conflict_check(nur, i, max_sft) == 0)
						{
							solution[nur][i][max_sft] = mx_skl + 1;
							requirements_fulfil[i][max_sft][mx_skl] = max(requirements_fulfil[i][max_sft][mx_skl] - 1, 0);

						}

					}




				}


			}




			//show_solution();
			//vailidator();



		}





















		ds.erase(ds.begin() + rnd);



	}

	show_solution();
	vailidator();

}








void add_noise()
{
	//vailidator();


	int rnd = rand() % (no_weeks * 7 * no_skills);
	int cnt = 0;
	while (rnd--)
	{
		int r_day = rand() % no_weeks * 7;
		int r_sft = rand() % no_shift_types;
		int r_skl = rand() % no_skills;
		int r_nrs = nurse_space[r_skl][rand() % nurse_space[r_skl].size()];


		if (conflict_check(r_nrs, r_day, r_sft) == 0)
		{
			//out << r_nrs << " " << r_day << " " <<r_sft << endl;

			int c = better_vailidator();

			int p_s = solution[r_nrs][r_day][r_sft];
			solution[r_nrs][r_day][r_sft] = r_skl;
			int c1 = better_vailidator();


			if (c1 == -1 || c1 > c)
			{
				solution[r_nrs][r_day][r_sft] = p_s;
			}


			//cnt++;
			//vailidator();
		}


	}
	//out << "after" <<cnt<< endl;




}








void insert_sol_nurse(int take)
{




	in.close();
	string file = "./output/random.txt";
	in.open(file);

	//int take = 1;
	while (take--)
	{


		for (int j = 0;j < no_nurses + 1;j++)
		{
			for (int k = 0;k < no_weeks * 7 + 1;k++)
			{
				memset(solution[j][k], 0, sizeof solution[j][k]);
				memset(sol[j][k], 0, sizeof sol[j][k]);
			}
		}




		for (int i = 0;i < no_nurses;i++)
		{
			string nur;
			in >> nur;

			for (int j = 0;j < no_weeks * 7;j++)
			{
				for (int k = 0;k < no_shift_types;k++)
				{


					in >> solution[i][j][k];

				}
			}

		}
		show_solution();
		vailidator();
		/*sol_nurse();
		add_noise();
		sol_nurse();
		vailidator();*/
	}






}


int week_hard_validator1(int i)
{
	int flag = 0;
	for (int nur = 0;nur < no_nurses;nur++)
	{
		for (int j = i * 7;j < i * 7 + 7;j++)
		{
			bool f = 0;

			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[nur][j][k] > 0)
				{
					if (f == 1)
					{
						flag++;
						//break;
					}

					f = 1;

				}

			}
		}

	}





	return flag;
}

int week_hard_validator2(int i)
{


	int total = 0;

	memset(requirements_fulfil, 0, sizeof requirements_fulfil);

	for (i = i * 7;i < i * 7 + 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{

			int t = 0, tt = 0;
			for (int k = 0;k < no_skills;k++)
			{
				t += requirements_minimum[i][j][k];
			}

			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
					tt++;
			}

			if (t > tt)
				total += t - tt;

		}


	}




	return total;

}

int week_hard_validator4(int i)
{
	int l = i;

	int flag = 0;

	memset(requirements_fulfil, 0, sizeof requirements_fulfil);

	for (i = i * 7;i < i * 7 + 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
				{
					int sk = solution[k][i][j] - 1;
					requirements_fulfil[i][j][sk]++;


				}

			}



		}


	}
	i = l;

	for (i = i * 7;i < i * 7 + 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_skills;k++)
			{
				if (requirements_fulfil[i][j][k] < requirements_minimum[i][j][k])
				{
					flag++;

				}

			}



		}


	}



	return flag;

}

void sol_week(int evoluation)
{
	int evul = 0;




	for (int i = 0;i < no_weeks;i++) {
		int evu = week_validator(i);

		evul += evu;


		for (int nur = 0;nur < no_nurses;nur++)
		{
			for (int j = i * 7; j < i * 7 + 7;j++)
			{

				for (int sft = 0;sft < no_shift_types;sft++)
				{

					week_sol[i][s_n].sol[nur][j][sft] = solution[nur][j][sft];
				}

			}

		}




		/*int hw1 = week_hard_validator1(i);
		int hw2 = week_hard_validator2(i);
		int hw3 = week_hard_validator4(i);


		out << "Week_Validator h1 h2 h3 " << hw1 << " " << hw2 << " " << hw3 << " " << endl;
		*/



		int quality = evu;
		week_sol[i][s_n].distance = evu;
		week_sol[i][s_n].trail = 1 / evoluation;
		week_sol[i][s_n].visibility = (1.0 / evu);

		out << "s_n" << s_n << endl;
		week_sol_point[i].push_back(make_pair(week_sol[i][s_n].trail + week_sol[i][s_n].visibility, s_n));
		//solution_no++;




	}

	s_n += 1;
	see_sol = s_n;


}





int better_vailidator()
{
	//out << "h1" << endl;
	int h1 = hard_validator1();
	//show_solution();
	int h2 = hard_validator2();
	int h4 = hard_validator4();
	//show_solution();
	int h3 = hard_validator3();
	//show_solution()


		//out<<s4<<" "<<s5<<endl;
	//show_solution();
	//out << h1 << " " << h2 << " " << h3 << " " << h4 << endl;
	//out << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s6 << " " << s7 << "   " << s1 + s2 + s3 + s4 + s5 + s6 + s7 << endl;
	if (h1 == 0 && h4 == 0 && h3 == 0 && h2 == 0)
	{
		//out << "final solution" << endl;

		int s1 = soft_validator1();
		//show_solution();
		//out << "s2" << endl;
		int s2 = soft_validator2();
		//show_solution();

		//out << "s3" << endl;
		int s3 = soft_validator3();
		//show_solution();
		//out << "s4" << endl;
		int s4 = soft_validator4();
		//show_solution();
		//out << "s5" << endl;
		int s5 = soft_validator5();
		//show_solution();
		int s6 = soft_validator6();
		//show_solution();
		int s7 = soft_validator7();
		//show_solution();

		int evoluation = s1 + s2 + s3 + s4 + s5 + s6 + s7;
		//sol_nurse(evoluation);
		//particle_create(evoluation);






		return evoluation;
	}
	else
		return -1;
}














bool vailidator()
{
	//out << "h1" << endl;
	int h1 = hard_validator1();
	//show_solution();
	int h2 = hard_validator2();
	int h4 = hard_validator4();
	//show_solution();
	int h3 = hard_validator3();
	//show_solution();
	//out << "s1" << endl;
	int s1 = soft_validator1();
	//show_solution();
	//out << "s2" << endl;
	int s2 = soft_validator2();
	//show_solution();

	//out << "s3" << endl;
	int s3 = soft_validator3();
	//show_solution();
	//out << "s4" << endl;
	int s4 = soft_validator4();
	//show_solution();
	//out << "s5" << endl;
	int s5 = soft_validator5();
	//show_solution();
	int s6 = soft_validator6();
	//show_solution();
	int s7 = soft_validator7();
	//show_solution();


		//out<<s4<<" "<<s5<<endl;
	//show_solution();
	out << h1 << " " << h2 << " " << h3 << " " << h4 << endl;
	out << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s6 << " " << s7 << "   " << s1 + s2 + s3 + s4 + s5 + s6 + s7 << endl;
	if (h1 == 0 && h4 == 0 && h3 == 0 && h2 == 0)
	{
		//out << "final solution" << endl;

		sol_cnt++;
		//out << sol_cnt << endl;

		//show_solution();
		out << h1 << " " << h2 << " " << h3 << " " << h4 << endl;

		out << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s6 << " " << s7 << "   " << "Solution :" << s1 + s2 + s3 + s4 + s5 + s6 + s7 << endl;


		int evoluation = s1 + s2 + s3 + s4 + s5 + s6 + s7;
		//sol_nurse(evoluation);
		//particle_create(evoluation);

		//sol_week(evoluation);




		return 1;
	}

	return 0;
}
vector<int>repeat[200];
int prb[100];
bool repair1()
{
	for (int i = 0;i < 100;i++)
		repeat[i].clear();


	//show_solution();
	for (int i = 0;i < no_nurses;i++)
	{
		for (int j = 0;j < no_weeks * 7;j++)
		{
			for (int i2 = 0;i2 < no_shift_types;i2++)
			{

				if (solution[i][j][i2] > 0)
				{



					int lsi = -1;
					if (j == 0)
					{
						string ls = nurses[i].history.lastAssignedShiftType;
						if (ls != "None")
						{
							lsi = shift_type_point.find(ls)->second;

						}
					}
					else
					{
						for (int m = 0;m < no_shift_types;m++)
						{
							if (solution[i][j - 1][m] > 0)
							{
								lsi = m;

							}
						}

					}

					if (lsi != -1)
					{
						for (int i1 = 0;i1 < shift_type[lsi].forbiddenSucceedingShiftTypes.size();i1++)
						{
							int frbd_sft = shift_type_point.find(shift_type[lsi].forbiddenSucceedingShiftTypes[i1])->second;
							if (frbd_sft == i2)
							{
								int her_skil = solution[i][j][i2] - 1;


								bool flag1 = 0;

								int itr1 = 0;

								while (flag1 == 0 && itr1 < 5000)
								{
									itr1++;



									//out<< solution[i][j][shift]<<" " << n_t <<endl;
									int rnd_nurse, rnd_nurse_name = -1;
									int rnddd = rand() % 5;
									//cout << rnddd << endl;
									vector<int>free;
									if (rnddd == 2)
									{
										if (skill_nurse[2][her_skil].size() == 0)
											continue;

										for (int k = 0;k < skill_nurse[2][her_skil].size();k++)
										{
											bool f = 0;


											int lsi = -1;
											if (j == 0)
											{
												string ls = nurses[skill_nurse[2][her_skil][k]].history.lastAssignedShiftType;
												if (ls != "None")
												{
													lsi = shift_type_point.find(ls)->second;

												}
											}
											else
											{
												for (int m = 0;m < no_shift_types;m++)
												{
													if (solution[skill_nurse[2][her_skil][k]][j - 1][m] > 0)
													{
														lsi = m;

													}
												}

											}

											if (lsi != -1)
											{
												for (int i1 = 0;i1 < shift_type[lsi].forbiddenSucceedingShiftTypes.size();i1++)
												{
													int frbd_sft = shift_type_point.find(shift_type[lsi].forbiddenSucceedingShiftTypes[i1])->second;
													if (frbd_sft == i2)
														f = 1;
												}

											}








											if (f == 0)
												free.push_back(skill_nurse[2][her_skil][k]);
										}
										if (free.size() == 0)
											continue;

										rnd_nurse = rand() % free.size();

										rnd_nurse_name = free[rnd_nurse];


									}

									else
									{
										if (skill_nurse[1][her_skil].size() == 0)
											continue;
										for (int k = 0;k < skill_nurse[1][her_skil].size();k++)
										{
											bool f = 0;
											int lsi = -1;
											if (j == 0)
											{
												string ls = nurses[skill_nurse[1][her_skil][k]].history.lastAssignedShiftType;
												if (ls != "None")
												{
													lsi = shift_type_point.find(ls)->second;

												}
											}
											else
											{
												for (int m = 0;m < no_shift_types;m++)
												{
													if (solution[skill_nurse[1][her_skil][k]][j - 1][m] > 0)
													{
														lsi = m;

													}
												}

											}

											if (lsi != -1)
											{
												for (int i1 = 0;i1 < shift_type[lsi].forbiddenSucceedingShiftTypes.size();i1++)
												{
													int frbd_sft = shift_type_point.find(shift_type[lsi].forbiddenSucceedingShiftTypes[i1])->second;
													if (frbd_sft == i2)
														f = 1;
												}

											}
											if (f == 0)
												free.push_back(skill_nurse[1][her_skil][k]);
										}
										if (free.size() == 0)
											continue;

										rnd_nurse = rand() % free.size();

										rnd_nurse_name = free[rnd_nurse];

									}

									//cout << rnd_nurse << " " << r_d << " " << r_sft << " " << n_t << " "<<rnddd<<endl;

									//show_solution();
									//out << endl;
									if (rnd_nurse_name != -1 && solution[rnd_nurse_name][j][i2] == 0)
									{
										//cout << "sdcv" << endl;
										//out<< rnd_nurse_name][j][shift]
										solution[rnd_nurse_name][j][i2] = her_skil + 1;
										//cout << rnd_nurse_name << " " << j << " " << shift << " " << n_t << endl;

										//show_solution();
										//repeat[i].erase(repeat[i].begin() + rnd);
										nurse_check_per_day[rnd_nurse_name][j] = her_skil + 1;
										//out << rnd_nurse_name<<" "<< j << " " << i2 << "     " << i <<"  "<<endl;
										solution[i][j][i2] = 0;
										//show_solution();
										if (vailidator())
											return 1;
										//out << endl << endl;
										flag1 = 1;
									}



								}





















							}

						}

					}
				}
			}


















			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					repeat[i].push_back(k);
				}

			}






			int iter = 0;
			while (repeat[i].size() > 1 && iter < 100)
			{
				//out << "strt" << endl;
				//show_solution();
				iter++;
				int rnd = rand() % repeat[i].size();
				int shift = repeat[i][rnd];
				//out << i << " " << j << " " << rnd << " " << shift << " ";
				int n_t = solution[i][j][shift] - 1;

				//out<< solution[i][j][shift]<<" " << n_t <<endl;
				int rnd_nurse, rnd_nurse_name = -1;
				int rnddd = rand() % 5;
				//cout << rnddd << endl;
				vector<int>free;
				if (rnddd == 2)
				{
					if (skill_nurse[2][n_t].size() == 0)
						continue;

					for (int k = 0;k < skill_nurse[2][n_t].size();k++)
					{
						bool f = 0;
						for (int l = 0;l < no_shift_types;l++)
						{
							if (solution[skill_nurse[2][n_t][k]][j][l] > 0)
								f = 1;
							int lsi = -1;
							if (j == 0)
							{
								string ls = nurses[skill_nurse[2][n_t][k]].history.lastAssignedShiftType;
								if (ls != "None")
								{
									lsi = shift_type_point.find(ls)->second;

								}
							}
							else
							{
								for (int m = 0;m < no_shift_types;m++)
								{
									if (solution[skill_nurse[2][n_t][k]][j - 1][m] > 0)
									{
										lsi = m;

									}
								}

							}

							if (lsi != -1)
							{
								for (int i1 = 0;i1 < shift_type[lsi].forbiddenSucceedingShiftTypes.size();i1++)
								{
									int frbd_sft = shift_type_point.find(shift_type[lsi].forbiddenSucceedingShiftTypes[i1])->second;
									if (frbd_sft == shift)
										f = 1;
								}

							}







						}
						if (f == 0)
							free.push_back(skill_nurse[2][n_t][k]);
					}
					if (free.size() == 0)
						continue;

					rnd_nurse = rand() % free.size();

					rnd_nurse_name = free[rnd_nurse];


				}

				else
				{
					if (skill_nurse[1][n_t].size() == 0)
						continue;
					for (int k = 0;k < skill_nurse[1][n_t].size();k++)
					{
						bool f = 0;
						for (int l = 0;l < no_shift_types;l++)
						{
							if (solution[skill_nurse[1][n_t][k]][j][l] > 0)
								f = 1;

						}
						if (f == 0)
							free.push_back(skill_nurse[1][n_t][k]);
					}
					if (free.size() == 0)
						continue;

					rnd_nurse = rand() % free.size();

					rnd_nurse_name = free[rnd_nurse];

				}

				//cout << rnd_nurse << " " << r_d << " " << r_sft << " " << n_t << " "<<rnddd<<endl;

				//show_solution();
				//out << endl;
				if (rnd_nurse_name != -1 && solution[rnd_nurse_name][j][shift] != -1)
				{
					//cout << "sdcv" << endl;
					//out<< rnd_nurse_name][j][shift]
					solution[rnd_nurse_name][j][shift] = n_t + 1;
					//cout << rnd_nurse_name << " " << j << " " << shift << " " << n_t << endl;

					//show_solution();
					repeat[i].erase(repeat[i].begin() + rnd);
					nurse_check_per_day[rnd_nurse_name][j] = n_t + 1;
					//cout << "ghjdrthtrfhef" << endl;
					solution[i][j][shift] = 0;
					//show_solution();
					//vailidator();
					//cout << endl << endl;
				}


			}





			repeat[i].clear();
			/*
				int itr = 0;
			while (repeat[i].size() > 1)
			{
					itr++;
					int rnd = rand() % repeat[i].size();

					int skill = solution[i][j][rnd];


					vector<int>free;nurse_from_skill[skill].size()
					for (int l = 0;l < ;l++)
					{
						bool ck = 0;
						for (int k = 0;k < no_shift_types;k++)
						{
							if (solution[l][j][k] > 0)
								ck = 1;
						}

						if (ck == 0)
						{
							//cout << nurse_from_skill[skill][l] << "as" << endl;
							free.push_back(nurse_from_skill[skill][l]);
						}
					}
					if (free.size() > 0)
					{
						int nrs = rand() % free.size();
						solution[i][j][rnd] = 0;
						solution[nrs][j][rnd] = skill;
						//cout << "kkk" << endl;
					}
					int itr = 0;
					while (repeat[i].size() > 1 && itr < 10)
					{
						itr++;
						int rnd = rand() % repeat[i].size();

						int skill = solution[i][j][rnd];


						vector<int>free;
						for (int l = 0;l < nurse_from_skill[skill].size();l++)
						{
							bool ck = 0;
							for (int k = 0;k < no_shift_types;k++)
							{
								if (solution[l][j][k] > 0)
									ck = 1;
							}

							if (ck == 0)
							{
								//cout << nurse_from_skill[skill][l] << "as" << endl;
								free.push_back(nurse_from_skill[skill][l]);
							}
						}
						if (free.size() > 0)
						{
							int nrs = rand() % free.size();
							solution[i][j][k] = 0;
							solution[nrs][j][k] = skill;
							//cout << "kkk" << endl;
						}
					}



					repeat[i].clear();
				}



			}*/
		}

	}
	return 0;
}





void nurse_add(int i)
{
	int max_assignment = contracts[contracts_point.find(nurses[i].contract)->second].maximumNumberOfAssignments;
	int min_assignment = contracts[contracts_point.find(nurses[i].contract)->second].minimumNumberOfAssignments;
	int max_con_assignment = contracts[contracts_point.find(nurses[i].contract)->second].maximumNumberOfConsecutiveWorkingDays;
	int min_con_assignment = contracts[contracts_point.find(nurses[i].contract)->second].minimumNumberOfConsecutiveWorkingDays;
	int max_con_off = contracts[contracts_point.find(nurses[i].contract)->second].maximumNumberOfConsecutiveDaysOff;
	int min_con_off = contracts[contracts_point.find(nurses[i].contract)->second].minimumNumberOfConsecutiveDaysOff;
	bool com_weekend = contracts[contracts_point.find(nurses[i].contract)->second].completeWeekends;

	int lst = -1;

	int assignment = 0, con_assignment = 0, con_off = 0, con_sft = 0;




	for (int j = 0;j < no_weeks * 7;j++)
		memset(solution[i][j], 0, sizeof solution[i][j]);

	int prob = no_weeks * 7;
	int yes = max_assignment;
	int no = no_weeks * 7 - yes;
	int sft = no_shift_types;

	int randd = 0;
	//out << i << endl;
	for (int j = 0;j < no_weeks * 7;j++)
	{
		if (j % 7 == 5)
		{
			prob = prob * 2;
		}



		if (j % 7 == 6 && com_weekend == 1)
		{
			//out << days[j % 7]<<endl;
			if (con_assignment == 0)
			{
				prob = prob * 2;
			}
			else
			{
				prob = prob / 2;
			}


		}




		randd = rand() % prob;
		bool as = 0;
		int iter = 0;
		while (randd <= yes && iter < no_shift_types * 2 && as == 0)
		{
			iter++;



			int r_sft = rand() % sft;

			if (r_sft >= no_shift_types)
				r_sft = lst;


			int r_skl = skills_point.find(nurses[i].skills[rand() % nurses[i].skills.size()])->second;

			if (conflict_check(i, j, r_sft) == 0)
			{
				solution[i][j][r_sft] = r_skl + 1;
				//out << i<<" "<<j << " " << r_sft << " "<<solution[i][j][r_sft]<< endl;
				as = 1;
				iter = 0;
				//	out << lst << " " << con_sft << " " << 100.0*(float)(sft - no_shift_types + 1) / (float)sft << " " << r_sft << endl;
				if (r_sft == lst)
				{
					con_sft++;
				}
				else
				{
					con_sft = 1;
					lst = r_sft;

				}
				if (lst != -1)
					sft = no_shift_types + (shift_type[lst].maximumNumberOfConsecutiveAssignments - con_sft) * 1;
				else
					sft = no_shift_types;

			}

		}

		if (as == 1)
		{
			assignment++;
			con_assignment++;
			con_off = 0;

			yes = (max_con_assignment - con_assignment) * 30 + 1;


			no = 1;


		}
		else
		{
			con_assignment = 0;
			con_off++;
			yes = 1;
			no = (min_con_off - con_off) * 30 + 1;
			lst = -1;
			con_sft = 0;

		}

		prob = yes + no;
		if (prob == 0)
			prob++;

		//out << j<<" "<<as<<" "<<(float)(yes/(float)prob)*100.0 << "%  " << (no/(float)prob)*100.0 << "%" << endl;
		//show_solution();

	}
	int single_nur_vali = 0;
	int single2 = single_nur_vali2(i);
	int single3 = single_nur_vali3(i);
	int single4 = single_nur_vali4(i);
	int single5 = single_nur_vali5(i);
	int single6 = single_nur_vali6(i);
	int single7 = single_nur_vali7(i);

	//single_nur_vali = single2 + single3 + single4 + single5 + single6 + single7;
//	out <<i<<"--->"<< single2 << " " << single3 << " " << single4 << " " << single5 << " " << single6 << " " << single7 <<" "<< single_nur_vali <<endl<<endl;


	//show_solution();


}









bool skill_check(int nur, int skl)
{

	for (int i = 0;i < nurses[nur].skills.size();i++)
	{
		if (skills_point.find(nurses[nur].skills[i])->second == skl)
			return 1;

	}

	return 0;
}



vector<pair< int, int> >assign_nurse[100];
void fit_nurse(int nur, int i, int j)
{


	vector<int>free_nurse;



	for (int l = 0;l < no_nurses;l++)
	{
		bool f = 0;
		for (int k = 0;k < no_shift_types;k++)
		{
			auto it = find(assign_nurse[i].begin(), assign_nurse[i].end(), make_pair(l, k));
			if (it != assign_nurse[i].end())
			{
				f = 1;
			}
		}
		if (conflict_check(l, i, j) == 0 && f == 0)
		{

			free_nurse.push_back(l);
		}

	}






	int iter = 0;
	bool flg = 1;
	int skl = solution[nur][i][j] - 1;

	while (iter < 500 && flg)
	{

		iter++;

		int rndd = rand() % nurse_space[skl].size();
		int chosen_nurse = nurse_space[skl][rndd];

		auto it = find(free_nurse.begin(), free_nurse.end(), chosen_nurse);

		if (it != free_nurse.end())
		{

			solution[nur][i][j] = 0;
			solution[chosen_nurse][i][j] = skl + 1;
			// assign_nurse[i][i].erase(std::remove(assign_nurse[i][i].begin(), assign_nurse[i][i].end(), nur), assign_nurse[i][i].end());
			auto itr = find(assign_nurse[i].begin(), assign_nurse[i].end(), make_pair(nur, j));
			if (itr != assign_nurse[i].end())
				assign_nurse[i].erase(itr);


			assign_nurse[i].push_back(make_pair(chosen_nurse, j));
			flg = 0;
			iter = 0;


			out << "free" << endl;
		}


		else if (iter > 300)
		{

			int prv_sft, ff = 0;
			for (int m = 0;m < no_shift_types;m++)
			{
				if (solution[chosen_nurse][i][m] > 0)
				{
					prv_sft = m;
					ff = 1;
				}
			}
			if (ff = 1)
			{
				if (conflict_check(chosen_nurse, i, j) == 0)
				{


					for (int m = 0;m < no_shift_types;m++)
						if (solution[chosen_nurse][i][m] > 0)
							prv_sft = m;
					int prv_skl = solution[chosen_nurse][i][prv_sft];
					if (prv_sft != j && solution[chosen_nurse][i][j] == 0)
					{

						solution[chosen_nurse][i][j] = skl + 1;


						if (conflict_check(nur, i, prv_sft) == 0 && skill_check(nur, prv_skl))
						{
							solution[chosen_nurse][i][prv_sft] = 0;
							solution[nur][i][j] = 0;
							solution[nur][i][prv_sft] = prv_skl;
							flg = 0;
							out << "from day" << endl;;

						}
						else
						{
							//solution[chosen_nurse][i][prv_sft] = -2;
							solution[nur][i][j] = 0;
							auto itr = find(assign_nurse[i].begin(), assign_nurse[i].end(), make_pair(nur, j));
							if (itr != assign_nurse[i].end())
								assign_nurse[i].erase(itr);

							out << "loop" << endl;
							fit_nurse(chosen_nurse, i, prv_sft);
							solution[chosen_nurse][i][prv_sft] = 0;
							flg = 0;

						}


					}

				}
			}

		}


	}


}


void repair2()
{

	for (int i = 0;i < 100;i++)
		assign_nurse[i].clear();

	for (int i = 0;i < no_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
				{
					assign_nurse[i].push_back(make_pair(k, j));

				}

			}
		}
	}

	vector<int>rand_day;
	for (int i = 0;i < no_weeks * 7;i++)
		rand_day.push_back(i);


	while (rand_day.size() > 0)
	{
		int ind = rand() % rand_day.size();
		int i = rand_day[ind];


		for (int k = 0;k < assign_nurse[i].size();k++)
		{
			int nur = assign_nurse[i][k].first;
			int j = assign_nurse[i][k].second;


			if (conflict_check(nur, i, j))
			{
				out << "--" << nur << " " << i << " " << j << " " << rand_day.size() << endl;
				fit_nurse(nur, i, j);
				vailidator();





			}

		}

		rand_day.erase(rand_day.begin() + ind);


	}









}






void repair()
{
	//int h1 = hard_validator1();
	//if (h1 > 0)
	repair1();



}

void print_nurse_from_skill()
{
	for (int i = 0;i < no_skills;i++)
	{

		for (int j = 0;j < nurse_from_skill[i].size();j++)
		{
			out << nurse_from_skill[i][j] << " ";
		}

		out << endl;

	}
}

void print_req()
{

	for (int i = 0;i < no_weeks * 7;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				out << requirements_minimum[i][j][k] << " ";
			}
			out << " ";
		}
		out << endl;

	}



}


void random_initialization()
{
	memset(nurse_check_per_day, -1, sizeof nurse_check_per_day);
	vector<int>ds;

	for (int i = 0;i < no_shift_types * 7 * no_weeks;i++)
	{
		ds.push_back(i);
	}


	create_req();

	while (ds.size() != 0)
	{

		int rnd = rand() % ds.size();
		//out << ds[rnd]<<" "<<ds.size()<<endl;


		int r_d = ds[rnd] / no_shift_types;
		int r_sft = ds[rnd] % no_shift_types;
		//out << r_d << " " << r_sft << " ";
		int r_t = 0;
		vector<pair<int, int>>r_n_s;
		for (int i = 0;i < no_skills;i++)
		{
			int req = 0;

			req = requirements_remain[r_d][r_sft][i];
			//out << req << " ";
			requirements_remain[r_d][r_sft][i] = 0;
			r_t += req;
			for (int j = 0;j < req;j++)
				r_n_s.push_back(make_pair(i, j));


		}
		//out << endl<<endl;
		for (int i = 0;i < r_t;i++)
		{

			int r_n = rand() % r_n_s.size();
			int n_t = r_n_s[r_n].first;
			int flag = 100;
			int iter = 0;
			while (flag && iter < 500)
			{
				//cout << "aefawegwagaWEGFFW" << endl;
				iter++;

				int rnd_nurse, rnd_nurse_name;
				int rnddd = rand() % 10;
				//cout << rnddd << endl;

				if (rnddd == 5)

				{
					if (skill_nurse[2][n_t].size() == 0)
						continue;
					//cout << "if" << endl;
					rnd_nurse = rand() % skill_nurse[2][n_t].size();
					//cout << rnd_nurse << " " << skill_nurse[2][n_t].size() << endl;
					rnd_nurse_name = skill_nurse[2][n_t][rnd_nurse];
					//cout << rnd_nurse << " " << rnd_nurse_name << endl;
				}

				else
				{
					if (skill_nurse[1][n_t].size() == 0)
						continue;
					//cout << "else" << endl;
					//cout <<  skill_nurse[1][n_t].size() << endl;
					rnd_nurse = rand() % skill_nurse[1][n_t].size();
					//cout << rnd_nurse << " " << " " << skill_nurse[1][n_t].size() << endl;
					rnd_nurse_name = skill_nurse[1][n_t][rnd_nurse];
					//cout << rnd_nurse << " " << rnd_nurse_name << endl;
				}

				//cout << rnd_nurse << " " << r_d << " " << r_sft << " " << n_t << " "<<rnddd<<endl;

				if (solution[rnd_nurse_name][r_d][r_sft] == 0)
				{
					solution[rnd_nurse_name][r_d][r_sft] = n_t + 1;
					flag = 0;
					r_n_s.erase(r_n_s.begin() + r_n);
					nurse_check_per_day[rnd_nurse_name][r_d] = r_sft;
					//cout << "ghjdrthtrfhef" << endl;
				}


			}

		}

		//show_solution();
		//out << endl << endl;

		ds.erase(ds.begin() + rnd);

	}

}








int week_sol_soft_validator1(vector<int>v)
{


	int flag = 0;
	int total = 0;
	int nom_weeks = 1;
	memset(requirements_fulfil, 0, sizeof requirements_fulfil);

	for (int i = 0;i < nom_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{
			bool f = 0;

			for (int k = 0;k < no_nurses;k++)
			{
				if (solution[k][i][j] > 0)
				{
					int sk = solution[k][i][j];
					requirements_fulfil[i][j][sk]++;

				}

			}



		}


	}


	for (int i = 0;i < nom_weeks * 7;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{


			for (int k = 0;k < no_skills;k++)
			{
				int cnt = 0;
				for (int l = 0;l < no_nurses;l++)
				{
					if (k == solution[l][i][j] - 1)
						cnt++;
				}


				if (requirements_optimal[i][j][k] > cnt)
					total += (requirements_optimal[i][j][k] - cnt) * 30;

			}



		}


	}



	return total;

}
int week_sol_soft_validator2(vector<int>v)
{
	//minimumNumberOfConsecutiveWorkingDays,
		//maximumNumberOfConsecutiveWorkingDays,4
	int mn_v = 0, mx_v = 0;
	int total = 0;

	for (int i = 0;i < no_nurses;i++)
	{
		//out << "full" << total << endl;
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfConsecutiveWorkingDays;
		int mx = contracts[key].maximumNumberOfConsecutiveWorkingDays;
		//out << "--------------------------" << endl;

		int cons_day = nurses[i].history.numberOfConsecutiveWorkingDays;

		if (cons_day >= mx)
			cons_day = mx;

		for (int m = 0;m < no_weeks;m++)
		{

			bool start = 0;
			if (cons_day > 0)
				start = 1;

			for (int j = m * 7 + 0;j < m * 7 + 7;j++)
			{
				bool f = 0;

				for (int k = 0;k < no_shift_types;k++)
				{

					if (solution[i][j][k] > 0)
					{
						f = 1;
						start = 1;

					}




				}

				if (f == 1)
				{
					cons_day++;

				}

				if ((f == 0 || j == no_weeks * 7 - 1) && start == 1)
				{
					//out << j << " " << cons_day << endl;
					if (cons_day > mx)
					{
						total += (cons_day - mx) * 30;
						cons_day = 0;
						start = 0;
					}
					else if (cons_day < mn && j != no_weeks * 7 - 1)
					{
						total += (mn - cons_day) * 30;
						cons_day = 0;
						start = 0;
					}
					else if (cons_day >= mn && cons_day <= mx)
					{
						cons_day = 0;
						start = 0;
					}
				}

			}

		}
		//out << endl;



		//out << "half" << total << endl;







		//out << "@@" << mn << " " << mx << endl;
		string ss = nurses[i].history.lastAssignedShiftType;
		int lst = -1;
		if (ss != "None")
			lst = shift_type_point.find(ss)->second;






		for (int k = 0;k < no_shift_types;k++)
		{
			bool start = 0;
			int cons_sft = 0;
			mn = shift_type[k].minimumNumberOfConsecutiveAssignments;
			mx = shift_type[k].maximumNumberOfConsecutiveAssignments;

			bool f = 0;
			if (k == lst)
			{
				cons_sft = nurses[i].history.numberOfConsecutiveAssignments;

				if (cons_sft >= mx)
					cons_sft = mx;
				if (cons_sft > 0)
					start = 1;

			}

			for (int j = 0;j < no_weeks * 7;j++)
			{

				if (solution[i][j][k] > 0)
				{
					f = 1;
					start = 1;
					cons_sft++;

				}
				else
				{
					f = 0;
				}

				if ((f == 0 || j == no_weeks * 7 - 1) && start == 1)
				{

					if (cons_sft > mx)
					{
						//out <<1<<" "<< j << " " << cons_sft << endl;
						total += (cons_sft - mx) * 15;
						cons_sft = 0;
						start = 0;
					}
					else if (cons_sft < mn && j != no_weeks * 7 - 1)
					{
						//out <<2<<" "<< j << " " << cons_sft << endl;
						total += (mn - cons_sft) * 15;
						cons_sft = 0;
						start = 0;
					}
					else if (cons_sft >= mn && cons_sft <= mx)
					{
						cons_sft = 0;
						start = 0;
					}
				}




			}
		}

	}

	return total;
}
int week_sol_soft_validator3(vector<int>v)
{
	int mn_v = 0, mx_v = 0;
	int res = 0;

	for (int i = 0;i < no_nurses;i++)
	{
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfConsecutiveDaysOff;
		int mx = contracts[key].maximumNumberOfConsecutiveDaysOff;

		//out << mn << " " << mx << endl;


		int cons_dayof = nurses[i].history.numberOfConsecutiveDaysOff;
		//out << "cons_dayof"<<cons_dayof << endl;


		for (int j = 0;j < no_weeks * 7;j++)
		{
			//out << "j"<<j << endl;


			if (j < (no_weeks * 7) - 1)
			{
				bool f = 1;
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						f = 0;
					}
					//out << "k" << k << endl;
				}
				if (f == 1)
				{
					//out << "f1cons_dayof" << cons_dayof << endl;

					cons_dayof++;
					//out << "res" << res << endl;

				}
				if (f == 0)
				{
					//out << "f0" << endl;
					if (cons_dayof != 0)
					{
						//out << "f0cons_dayof" << cons_dayof << endl;
						if (cons_dayof > mx)
						{
							res += cons_dayof - mx;
							//cons_dayof = 0;
							//out << "res" << res << endl;


						}
						if (cons_dayof < mn)
						{
							res += mn - cons_dayof;
							//cons_dayof = 0;
								//out << "res" << res << endl;
						}
						cons_dayof = 0;
						//out << "cons_dayof" << cons_dayof << endl;
						//out << "res" << res << endl;
					}

				}

			}
			else
			{
				bool f = 1;
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						f = 0;
					}
					//out << "k" << k << endl;

				}
				if (f == 1)
				{
					//out << "f1cons_dayof" << cons_dayof << endl;

					cons_dayof++;
					if (cons_dayof > mx)
					{
						res += cons_dayof - mx;
						//cons_dayof = 0;
						//out << "res" << res << endl;


					}
					/*if (cons_dayof < mn)
					{
						res += mn - cons_dayof;
						//cons_dayof = 0;
						//out << "res" << res << endl;
					}*/
					cons_dayof = 0;
					//out << "res" << res << endl;

				}
				if (f == 0)
				{
					if (cons_dayof != 0)
					{
						//out << "f0cons_dayof" << cons_dayof << endl;
						if (cons_dayof > mx)
						{
							res += cons_dayof - mx;
							//cons_dayof = 0;
							//out << "res" << res << endl;


						}
						if (cons_dayof < mn)
						{
							res += mn - cons_dayof;
							//cons_dayof = 0;
							//out << "res" << res << endl;
						}
						cons_dayof = 0;
						//out << "cons_dayof" << cons_dayof << endl;
						//out << "res" << res << endl;
					}

				}





			}

		}
		//out <<"rws"<< res << endl;
	}
	//out <<"res"<< res << endl;


	return (res) * 30;

}
int week_sol_soft_validator4(vector<int>v)
{
	int flag = 0;
	for (int i = 0;i < no_nurses;i++)
	{

		for (int j = 0;j < shift_off_req[i].size();j++)
		{
			int d = shift_off_req[i][j].second;
			string shift = shift_off_req[i][j].first;

			if (shift == "Any")
			{
				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][d][k] > 0)
					{
						//solution[i][d][k] = 500;


						//out << endl << i << " " << d << " " << k << endl;
						flag++;
					}

				}
			}

			else
			{

				int s = shift_type_point.find(shift)->second;

				if (solution[i][d][s] > 0)
				{
					//solution[i][d][s] = 500;
					//out << endl << i << " " << d << " " << s << endl;
					flag++;
				}
			}

		}
	}
	return flag * 10;
}
int week_sol_soft_validator5(vector<int>v)
{
	int flag = 0;
	int total = 0;
	for (int i = 0;i < no_nurses;i++)
	{

		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].completeWeekends;


		if (mn == 1)
		{
			for (int j = 5;j < no_weeks * 7;j += 7)
			{
				//out << days[j % 7];

				int flag5 = 0;
				int flag6 = 0;


				for (int k = 0;k < no_shift_types;k++)
				{
					if (solution[i][j][k] > 0)
					{
						//solution[i][j][k] = 1000;
						flag5 = 1;
						//out << "f5" << flag5 << endl;

					}
					if (solution[i][j + 1][k] > 0)
					{
						//solution[i][j][k] = 1000;
						flag6 = 1;
						//out << "f6" << flag6 << endl;

					}
				}
				if (flag5 != flag6)
					total += 30;


			}
		}
	}
	return total;
}

int week_sol_soft_validator6(vector<int>v)
{
	int mn_v = 0, mx_v = 0;

	int total = 0;
	for (int i = 0;i < no_nurses;i++)
	{
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mn = contracts[key].minimumNumberOfAssignments;
		int mx = contracts[key].maximumNumberOfAssignments;


		int cons_assign = nurses[i].history.numberOfAssignments;
		int total_assign = 0;

		for (int j = 0;j < no_weeks * 7;j++)
		{
			bool f = 1;

			for (int k = 0;k < no_shift_types;k++)
			{

				if (solution[i][j][k] > 0)
					total_assign++;




			}



		}
		if (total_assign < mn)
			total += (mn - total_assign) * 20;
		else if (total_assign > mx)
			total += (total_assign - mx) * 20;




	}


	return total;
}
int week_sol_soft_validator7(vector<int>v)
{

	int total = 0;
	for (int i = 0;i < no_nurses;i++)
	{
		int f = 0;
		string s = nurses[i].contract;
		int key = contracts_point.find(s)->second;
		int mx = contracts[key].maximumNumberOfWorkingWeekends;


		int working_week_end = nurses[i].history.numberOfWorkingWeekends;
		int cnt = 0;
		bool flg = 0;
		for (int j = 5;j < no_weeks * 7;j += 7)
		{
			//out << days[j % 7];

			flg = 0;



			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[i][j][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flg = 1;
					//out << "f5" << flag5 << endl;
					//out << j << days[j % 7] << k<<" " ;

				}
				if (solution[i][j + 1][k] > 0)
				{
					//solution[i][j][k] = 1000;
					flg = 1;
					//out << "f6" << flag6 << endl;
					//out << j+1 << days[(j+1) % 7] << k<<" "  ;

				}




			}
			if (flg == 1)
				cnt++;

		}
		//cout << endl;

		//out <<i<<" "<< cnt << endl;
		if (cnt > mx)
			total += (cnt - mx) * 30;





	}
	return total;

}


int quality(vector<int>v)
{
	//out << "s1" << endl;
	int s1 = week_sol_soft_validator1(v);
	//show_solution();
	//out << "s2" << endl;
	int s2 = week_sol_soft_validator2(v);
	//show_solution();

	//out << "s3" << endl;
	int s3 = week_sol_soft_validator3(v);
	//show_solution();
	//out << "s4" << endl;
	int s4 = week_sol_soft_validator4(v);
	//show_solution();
	//out << "s5" << endl;
	int s5 = week_sol_soft_validator5(v);
	//show_solution();
	int s6 = week_sol_soft_validator6(v);
	//show_solution();
	int s7 = week_sol_soft_validator7(v);
	//show_solution();
	out << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s6 << " " << s7 << "   " << s1 + s2 + s3 + s4 + s5 + s6 + s7 << endl;

	return 0;

}

//vector< pair< int, vector<int> > > week_sol[17];


void divide_sol()
{


	for (int s = 0;s < no_weeks * 7 - 1;s = s + 7)
	{
		vector<int>v;




		for (int j = 0;j < no_nurses;j++)
		{
			for (int k = 0;k < s;k++)
			{
				for (int l = 0;l < no_shift_types;l++)
				{


					v.push_back(solution[j][k][l]);

				}
			}
		}


		int q = quality(v);











	}



}






void better_repair(int cnt)
{


	for (int i = 0;i < cnt;i++)
	{
		int d = ((rand() + rand())*rand()) % (no_weeks * 7);
		int s = ((rand() + rand())*rand()) % (no_shift_types);


		for (int j = 0;j < no_nurses;j++)
		{
			if (solution[j][d][s] > 0)
			{
				vector<pair<int, int>> change;
				int ck = 0;
				ck = better_vailidator();
				change.push_back(make_pair(ck, j));

				int skl = solution[j][d][s];
				solution[j][d][s] = 0;

				//out << 1 << endl;
				//vailidator();
				vector<int>nn;
				for (int k = 0;k < nurse_space[skl].size();k++)
				{
					nn.push_back(nurse_space[skl][k]);

				}


				for (int l = 0;l < nn.size();l++)
				{
					int nur = nn[l];

					int n_s = solution[nur][d][s];
					if (n_s > 0)
						continue;
					solution[nur][d][s] = skl;

					//out << 2 << endl;
					//vailidator();

					ck = better_vailidator();
					if (ck > -1)
					{
						change.push_back(make_pair(ck, nur));

					}
					solution[nur][d][s] = 0;
					//	out << 3 << endl;
						//vailidator();

				}
				out << 4 << endl;
				//vailidator();
				if (change.size() > 0)
				{
					bool f = 0;

					sort(change.begin(), change.end());

					if (change[0].second == j)
						f = 1;

					solution[change[0].second][d][s] = skl;
					//vailidator();
					if (f == 0)
					{
						solution[j][d][s] = skl;

						int ck = better_vailidator();

						if (ck > change[0].first)
						{
							solution[j][d][s] = 0;
						}
					}
					//out << 6 << endl;
					//vailidator();






				}





			}
		}




		out << i << "----------------------------------------------------->" << endl;
		//show_solution();
		vailidator();





	}





}

void repair10()
{

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			memset(requirements_fulfil, 0, sizeof requirements_fulfil);
			//memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
		}
	}

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];
				//requirements_optimal_fulfil[i][j][k] = requirements_optimal[i][j][k];

			}
		}
	}



	for (int nur = 0;nur < no_nurses;nur++)
	{
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{

				if (solution[nur][i][j] > 0)
				{
					int sk = solution[nur][i][j];
					requirements_fulfil[i][j][sk - 1]--;
					//requirements_optimal_fulfil[i][j][sk - 1]--;
				}
			}
		}
	}






	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				if (requirements_fulfil[i][j][k] > 0)
				{


					for (int l = 0; l < no_nurses;l++)
					{
						if (solution[l][i][j] > 0 && requirements_fulfil[i][j][solution[l][i][j] - 1] < 0 && nurse_have_skill(l, k))
						{
							requirements_fulfil[i][j][solution[l][i][j] - 1]++;
							requirements_fulfil[i][j][k]--;
							solution[l][i][j] = k + 1;
						}
					}




				}

			}
		}
	}




}

void optimalition_ses()
{


	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			memset(requirements_fulfil, 0, sizeof requirements_fulfil);
			memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
		}
	}

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];
				requirements_optimal_fulfil[i][j][k] = requirements_optimal[i][j][k];

			}
		}
	}



	for (int nur = 0;nur < no_nurses;nur++)
	{
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{

				if (solution[nur][i][j] > 0)
				{
					int sk = solution[nur][i][j];
					requirements_fulfil[i][j][sk - 1]--;
					requirements_optimal_fulfil[i][j][sk - 1]--;
				}
			}
		}
	}





	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				if (requirements_optimal_fulfil[i][j][k] > 0)
				{
					for (int l = 0; l < no_nurses;l++)
					{
						if (solution[l][i][j] > 0 && requirements_fulfil[i][j][solution[l][i][j] - 1] < 0 && nurse_have_skill(l, k) && requirements_optimal_fulfil[i][j][solution[l][i][j] - 1] < 0)
						{
							requirements_fulfil[i][j][solution[l][i][j] - 1]++;
							requirements_optimal_fulfil[i][j][k]--;
							solution[l][i][j] = k + 1;
						}
					}


				}


			}

		}

	}




}



void total_weekend_optimal()
{
	int trp = 0, ft = 0;
	for (int nur = 0;nur < no_nurses;nur++)
	{
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				/*if (solution[nur][i][j] > 0 )
				{
					if ((i % 7) == 5)
					{
						if (solution[nur][i + 1][j] == 0)
						{
							ft = 1;
						}
					}

					trp++;
				}
				if ((i % 7) == 5 && ft==1)
				{
					int jj = 5 - trp + 1;
					if (solution[nur][jj][j] == 0)
					{
						solution[nur][jj][j] = solution[nur][i][j];
						solution[nur][i][j] = 0;
					}
				}
				if ((i-trp)==6)
				{
					//int jj = 5 - trp + 1;
					if (solution[nur][i-trp-1][j] == 0)
					{
						solution[nur][i + 1][j] = solution[nur][i - trp][j];

						solution[nur][i - trp][j] = 0;

						//solution[nur][i][j] = 0;
					}
				}
				*/

				if (solution[nur][i][j] > 0 && solution[nur][i + 1][j] == 0 && (i % 7) == 5)
				{
					solution[nur][i][j] = 0;


				}
				else if (solution[nur][i][j] > 0 && solution[nur][i - 1][j] == 0 && (i % 7) == 6)
				{
					solution[nur][i][j] = 0;

				}

			}

		}



	}

}
void total_assignment()
{


	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{
		int total_assignm = 0, maxm_assign = 0;
		int cnt_type = contracts_point.find(nurses[nur1].contract)->second;
		//out << "cnt_typw " << cnt_type << endl;
		int mx = contracts[cnt_type].maximumNumberOfAssignments;
		int mn = contracts[cnt_type].minimumNumberOfAssignments;
		//int max_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfAssignments;
		//int min_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfAssignments;
		int max_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfConsecutiveWorkingDays;
		int min_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfConsecutiveWorkingDays;
		int max_con_off = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfConsecutiveDaysOff;
		int min_con_off = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfConsecutiveDaysOff;
		/*bool com_weekend = contracts[contracts_point.find(nurses[ii].contract)->second].completeWeekends;

		int last_assign_sft = shift_type_point[nurses[ii].history.lastAssignedShiftType];
		int last_assign_cons_sft = nurses[ii].history.numberOfConsecutiveAssignments;
		int last_cons = nurses[ii].history.numberOfConsecutiveWorkingDays;
		int last_con_off = nurses[ii].history.numberOfConsecutiveDaysOff;


		*/
		int eve = better_vailidator();

		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] > 0)
				{
					total_assignm++;
				}
				else
				{
					//out << "total_assignm   " << endl;
					if (total_assignm > max_con_assignment)
					{
						solution[nur1][i][j] = 0;



					}
					else if (total_assignm < min_con_assignment)
					{

					}
					//total_assignm = 0;
				}

			}

		}



		if (maxm_assign < mn)
		{
			int rend = rand() % (mx - maxm_assign);

			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					if (solution[nur1][i][j] == 0)
					{
						total_assignm++;
					}
					else
					{
						//out<<"
						int y = i;
						//	out << "total_assignm   lllllll" << endl;
						if (total_assignm > max_con_off)
						{
							out << "total_assignm   jjjjlllllll" << endl;
							int y = i;

							for (int off = 0;off < rend;off++)
							{
								int kkk = rand() % nurses[nur1].skills.size();
								solution[nur1][y][j] = skills_point[nurses[nur1].skills[kkk]];
								y--;
							}
							vailidator;



						}
						total_assignm = 0;
					}

				}
				rend--;
			}




		}








		/*if (total_assignm > max_assignment)
		{
			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					memset(requirements_fulfil, 0, sizeof requirements_fulfil);
					memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
				}
			}

			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					for (int k = 0;k < no_skills;k++)
					{
						requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];
						requirements_optimal_fulfil[i][j][k] = requirements_optimal[i][j][k];

					}
				}
			}



			for (int nur = 0;nur < no_nurses;nur++)
			{
				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{

						if (solution[nur][i][j] > 0)
						{
							int sk = solution[nur][i][j];
							requirements_fulfil[i][j][sk - 1]--;
							requirements_optimal_fulfil[i][j][sk - 1]--;
						}
					}
				}
			}





			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					for (int k = 0;k < no_skills;k++)
					{
						if (requirements_fulfil[i][j][k] > 0)
						{
							for (int l = 0; l < no_nurses;l++)
							{
								if (solution[l][i][j] > 0 && solution[l][i - 1][j] == 0)
								{
									solution[l][i][j] = 0;
								}
								else if (solution[l][i][j] > 0 && solution[l][i + 1][j] == 0)
								{
									solution[l][i][j] = 0;
								}

							}


						}


					}

				}

			}

		}
		else if (total_assignm < min_assignment)
		{
			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					memset(requirements_fulfil, 0, sizeof requirements_fulfil);
					memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
				}
			}

			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					for (int k = 0;k < no_skills;k++)
					{
						requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];
						requirements_optimal_fulfil[i][j][k] = requirements_optimal[i][j][k];

					}
				}
			}



			for (int nur = 0;nur < no_nurses;nur++)
			{
				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{

						if (solution[nur][i][j] > 0)
						{
							int sk = solution[nur][i][j];
							requirements_fulfil[i][j][sk - 1]--;
							requirements_optimal_fulfil[i][j][sk - 1]--;
						}
					}
				}
			}





			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					for (int k = 0;k < no_skills;k++)
					{
						if (requirements_fulfil[i][j][k] > 0)
						{
							for (int l = 0; l < no_nurses;l++)
							{
								if (solution[l][i][j] > 0 && solution[l][i - 1][j] == 0)
								{
									solution[l][i - 1][j] = 1;
								}
								else if (solution[l][i][j] > 0 && solution[l][i + 1][j] == 0)
								{
									solution[l][i + 1][j] = 1;
								}

							}


						}


					}

				}

			}
		}*/
		//total_assignm = 0;
	}



}

void preference()
{



	for (int i = 0;i < no_nurses;i++)
	{
		shift_off_req[i].size();
		for (int j = 0;j < shift_off_req[i].size();j++)
		{
			int sft = shift_type_point[shift_off_req[i][j].first];
			int d_n = shift_off_req[i][j].second;

			if (solution[i][d_n][sft] > 0)
			{
				int skl = solution[i][d_n][sft];
				int chk = better_vailidator();
				if (chk != -1)
				{
					solution[i][d_n][sft] = 0;
					int chk1 = better_vailidator();
					if (chk1 > chk || chk1 == -1)
					{
						solution[i][d_n][sft] = skl;
					}

				}



			}

		}
	}


}

void total_assign()
{

	vector<int>ds;

	for (int i = 0;i < no_nurses;i++)
	{
		ds.push_back(i);
	}


	while (ds.size() != 0)
	{
		int rnd = rand() % ds.size();

		//out << ds[rnd]<<" "<<ds.size()<<endl;


		int nur = ds[rnd];


		std::srand(unsigned(std::time(0)));




		vector<int>serial;

		for (int i = 0; i < 7 * no_weeks; ++i) serial.push_back(i);
		random_shuffle(serial.begin(), serial.end());
		random_shuffle(serial.begin(), serial.end(), myrandom);


		int eve = better_vailidator();

		for (int jj = 0;jj < 7 * no_weeks;jj++)
		{
			int j = serial[jj];
			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[nur][j][k] > 0)
				{
					int sk = solution[nur][j][k];
					solution[nur][j][k] = 0;
					int chk = better_vailidator();
					if (chk == -1 || chk > eve)
					{
						solution[nur][j][k] = sk;
					}
					else
						eve = chk;


				}

			}
		}
		ds.erase(ds.begin() + rnd);



	}
}



void optimum_add()
{

	vector<int>ds;

	for (int i = 0;i < no_nurses;i++)
	{
		ds.push_back(i);
	}


	while (ds.size() != 0)
	{
		int rnd = rand() % ds.size();

		//out << ds[rnd]<<" "<<ds.size()<<endl;


		int nur = ds[rnd];


		//int t = contracts[contracts_point[nurses[nur].contract]].maximumNumberOfAssignments;


		for (int j = 0;j < 7 * no_weeks;j++)
		{
			int flg = 0;
			for (int k = 0;k < no_shift_types;k++)
			{
				if (solution[nur][j][k] != 0)
				{
					flg = 1;
					break;
				}
			}

			if (flg == 0)
			{
				int eve = better_vailidator();

				for (int k = 0;k < no_shift_types;k++)
				{
					for (int l = 0;l < nurses[nur].skills.size();l++)
					{
						int skl = skills_point[nurses[nur].skills[l]];
						solution[nur][j][k] = skl + 1;

						int chk = better_vailidator();

						if (chk == -1 || chk > eve)
							solution[nur][j][k] = 0;
						else
							eve = chk;

					}
				}
			}


		}
		ds.erase(ds.begin() + rnd);



	}
}


void total_assignment_optimal()
{
	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{
		int total_assignm = 0, maxm_assign = 0;
		int cnt_type = contracts_point.find(nurses[nur1].contract)->second;
		//out << "cnt_typw " << cnt_type << endl;
		int mx = contracts[cnt_type].maximumNumberOfAssignments;
		int mn = contracts[cnt_type].minimumNumberOfAssignments;
		//int max_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfAssignments;
		//int min_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfAssignments;
		int max_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfConsecutiveWorkingDays;
		int min_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfConsecutiveWorkingDays;
		int max_con_off = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfConsecutiveDaysOff;
		int min_con_off = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfConsecutiveDaysOff;
		/*bool com_weekend = contracts[contracts_point.find(nurses[ii].contract)->second].completeWeekends;

		int last_assign_sft = shift_type_point[nurses[ii].history.lastAssignedShiftType];
		int last_assign_cons_sft = nurses[ii].history.numberOfConsecutiveAssignments;
		int last_cons = nurses[ii].history.numberOfConsecutiveWorkingDays;
		int last_con_off = nurses[ii].history.numberOfConsecutiveDaysOff;


		*/
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] > 0)
				{
					maxm_assign++;
				}
			}
		}
		int evu = better_vailidator();
		//out << maxm_assign << " " << mx << " " << mn << endl << endl << endl;
		if (maxm_assign > mx)
		{
			for (int i = 0;i < 7 * no_weeks;i++)
			{
				for (int j = 0;j < no_shift_types;j++)
				{
					if (solution[nur1][i][j] > 0)
					{
						total_assignm++;
					}
					else
					{
						//out << "total_assignm   " << endl;
						if (total_assignm > max_con_assignment)
						{
							int tmp1 = 0, tmp2 = 0, tmp4 = 0;
							tmp1 = solution[nur1][i - total_assignm][j];
							tmp4 = solution[nur1][i - total_assignm + 1][j];
							solution[nur1][i - total_assignm][j] = 0;
							solution[nur1][i - total_assignm + 1][j] = 0;
							int evu1 = better_vailidator();
							solution[nur1][i - total_assignm][j] = tmp1;
							solution[nur1][i - total_assignm + 1][j] = tmp4;

							tmp2 = solution[nur1][i - 1][j];
							solution[nur1][i - 1][j] = 0;
							int evu2 = better_vailidator();
							solution[nur1][i - 1][j] = tmp2;

							tmp1 = solution[nur1][i - total_assignm][j];
							solution[nur1][i - total_assignm][j] = 0;
							tmp2 = solution[nur1][i - 1][j];
							solution[nur1][i - 1][j] = 0;
							int evu3 = better_vailidator();
							solution[nur1][i - total_assignm][j] = tmp1;
							solution[nur1][i - 1][j] = tmp2;
							//solution[nur1][i][j] = 0;




							if (evu1 < evu2 && evu1 < evu3 &&  evu1 < evu)
							{
								solution[nur1][i - total_assignm][j] = 0;
								solution[nur1][i - total_assignm + 1][j] = 0;

							}

							else if (evu2 < evu3 && evu2 < evu1 && evu2 < evu)
							{
								solution[nur1][i - 1][j] = 0;
							}

							else if (evu3 < evu2 && evu3 < evu1 && evu3 < evu)
							{
								solution[nur1][i - total_assignm][j] = 0;
								solution[nur1][i - 1][j] = 0;

							}



						}
						total_assignm = 0;
					}

				}

			}

		}

		/*	if (maxm_assign < mn)
			{
				int rend = rand() % (mx - maxm_assign);

				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						if (solution[nur1][i][j] == 0)
						{
							total_assignm++;
						}
						else
						{
							//out<<"
							int y = i;
							//	out << "total_assignm   lllllll" << endl;
							if (total_assignm > max_con_off)
							{
								out << "total_assignm   jjjjlllllll" << endl;
								int y = i;

								for (int off = 0;off < rend;off++)
								{
									int kkk = rand() % nurses[nur1].skills.size();
									solution[nur1][y][j] = skills_point[nurses[nur1].skills[kkk]];
									y--;
								}
								vailidator;



							}
							total_assignm = 0;
						}

					}
					rend--;
				}




			}








			/*if (total_assignm > max_assignment)
			{
				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						memset(requirements_fulfil, 0, sizeof requirements_fulfil);
						memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
					}
				}

				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						for (int k = 0;k < no_skills;k++)
						{
							requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];
							requirements_optimal_fulfil[i][j][k] = requirements_optimal[i][j][k];

						}
					}
				}



				for (int nur = 0;nur < no_nurses;nur++)
				{
					for (int i = 0;i < 7 * no_weeks;i++)
					{
						for (int j = 0;j < no_shift_types;j++)
						{

							if (solution[nur][i][j] > 0)
							{
								int sk = solution[nur][i][j];
								requirements_fulfil[i][j][sk - 1]--;
								requirements_optimal_fulfil[i][j][sk - 1]--;
							}
						}
					}
				}





				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						for (int k = 0;k < no_skills;k++)
						{
							if (requirements_fulfil[i][j][k] > 0)
							{
								for (int l = 0; l < no_nurses;l++)
								{
									if (solution[l][i][j] > 0 && solution[l][i - 1][j] == 0)
									{
										solution[l][i][j] = 0;
									}
									else if (solution[l][i][j] > 0 && solution[l][i + 1][j] == 0)
									{
										solution[l][i][j] = 0;
									}

								}


							}


						}

					}

				}

			}
			else if (total_assignm < min_assignment)
			{
				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						memset(requirements_fulfil, 0, sizeof requirements_fulfil);
						memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
					}
				}

				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						for (int k = 0;k < no_skills;k++)
						{
							requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];
							requirements_optimal_fulfil[i][j][k] = requirements_optimal[i][j][k];

						}
					}
				}



				for (int nur = 0;nur < no_nurses;nur++)
				{
					for (int i = 0;i < 7 * no_weeks;i++)
					{
						for (int j = 0;j < no_shift_types;j++)
						{

							if (solution[nur][i][j] > 0)
							{
								int sk = solution[nur][i][j];
								requirements_fulfil[i][j][sk - 1]--;
								requirements_optimal_fulfil[i][j][sk - 1]--;
							}
						}
					}
				}





				for (int i = 0;i < 7 * no_weeks;i++)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						for (int k = 0;k < no_skills;k++)
						{
							if (requirements_fulfil[i][j][k] > 0)
							{
								for (int l = 0; l < no_nurses;l++)
								{
									if (solution[l][i][j] > 0 && solution[l][i - 1][j] == 0)
									{
										solution[l][i - 1][j] = 1;
									}
									else if (solution[l][i][j] > 0 && solution[l][i + 1][j] == 0)
									{
										solution[l][i + 1][j] = 1;
									}

								}


							}


						}

					}

				}
			}*/
			//total_assignm = 0;
	}

}

void total_working_weekend()
{
	int trp = 0, ft = 0, break1 = 0;
	//bool com_weekend = contracts[contracts_point.find(nurses[ii].contract)->second].completeWeekends;
	for (int nur = 0;nur < no_nurses;nur++)
	{
		int max_total_weekend = contracts[contracts_point.find(nurses[nur].contract)->second].completeWeekends;
		//int min_assignment = contracts[contracts_point.find(nurses[nur].contract)->second];
		int week_wk = 0;



		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if ((i % 7) == 5)
				{
					if (solution[nur][i][j] > 0 && solution[nur][i + 1][j] > 0)
					{
						week_wk++;
					}
					else if (solution[nur][i][j] > 0)
					{
						week_wk++;
					}
					else if (solution[nur][i + 1][j] > 0)
					{
						week_wk++;
					}
				}


			}

		}

		if (week_wk > max_total_weekend)
		{
			for (int i = 0;i < 7 * no_weeks;i++)
			{
				if (break1 == 1)
				{
					break1 = 1;
					break;
				}
				for (int j = 0;j < no_shift_types;j++)
				{
					if ((i % 7) == 5)
					{
						if (week_wk == max_total_weekend)
						{
							break1 = 1;
							break;
						}
						if (solution[nur][i][j] > 0 && solution[nur][i + 1][j] > 0)
						{
							if ((solution[nur][i + 2][j] > 0 && solution[nur][i + 2][j] > 0) && (solution[nur][i - 1][j] == 0 && solution[nur][i - 2][j] == 0))
							{
								solution[nur][i][j] = 0;
								solution[nur][i + 1][j] = 0;
								week_wk--;


							}
							else if ((solution[nur][i + 2][j] == 0 && solution[nur][i + 2][j] == 0) && (solution[nur][i - 1][j] >= 0 && solution[nur][i - 2][j] >= 0))
							{
								solution[nur][i][j] = 0;
								solution[nur][i + 1][j] = 0;
								week_wk--;


							}


						}

						else if (solution[nur][i][j] > 0 && solution[nur][i + 1][j] == 0)
						{
							int eve = 0, chk = 0, temp, flag = 0; //= better_vailidator();
							temp = solution[nur][i][j];
							solution[nur][i][j] = 0;
							eve = better_vailidator();
							solution[nur][i][j] = temp;

							for (int l = 0;l < nurses[nur].skills.size();l++)
							{
								int skl = skills_point[nurses[nur].skills[l]];
								solution[nur][i + 1][j] = skl + 1;

								chk = better_vailidator();
								if (chk < eve)
								{
									eve = chk;
									flag = 1;
								}

							}
							if (flag == 0)
							{

								solution[nur][i][j] = 0;
								week_wk--;

							}
							if (flag == 1)
							{
								week_wk--;
							}


						}
						else if (solution[nur][i + 1][j] > 0 && solution[nur][i][j] == 0)
						{
							int eve = 0, chk = 0, temp, flag = 0; //= better_vailidator();
							temp = solution[nur][i + 1][j];
							solution[nur][i + 1][j] = 0;
							eve = better_vailidator();
							solution[nur][i + 1][j] = temp;

							for (int l = 0;l < nurses[nur].skills.size();l++)
							{
								int skl = skills_point[nurses[nur].skills[l]];
								solution[nur][i][j] = skl + 1;

								chk = better_vailidator();
								if (chk < eve)
								{
									eve = chk;
									flag = 1;
								}

							}
							if (flag == 0)
							{

								solution[nur][i + 1][j] = 0;
								week_wk--;

							}
							if (flag == 1)
							{
								week_wk--;
							}
						}
					}


				}

			}

		}



	}

}

void optimum1()
{


	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
			//memset(requirements_optimal_fulfil, 0, sizeof requirements_optimal_fulfil);
		}
	}

	for (int i = 0;i < 7 * no_weeks;i++)
	{
		for (int j = 0;j < no_shift_types;j++)
		{
			for (int k = 0;k < no_skills;k++)
			{
				//requirements_fulfil[i][j][k] = requirements_minimum[i][j][k];
				requirements_optimal_fulfil[i][j][k] = requirements_optimal[i][j][k];

			}
		}
	}



	for (int nur = 0;nur < no_nurses;nur++)
	{
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{

				if (solution[nur][i][j] > 0)
				{
					int sk = solution[nur][i][j];
					//requirements_fulfil[i][j][sk - 1]--;
					requirements_optimal_fulfil[i][j][sk - 1]--;
				}
			}
		}
	}




	int tmpo = no_nurses;
	int evu = better_vailidator();

	for (int i = 0;i < 7 * no_weeks;i++)
	{

		for (int j = 0;j < no_shift_types;j++)
		{

			for (int k = 0;k < no_skills;k++)
			{


				if (requirements_optimal_fulfil[i][j][k] > 0)
				{



					for (int l = 0; l < no_nurses;l++)
					{
						/*if (tmpo <= 0)
						{
							break;
						}*/
						if (solution[l][i][j] > 0 && requirements_optimal_fulfil[i][j][solution[l][i][j] - 1] < 0 && nurse_have_skill(l, k))
						{

							requirements_optimal_fulfil[i][j][solution[l][i][j] - 1]++;
							requirements_optimal_fulfil[i][j][k]--;
							solution[l][i][j] = k + 1;
							int evu1 = better_vailidator();
							if (evu1 > evu)
							{
								requirements_optimal_fulfil[i][j][solution[l][i][j] - 1]--;
								requirements_optimal_fulfil[i][j][k]++;
								solution[l][i][j] = 0;
								tmpo + 1;
							}


						}
					}





				}



			}
		}
	}





}


void total_consecutive_optimal()
{
	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{
		int total_assignm = 0, maxm_assign = 0;
		int cnt_type = contracts_point.find(nurses[nur1].contract)->second;
		//out << "cnt_typw " << cnt_type << endl;
		int mx = contracts[cnt_type].maximumNumberOfAssignments;
		int mn = contracts[cnt_type].minimumNumberOfAssignments;
		//int max_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfAssignments;
		//int min_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfAssignments;
		int max_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfConsecutiveWorkingDays;
		int min_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfConsecutiveWorkingDays;
		int max_con_off = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfConsecutiveDaysOff;
		int min_con_off = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfConsecutiveDaysOff;
		/*bool com_weekend = contracts[contracts_point.find(nurses[ii].contract)->second].completeWeekends;

		int last_assign_sft = shift_type_point[nurses[ii].history.lastAssignedShiftType];
		int last_assign_cons_sft = nurses[ii].history.numberOfConsecutiveAssignments;
		int last_cons = nurses[ii].history.numberOfConsecutiveWorkingDays;
		int last_con_off = nurses[ii].history.numberOfConsecutiveDaysOff;


		*/
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] > 0)
				{
					maxm_assign++;
				}
			}
		}
		int evu = better_vailidator();
		out << maxm_assign << " " << mx << " " << mn << endl << endl << endl;

		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] > 0)
				{
					total_assignm++;
				}
				else
				{
					//out << "total_assignm   " << endl;
					if (total_assignm > max_con_assignment)
					{
						solution[nur1][i][j] = 0;




					}

					else if (total_assignm < min_con_assignment)
					{
						for (int l = 0;l < nurses[nur1].skills.size();l++)
						{
							int skl = skills_point[nurses[nur1].skills[l]];
							solution[nur1][i][j] = skl + 1;


						}
					}
					total_assignm = 0;
				}

			}

		}



	}
}




void total_check_assignment()
{

	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{
		//int last_cons = nurses[nur1].history.numberOfConsecutiveWorkingDays;
		//int last_con_off = nurses[nur1].history.numberOfConsecutiveDaysOff;
		int max_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfAssignments;
		int min_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfAssignments;
		//	int max_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].maximumNumberOfConsecutiveWorkingDays;
			//int min_con_assignment = contracts[contracts_point.find(nurses[nur1].contract)->second].minimumNumberOfConsecutiveWorkingDays;
			//int max_con_off = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfConsecutiveDaysOff;
			//int min_con_off = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfConsecutiveDaysOff;
			//int last_assign_sft = shift_type_point[nurses[ii].history.lastAssignedShiftType];
			//int last_assign_cons_sft = nurses[ii].history.numberOfConsecutiveAssignments;
			//int key1 = contracts_point.find(nurses[ii].contract)->second;
			//	int max_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].maximumNumberOfAssignments;
				//int min_assignment = contracts[contracts_point.find(nurses[ii].contract)->second].minimumNumberOfAssignments;
			//bool com_weekend = contracts[contracts_point.find(nurses[ii].contract)->second].completeWeekends;
		string nurse_type = nurses[nur1].contract;
		int amax = 0;
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] > 0)
				{
					amax++;
					//maxm_assign++;
				}
			}
		}
		out << "nurse_type " << nurse_type << "max_assignment " << max_assignment << "min_assignment " << min_assignment << endl;
		out << "Total assignment " << amax << endl;





	}

}



void total_optimal_consecutive_assignment()
{
	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{

		int amax = 0, brk = 0;
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			brk = 0;
			for (int j = 0;j < no_shift_types;j++)
			{
				if (brk == no_shift_types)
				{
					for (int j = 0;j < no_shift_types;j++)
					{
						if (solution[nur1][i - 1][j] > 0)
						{
							int pev = solution[nur1][i - 1][j];
							int chk = better_vailidator();
							solution[nur1][i - 1][j] = 0;
							int evu = better_vailidator();
							int h1 = hard_validator1();
							int h2 = hard_validator2();
							int h3 = hard_validator3();
							int h4 = hard_validator4();
							if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu < chk && evu != 1)
							{
								solution[nur1][i - 1][j] = 0;

							}
							else
							{
								solution[nur1][i - 1][j] = pev;
							}

						}
					}



					continue;
				}
				if (solution[nur1][i][j] > 0)
				{
					brk = 0;

					amax++;

					int pev = solution[nur1][i][j];
					int chk = better_vailidator();
					solution[nur1][i][j] = 0;
					int evu = better_vailidator();
					int h1 = hard_validator1();
					int h2 = hard_validator2();
					int h3 = hard_validator3();
					int h4 = hard_validator4();
					if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu < chk && evu != 1)
					{
						solution[nur1][i][j] = 0;

					}
					else
					{
						solution[nur1][i][j] = pev;
					}

					//maxm_assign++;
				}
				else
				{
					brk++;
					/*amax = 0;
					int pev = solution[nur1][i-1][j];
					int chk = better_vailidator();
					solution[nur1][i-1][j] = 0;
					int evu = better_vailidator();
					int h1 = hard_validator1();
					int h2 = hard_validator2();
					int h3 = hard_validator3();
					int h4 = hard_validator4();
					if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu < chk && evu != 1)
					{
						solution[nur1][i-1][j] = 0;

					}
					else
					{
						solution[nur1][i-1][j] = pev;
					}*/
				}
			}
		}
		//out << "nurse_type " << nurse_type << "max_assignment " << max_assignment << "min_assignment " << min_assignment << endl;
		//out << "Total assignment " << amax << endl;





	}
}
void total_optimal_coverage_assignment()
{
	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{

		int amax = 0, brk = 0;
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] == 0)
				{
					for (int k = 0;k < nurses[nur1].skills.size();k++)
					{

						int chk = better_vailidator();
						int sk = skills_point[nurses[nur1].skills[k]];
						solution[nur1][i][j] = sk;
						//solution[nur1][i][j - 1] = 0;
						int evu = better_vailidator();
						int h1 = hard_validator1();
						int h2 = hard_validator2();
						int h3 = hard_validator3();
						int h4 = hard_validator4();
						if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu < chk && evu != 1)
						{
							solution[nur1][i][j] = sk;

						}
						else
						{
							solution[nur1][i][j] = 0;
						}

					}
				}



			}
		}
		//out << "nurse_type " << nurse_type << "max_assignment " << max_assignment << "min_assignment " << min_assignment << endl;
		//out << "Total assignment " << amax << endl;





	}
}
void total_consecutive_assignment()
{
	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{

		int amax = 0, brk = 0;
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] > 0)
				{

					for (int kj = 0;kj < no_shift_types;kj++)
					{
						if (solution[nur1][i - 1][kj] > 0)
						{
							if (j != kj)
							{
								int pv = solution[nur1][i - 1][kj];
								int pv1 = solution[nur1][i][j];
								int chk = better_vailidator();
								solution[nur1][i - 1][j] = solution[nur1][i - 1][kj];
								solution[nur1][i - 1][kj] = 0;

								int evu = better_vailidator();
								solution[nur1][i - 1][kj] = pv;
								solution[nur1][i - 1][j] = 0;

								solution[nur1][i][kj] = solution[nur1][i][j];
								solution[nur1][i][j] = 0;
								int evu1 = better_vailidator();
								solution[nur1][i][j] = pv1;
								solution[nur1][i][kj] = 0;

								if (evu < chk && evu < evu1 && evu != 1)
								{
									solution[nur1][i - 1][j] = solution[nur1][i - 1][kj];
									solution[nur1][i - 1][kj] = 0;

									int h1 = hard_validator1();
									int h2 = hard_validator2();
									int h3 = hard_validator3();
									int h4 = hard_validator4();
									if (h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0)
									{
										solution[nur1][i][j] = pv1;
										solution[nur1][i - 1][kj] = pv;
									}



								}
								else if (evu1 < chk && evu1 < evu && evu1 != 1)
								{
									solution[nur1][i][kj] = solution[nur1][i][j];
									solution[nur1][i][j] = 0;

									int h1 = hard_validator1();
									int h2 = hard_validator2();
									int h3 = hard_validator3();
									int h4 = hard_validator4();
									if (h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0)
									{
										solution[nur1][i][j] = pv1;
										solution[nur1][i - 1][kj] = pv;
									}
								}


							}
						}
						else if (solution[nur1][i + 1][kj] > 0)
						{
							if (j != kj)
							{
								int pv = solution[nur1][i + 1][kj];
								int pv1 = solution[nur1][i][j];
								int chk = better_vailidator();
								solution[nur1][i + 1][j] = solution[nur1][i + 1][kj];
								solution[nur1][i + 1][kj] = 0;
								int evu = better_vailidator();
								solution[nur1][i + 1][kj] = pv;
								solution[nur1][i + 1][j] = 0;

								solution[nur1][i][kj] = solution[nur1][i][j];
								solution[nur1][i][j] = 0;
								int evu1 = better_vailidator();
								solution[nur1][i][j] = pv1;
								solution[nur1][i][kj] = 0;


								if (evu < chk && evu < evu1 && evu != 1)
								{
									solution[nur1][i + 1][j] = solution[nur1][i + 1][kj];
									solution[nur1][i + 1][kj] = 0;
									int h1 = hard_validator1();
									int h2 = hard_validator2();
									int h3 = hard_validator3();
									int h4 = hard_validator4();
									if (h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0)
									{
										solution[nur1][i][j] = pv1;
										solution[nur1][i + 1][kj] = pv;
									}

								}
								else if (evu1 < chk && evu1 < evu && evu1 != 1)
								{
									solution[nur1][i][kj] = solution[nur1][i][j];
									solution[nur1][i][j] = 0;
									int h1 = hard_validator1();
									int h2 = hard_validator2();
									int h3 = hard_validator3();
									int h4 = hard_validator4();
									if (h1 != 0 || h2 != 0 || h3 != 0 || h4 != 0)
									{
										solution[nur1][i][j] = pv1;
										solution[nur1][i + 1][kj] = pv;
									}
								}


							}

						}

					}




				}



			}
		}
		//out << "nurse_type " << nurse_type << "max_assignment " << max_assignment << "min_assignment " << min_assignment << endl;
		//out << "Total assignment " << amax << endl;





	}

}

void total_complete_weekend()
{
	for (int nur1 = 0;nur1 < no_nurses;nur1++)
	{

		int amax = 0, brk = 0;
		for (int i = 0;i < 7 * no_weeks;i++)
		{
			brk = 0;
			for (int j = 0;j < no_shift_types;j++)
			{
				if (solution[nur1][i][j] > 0 && (i % 5) == 0)
				{
					for (int kj = 0;kj < no_shift_types;kj++)
					{
						if (solution[nur1][i + 1][kj] == 0)
						{
							brk++;
						}

					}
					if (brk == no_shift_types)
					{
						for (int k1 = 0;k1 < nurses[nur1].skills.size();k1++)
						{

							int chk = better_vailidator();
							int sk = skills_point[nurses[nur1].skills[k1]];
							solution[nur1][i + 1][j] = sk;
							//solution[nur1][i][j - 1] = 0;
							int evu = better_vailidator();
							int h1 = hard_validator1();
							int h2 = hard_validator2();
							int h3 = hard_validator3();
							int h4 = hard_validator4();
							if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu < chk && evu != 1)
							{
								solution[nur1][i + 1][j] = sk;

							}
							else
							{
								solution[nur1][i + 1][j] = 0;
								int pv = solution[nur1][i][j];
								solution[nur1][i][j] = 0;
								//solution[nur1][i][j - 1] = 0;
								int evu1 = better_vailidator();
								int h1 = hard_validator1();
								int h2 = hard_validator2();
								int h3 = hard_validator3();
								int h4 = hard_validator4();
								if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu1 < chk && evu1 != 1)
								{
									solution[nur1][i][j] = 0;

								}
								else
								{
									solution[nur1][i][j] = pv;
								}
							}

						}

					}





				}
				else if (solution[nur1][i][j] > 0 && (i % 6) == 0)
				{
					for (int kj = 0;kj < no_shift_types;kj++)
					{
						if (solution[nur1][i - 1][kj] == 0)
						{
							brk++;
						}

					}
					if (brk == no_shift_types)
					{
						for (int k1 = 0;k1 < nurses[nur1].skills.size();k1++)
						{

							int chk = better_vailidator();
							int sk = skills_point[nurses[nur1].skills[k1]];
							solution[nur1][i - 1][j] = sk;
							//solution[nur1][i][j - 1] = 0;
							int evu = better_vailidator();
							int h1 = hard_validator1();
							int h2 = hard_validator2();
							int h3 = hard_validator3();
							int h4 = hard_validator4();
							if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu < chk && evu != 1)
							{
								solution[nur1][i - 1][j] = sk;

							}
							else
							{
								solution[nur1][i - 1][j] = 0;
								int pv = solution[nur1][i][j];
								solution[nur1][i][j] = 0;
								//solution[nur1][i][j - 1] = 0;
								int evu1 = better_vailidator();
								int h1 = hard_validator1();
								int h2 = hard_validator2();
								int h3 = hard_validator3();
								int h4 = hard_validator4();
								if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && evu1 < chk && evu1 != 1)
								{
									solution[nur1][i][j] = 0;

								}
								else
								{
									solution[nur1][i][j] = pv;
								}
							}

						}

					}





				}



			}
		}
		//out << "nurse_type " << nurse_type << "max_assignment " << max_assignment << "min_assignment " << min_assignment << endl;
		//out << "Total assignment " << amax << endl;





	}
}


void input_from_file()
{

	in.close();
	string file = "./output/random.txt";
	in.open(file);



	for (int j = 0;j < no_nurses + 1;j++)
	{
		for (int k = 0;k < no_weeks * 7 + 1;k++)
		{
			memset(solution[j][k], 0, sizeof solution[j][k]);
			memset(sol[j][k], 0, sizeof sol[j][k]);
		}
	}



	for (int i = 0;i < no_nurses;i++)
	{
		string s;
		in >> s;




	}









}















int main()
{

	srand(time(NULL));





	string file = "./input/input.txt";
	in.open(file);
	if (!in)
	{
		out << "File not found" << endl;
	}

	string null, f_name, h_no, w1, w2, w3, w4;

	in >> null >> null >> null >> null >> null >> null >> null >> null;

	no_particle = -1;

	while (in >> f_name >> h_no >> w1 >> w2 >> w3 >> w4)
	{
		//out << f_name << " " << h_no << " " << w1 << " " << w2 << " " << w3 << " " << w4 << endl;

		//string file = "./input/"+f_name+".txt";
		out.open("./output/" + f_name + h_no + w1 + w2 + w3 + w4 + ".txt");
		in.close();



		// for (int i = 0;i < 100000;i++){

		input(f_name, h_no, w1, w2, w3, w4);


		nurse_space_create();
		int no_of_solution = 0;
		int trial = 2000;
		cout << "no_of_solution :  ";
		while (trial--)
		{
			constraint();
			out << "trial" << trial << endl;
			//print_req();
			//nurse_skill();
			//random_initialization();



			initial_sol();
			
			/*
						//vailidator();

						vailidator();
						out << "optimum+++++++++++++" << endl;
						out << "repair-10" << endl;
						//repair10();
						//vailidator();








						out << endl << endl;
						out << "optimum+++++++++++++MMMMMMMMMmm" << endl;
						total_weekend_optimal();
						//optimal_complete_weekend();
						vailidator();


						out << "optimum+++++++++++++MMMMMMMMMmm" << endl;
						total_working_weekend();
						vailidator();


						out << "1111111optimum" << endl;
						optimum1();
						vailidator();

						out << "repair-10" << endl;
						repair10();
						vailidator();


						out << "total consecutive 1111111optimum" << endl;
						//total_consecutive_optimal();
						///vailidator();


						out << "1111111optimum" << endl;
						optimum1();
						vailidator();



						out << "total consecutive 1111111optimum" << endl;
						//total_consecutive_optimal();
						//vailidator();
						//repair10();
						//vailidator();



						out << endl << endl;




						//out << "trial" << trial << endl;
						//vailidator();
						out << "optimum" << endl;
						optimalition_ses();


						*/

			int iter = 1;
			while (iter < 3)
			{
				
				repair5();

				vailidator();
				//	break;

			//	cout << "repair: " << iter << endl;
				//show_solution();

				iter++;
			}

			/*int t =3;
			while (t--)
			{
				cout << "random" << (5 - t) << endl;
				out << "random" << (5 - t) << endl;
				//random_init();
				vailidator();


			}*/



			int h1 = hard_validator1();
			int h2 = hard_validator2();
			int h4 = hard_validator4();
			int h3 = hard_validator3();




			if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0)
			{
				out << "start checking------------" << endl;
				//total_check_assignment();
				out << "optimum" << endl;
				optimalition_ses();

				vailidator();


				out << "total assign" << endl;
				total_assignment_optimal();
				vailidator();

				//////////////////
				/*out << "1111111optimum" << endl;
				optimum1();
				vailidator();
				out << "optimum+++++++++++++" << endl;
				//optimalition();
				//vailidator();



				vailidator();
				out << "total assign" << endl;
				total_assign();
				vailidator();


				out << "1111111optimum" << endl;
				optimum1();
				vailidator();
				*/
				//////////////////////

				//out << "total consecutive 1111111optimum" << endl;
				//total_consecutive_optimal();
				//vailidator();
				//////////////////////////////////////
				/*out << "optimum" << endl;
				for (int jl = 0;jl < 5;jl++)
				{
					out << "total assign" << endl;
					total_assign();
					vailidator();

					out << "add optimum" << endl;
					optimum_add();
					vailidator();
				}


				out << "optimum" << endl;
				optimalition_ses();

				vailidator();


				out << "total assign" << endl;
				total_assignment_optimal();
				vailidator();

				out << "1111111optimum" << endl;
				optimum1();
				vailidator();

				out << "add optimum" << endl;
				optimum_add();
				vailidator();


				out << "total assign" << endl;
				total_assign();
				vailidator();


				out << "total assign" << endl;
				total_assign();
				vailidator();*/
				//////////////////////
				/*
								out << "optimum+++++++++++++" << endl;
								optimalition();
								vailidator();


										out << "preference" << endl;
										preference();
										vailidator();*/
										//optimalition_ses();
										//vailidator();


				int iter = 1;






				// show_solution();


				 //out << endl;

				 //sol3_2();

				/////////////
				/*vailidator();



				while (iter < 2)
				{
					out << "Better_Repair" << (2 - iter) << endl;
					//better_repair(1000);

					iter++;


				}*/
				////////////////////
				//show_solution();
			//	vailidator();
				//insert_sol_nurse(1);
				//show_solution();
				//ailidator();



				///////////////////
				/*iter = 0;

				while (iter < 1)
				{
					out << "noise" << (2 - iter) << endl;
					add_noise();

					iter++;

				}

				vailidator();
				*/

				/////////////////////


				/*iter = 0;
				while (iter < 1)
				{
					out << "optimum" << iter << endl;
					optimalition();

					iter++;
				}
				/*
				//vailidator();
				nurse_skill();



				show_solution();
				vailidator();




				//show_solution();
				//vailidator();
				//show_solution();
				//vailidator();
				*/

				show_solution();
				no_of_solution++;
				//out <<  no_of_solution <<flush;





				//out << "end checking------------" << endl;
				//total_check_assignment();
				////////////////

				/*iter = 0;
				int eve = better_vailidator();
				if (eve <= 3000)
				{
					while (iter < 2)
					{
						out << "Better_Repair" << (2 - iter) << endl;
						better_repair(2000);

						iter++;


					}
				}
				vailidator();

				show_solution();

				no_of_solution++;
				out << "no_of_solution" << no_of_solution << endl << endl;*/
				/*out << "----------------------------------------------------------" << endl;
				vailidator();

				total_optimal_consecutive_assignment();

				vailidator();

				out << "----------------------------------------------------------" << endl;*/


				/*out << "----------------------------------------------------------" << endl;
				vailidator();

				total_optimal_coverage_assignment();
				//total_consecutive_assignment()

				vailidator();

				out << "----------------------------------------------------------" << endl;


				out << "----------------------------------------------------------" << endl;
				vailidator();

				//total_optimal_coverage_assignment();
				total_consecutive_assignment();
				show_solution();

				vailidator();

				out << "----------------------------------------------------------" << endl;


				/*out << "----------------------------------------------------------" << endl;
				vailidator();

				//total_optimal_coverage_assignment();
			//	total_complete_weekend();
				show_solution();

				vailidator();

				out << "----------------------------------------------------------" << endl;*/


				/*for (int i = 0;i < 20;i++)
				{
					int aaa = repair1();
					if (aaa)
						break;

				}


				vailidator();
				add_noise();



				//out << endl;

				//sol3_2();
				//vailidator();

				cout << "trial" << trial << endl;

				//show_solution();
				*/

				int eve = better_vailidator();
				particle_create(eve);

				if(no_of_solution<=10)
				cout << "\b"<<no_of_solution << flush;

				else
					cout << "\b\b" << no_of_solution << flush;

			}
				//out << endl << "sol count: " << sol_cnt << endl << endl;
				for (int j = 0;j < no_nurses + 1;j++)
				{
					for (int k = 0;k < no_weeks * 7 + 1;k++)
					{
						memset(solution[j][k], 0, sizeof solution[j][k]);
						memset(sol[j][k], 0, sizeof sol[j][k]);
					}
				}
				if (no_of_solution == 50)
					break;

			

		}

		/*for (int iter = 0;iter < 50;iter++)
		{
			cout << iter << " ";
			for (int i = no_nurses - 1;i >= 0;i--)
			{
				nurse_add(i);
			}
			show_solution();
			vailidator();

			//sol_nurse();
		}
		*/
		//insert_sol_nurse(50);

		//out << "ACO Sollllllllllwwwwww:" << endl;
		//ACO();




		/*

		int h1 = hard_validator1();
		int h2 = hard_validator2();
		int h4 = hard_validator4();
		int h3 = hard_validator3();
		out << "best" << evoluation() << " " << hard_validator1() << " " << hard_validator2() << " " << hard_validator3() << " " << hard_validator4() << endl;
		show_solution();


		//divide_sol();









		

		//selection();
		show_solution();
		vailidator();

		cout << "best_result" << best_result << endl;
		//insert_sol_nurse(20);
		selection();
		out << "best_result" << best_result << endl;
		optimalition();
		out << "best_result" << best_result << endl;


		print_particle();


		*/

		out << no_particle << endl;
		print_particle();

		pso1();

		out << "gbest111111111" << gbest_val << endl;
		gbest_to_solution();

		show_solution();

		out << "jjjjjjjjjjjjjjjjjjjjjj " << endl;
		vailidator();





		out << "After PSO total_assign" << endl;
		out << "After PSO total_assign" << endl;
		out << "After PSO total_assign" << endl;



		int h1 = hard_validator1();
		int h2 = hard_validator2();
		int h4 = hard_validator4();
		int h3 = hard_validator3();
		out << "best" << evoluation() << " " << hard_validator1() << " " << hard_validator2() << " " << hard_validator3() << " " << hard_validator4() << endl;
		show_solution();



		if (h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0)
		{

			out << "optimum" << endl;
			optimalition_ses();

			out << "optimum+++++++++++++" << endl;
			optimalition();
			vailidator();



			vailidator();
			out << "total assign" << endl;
			total_assign();
			vailidator();


			out << "add optimum" << endl;
			optimum_add();
			vailidator();
			out << "optimum" << endl;


			out << "total assign" << endl;
			total_assign();
			vailidator();

			out << "add optimum" << endl;
			optimum_add();
			vailidator();

			out << "add optimum" << endl;
			optimum_add();
			vailidator();


			out << "total assign" << endl;
			total_assign();
			vailidator();


			out << "total assign" << endl;
			total_assign();
			vailidator();


			out << "optimum+++++++++++++" << endl;



			/*int iter = 1;

			vailidator();



			while (iter < 2)
			{
				out << "Better_Repair" << (2 - iter) << endl;
				//better_repair(1000);

				iter++;


			}
			//show_solution();
			vailidator();
			//insert_sol_nurse(1);
			//show_solution();
			//ailidator();




			iter = 0;

			while (iter < 1)
			{
				out << "noise" << (2 - iter) << endl;
				add_noise();

				iter++;

			}

			vailidator();





			iter = 0;
			while (iter < 1)
			{
				out << "optimum" << iter << endl;
				optimalition();

				iter++;
			}
			/*
			//vailidator();
			nurse_skill();



			show_solution();
			vailidator();




			//show_solution();
			//vailidator();
			//show_solution();
			//vailidator();
			*/
			out << "----------------------------------------------------------" << endl;
			vailidator();

			total_optimal_coverage_assignment();

			vailidator();

			out << "----------------------------------------------------------" << endl;


			out << "----------------------------------------------------------" << endl;
			//vailidator();

			//total_consecutive_assignment();

			//vailidator();

			out << "----------------------------------------------------------" << endl;



			show_solution();
		//total_check_assignment();
			vailidator();
			int iter = 0;
			int eve = better_vailidator();
			out << eve << endl;
			if (eve <= 3000)
			{
				while (iter < 2)
				{
					out << "Better_Repair" << (2 - iter) << endl;
					better_repair(2000);

					iter++;


				}
			}
			vailidator();

			show_solution();


		}

		out << "After PsO result::::::" << endl;

		h1 = hard_validator1();
		h2 = hard_validator2();
		h4 = hard_validator4();
		h3 = hard_validator3();
		out << "best" << evoluation() << " " << hard_validator1() << " " << hard_validator2() << " " << hard_validator3() << " " << hard_validator4() << endl;
		show_solution();

	}

	//print_sol_nurse();
	//out << "After Selection" << endl;

	//selection();
}