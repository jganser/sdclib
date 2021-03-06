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
 *  LocationReference.cpp
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

#include "SDCLib/Data/SDC/MDIB/LocationReference.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/LocationDetail.h"

namespace SDCLib {
namespace Data {
namespace SDC {


LocationReference::LocationReference(
) : data(Defaults::LocationReferenceInit(
))
{}

LocationReference::operator CDM::LocationReference() const {
	return *data;
}

LocationReference::LocationReference(const CDM::LocationReference & object)
: data(new CDM::LocationReference(object))
{ }

LocationReference::LocationReference(const LocationReference & object)
: data(std::make_shared<CDM::LocationReference>(*object.data))
{ }

void LocationReference::copyFrom(const LocationReference & object) {
	data = std::make_shared<CDM::LocationReference>(*object.data);
}

LocationReference & LocationReference:: operator=(const LocationReference& object) {
	copyFrom(object);
	return *this;
}


LocationReference & LocationReference::setLocationDetail(const LocationDetail & value) {
	data->setLocationDetail(ConvertToCDM::convert(value));
	return *this;
}

bool LocationReference::getLocationDetail(LocationDetail & out) const {
	if (data->getLocationDetail().present()) {
		out = ConvertFromCDM::convert(data->getLocationDetail().get());
		return true;
	}
	return false;
}

LocationDetail LocationReference::getLocationDetail() const {
	return ConvertFromCDM::convert(data->getLocationDetail().get());
}

bool LocationReference::hasLocationDetail() const {
	return data->getLocationDetail().present();
}

LocationReference & LocationReference::addIdentification(const InstanceIdentifier & value) {
	data->getIdentification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> LocationReference::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getIdentification().size());
	for (const auto & value: data->getIdentification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LocationReference::clearIdentificationList() {
	data->getIdentification().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

