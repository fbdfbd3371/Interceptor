#include <iostream>
#include <fstream>
#include <Integrator.hpp>

inputDescr_t inputDescr;
ofstream outFile;

bool idleStopCriteria(vector<double>, double)
{
	return false;
}

bool solve_system(inputDescr_t prm)
{
	outFile << "t, sec" << "\t";
	for (auto el : prm.prm_names)
		if (el.second)
			outFile << el.first << "\t";
	for (auto el : prm.funcs)
		if (std::get<2>(el))
			outFile << std::get<1>(el) << "\t";
	outFile << std::endl;

	map<string, vector<double>> allParams;
	for (int i = 0; i < prm.rhss.size(); i++)
	{
		allParams.emplace(prm.prm_names[i].first, NULL);
	}
	allParams.emplace(prm.integr_param_name, NULL);

	vector<double> state_sys(prm.rhss.size());
	state_sys = prm.init_conds;

	vector<double> cur_params(prm.rhss.size());
	cur_params = prm.init_conds;

	for (double t = prm.T0; t < prm.Tk; t += prm.step)
	{
		vector<double> k1(prm.rhss.size());
		vector<double> k2(prm.rhss.size());
		vector<double> k3(prm.rhss.size());
		vector<double> k4(prm.rhss.size());

		// ------------k1-------------
		for (int i = 0; i < prm.rhss.size(); i++)
		{
			k1[i] = prm.rhss[i](state_sys, t);
		}

		// ------------k2-------------
		state_sys = cur_params;

		for (int i = 0; i < prm.rhss.size(); i++)
		{
			state_sys[i] += 0.5 * k1[i] * prm.step;
		}

		for (int i = 0; i < prm.rhss.size(); i++)
		{
			k2[i] = prm.rhss[i](state_sys, t + prm.step / 2);
		}

		// ------------k3-------------
		state_sys = cur_params;

		for (int i = 0; i < prm.rhss.size(); i++)
		{
			state_sys[i] += 0.5 * k2[i] * prm.step;
		}

		for (int i = 0; i < prm.rhss.size(); i++)
		{
			k3[i] = prm.rhss[i](state_sys, t + prm.step / 2);
		}

		// ------------k4-------------
		state_sys = cur_params;

		for (int i = 0; i < prm.rhss.size(); i++)
		{
			state_sys[i] += k3[i] * prm.step;
		}

		for (int i = 0; i < prm.rhss.size(); i++)
		{
			k4[i] = prm.rhss[i](state_sys, t + prm.step);
		}

		for (int i = 0; i < prm.rhss.size(); i++)
		{
			cur_params[i] += (prm.step / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
		}

		outFile << t + prm.step << "\t";
		for (int i = 0; i < prm.rhss.size(); i++)
		{
			allParams[prm.prm_names[i].first].push_back(cur_params[i]); // *180 / 3.1415926535);

			if (prm.prm_names[i].second)
				outFile << cur_params[i] << "\t";
		}

		for (auto el : prm.funcs)
		{
			if (std::get<2>(el))
				outFile << std::get<0>(el)(cur_params, t + prm.step) << "\t";
		}
		outFile << std::endl;

		allParams[prm.integr_param_name].push_back(t);

		for (auto el : prm.stopCriteriaVector)
		{
			auto res = el(cur_params, t + prm.step);
			if (res.has_value())
				return res.value();
		}
	}

	outFile.close();
	return false;
}