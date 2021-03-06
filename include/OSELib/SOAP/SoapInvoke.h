/*
 * SoapInvoke.h
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 26.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_SOAPINVOKE_H_
#define OSELIB_SOAP_SOAPINVOKE_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/URI.h>
#include <Poco/Net/Context.h>


namespace OSELib
{
    namespace SOAP
    {
        class SoapInvoke : public OSELib::Helper::WithLogger
        {
        private:
            const Poco::URI m_requestURI;
            OSELib::Helper::XercesGrammarPoolProvider& m_grammarProvider;

        public:
            // Special Member Functions
            SoapInvoke(const Poco::URI & p_requestURI, OSELib::Helper::XercesGrammarPoolProvider & p_grammarProvider);
            SoapInvoke(const SoapInvoke& p_obj) = delete;
            SoapInvoke(SoapInvoke&& p_obj) = delete;
            SoapInvoke& operator=(const SoapInvoke& p_obj) = delete;
            SoapInvoke& operator=(SoapInvoke&& p_obj) = delete;
            virtual ~SoapInvoke() = default;

            virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader();
            virtual std::unique_ptr<MESSAGEMODEL::Body> createBody();
            virtual std::unique_ptr<MESSAGEMODEL::Envelope> createMessage();

            // Plain Invoke
            virtual std::unique_ptr<MESSAGEMODEL::Envelope> invoke(std::unique_ptr<MESSAGEMODEL::Envelope> p_invokeMessage);
            // SSL Invoke
            virtual std::unique_ptr<MESSAGEMODEL::Envelope> invoke(std::unique_ptr<MESSAGEMODEL::Envelope> p_invokeMessage, Poco::Net::Context::Ptr p_context);
        };

    }
}

#endif
