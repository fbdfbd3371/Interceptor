#pragma once
//#include<cmath>
#include<math.h>
#define RADIUS_EARTH 6356767
#define GRAVITY_CONST 9.80665
#define GASE_CONST 287.05287
#define MOLAR_MASS 28.964420

class atmosphere
{
public:
	//�������
	double _getGeopotentialHeight();
	double _getGravityCurrent();
	double _getTemperatureCurrent();
	double _getPressureCurrent();
	double _getDensityCurrent();
	double _getSoundSpeedCurrent();

	atmosphere(double currentHeight)
	{
		this->currentHeight = currentHeight;
		processGeopotentialHeight();//������� ���������������� ������
		processGravityCurrent();//������� �������������� ����������
		definingLayerParameters();//������ ����������, ��������� �� ����
		processTemperatureCurrent();//������ ������� �����������
		processPressureCurrent();//������� �������� ��������
		processDensityCurrent();//������ ������� ���������
		processSoundSpeed();//������ ������� �������� �����

	}

private:
	void processGeopotentialHeight();
	void processGravityCurrent();
	void processTemperatureCurrent();
	void processPressureCurrent();
	void processDensityCurrent();
	void processSoundSpeed();

	void definingLayerParameters();


	double geopotentialHeight;//���������������� ������
	double gravityCurrent;//������� �������������� ����������
	double currentHeight;//������� ������, ������� �������������
	double currentTemperature;//������� ����������� �� ������� ������
	double currentPressure;//������� �������� �� ������� ������
	double currentDensity;//������� ��������� �� ������� ������
	double currentSoundSpeed;//������� �������� �����


	double T_star;	//T* �� �����
	double H_star;	//H* �� �����
	double betta;	//�� �����
	double p_star;	//�� ����� �� �������
	double Tm_star;	//�� ����� �� ������� 5
	double betta_m;	//�� ����� �� ������� 5

};

