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
 *  StringMetricState.h
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

#ifndef STRINGMETRICSTATE_H_
#define STRINGMETRICSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class StringMetricState {
private:
	StringMetricState(const CDM::StringMetricState & object);
	operator CDM::StringMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	StringMetricState();
	StringMetricState(const StringMetricState & object);
	virtual ~StringMetricState();
    
    void copyFrom(const StringMetricState & object);
    StringMetricState & operator=(const StringMetricState & object);
    
    typedef CDM::StringMetricState WrappedType;
    typedef StringMetricDescriptor DescriptorType;
    typedef OSCPProviderStringMetricStateHandler ProviderHandlerType;
    typedef OSCPConsumerStringMetricStateHandler ConsumerHandlerType;

	StringMetricState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	StringMetricState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	StringMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	StringMetricState & setComponentActivationState(const ComponentActivation & value);
	ComponentActivation getComponentActivationState() const;
	bool getComponentActivationState(ComponentActivation & out) const;
	bool hasComponentActivationState() const;

	StringMetricState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	StringMetricState & setOperatingHours(const int & value);
	int getOperatingHours() const;
	bool getOperatingHours(int & out) const;
	bool hasOperatingHours() const;

	StringMetricState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;
	bool getOperatingCycles(int & out) const;
	bool hasOperatingCycles() const;

	StringMetricState & setObservedValue(const StringMetricValue & value);
	StringMetricValue getObservedValue() const;
	bool getObservedValue(StringMetricValue & out) const;
	bool hasObservedValue() const;

private:
	std::shared_ptr<CDM::StringMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* STRINGMETRICSTATE_H_ */
