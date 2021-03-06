/*
 * MessageAdapter.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/MessageAdapter.h"

#include "DataModel/wsdd-discovery-1.1-schema-os.hxx"

namespace OSELib {
namespace DPWS {

template<class Message>
AddressType MessageAdapter::EPRAddress(const Message & p_message) {
	return p_message.getEndpointReference().getAddress();
}

template<class Message>
MetadataVersionType MessageAdapter::MetadataVersion(const Message & p_message) {
	return p_message.getMetadataVersion();
}

template<class Message>
XAddressesType MessageAdapter::XAddresses(const Message & p_message) {
	if (p_message.getXAddrs().present()) {
		return p_message.getXAddrs().get();
	} else {
		return XAddressesType();
	}
	// FIXME: Return the "else par" here?!
}

template<class Message>
ScopesType MessageAdapter::Scopes(const Message & p_message) {
	if (p_message.getScopes().present()) {
		return p_message.getScopes().get();
	} else {
		return ScopesType();
	}
	// FIXME: Return the "else par" here?!
}

template<class Message>
TypesType MessageAdapter::Types(const Message & p_message) {
	if (p_message.getTypes().present()) {
		return p_message.getTypes().get();
	} else {
		return TypesType();
	}
	// FIXME: Return the "else par" here?!
}

UriType MessageAdapter::URI(const QName & p_qname) {
	return p_qname.namespace_();
}

std::string MessageAdapter::LocalName(const QName & p_qname) {
	return p_qname.name();
}

template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ByeType & p_message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::HelloType & p_message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ProbeType & p_message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ProbeMatchType & p_message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ResolveMatchType & p_message);

template TypesType MessageAdapter::Types(const WS::DISCOVERY::ByeType & p_message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::HelloType & p_message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::ProbeType & p_message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::ProbeMatchType & p_message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::ResolveMatchType & p_message);

template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::ByeType & p_message);
template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::HelloType & p_message);
template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::ProbeMatchType & p_message);
template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::ResolveMatchType & p_message);

template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ByeType & p_message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::HelloType & p_message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ResolveType & p_message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ResolveMatchType & p_message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ProbeMatchType & p_message);

template MetadataVersionType MessageAdapter::MetadataVersion(const WS::DISCOVERY::HelloType & p_message);
template MetadataVersionType MessageAdapter::MetadataVersion(const WS::DISCOVERY::ProbeMatchType & p_message);
template MetadataVersionType MessageAdapter::MetadataVersion(const WS::DISCOVERY::ResolveMatchType & p_message);

}
}
