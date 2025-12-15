#pragma once
#define PI 3.1415926535
#include <vector>
#include <Atmos.hpp>

namespace DP6sem_DZV2_funcs
{
	using namespace std;

	double cur_mass(vector<double> st, double t);
	double P(vector<double> st, double t);

	enum class sId_t
	{
		V_k = 0,
		Tetta_k,
		Psi_k,
		omg_x,
		omg_y,
		omg_z,
		pitch,
		yaw,
		roll,
		x_g,
		y_g,
		z_g,

		x_c,
		y_c,
		z_c,

		COUNT
	};

	double V_k(vector<double> st, double t);

	// Tetta_k - ���������� ����
	double Tetta_k(vector<double> st, double t);

	// Psi_k - ���� ����
	double Psi_k(vector<double> st, double t);

	// omg_x - �������� ������� �������� �� Ox1 ��������� ��
	double omg_x(vector<double> st, double t);

	// omg_y - �������� ������� �������� �� Oy1 ��������� ��
	double omg_y(vector<double> st, double t);

	// omg_z - �������� ������� �������� �� Oz1 ��������� ��
	double omg_z(vector<double> st, double t);

	// pitch - ������
	double pitch(vector<double> st, double t);

	// yaw - ��������
	double yaw(vector<double> st, double t);

	// roll - ����
	double roll(vector<double> st, double t);

	// x_g - ���������� �� ��� Oxg
	double x_g(vector<double> st, double t);

	// y_g - ���������� �� ��� Oyg
	double y_g(vector<double> st, double t);

	// z_g - ���������� �� ��� Oyg
	double z_g(vector<double> st, double t);

	double x_c(vector<double> st, double t);
	double y_c(vector<double> st, double t);
	double z_c(vector<double> st, double t);
}
