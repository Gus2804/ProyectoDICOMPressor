#include "Study.h"

#include <stdio.h>

Study::Study()
{
	this->patientName.clear();
	this->patientBirthdate.clear();
	this->patientSex.clear();
	this->responsable.clear();
	this->responsableRol.clear();
	this->studyDescription.clear();
	this->studyDate.clear();
	this->institutionName.clear();
	this->institutionDepartament.clear();
}


Study::~Study()
{
}
