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
 *  ProductionSpecification.cpp
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

#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ProductionSpecification::ProductionSpecification(
		CodedValue spectype
		,
		std::string productionspec
) : data(Defaults::ProductionSpecificationInit(
		spectype
		,
		productionspec
))
{}

ProductionSpecification::operator CDM::ProductionSpecification() const {
	return *data;
}

ProductionSpecification::ProductionSpecification(const CDM::ProductionSpecification & object)
: data(new CDM::ProductionSpecification(object))
{ }

ProductionSpecification::ProductionSpecification(const ProductionSpecification & object)
: data(std::make_shared<CDM::ProductionSpecification>(*object.data))
{ }

void ProductionSpecification::copyFrom(const ProductionSpecification & object) {
	data = std::make_shared<CDM::ProductionSpecification>(*object.data);
}

ProductionSpecification & ProductionSpecification:: operator=(const ProductionSpecification& object) {
	copyFrom(object);
	return *this;
}


ProductionSpecification & ProductionSpecification::setSpecType(const CodedValue & value) {
	data->setSpecType(ConvertToCDM::convert(value));
	return *this;
}


CodedValue ProductionSpecification::getSpecType() const {
	return ConvertFromCDM::convert(data->getSpecType());
}

ProductionSpecification & ProductionSpecification::setProductionSpec(const std::string & value) {
	data->setProductionSpec(ConvertToCDM::convert(value));
	return *this;
}


std::string ProductionSpecification::getProductionSpec() const {
	return ConvertFromCDM::convert(data->getProductionSpec());
}

ProductionSpecification & ProductionSpecification::setComponentId(const InstanceIdentifier & value) {
	data->setComponentId(ConvertToCDM::convert(value));
	return *this;
}

bool ProductionSpecification::getComponentId(InstanceIdentifier & out) const {
	if (data->getComponentId().present()) {
		out = ConvertFromCDM::convert(data->getComponentId().get());
		return true;
	}
	return false;
}

InstanceIdentifier ProductionSpecification::getComponentId() const {
	return ConvertFromCDM::convert(data->getComponentId().get());
}

bool ProductionSpecification::hasComponentId() const {
	return data->getComponentId().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

