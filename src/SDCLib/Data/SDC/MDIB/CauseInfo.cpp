/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 *  CauseInfo.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/CauseInfo.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/RemedyInfo.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"

namespace SDCLib {
namespace Data {
namespace SDC {


CauseInfo::CauseInfo(
) : data(Defaults::CauseInfoInit(
))
{}

CauseInfo::operator CDM::CauseInfo() const {
	return *data;
}

CauseInfo::CauseInfo(const CDM::CauseInfo & object)
: data(new CDM::CauseInfo(object))
{ }

CauseInfo::CauseInfo(const CauseInfo & object)
: data(std::make_shared<CDM::CauseInfo>(*object.data))
{ }

void CauseInfo::copyFrom(const CauseInfo & object) {
	data = std::make_shared<CDM::CauseInfo>(*object.data);
}

CauseInfo & CauseInfo:: operator=(const CauseInfo& object) {
	copyFrom(object);
	return *this;
}


CauseInfo & CauseInfo::setRemedyInfo(const RemedyInfo & value) {
	data->setRemedyInfo(ConvertToCDM::convert(value));
	return *this;
}

bool CauseInfo::getRemedyInfo(RemedyInfo & out) const {
	if (data->getRemedyInfo().present()) {
		out = ConvertFromCDM::convert(data->getRemedyInfo().get());
		return true;
	}
	return false;
}

RemedyInfo CauseInfo::getRemedyInfo() const {
	return ConvertFromCDM::convert(data->getRemedyInfo().get());
}

bool CauseInfo::hasRemedyInfo() const {
	return data->getRemedyInfo().present();
}

CauseInfo & CauseInfo::addDescription(const LocalizedText & value) {
	data->getDescription().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CauseInfo::getDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getDescription().size());
	for (const auto & value: data->getDescription()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CauseInfo::clearDescriptionList() {
	data->getDescription().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

