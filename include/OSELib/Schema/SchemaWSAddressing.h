#ifndef SCHEMA_WSADDRESSING_H
#define SCHEMA_WSADDRESSING_H

#include <string.h>

namespace SCHEMA
{

const std::string SCHEMA_WSADDRESSING_NAME("WSAddressing.xsd");

const std::string SCHEMA_WSADDRESSING_CONTENT = std::string(R"(<?xml version="1.0" encoding="utf-8"?>
<!--
    W3C XML Schema defined in the Web Services Addressing 1.0 specification
    http://www.w3.org/TR/ws-addr-core

   Copyright © 2005 World Wide Web Consortium,

   (Massachusetts Institute of Technology, European Research Consortium for
   Informatics and Mathematics, Keio University). All Rights Reserved. This
   work is distributed under the W3C® Software License [1] in the hope that
   it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   [1] http://www.w3.org/Consortium/Legal/2002/copyright-software-20021231

   $Id: ws-addr.xsd,v 1.2 2008/07/23 13:38:16 plehegar Exp $
-->
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:tns="http://www.w3.org/2005/08/addressing" xmlns:wse="http://schemas.xmlsoap.org/ws/2004/08/eventing" targetNamespace="http://www.w3.org/2005/08/addressing" blockDefault="#all" elementFormDefault="qualified" finalDefault="" attributeFormDefault="unqualified">
	
	<xs:import namespace="http://schemas.xmlsoap.org/ws/2004/08/eventing" schemaLocation="eventing.xsd"/>
	
	<!-- Constructs from the WS-Addressing Core -->

	<xs:element name="EndpointReference" type="tns:EndpointReferenceType"/>
	<xs:complexType name="EndpointReferenceType" mixed="false">
		<xs:sequence>
			<xs:element name="Address" type="tns:AttributedURIType"/>
			<xs:element ref="tns:ReferenceParameters" minOccurs="0"/>
			<xs:element ref="tns:Metadata" minOccurs="0"/>
			<xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		</xs:sequence>
		<xs:anyAttribute namespace="##other" processContents="lax"/>
	</xs:complexType>
	
	<xs:element name="ReferenceParameters" type="tns:ReferenceParametersType"/>
	<xs:complexType name="ReferenceParametersType" mixed="false">
		<xs:sequence>
			<!-- Add Identifier for ws-eventing -->
			<xs:element ref="wse:Identifier" minOccurs="0" maxOccurs="1"/>
			<!-- <xs:any namespace="##any" processContents="lax" minOccurs="0" maxOccurs="unbounded"/> -->
		</xs:sequence>
		<xs:anyAttribute namespace="##other" processContents="lax"/>
	</xs:complexType>
	
	<xs:element name="Metadata" type="tns:MetadataType"/>
	<xs:complexType name="MetadataType" mixed="false">
		<xs:sequence>
			<xs:any namespace="##any" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		</xs:sequence>
		<xs:anyAttribute namespace="##other" processContents="lax"/>
	</xs:complexType>
	
	<xs:element name="MessageID" type="tns:AttributedURIType"/>
	<xs:element name="RelatesTo" type="tns:RelatesToType"/>
	<xs:complexType name="RelatesToType" mixed="false">
		<xs:simpleContent>
			<xs:extension base="xs:anyURI">
				<xs:attribute name="RelationshipType" type="tns:RelationshipTypeOpenEnum" use="optional" />
				<xs:anyAttribute namespace="##other" processContents="lax"/>
			</xs:extension>
		</xs:simpleContent>
	</xs:complexType>
	
	<xs:simpleType name="RelationshipTypeOpenEnum">
		<xs:union memberTypes="tns:RelationshipType xs:anyURI"/>
	</xs:simpleType>
	
	<xs:simpleType name="RelationshipType">
		<xs:restriction base="xs:anyURI">
			<xs:enumeration value="http://www.w3.org/2005/08/addressing/reply"/>
		</xs:restriction>
	</xs:simpleType>
	
	<xs:element name="ReplyTo" type="tns:EndpointReferenceType"/>
	<xs:element name="From" type="tns:EndpointReferenceType"/>
	<xs:element name="FaultTo" type="tns:EndpointReferenceType"/>
	<xs:element name="To" type="tns:AttributedURIType"/>
	<xs:element name="Action" type="tns:AttributedURIType"/>

	<xs:attribute name="Action" type="xs:anyURI" />

	<xs:complexType name="AttributedURIType" mixed="false">
		<xs:simpleContent>
			<xs:extension base="xs:anyURI">
				<xs:anyAttribute namespace="##other" processContents="lax"/>
			</xs:extension>
		</xs:simpleContent>
	</xs:complexType>
	
	<!-- Constructs from the WS-Addressing SOAP binding -->

	<xs:attribute name="IsReferenceParameter" type="xs:boolean"/>
	
	<xs:simpleType name="FaultCodesOpenEnumType">
		<xs:union memberTypes="tns:FaultCodesType xs:QName"/>
	</xs:simpleType>
	
	<xs:simpleType name="FaultCodesType">
		<xs:restriction base="xs:QName">
			<xs:enumeration value="tns:InvalidAddressingHeader"/>
			<xs:enumeration value="tns:InvalidAddress"/>
			<xs:enumeration value="tns:InvalidEPR"/>
			<xs:enumeration value="tns:InvalidCardinality"/>
			<xs:enumeration value="tns:MissingAddressInEPR"/>
			<xs:enumeration value="tns:DuplicateMessageID"/>
			<xs:enumeration value="tns:ActionMismatch"/>
			<xs:enumeration value="tns:MessageAddressingHeaderRequired"/>
			<xs:enumeration value="tns:DestinationUnreachable"/>
			<xs:enumeration value="tns:ActionNotSupported"/>
			<xs:enumeration value="tns:EndpointUnavailable"/>
		</xs:restriction>
	</xs:simpleType>
	
	<xs:element name="RetryAfter" type="tns:AttributedUnsignedLongType"/>
	<xs:complexType name="AttributedUnsignedLongType" mixed="false">
		<xs:simpleContent>
			<xs:extension base="xs:unsignedLong">
				<xs:anyAttribute namespace="##other" processContents="lax"/>
			</xs:extension>
		</xs:simpleContent>
	</xs:complexType>
	
	<xs:element name="ProblemHeaderQName" type="tns:AttributedQNameType"/>
	<xs:complexType name="AttributedQNameType" mixed="false">
		<xs:simpleContent>
			<xs:extension base="xs:QName">
				<xs:anyAttribute namespace="##other" processContents="lax"/>
			</xs:extension>
		</xs:simpleContent>
	</xs:complexType>
	
	<xs:element name="ProblemIRI" type="tns:AttributedURIType"/>
	
	<xs:element name="ProblemAction" type="tns:ProblemActionType"/>
	<xs:complexType name="ProblemActionType" mixed="false">
		<xs:sequence>
			<xs:element ref="tns:Action" minOccurs="0"/>
			<xs:element name="SoapAction" minOccurs="0" type="xs:anyURI"/>
		</xs:sequence>
		<xs:anyAttribute namespace="##other" processContents="lax"/>
	</xs:complexType>
	
</xs:schema>)");

}
#endif
