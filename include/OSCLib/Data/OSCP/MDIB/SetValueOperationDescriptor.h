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
 *  SetValueOperationDescriptor.h
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

#ifndef SETVALUEOPERATIONDESCRIPTOR_H_
#define SETVALUEOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetValueOperationDescriptor {
private:
	SetValueOperationDescriptor(const CDM::SetValueOperationDescriptor & object);
	operator CDM::SetValueOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SetValueOperationDescriptor();
	SetValueOperationDescriptor(const SetValueOperationDescriptor & object);
	virtual ~SetValueOperationDescriptor();
    
    void copyFrom(const SetValueOperationDescriptor & object);
    SetValueOperationDescriptor & operator=(const SetValueOperationDescriptor & object);
    
    typedef CDM::SetValueOperationDescriptor WrappedType;

	SetValueOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetValueOperationDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	SetValueOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetValueOperationDescriptor & setIntendedUse(const IntendedUse & value);
	IntendedUse getIntendedUse() const;
	bool getIntendedUse(IntendedUse & out) const;
	bool hasIntendedUse() const;

	SetValueOperationDescriptor & setOperationTarget(const std::string & value);
	std::string getOperationTarget() const;

	SetValueOperationDescriptor & addModifiableElement(const CodedValue & value);
	std::vector<CodedValue> getModifiableElements() const;
	void clearModifiableElements();
	
private:
	std::shared_ptr<CDM::SetValueOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETVALUEOPERATIONDESCRIPTOR_H_ */
