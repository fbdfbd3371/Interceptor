#pragma once
#define PI 3.1415926535
#include <vector>
#include <Atmos.hpp>

using namespace std;

double cur_mass(vector<double> st, double t);
double P(vector<double> st, double t);
double phi_t(vector<double> st, double t);

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
	x_i,
	y_i,
	z_i,

	x_t,
	y_t,
	z_t,

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

// x_i - ���������� �� ��� Oxg
double x_i(vector<double> st, double t);

// y_i - ���������� �� ��� Oyg
double y_i(vector<double> st, double t);

// z_i - ���������� �� ��� Oyg
double z_i(vector<double> st, double t);

double x_t(vector<double> st, double t);
double y_t(vector<double> st, double t);
double z_t(vector<double> st, double t);
