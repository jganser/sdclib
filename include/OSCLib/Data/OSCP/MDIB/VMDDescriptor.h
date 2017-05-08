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
 *  VMDDescriptor.h
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

#ifndef VMDDESCRIPTOR_H_
#define VMDDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class VMDDescriptor {
private:
	VMDDescriptor(const CDM::VMDDescriptor & object);
	operator CDM::VMDDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	VMDDescriptor();
	VMDDescriptor(const VMDDescriptor & object);
	virtual ~VMDDescriptor();
    
    void copyFrom(const VMDDescriptor & object);
    VMDDescriptor & operator=(const VMDDescriptor & object);
    
    typedef CDM::VMDDescriptor WrappedType;

	VMDDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	VMDDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	VMDDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	VMDDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecifications() const;
	void clearProductionSpecifications();
	
	VMDDescriptor & setAlertSystem(const AlertSystemDescriptor & value);
	AlertSystemDescriptor getAlertSystem() const;
	bool getAlertSystem(AlertSystemDescriptor & out) const;
	bool hasAlertSystem() const;

	VMDDescriptor & addChannel(const ChannelDescriptor & value);
	std::vector<ChannelDescriptor> getChannels() const;
	void clearChannels();
	
private:
	std::shared_ptr<CDM::VMDDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* VMDDESCRIPTOR_H_ */
