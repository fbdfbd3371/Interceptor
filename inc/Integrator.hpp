#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <atmos.hpp>
namespace uIntegr
{
	struct inputDescr_t;
	extern inputDescr_t inputDescr;

	using namespace std;
	bool idleStopCriteria(vector<double>, double);

	typedef function<double(vector<double>, double)> rightPtDU_t;
	struct inputDescr_t
	{
		vector<rightPtDU_t> rhss;
		vector<std::tuple<function<double(vector<double>, double)>, std::string, bool>> funcs;
		vector<double> init_conds;
		double T0;
		double Tk;
		double step;
		vector<std::pair<string, bool>> prm_names;
		string integr_param_name;
		function<bool(vector<double>, double)> stopCriteria = function(idleStopCriteria);
	};

	map<string, vector<double>> solve_system(inputDescr_t prm);
}