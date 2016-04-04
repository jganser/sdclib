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
 *  InstanceIdentifier.h
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

#ifndef INSTANCEIDENTIFIER_H_
#define INSTANCEIDENTIFIER_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class InstanceIdentifier {
private:
	InstanceIdentifier(const CDM::InstanceIdentifier & object);
	operator CDM::InstanceIdentifier() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	InstanceIdentifier();
	InstanceIdentifier(const InstanceIdentifier & object);
	virtual ~InstanceIdentifier();
    
    void copyFrom(const InstanceIdentifier & object);
    InstanceIdentifier & operator=(const InstanceIdentifier & object);
    
    typedef CDM::InstanceIdentifier WrappedType;

	InstanceIdentifier & setroot(const std::string & value);
	std::string getroot() const;

	InstanceIdentifier & setextension(const std::string & value);
	std::string getextension() const;
	bool getextension(std::string & out) const;
	bool hasextension() const;

	InstanceIdentifier & addIdentifierName(const LocalizedText & value);
	std::vector<LocalizedText> getIdentifierNames() const;
	void clearIdentifierNames();
	
private:
	std::shared_ptr<CDM::InstanceIdentifier> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* INSTANCEIDENTIFIER_H_ */
