#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <fstream>
#include <optional>
#include <atmos.hpp>

struct inputDescr_t;
extern inputDescr_t inputDescr;
extern std::ofstream outFile;

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
	std::vector<function<std::optional<bool>(vector<double>, double)>> stopCriteriaVector{function(idleStopCriteria)};

	double propoN{80.0};
	double Vt{48.0};
	double m = 2;
	double Jx = 0;
	double Jy = 0;
	double Jz = 0.2;
	double ld_lc = 0.21;
	double Sm = 0.017289;
	double Vc_min{10};
	double Kp{20};
};

bool solve_system(inputDescr_t prm);
