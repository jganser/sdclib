
	template <class MdsDescriptor>
	void addMdsDescriptor(const MdsDescriptor & source);
	template <class MdsDescriptor>
	bool removeMdsDescriptor(const MdsDescriptor & object);

	bool getFirstMdsDescriptor(MdsDescriptor & outDescriptor) const;

	// use this API method to get a copy of the MDIB's descriptors
	template<class TDescriptor>
	std::unique_ptr<TDescriptor> findDescriptor(const std::string & handle) const;

	std::string getOperationTargetForOperationHandle(const std::string & operationHandle) const;
	std::string getFirstOperationHandleForOperationTarget(const std::string & operationTarget) const;

	std::vector<AlertConditionDescriptor> collectAllAlertConditionDescriptors() const;
	std::vector<AlertSignalDescriptor> collectAllAlertSignalDescriptors() const;
	std::vector<AlertSystemDescriptor> collectAllAlertSystemDescriptors() const;
	std::vector<LimitAlertConditionDescriptor> collectAllLimitAlertConditionDescriptors() const;

	std::vector<ChannelDescriptor> collectAllChannelDescriptors() const;
	std::vector<ClockDescriptor> collectAllClockDescriptors() const;
	std::vector<DicomDeviceDescriptor> collectAllDicomDeviceDescriptors() const;
	std::vector<EnumStringMetricDescriptor> collectAllEnumStringMetricDescriptors() const;
	std::vector<MdsDescriptor> collectAllMdsDescriptors() const;
	std::vector<NumericMetricDescriptor> collectAllNumericMetricDescriptors() const;
	std::vector<RealTimeSampleArrayMetricDescriptor> collectAllRealTimeSampleArrayMetricDescriptors() const;
	std::vector<StringMetricDescriptor> collectAllStringMetricDescriptors() const;
	std::vector<ActivateOperationDescriptor> collectAllActivateOperationDescriptors() const;
	std::vector<VmdDescriptor> collectAllVmdDescriptors() const;

private:
	// historical atavisms: those functions are used inside the framework
	// API use the unique_ptr returning methods
	bool findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, ChannelDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, ClockDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, EnsembleContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, MdsDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, LocationContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, OperatorContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, PatientContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, VmdDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, WorkflowContextDescriptor & outDescriptor) const;

	template <class WrapperMetricDescriptorType>
	bool findMetricDescriptorImpl(const std::string & handle, WrapperMetricDescriptorType & out) const;

	template <class WrapperMetricDescriptorType>
	void collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const;
	template <class WrapperMetricDescriptorType, class ForbiddenType>
	void collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const;
