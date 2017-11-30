
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"

#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace StreamOSCP {

const std::string deviceEPR("UDI_STREAMINGTEST");

class StreamConsumerEventHandler : public OSCPConsumerRealTimeSampleArrayMetricStateHandler {
public:
	StreamConsumerEventHandler(const std::string & handle) :
    	verifiedChunks(false),
		handle(handle)
    {
    }

    void onStateChanged(const RealTimeSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        DebugOut(DebugOut::Default, "StreamOSCP") << "Received chunk! Handle: " << handle << std::endl;
        std::vector<double> values = state.getMetricValue().getSamples();
        verifiedChunks = true;

        for (size_t i = 0; i < values.size(); i++) {
            if (values[i] != double(i))
                verifiedChunks = false;
        }
    }

    std::string getHandle() override {
        return handle;
    }

    bool getVerifiedChunks() {
    	Poco::Mutex::ScopedLock lock(mutex);
        return verifiedChunks;
    }

private:
    Poco::Mutex mutex;
    bool verifiedChunks;
    const std::string handle;
};

class StreamProviderStateHandler : public OSCPProviderRealTimeSampleArrayMetricStateHandler {
public:

    StreamProviderStateHandler(std::string descriptorHandle) : descriptorHandle(descriptorHandle) {
    }

    // Helper method
    RealTimeSampleArrayMetricState createState() {
        RealTimeSampleArrayMetricState realTimeSampleArrayState(descriptorHandle);
        realTimeSampleArrayState
        	.setActivationState(ComponentActivation::On);
        return realTimeSampleArrayState;
    }


    RealTimeSampleArrayMetricState getInitialState() override {
        return createState();
    }

    void updateStateValue(const SampleArrayValue & rtsav) {
        RealTimeSampleArrayMetricState realTimeSampleArrayState = createState();
        realTimeSampleArrayState
            .setMetricValue(rtsav);
        updateState(realTimeSampleArrayState);
    }

private:
    std::string descriptorHandle;
};

class OSCPStreamHoldingDeviceProvider : public Util::Task {
public:

    OSCPStreamHoldingDeviceProvider() : oscpProvider(), streamHandler("handle_plethysmogram_stream"), streamHandlerAlt("handle_plethysmogram_stream_alt") {

		oscpProvider.setEndpointReference(OSCLib::Tests::StreamOSCP::deviceEPR);


		// Currentweight stream metric (read-only)
		// Metric references the handler
		RealTimeSampleArrayMetricDescriptor currentMetric("handle_plethysmogram_stream",
				CodedValue(CodeIdentifier("MDCX_PLETHYSMOGRAM")).addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				1,
				xml_schema::Duration(0,0,0,0,0,0,1));

		// alternative current matrix
		// Metric references the handler
	    RealTimeSampleArrayMetricDescriptor currentMetricAlt("handle_plethysmogram_stream_alt",
	    		CodedValue(CodeIdentifier("MDCX_PLETHYSMOGRAM_ALT")).addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")),
	    		MetricCategory::Msrmt,
	    		MetricAvailability::Cont,
	    		1,
	    		xml_schema::Duration(0,0,0,0,0,0,1));

        // alternative current matrix: non-mandatory information
        currentMetricAlt.addTechnicalRange(Range().setLower(0).setUpper(2));


        // Channel
        ChannelDescriptor holdingDeviceParameters("handle_channel");
        holdingDeviceParameters
			.addMetric(currentMetric)
            .addMetric(currentMetricAlt)
			.setSafetyClassification(SafetyClassification::Inf);

        // VMD
        VmdDescriptor holdingDeviceModule("handle_vmd");
        holdingDeviceModule.addChannel(holdingDeviceParameters);

        // MDS
        MdsDescriptor holdingDeviceSystem("handle_mds");
        holdingDeviceSystem
			.setMetaData(
				MetaData()
					.addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
	        		.setModelNumber("1")
	        		.addModelName(LocalizedText().setRef("EndoTAIX"))
	        		.addSerialNumber("1234"))
            .setType(CodedValue(CodeIdentifier("MDC_DEV_ANALY_SAT_O2_MDS")))
			.addVmd(holdingDeviceModule);

        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(holdingDeviceSystem);

		oscpProvider.setMdDescription(mdDescription);

        // Add handler
        oscpProvider.addMdSateHandler(&streamHandler);
        oscpProvider.addMdSateHandler(&streamHandlerAlt);
    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    void updateStateValue(const SampleArrayValue & rtsav) {
        streamHandler.updateStateValue(rtsav); // updates handles and the parent provider
        streamHandlerAlt.updateStateValue(rtsav);
    }

private:

    OSCPProvider oscpProvider;

    StreamProviderStateHandler streamHandler;
    StreamProviderStateHandler streamHandlerAlt;

public:
    
    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {
    	DebugOut(DebugOut::Default, "StreamOSCP") << "\nPoducer thread started." << std::endl;
		const std::size_t size(1000);
		std::vector<double> samples;
		for (std::size_t i = 0; i < size; i++) {
			samples.push_back(i);
		}
		long index(0);
		while (!isInterrupted()) {
			{
                updateStateValue(
						SampleArrayValue(MetricQuality(MeasurementValidity::Vld))
						.setSamples(samples));

			}
			DebugOut(DebugOut::Default, "StreamOSCP") << "Produced stream chunk of size " << size << ", index " << index << std::endl;
			Poco::Thread::sleep(1000);
			index += size;
		}
    }
};

}
}
}

struct FixtureStreamOSCP : Tests::AbstractOSCLibFixture {
	FixtureStreamOSCP() : AbstractOSCLibFixture("FixtureStreamOSCP", OSELib::LogLevel::NOTICE, 10000) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureStreamOSCP, streamoscp)
{
	DebugOut::openLogFile("TestStream.log.txt", true);
	try
	{
        // Provider
		Tests::StreamOSCP::OSCPStreamHoldingDeviceProvider provider;
		DebugOut(DebugOut::Default, "StreamOSCP") << "Provider init.." << std::endl;
		provider.startup();

        // Consumer
        OSELib::OSCP::ServiceManager oscpsm;
        DebugOut(DebugOut::Default, "StreamOSCP") << "Consumer discovery..." << std::endl;
        std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(OSCLib::Tests::StreamOSCP::deviceEPR));
        std::shared_ptr<Tests::StreamOSCP::StreamConsumerEventHandler> eventHandler = std::make_shared<Tests::StreamOSCP::StreamConsumerEventHandler>("handle_plethysmogram_stream");
        std::shared_ptr<Tests::StreamOSCP::StreamConsumerEventHandler> eventHandlerAlt = std::make_shared<Tests::StreamOSCP::StreamConsumerEventHandler>("handle_plethysmogram_stream_alt");

        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

        if (c != nullptr) {
            c->registerStateEventHandler(eventHandler.get());
            c->registerStateEventHandler(eventHandlerAlt.get());

            provider.start();// starts provider in a thread and calls the overwritten function runImpl()

			// Metric event reception test
            Poco::Thread::sleep(10000);
            CHECK_EQUAL(true, eventHandler->getVerifiedChunks());
            CHECK_EQUAL(true, eventHandlerAlt->getVerifiedChunks());
            
            provider.interrupt();
            c->unregisterStateEventHandler(eventHandler.get());
            c->unregisterStateEventHandler(eventHandlerAlt.get());
            c->disconnect();
        }

        Poco::Thread::sleep(2000);
        provider.shutdown();
	}
	catch (char const* exc)
	{
		DebugOut(DebugOut::Default, std::cerr, "streamoscp") << exc;
	}    
	catch (...)
	{
		DebugOut(DebugOut::Default, std::cerr, "streamoscp") << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
