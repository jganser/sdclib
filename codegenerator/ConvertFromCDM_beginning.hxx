/*
 * ConvertFromCDM.h
 *
 *  Created on: 22.06.2017
 *      Author: buerger
 *
 *  This file is autogenerated.
 *
 *  Do not edit this file. For customization please edit the ConvertFromCDM_beginning.hxx or ConvertFromCDM_ending.hxx
 */

#ifndef DATA_SDC_MDIB_CONVERTFROMCDM_H_
#define DATA_SDC_MDIB_CONVERTFROMCDM_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/MDIB-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class ConvertFromCDM {
public:
	ConvertFromCDM();
	virtual ~ConvertFromCDM();

	// build-in type conversions for the basetyes (see typedefs in SimpleTypesMapping.h)
	static bool convert(const bool source);
	static double convert(const double source);
	static unsigned int convert(const unsigned int source);
	static int convert(const int source);
	static long convert(const long source);
	static long long convert(const long long source);
	static unsigned short int convert(const unsigned short int source);
	static unsigned long convert(const unsigned long source);
	static unsigned long long convert(const unsigned long long source);
    static std::string convert(const std::string & source);
	static xml_schema::Duration convert(const xml_schema::Duration & source);
	static xml_schema::Qname convert(const xml_schema::Qname & source);
	static xml_schema::Language convert(const xml_schema::Language & source);
	static xml_schema::Uri convert(const xml_schema::Uri & source);
	static xml_schema::DateTime convert(const xml_schema::DateTime & source);
	static xml_schema::Idrefs convert(const xml_schema::Idrefs & source);
	static xml_schema::Id convert(const xml_schema::Id & source);

	static InvocationState convert(const MDM::InvocationState & source);

	// autogenerated here
