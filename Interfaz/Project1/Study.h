#include <stdio.h>
#include <iostream>

using namespace std;

#pragma once
class Study
{
public:
	Study();
	~Study();

	string patientName;
	string patientBirthdate;
	string patientSex;
	string responsable;
	string responsableRol;
	string studyDescription;
	string studyDate;
	string institutionName;
	string institutionDepartament;
};

