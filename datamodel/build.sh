xsdcxx cxx-tree --show-sloc --type-naming ucc --generate-polymorphic --polymorphic-type-all --generate-forward --generate-serialization --hxx-suffix ".hxx" --cxx-suffix ".cxx" --ixx-suffix ".ixx" --namespace-map http://extension-point-uri/15/03=CDM --namespace-map http://domain-model-uri/15/04=CDM --namespace-map http://message-model-uri/15/04=CDM --namespace-map http://dicom-gateway-model-uri/15/04=CDM --std c++11 BICEPS_DomainModel.xsd BICEPS_MessageModel.xsd ExtensionPoint.xsd DICOMDeviceDescription.xsd

xsdcxx cxx-tree --show-sloc --type-naming ucc --generate-polymorphic --polymorphic-type-all --generate-forward --generate-wildcard --generate-serialization --hxx-suffix ".hxx" --cxx-suffix ".cxx" --ixx-suffix ".ixx" --namespace-map http://schemas.xmlsoap.org/wsdl/=WS::WSDL --namespace-map http://standardized.namespace.org/ws-streaming=WS::STREAMING --namespace-map http://www.w3.org/ns/ws-policy=WS::POLICY --namespace-map http://www.w3.org/2005/08/addressing=WS::ADDRESSING --namespace-map http://schemas.xmlsoap.org/wsdl/soap12/=WS::WSDL::SOAP_BINDING --namespace-map http://schemas.xmlsoap.org/ws/2004/08/eventing/=WS::EVENTING --std c++11 wsdl-custom.xsd ws-addressing.xsd ws-policy.xsd ws-streaming.xsd wsdl-soap-binding.xsd eventing.xsd

xsdcxx cxx-tree --show-sloc --type-naming ucc --generate-polymorphic --polymorphic-type-all --generate-forward --generate-serialization --hxx-suffix ".hxx" --cxx-suffix ".cxx" --ixx-suffix ".ixx" --namespace-map http://www.w3.org/2005/08/addressing=WS::ADDRESSING --namespace-map http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01=WS::DISCOVERY --namespace-map http://www.w3.org/2003/05/soap-envelope=WS::MESSAGEMODEL::DISCOVERY --std c++11 wsdd-discovery-1.1-schema-os.xsd MessageModel-Discovery.xsd
