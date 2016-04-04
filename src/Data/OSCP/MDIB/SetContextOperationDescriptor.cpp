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
 *  SetContextOperationDescriptor.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/SetContextOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetContextOperationDescriptor::SetContextOperationDescriptor() : data(Defaults::SetContextOperationDescriptor()) {
}

SetContextOperationDescriptor::operator CDM::SetContextOperationDescriptor() const {
	return *data;
}

SetContextOperationDescriptor::SetContextOperationDescriptor(const CDM::SetContextOperationDescriptor & object) : data(new CDM::SetContextOperationDescriptor(object)) {

}

SetContextOperationDescriptor::SetContextOperationDescriptor(const SetContextOperationDescriptor & object) : data(new CDM::SetContextOperationDescriptor(*object.data)) {

}

SetContextOperationDescriptor::~SetContextOperationDescriptor() {

}

void SetContextOperationDescriptor::copyFrom(const SetContextOperationDescriptor & object) {
	*data = *object.data;
}

SetContextOperationDescriptor & SetContextOperationDescriptor:: operator=(const SetContextOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetContextOperationDescriptor & SetContextOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetContextOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetContextOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetContextOperationDescriptor & SetContextOperationDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string SetContextOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetContextOperationDescriptor & SetContextOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetContextOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetContextOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetContextOperationDescriptor & SetContextOperationDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextOperationDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse SetContextOperationDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool SetContextOperationDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
SetContextOperationDescriptor & SetContextOperationDescriptor::setOperationTarget(const std::string & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


std::string SetContextOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetContextOperationDescriptor & SetContextOperationDescriptor::addModifiableElement(const CodedValue & value) {
	data->ModifiableElement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> SetContextOperationDescriptor::getModifiableElements() const {
	std::vector<CodedValue> result;
	result.reserve(data->ModifiableElement().size());
	for (const auto & value: data->ModifiableElement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetContextOperationDescriptor::clearModifiableElements() {
	data->ModifiableElement().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

