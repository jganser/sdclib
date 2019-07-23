/*
 * AbstractConsumer.cpp
 *
 *  Created on: Jul 23, 2019
 *      Author: rosenau
 */

#include "AbstractConsumer.h"
#include "SDCLib/Util/DebugOut.h"

#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"




namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
public:
	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
	}
	void onConnectionLost() override {
		std::cerr << "Connection lost, disconnecting... ";
		consumer.disconnect();
		std::cerr << "disconnected." << std::endl;
	}
private:
	Data::SDC::SDCConsumer & consumer;
};

AbstractConsumer::AbstractConsumer() :
		DUTMirrorProvider(nullptr),
		consumer(nullptr),
		connectionLostHandler(nullptr)
		{
	// TODO Auto-generated constructor stub

}

bool AbstractConsumer::discoverDUT(const std::string& deviceEPR) {

	 // Create a new SDCInstance (no flag will auto init) for Consumer
	    auto t_SDCInstance = std::make_shared<SDCInstance>();
		// Some restriction
		t_SDCInstance->setIP6enabled(false);
		t_SDCInstance->setIP4enabled(true);
		// Bind it to interface that matches the internal criteria (usually the first enumerated)
		if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
			Util::DebugOut(Util::DebugOut::Default, "AbstractConsumer") << "Failed to bind to default network interface! Exit..." << std::endl;
			return false;
		}


		//Discovery of Device under Test
		OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);

		std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));


		try {
			if (c != nullptr) {
				consumer = std::move(c);
				return true;
			}
			else {
				Util::DebugOut(Util::DebugOut::Default, "AbstractConsumer") << "Discovery failed."; //Not debug out but inform orchestrator
				return false;
			}
		} catch (std::exception & e) {
		Util::DebugOut(Util::DebugOut::Default, "AbstractConsumer") << "Exception: " << e.what() << std::endl; //Not debug out but inform orchestrator
			return false;
		}
}

bool AbstractConsumer::setupMirrorProvider(const std::string& MirrorProviderEndpointReference="DUTMirrorProvider") {
	auto t_SDCInstanceProvider = std::make_shared<SDCInstance>();		    // Some restriction
	t_SDCInstanceProvider->setIP6enabled(false);
	t_SDCInstanceProvider->setIP4enabled(true);
	// Bind it to interface that matches the internal criteria (usually the first enumerated)
	if(!t_SDCInstanceProvider->bindToDefaultNetworkInterface()) {
		std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
		return false;
	}

	//initialize Mirror Provider which mirrors the behavior of the DUT
	MirrorProvider mirrorProvider(t_SDCInstanceProvider);
	mirrorProvider.setEndpointReference("DUTMirrorProvider");
	Dev::DeviceCharacteristics devChar;
	devChar.addFriendlyName("en", "DUTMirrorProvider");
	mirrorProvider.setDeviceCharacteristics(devChar);
	mirrorProvider.setMdDescription(getConsumerStringRepresentationOfMDIB());
	startMirrorProvider();
	return true;

}

void AbstractConsumer::startMirrorProvider() {
	DUTMirrorProvider->startup();
	DUTMirrorProvider->start();
}

bool AbstractConsumer::addSubscriptionHandler(HandleRef descriptionHandler) {
	return false;
}

bool AbstractConsumer::addSetHandler(HandleRef descriptionHandler) {
	return false;
}

bool AbstractConsumer::addGetHandler(HandleRef descriptionHandler) {
	return false;
}

const std::string AbstractConsumer::getConsumerStringRepresentationOfMDIB() {
	return getStringRepresentationOfMDIB(consumer->getMdib());
}

const std::string AbstractConsumer::getMirrorProviderStringRepresentationOfMDIB() {
	return getStringRepresentationOfMDIB(DUTMirrorProvider->getMdib());
}

const std::string AbstractConsumer::getStringRepresentationOfMDIB(const MdibContainer MDIB) {
	MDM::GetMdibResponse MdibResponse(xml_schema::Uri("0"),ConvertToCDM::convert(MDIB));
	MdibResponse.MdibVersion(MDIB.getMdibVersion());
	const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);
	xml_schema::NamespaceInfomap map;
	std::ostringstream providerMdibStringRepresentation;
	CDM::MdibContainer(providerMdibStringRepresentation, MdibResponse.Mdib(), map, OSELib::XML_ENCODING, xercesFlags);
	return providerMdibStringRepresentation.str();
}


} //ACS
} //SDC
} //Data
} //SDCLib

