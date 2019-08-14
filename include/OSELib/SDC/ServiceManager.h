/*
 * ServiceManager.h
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 05.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_SERVICEMANAGER_H_
#define OSELIB_SDC_SERVICEMANAGER_H_


#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/DPWS/DeviceDescription.h"

#include "SDCLib/Prerequisites.h"

namespace OSELib
{
	namespace SDC
	{

		class HelloReceivedHandler {
		public:
			HelloReceivedHandler() = default;
			virtual ~HelloReceivedHandler() = default;

			virtual void helloReceived(const std::string & epr);
		};

		class ServiceManager final: public WithLogger
		{

		private:

			mutable std::mutex m_mutex;

			SDCLib::SDCInstance_shared_ptr m_SDCInstance = nullptr;
			std::unique_ptr<DPWS::MDPWSDiscoveryClientAdapter> _dpwsClient;

			// todo: kick this helloCallback. Supposedly it is not needed.
			std::unique_ptr<DPWS::HelloCallback> _helloCallback;


		public:

			ServiceManager(SDCLib::SDCInstance_shared_ptr p_SDCInstance);
			// Special Member Functions
			ServiceManager(const ServiceManager& p_obj) = delete;
			ServiceManager(ServiceManager&& p_obj) = delete;
			ServiceManager& operator=(const ServiceManager& p_obj) = delete;
			ServiceManager& operator=(ServiceManager&& p_obj) = delete;
			~ServiceManager();

			/**
			* @brief Set a handler that will be called when device send DPWS hello.
			*
			* @param handler The handler
			*/
			void setHelloReceivedHandler(HelloReceivedHandler * handler);

			/**
			* @brief Discover all SDC providers currently available
			*
			* @return List of all provider eprs
			*/
			std::vector<std::string> discoverEndpointReferences();

			/**
			* @brief Create a consumer and connect to Xaddr.
			*
			* @param p_xaddr The address
			* @return The consumer or nullptr
			*/
			std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> connect(const std::string & p_xaddr);

			/**
			* @brief Create a consumer and try to discover provider using endpointreference (EPR).
			*
			* @param p_epr The endpointreference
			* @return The consumer or null
			*/
			std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> discoverEndpointReference(const std::string & p_epr);

			/**
			* @brief Discover all SDC providers currently available
			*
			* @return List of all providers
			*/
			using DiscoverResults = std::vector<std::unique_ptr<SDCLib::Data::SDC::SDCConsumer>>;
			DiscoverResults discover();

			/**
			 * @deprecated Discover all SDC providers currently available in an async manner
			 *
			 * @return std::future of a list of all providers (DiscoverResults)
			 */
			using AsyncDiscoverResults  = std::future<DiscoverResults>;
			AsyncDiscoverResults async_discover();

		private:

			std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> connectXAddress(const SDCLib::StringVector& pl_xAddresses, const std::string & p_epr);
			void resolveServiceURIsFromMetadata(const WS::MEX::MetadataSection & metadata, OSELib::DPWS::DeviceDescription & deviceDescription);
		};

	} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_SERVICEMANAGER_H_ */
