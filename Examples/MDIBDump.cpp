
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/MDIBContainer.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPServiceManager.h"
#include "OSCLib/Util/DebugOut.h"

#include "osdm.hxx"

#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"

#include <fstream>

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

std::string stripCharacters(const std::string & input, const std::string & removeChars) {
	std::string str(input);
    str.erase(
        std::remove_if(str.begin(), str.end(), [&](char c){
            return removeChars.find(c) != std::string::npos;
        }),
        str.end()
    );
    return str;
}

std::string stateTypeAsString(const AlertConditionState & ) {
	return "AlertConditionState";
}

std::string stateTypeAsString(const AlertSignalState & ) {
	return "AlertSignalState";
}

std::string stateTypeAsString(const AlertSystemState & ) {
	return "AlertSystemState";
}

std::string stateTypeAsString(const ClockState & ) {
	return "ClockState";
}

std::string stateTypeAsString(const ComponentState & ) {
	return "ComponentState";
}

std::string stateTypeAsString(const EnumStringMetricState & ) {
	return "EnumStringMetricState";
}

std::string stateTypeAsString(const HydraMDSState & ) {
	return "HydraMDSState";
}

std::string stateTypeAsString(const LimitAlertConditionState & ) {
	return "LimitAlertConditionState";
}

std::string stateTypeAsString(const NumericMetricState & ) {
	return "NumericMetricState";
}

std::string stateTypeAsString(const RealTimeSampleArrayMetricState & ) {
	return "RealTimeSampleArrayMetricState";
}

std::string stateTypeAsString(const StringMetricState & ) {
	return "StringMetricState";
}

template<class StateType>
void validateStates(const MDDescription & mdd, const std::vector<StateType> & states, std::vector<std::string> & stateHandles) {
	for (const auto & state : states) {
		if (state.hasHandle()) {
			stateHandles.push_back(state.getHandle());
		}

		typename StateType::DescriptorType descriptor;
		if (!mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
			if (state.hasHandle()) {
				DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " with handle " << state.getHandle() << " references non existing descriptor " << state.getDescriptorHandle();
			} else {
				DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " (without own handle) references non existing descriptor " << state.getDescriptorHandle();
			}
		}
	}
}

template<>
void validateStates(const MDDescription & mdd, const std::vector<ComponentState> & states, std::vector<std::string> & stateHandles) {
	for (const auto & state : states) {
		if (state.hasHandle()) {
			stateHandles.push_back(state.getHandle());
		}

		bool match = false;

		{
			for (const auto & hydramds : mdd.collectAllHydraMDSDescriptors()) {
				if (hydramds.getHandle() == state.getDescriptorHandle()) {
					match |= true;
				}
				if (!hydramds.hasSCO()) {
					continue;
				}
				if (hydramds.getSCO().getHandle() == state.getDescriptorHandle()) {
					match |= true;
				}
			}
		}
		{
			VMDDescriptor descriptor;
			if (mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
				match |= true;
			}
		}
		{
			ChannelDescriptor descriptor;
			if (mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
				match |= true;
			}
		}

		if (match) {
			continue;
		}

		if (state.hasHandle()) {
			DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " with handle " << state.getHandle() << " references non existing descriptor " << state.getDescriptorHandle();
		} else {
			DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " (without own handle) references non existing descriptor " << state.getDescriptorHandle();
		}
	}
}

void validate(const MDIBContainer & mdib) {
	std::vector<std::string> descriptorHandles;
	std::vector<std::string> stateHandles;

	const MDDescription mdd(mdib.getMDDescription());
	const MDState mdstate(mdib.getMDState());

	{
		HydraMDSDescriptor mds;
		if (!mdd.getFirstHydraMDSDescriptor(mds)) {
			DebugOut(DebugOut::Default, "MDIBDump") << "No MDS found!" << std::endl;
			return;
		}
	}

	for (const auto & mds : mdd.collectAllHydraMDSDescriptors()) {
		descriptorHandles.push_back(mds.getHandle());
		if (mds.hasSCO()) {
			descriptorHandles.push_back(mds.getSCO().getHandle());
		}
	}
	for (const auto & vmd: mdd.collectAllVMDDescriptors()) {
		descriptorHandles.push_back(vmd.getHandle());
	}
	for (const auto & channel : mdd.collectAllChannelDescriptors()) {
		descriptorHandles.push_back(channel.getHandle());
	}
	for (const auto & clockDescriptor : mdd.collectAllClockDescriptors()) {
		descriptorHandles.push_back(clockDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllEnumStringMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllNumericMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllRealTimeSampleArrayMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllStringMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}

	for (const auto & alertSystem : mdd.collectAllAlertSystemDescriptors()) {
		descriptorHandles.push_back(alertSystem.getHandle());
		for (const auto & alertSignal : alertSystem.getAlertSignals()) {
			descriptorHandles.push_back(alertSignal.getHandle());
		}
		for (const auto & condition : alertSystem.getAlertConditions()) {
			descriptorHandles.push_back(condition.getHandle());
		}
		for (const auto & condition : alertSystem.getLimitAlertConditions()) {
			descriptorHandles.push_back(condition.getHandle());
		}
	}


	{ //verify if all descriptors have a state
		std::vector<std::string> tempDescriptorHandles(descriptorHandles);
		std::sort(tempDescriptorHandles.begin(), tempDescriptorHandles.end());

		CDM::MDState states(*ConvertToCDM::convert(mdstate));
		for (const auto & state : states.State()) {
			const auto iterator(std::find(tempDescriptorHandles.begin(), tempDescriptorHandles.end(), state.DescriptorHandle()));
			if (iterator != tempDescriptorHandles.end()) {
				tempDescriptorHandles.erase(iterator);
			}
		}

		for (const auto & handle : tempDescriptorHandles) {
			DebugOut(DebugOut::Default, "MDIBDump") << "Error: Found descriptor without state. It has handle: " << handle << std::flush;
		}
	}

	validateStates(mdd, mdstate.findAlertSystemStates(), stateHandles);
	validateStates(mdd, mdstate.findAlertSignalStates(), stateHandles);
	validateStates(mdd, mdstate.findAlertConditionStates(), stateHandles);
	validateStates(mdd, mdstate.findClockStates(), stateHandles);
	validateStates(mdd, mdstate.findComponentStates(), stateHandles);
	validateStates(mdd, mdstate.findHydraMDSStates(), stateHandles);
	validateStates(mdd, mdstate.findLimitAlertConditionStates(), stateHandles);
	validateStates(mdd, mdstate.findEnumStringMetricStates(), stateHandles);
	validateStates(mdd, mdstate.findNumericMetricStates(), stateHandles);
	validateStates(mdd, mdstate.findRealTimeSampleArrayMetricStates(), stateHandles);
	validateStates(mdd, mdstate.findStringMetricStates(), stateHandles);

	// check for duplicates
	std::vector<std::string> allHandles;
	allHandles.insert(allHandles.end(), descriptorHandles.begin(), descriptorHandles.end());
	allHandles.insert(allHandles.end(), stateHandles.begin(), stateHandles.end());
	std::sort(allHandles.begin(), allHandles.end());

	if (allHandles.size() > 1) {
		std::vector<std::string>::const_iterator cur_iter(allHandles.begin());
		std::vector<std::string>::const_iterator prev_iter(allHandles.begin());
		++cur_iter;
		while (cur_iter != allHandles.end()) {
			if (*cur_iter == *prev_iter) {
				DebugOut(DebugOut::Default, "MDIBDump") << "Error: Found duplicate handle: " << *cur_iter << std::flush;
			}
			++cur_iter;
			++prev_iter;
		}
	}
	DebugOut(DebugOut::Default, "MDIBDump") << std::flush;
}

int main (int argc, char * argv[])
{
	const std::string testname(argc != 2 ? "Dump MDIBs of all found devices" : "Dump MDIBs of given EPR");
	DebugOut(DebugOut::Default, "MDIBDump") << std::endl << "Startup: " << testname;
	OSCLibrary::getInstance()->startup(DebugOut::Default);

	OSCPServiceManager oscpsm;

	while (true) {
		DebugOut(DebugOut::Default, "MDIBDump") << "Refreshing ..." << std::flush;
		Poco::Timestamp refreshStarted;

		std::vector<std::shared_ptr<OSCPConsumer> > results;
		if (argc != 2) {
			results = oscpsm.discoverOSCP();
		} else {
			std::shared_ptr<OSCPConsumer> result(oscpsm.discoverEndpointReference(std::string(argv[1])));
			if (result != nullptr) {
				results.emplace_back(result);
			}
		}

		DebugOut(DebugOut::Default, "MDIBDump") << "Found devices with these EPRs: ";

		for (auto & consumer : results) {
			const std::string epr(consumer->getEndpointReference());
			const std::string filename("mdib" + stripCharacters(epr, ".:/\\!?*") + ".xml");

			DebugOut(DebugOut::Default, "MDIBDump") << "Found EPR " << epr << " and dumping to file " << filename;

			try {
				std::ofstream outFile;
				outFile.open(filename, std::ios::trunc);
				Poco::Timestamp dumpStarted;
				outFile << consumer->requestRawMDIB();
				DebugOut(DebugOut::Default, "MDIBDump") << "   -> took " << Poco::DateTimeFormatter::format(Poco::Timespan(dumpStarted.elapsed()), "%s:%i") << " s:ms." << std::endl;
				outFile.close();
			} catch (...) {
				DebugOut(DebugOut::Default, "MDIBDump") << "Error writing file." << std::endl;
			}

			const MDIBContainer mdib(consumer->getMDIB());
			validate(mdib);
		}

		for (auto & consumer : results) {
			consumer->disconnect();
			consumer.reset();
		}
		results.clear();
		DebugOut(DebugOut::Default, "MDIBDump") << "Done after " << Poco::DateTimeFormatter::format(Poco::Timespan(refreshStarted.elapsed()), "%s:%i") << " s:ms." << std::endl << std::flush;

		if (argc != 2) {
			Poco::Thread::sleep(5000);
		}
	}

	Poco::Thread::sleep(2000);

	DebugOut(DebugOut::Default, "MDIBDump") << "Shutdown: " << testname << std::endl;
}

