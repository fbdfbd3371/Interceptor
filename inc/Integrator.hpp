#pragma once
#include<vector>
#include<map>
#include<string>
#include<functional>
#include<atmos.hpp>
namespace uIntegr
{
	using namespace std;
	typedef function<double(vector<double>, double)> rightPtDU_t;
	struct inputDescr_t {
		vector<rightPtDU_t> funcs;
		vector<double> init_conds;
		double a;
		double b;
		double step;
		vector<string> prm_names;
		string integr_param_name;
	};

	
	map <string, vector<double>> solve_system(inputDescr_t prm);
}