/* File : OSCLib.i fff*/
%module(directors="1") OSCLib

/*%typemap(csclassmodifiers) SWIGTYPE "public partial class"*/

%{
#include "osdm.hxx"

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionReference.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/Annotation.h"
#include "OSCLib/Data/OSCP/MDIB/Base64Binary.h"
#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CauseInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkAE.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/MDIB/EnumNomenRef.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/Language.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MDIBContainer.h"
#include "OSCLib/Data/OSCP/MDIB/MDIB-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/MDState.h"
#include "OSCLib/Data/OSCP/MDIB/Measure.h"
#include "OSCLib/Data/OSCP/MDIB/MeasurementState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/OperationState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/OrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/Order.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/PersonParticipation.h"
#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/RemedyInfo.h"
#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"
#include "OSCLib/Data/OSCP/MDIB/SampleIndex.h"
#include "OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetContextOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetRangeOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/TimeZone.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/FutureInvocationState.h"
#include "OSCLib/Data/OSCP/OSCPCachedProvider.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerContextStateChangedHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerLimitAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerSubscriptionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderActivateOperationHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderClockStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderComponentStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderContextStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderLimitAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPServiceManager.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"

using namespace std;
using namespace OSCLib;
using namespace OSCLib::Cli;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

%}

%feature("director") OSCPCachedProvider;
%feature("director") OSCPConsumerEventHandler;
%feature("director") OSCPConsumerAlertConditionStateHandler;
%feature("director") OSCPConsumerAlertSignalStateHandler;
%feature("director") OSCPConsumerAlertSystemStateHandler;
%feature("director") OSCPConsumerConnectionLostHandler;
%feature("director") OSCPConsumerContextStateChangedHandler;
%feature("director") OSCPConsumerEnumStringMetricStateHandler;
%feature("director") OSCPConsumerLimitAlertConditionStateHandler;
%feature("director") OSCPConsumerNumericMetricStateHandler;
%feature("director") OSCPConsumerRealTimeSampleArrayMetricStateHandler;
%feature("director") OSCPConsumerStringMetricStateHandler;
%feature("director") OSCPHelloReceivedHandler;
%feature("director") OSCPSubscriptionLostHandler;
%feature("director") OSCPProviderMDStateHandler;
%feature("director") OSCPProviderActivateOperationHandler;
%feature("director") OSCPProviderAlertConditionStateHandler;
%feature("director") OSCPProviderAlertSignalStateHandler;
%feature("director") OSCPProviderAlertSystemStateHandler;
%feature("director") OSCPProviderClockStateHandler;
%feature("director") OSCPProviderComponentStateHandler;
%feature("director") OSCPProviderContextStateHandler;
%feature("director") OSCPProviderEnumStringMetricStateHandler;
%feature("director") OSCPProvider;
%feature("director") OSCPProviderHydraMDSStateHandler;
%feature("director") OSCPProviderLimitAlertConditionStateHandler;
%feature("director") OSCPProviderNumericMetricStateHandler;
%feature("director") OSCPProviderRealTimeSampleArrayMetricStateHandler;
%feature("director") OSCPProviderStringMetricStateHandler;

/* java specific */
%include "arrays_java.i"

/* common */
%include "std_auto_ptr.i"
%include "std_common.i"
%include "std_deque.i"
%include "std_except.i"
%include "std_map.i"
%include "std_pair.i"
%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_wstring.i"
%include "typemaps.i"
%include "wchar.i"

%shared_ptr(OSCLib::Data::OSCP::OSCPConsumer)

%template(CharVector) std::vector<char>;
%template(DoubleVector) std::vector<double>;
%template(StringVector) std::vector<std::string>;

%template(OSCPConsumerVector) std::vector<std::shared_ptr<OSCLib::Data::OSCP::OSCPConsumer>>;

%template(CodedValueVector) std::vector<OSCLib::Data::OSCP::CodedValue>;
%template(LocalizedTextVector) std::vector<OSCLib::Data::OSCP::LocalizedText>;

%template(ChannelDescriptorVector) std::vector<OSCLib::Data::OSCP::ChannelDescriptor>;
%template(HydraMDSDescriptorVector) std::vector<OSCLib::Data::OSCP::HydraMDSDescriptor>;
%template(VMDDescriptorVector) std::vector<OSCLib::Data::OSCP::VMDDescriptor>;

%template(ActivateOperationDescriptorVector) std::vector<OSCLib::Data::OSCP::ActivateOperationDescriptor>;
%template(AlertConditionDescriptorVector) std::vector<OSCLib::Data::OSCP::AlertConditionDescriptor>;
%template(AlertConditionStateVector) std::vector<OSCLib::Data::OSCP::AlertConditionState>;
%template(AlertSignalDescriptorVector) std::vector<OSCLib::Data::OSCP::AlertSignalDescriptor>;
%template(AlertSignalStateVector) std::vector<OSCLib::Data::OSCP::AlertSignalState>;
%template(AlertSystemDescriptorVector) std::vector<OSCLib::Data::OSCP::AlertSystemDescriptor>;
%template(AlertSystemStateVector) std::vector<OSCLib::Data::OSCP::AlertSystemState>;
%template(AnnotationVector) std::vector<OSCLib::Data::OSCP::Annotation>;
%template(Base64BinaryVector) std::vector<OSCLib::Data::OSCP::Base64Binary>;
%template(BaseDemographicsVector) std::vector<OSCLib::Data::OSCP::BaseDemographics>;
%template(CauseInfoVector) std::vector<OSCLib::Data::OSCP::CauseInfo>;
%template(ClinicalInfoVector) std::vector<OSCLib::Data::OSCP::ClinicalInfo>;
%template(ClockDescriptorVector) std::vector<OSCLib::Data::OSCP::ClockDescriptor>;
%template(ClockStateVector) std::vector<OSCLib::Data::OSCP::ClockState>;
%template(ComponentStateVector) std::vector<OSCLib::Data::OSCP::ComponentState>;
%template(DICOMDeviceDescriptorVector) std::vector<OSCLib::Data::OSCP::DICOMDeviceDescriptor>;
%template(DICOMNetworkAEVector) std::vector<OSCLib::Data::OSCP::DICOMNetworkAE>;
%template(DICOMNetworkConnectionVector) std::vector<OSCLib::Data::OSCP::DICOMNetworkConnection>;
%template(DICOMTransferCapabilityVector) std::vector<OSCLib::Data::OSCP::DICOMTransferCapability>;
%template(EnsembleContextStateVector) std::vector<OSCLib::Data::OSCP::EnsembleContextState>;
%template(EnumNomenRefVector) std::vector<OSCLib::Data::OSCP::EnumNomenRef>;
%template(EnumStringMetricDescriptorVector) std::vector<OSCLib::Data::OSCP::EnumStringMetricDescriptor>;
%template(EnumStringMetricStateVector) std::vector<OSCLib::Data::OSCP::EnumStringMetricState>;
%template(HydraMDSStateVector) std::vector<OSCLib::Data::OSCP::HydraMDSState>;
%template(ImagingProcedureVector) std::vector<OSCLib::Data::OSCP::ImagingProcedure>;
%template(InstanceIdentifierVector) std::vector<OSCLib::Data::OSCP::InstanceIdentifier>;
%template(LimitAlertConditionDescriptorVector) std::vector<OSCLib::Data::OSCP::LimitAlertConditionDescriptor>;
%template(LimitAlertConditionStateVector) std::vector<OSCLib::Data::OSCP::LimitAlertConditionState>;
%template(LocationContextStateVector) std::vector<OSCLib::Data::OSCP::LocationContextState>;
%template(MeasureVector) std::vector<OSCLib::Data::OSCP::Measure>;
%template(NumericMetricDescriptorVector) std::vector<OSCLib::Data::OSCP::NumericMetricDescriptor>;
%template(NumericMetricStateVector) std::vector<OSCLib::Data::OSCP::NumericMetricState>;
%template(OperatorContextStateVector) std::vector<OSCLib::Data::OSCP::OperatorContextState>;
%template(PatientContextStateVector) std::vector<OSCLib::Data::OSCP::PatientContextState>;
%template(PersonParticipationVector) std::vector<OSCLib::Data::OSCP::PersonParticipation>;
%template(ProductionSpecificationVector) std::vector<OSCLib::Data::OSCP::ProductionSpecification>;
%template(RangeVector) std::vector<OSCLib::Data::OSCP::Range>;
%template(RealTimeSampleArrayMetricDescriptorVector) std::vector<OSCLib::Data::OSCP::RealTimeSampleArrayMetricDescriptor>;
%template(RealTimeSampleArrayMetricStateVector) std::vector<OSCLib::Data::OSCP::RealTimeSampleArrayMetricState>;
%template(SetAlertStateOperationDescriptorVector) std::vector<OSCLib::Data::OSCP::SetAlertStateOperationDescriptor>;
%template(SetContextOperationDescriptorVector) std::vector<OSCLib::Data::OSCP::SetContextOperationDescriptor>;
%template(SetRangeOperationDescriptorVector) std::vector<OSCLib::Data::OSCP::SetRangeOperationDescriptor>;
%template(SetStringOperationDescriptorVector) std::vector<OSCLib::Data::OSCP::SetStringOperationDescriptor>;
%template(SetValueOperationDescriptorVector) std::vector<OSCLib::Data::OSCP::SetValueOperationDescriptor>;
%template(StringMetricDescriptorVector) std::vector<OSCLib::Data::OSCP::StringMetricDescriptor>;
%template(StringMetricStateVector) std::vector<OSCLib::Data::OSCP::StringMetricState>;
%template(WorkflowContextStateVector) std::vector<OSCLib::Data::OSCP::WorkflowContextState>;

%apply double * INOUT{double * d}

/* Let's just grab the original header file here */

%include "../include/OSCLib/OSCLibrary.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/AlertConditionReference.h"
%include "../include/OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Annotation.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Base64Binary.h"
%include "../include/OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
%include "../include/OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
%include "../include/OSCLib/Data/OSCP/MDIB/CauseInfo.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ClockState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/CodedValue.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ComponentState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/DateTime.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Defaults.h"
%include "../include/OSCLib/Data/OSCP/MDIB/DICOMDeviceDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/DICOMNetworkAE.h"
%include "../include/OSCLib/Data/OSCP/MDIB/DICOMNetworkConnection.h"
%include "../include/OSCLib/Data/OSCP/MDIB/DICOMTransferCapability.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Duration.h"
%include "../include/OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/EnumMappings.h"
%include "../include/OSCLib/Data/OSCP/MDIB/EnumNomenRef.h"
%include "../include/OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
%include "../include/OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Language.h"
%include "../include/OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/LocalizedText.h"
%include "../include/OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/LocationContextState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/MDDescription.h"
%include "../include/OSCLib/Data/OSCP/MDIB/MDIBContainer.h"
%include "../include/OSCLib/Data/OSCP/MDIB/MDIB-fwd.h"
%include "../include/OSCLib/Data/OSCP/MDIB/MDState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Measure.h"
%include "../include/OSCLib/Data/OSCP/MDIB/MeasurementState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
%include "../include/OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
%include "../include/OSCLib/Data/OSCP/MDIB/OperationState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/OrderDetail.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Order.h"
%include "../include/OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/PatientContextState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
%include "../include/OSCLib/Data/OSCP/MDIB/PersonParticipation.h"
%include "../include/OSCLib/Data/OSCP/MDIB/PersonReference.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Range.h"
%include "../include/OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
%include "../include/OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
%include "../include/OSCLib/Data/OSCP/MDIB/RemedyInfo.h"
%include "../include/OSCLib/Data/OSCP/MDIB/RTValueType.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SampleIndex.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SetContextOperationDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SetRangeOperationDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/StringMetricState.h"
%include "../include/OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SystemContext.h"
%include "../include/OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
%include "../include/OSCLib/Data/OSCP/MDIB/Timestamp.h"
%include "../include/OSCLib/Data/OSCP/MDIB/TimeZone.h"
%include "../include/OSCLib/Data/OSCP/MDIB/VersionCounter.h"
%include "../include/OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
%include "../include/OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
%include "../include/OSCLib/Data/OSCP/FutureInvocationState.h"
%include "../include/OSCLib/Data/OSCP/OSCPCachedProvider.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerAlertConditionStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerAlertSignalStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerAlertSystemStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerContextStateChangedHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerEnumStringMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumer.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerLimitAlertConditionStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerRealTimeSampleArrayMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerStringMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPConsumerSubscriptionLostHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderActivateOperationHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderAlertConditionStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderAlertSignalStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderAlertSystemStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderClockStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderComponentStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderContextStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderEnumStringMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProvider.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderLimitAlertConditionStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderRealTimeSampleArrayMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPProviderStringMetricStateHandler.h"
%include "../include/OSCLib/Data/OSCP/OSCPServiceManager.h"
%include "../include/OSCLib/Dev/DeviceCharacteristics.h"
%include "../include/OSCLib/Util/DebugOut.h"

using namespace std;
using namespace OSCLib;
using namespace OSCLib::Cli;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;