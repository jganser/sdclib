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
 * OSCPProvider.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef OSCPPROVIDER_H_
#define OSCPPROVIDER_H_

#include <atomic>
#include <memory>

#include "Poco/NotificationQueue.h"
#include "Poco/Mutex.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"

#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/OSELibProviderAdapter.h"
#include "OSCLib/Data/OSCP/MDIB/MDIB-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/MDState.h"

#include "OSELib/Helper/WithLogger.h"


// todo remove
namespace OSELib {
	struct ContextReportServiceImpl;
	struct GetServiceImpl;
	struct SetServiceImpl;
}

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProvider final : public OSELib::WithLogger {
    friend class AsyncProviderInvoker;

    friend class OSCPProviderMDStateHandler;
    
    // todo replace by friend class OSELibProviderAdapter
    friend struct OSELib::ContextReportServiceImpl;
    friend struct OSELib::GetServiceImpl;
    friend struct OSELib::SetServiceImpl;

public:
    OSCPProvider();
    virtual ~OSCPProvider();

    /**
    * @brief Get the complete MDIB (description and states).
    *
    * @return The MDIB container
    */
    MDIBContainer getMDIB();

    /**
    * @brief Get the Medical Device Description.
    *
    * @return The MDDescription container
    */

    void setMDDescrition(const MDDescription & mdDescription);
    MDDescription getMDDescription() const;

    /**
    * @brief Get all states as part of the MDIB.
    *
    * @return The MD state container
    */
    MDState getMDState();

    void addActivateOperationForDescriptor(const ActivateOperationDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const AlertConditionDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const AlertSignalDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const AlertSystemDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const EnumStringMetricDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const LimitAlertConditionDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const NumericMetricDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const StringMetricDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const PatientContextDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const LocationContextDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const EnsembleContextDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const OperatorContextDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const WorkflowContextDescriptor & descriptor, HydraMDSDescriptor & ownerMDS);

    /**
    * @brief Notify all registered consumers about a changed MDIB object (fires episodic metric changed event).
    *
    * @param object The MDIB object
    */
    void updateState(const AlertSystemState & object);
    void updateState(const AlertSignalState & object);
    void updateState(const AlertConditionState & object);
    void updateState(const EnumStringMetricState & object);
    void updateState(const EnsembleContextState & object);
    void updateState(const LimitAlertConditionState & object);
    void updateState(const LocationContextState & object);
    void updateState(const NumericMetricState & object);
    void updateState(const OperatorContextState & object);
    void updateState(const PatientContextState & object);
    void updateState(const StringMetricState & object);
    void updateState(const RealTimeSampleArrayMetricState & object);
    void updateState(const WorkflowContextState & object);

    /**
    * @brief Trigger an alert condition using a flag to indicate the condition's presence.
    *
    * Calling this method will handle all alert signals which reference this condition automatically.
    *
    * Depending on the condition's presence (true or false), alert signals will be handled as follows:
    * 1. True: the alert signal's presence state will be set ON (no matter what the previous value was)
    * 2. False: if an alert signal's presence state is currently set to ON, it will be set to LATCHED
    * However, it will never be set OFF or ACK (see notes below).
    * Due to the modification of signal states by this method, condition and signal state handlers implemented by user
    * code will be invoked. This implementation should trigger an event to inform all consumers about
    * that modification of the modified alert signal states.
    *
    * @param alertConditionHandle The handle of the alert condition state.
    * @param conditionPresence True, if the condition has been detected.
    * @param oic operation invocation context
    */
    void setAlertConditionPresence(const std::string & alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic);
    void evaluateAlertConditions(const std::string & source);

    /**
    * @brief Start the provider.
    *
    * All needed DPWS devices & services will be created and hosted.
    */
    void startup();
    
    /**
    * @brief Stop the provider.
    *
    * All needed DPWS devices & services will be stopped and deleted.
    */
    void shutdown();
    
    template<class T>
    void replaceState(const T & state);    

    /**
    * @brief Add a state handler to provide states and to process incoming change requests from a consumer.
    *
    * @param handler The handler
    */
    void addMDStateHandler(OSCPProviderMDStateHandler * handler);

    /**
    * @brief Remove a request handler which provides states and processes incoming change requests from a consumer.
    *
    * @param handler The handler
    */
    void removeMDStateHandler(OSCPProviderMDStateHandler * handler);

	void setEndpointReference(const std::string & epr);
	const std::string getEndpointReference() const;

	const Dev::DeviceCharacteristics& getDeviceCharacteristics() const;
	void setDeviceCharacteristics(const Dev::DeviceCharacteristics& deviceCharacteristics);

    unsigned long long int getMDIBVersion() const;
    void incrementMDIBVersion();

    Poco::Mutex & getMutex();
    
    void lock() {
    	getMutex().lock();
    }

    void unlock() {
    	getMutex().unlock();
    }    

    void setPeriodicEventInterval(const int seconds, const int milliseconds);
    std::vector<std::string> getHandlesForPeriodicUpdate();
    void addHandleForPeriodicEvent(const std::string & handle);
    void removeHandleForPeriodicEvent(const std::string & handle);

    /**
	* @brief Called on incoming consumer request for a state change.
	*
	* Notes:
	* - Can be overridden by a custom OSCP provider as an alternative to the usage of handlers.
	* - The consumer will wait for this method to complete.
	* - Make sure to update the state's invocation state and notify about the change.
	*
	* @param state The requested state containing fields to be updated.
	*
	* @return invocation state
	*/

	template<typename T>
		InvocationState onStateChangeRequest(const T & state, const OperationInvocationContext & oic);

// TODO no inheritance no need for protected methods..
protected:

    /**
    * @brief Notify all registered consumers about an operation invoked event (fires operation invoked event).
    *
    * @param object The MDIB object
    */
    void notifyOperationInvoked(const OperationInvocationContext & oic, Data::OSCP::InvocationState is);

private:
    void firePeriodicReportImpl(const std::vector<std::string> & handles);

    template<class T>
    void notifyAlertEventImpl(const T & object);
    template<class T>
    void notifyContextEventImpl(const T & object);
    template<class T>
	void notifyEpisodicMetricImpl(const T & object);

    template<class T>
    void createSetOperationForContextDescriptor(const T & descriptor, HydraMDSDescriptor & ownerMDS);

	CDM::SetValueResponse SetValueAsync(const CDM::SetValue & request);
    void SetValue(const CDM::SetValue & request, const OperationInvocationContext & oic);

    CDM::ActivateResponse OnActivateAsync(const CDM::Activate & request);
    void OnActivate(const OperationInvocationContext & oic);

    CDM::SetStringResponse SetStringAsync(const CDM::SetString & request);
    void SetString(const CDM::SetString & request, const OperationInvocationContext & oic);
    template<class T>
    void SetStringImpl(const T & state, const OperationInvocationContext & oic);

    CDM::SetAlertStateResponse SetAlertStateAsync(const CDM::SetAlertState & request);
    void SetAlertState(const CDM::SetAlertState & request, const OperationInvocationContext & oic);
    template<typename StateType>
    void SetAlertStateImpl(const StateType & state, const OperationInvocationContext & oic);

    CDM::GetMDIBResponse GetMDIB(const CDM::GetMDIB & request);
    CDM::GetMDDescriptionResponse GetMDDescription(const CDM::GetMDDescription & request);
    CDM::GetMDStateResponse GetMDState(const CDM::GetMDState & request);

    CDM::GetContextStatesResponse GetContextStates(const CDM::GetContextStates & request);
    CDM::SetContextStateResponse SetContextStateAsync(const CDM::SetContextState & request);
    void SetContextState(const CDM::SetContextState & request, const OperationInvocationContext & oic);

    template<class T>
    void addSetOperationToSCOObjectImpl(const T & source, HydraMDSDescriptor & ownerMDS);

    template<class T>
    void enqueueInvokeNotification(const T & request, const OperationInvocationContext & oic);

    unsigned int incrementAndGetTransactionId();
    std::atomic_uint atomicTransactionId;

    std::atomic_ullong mdibVersion;

    std::map<std::string, OSCPProviderMDStateHandler *> stateHandlers;

	std::shared_ptr<MDDescription> m_mdDescription;
    std::unique_ptr<OSELibProviderAdapter> _adapter;
    Dev::DeviceCharacteristics devicecharacteristics;
	Poco::Mutex mutex;

    std::string endpointReference;

	MDState mdibStates;
    MDState operationStates;
    Poco::NotificationQueue invokeQueue;
    std::shared_ptr<AsyncProviderInvoker> providerInvoker;

    std::vector<std::string> handlesForPeriodicUpdates;
    Poco::Timestamp lastPeriodicEvent;
    Poco::Timespan periodicEventInterval;
    
//    std::map<std::string, int> streamingPorts;

};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPPROVIDER_H_ */
