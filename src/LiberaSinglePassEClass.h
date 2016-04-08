/*----- PROTECTED REGION ID(LiberaSinglePassEClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        LiberaSinglePassEClass.h
//
// description : Include for the LiberaSinglePassEClass root class.
//               This class is the singleton class for.
//               the LiberaSinglePassE device class..
//               It contains all properties and methods which the .
//               LiberaSinglePassE requires only once e.g. the commands.
//
// project :     Libera Brillance Single Pass E.
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL:  $
//
// CVS only:
// $Source:  $
// $Log:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef LIBERASINGLEPASSECLASS_H
#define LIBERASINGLEPASSECLASS_H

#include <tango.h>
#include <LiberaSinglePassE.h>

/*----- PROTECTED REGION END -----*/	//	LiberaSinglePassEClass.h


namespace LiberaSinglePassE_ns
{
/*----- PROTECTED REGION ID(LiberaSinglePassEClass::classes for dynamic creation) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	LiberaSinglePassEClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute ADCBufferSize class definition
class ADCBufferSizeAttrib: public Tango::Attr
{
public:
	ADCBufferSizeAttrib():Attr("ADCBufferSize",
			Tango::DEV_LONG, Tango::READ_WRITE) {};
	~ADCBufferSizeAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_ADCBufferSize(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_ADCBufferSize(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_ADCBufferSize_allowed(ty);}
};

//	Attribute TriggerCounter class definition
class TriggerCounterAttrib: public Tango::Attr
{
public:
	TriggerCounterAttrib():Attr("TriggerCounter",
			Tango::DEV_ULONG64, Tango::READ) {};
	~TriggerCounterAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_TriggerCounter(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_TriggerCounter_allowed(ty);}
};

//	Attribute Fan1Speed class definition
class Fan1SpeedAttrib: public Tango::Attr
{
public:
	Fan1SpeedAttrib():Attr("Fan1Speed",
			Tango::DEV_USHORT, Tango::READ) {};
	~Fan1SpeedAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Fan1Speed(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Fan1Speed_allowed(ty);}
};

//	Attribute Fan2Speed class definition
class Fan2SpeedAttrib: public Tango::Attr
{
public:
	Fan2SpeedAttrib():Attr("Fan2Speed",
			Tango::DEV_USHORT, Tango::READ) {};
	~Fan2SpeedAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Fan2Speed(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Fan2Speed_allowed(ty);}
};

//	Attribute Temp1 class definition
class Temp1Attrib: public Tango::Attr
{
public:
	Temp1Attrib():Attr("Temp1",
			Tango::DEV_USHORT, Tango::READ) {};
	~Temp1Attrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Temp1(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Temp1_allowed(ty);}
};

//	Attribute Temp2 class definition
class Temp2Attrib: public Tango::Attr
{
public:
	Temp2Attrib():Attr("Temp2",
			Tango::DEV_USHORT, Tango::READ) {};
	~Temp2Attrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Temp2(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Temp2_allowed(ty);}
};

//	Attribute Temp3 class definition
class Temp3Attrib: public Tango::Attr
{
public:
	Temp3Attrib():Attr("Temp3",
			Tango::DEV_USHORT, Tango::READ) {};
	~Temp3Attrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Temp3(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Temp3_allowed(ty);}
};

//	Attribute Calibration_ka class definition
class Calibration_kaAttrib: public Tango::Attr
{
public:
	Calibration_kaAttrib():Attr("Calibration_ka",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Calibration_kaAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Calibration_ka(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Calibration_ka(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Calibration_ka_allowed(ty);}
};

//	Attribute Calibration_kb class definition
class Calibration_kbAttrib: public Tango::Attr
{
public:
	Calibration_kbAttrib():Attr("Calibration_kb",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Calibration_kbAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Calibration_kb(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Calibration_kb(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Calibration_kb_allowed(ty);}
};

//	Attribute Calibration_kc class definition
class Calibration_kcAttrib: public Tango::Attr
{
public:
	Calibration_kcAttrib():Attr("Calibration_kc",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Calibration_kcAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Calibration_kc(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Calibration_kc(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Calibration_kc_allowed(ty);}
};

//	Attribute Calibration_kd class definition
class Calibration_kdAttrib: public Tango::Attr
{
public:
	Calibration_kdAttrib():Attr("Calibration_kd",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Calibration_kdAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Calibration_kd(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Calibration_kd(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Calibration_kd_allowed(ty);}
};

//	Attribute Linear_x_k class definition
class Linear_x_kAttrib: public Tango::Attr
{
public:
	Linear_x_kAttrib():Attr("Linear_x_k",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_x_kAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_x_k(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_x_k(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_x_k_allowed(ty);}
};

//	Attribute Linear_x_offs class definition
class Linear_x_offsAttrib: public Tango::Attr
{
public:
	Linear_x_offsAttrib():Attr("Linear_x_offs",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_x_offsAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_x_offs(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_x_offs(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_x_offs_allowed(ty);}
};

//	Attribute Linear_y_k class definition
class Linear_y_kAttrib: public Tango::Attr
{
public:
	Linear_y_kAttrib():Attr("Linear_y_k",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_y_kAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_y_k(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_y_k(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_y_k_allowed(ty);}
};

//	Attribute Linear_y_offs class definition
class Linear_y_offsAttrib: public Tango::Attr
{
public:
	Linear_y_offsAttrib():Attr("Linear_y_offs",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_y_offsAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_y_offs(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_y_offs(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_y_offs_allowed(ty);}
};

//	Attribute Linear_q_k class definition
class Linear_q_kAttrib: public Tango::Attr
{
public:
	Linear_q_kAttrib():Attr("Linear_q_k",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_q_kAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_q_k(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_q_k(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_q_k_allowed(ty);}
};

//	Attribute Linear_q_offs class definition
class Linear_q_offsAttrib: public Tango::Attr
{
public:
	Linear_q_offsAttrib():Attr("Linear_q_offs",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_q_offsAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_q_offs(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_q_offs(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_q_offs_allowed(ty);}
};

//	Attribute Linear_sum_k class definition
class Linear_sum_kAttrib: public Tango::Attr
{
public:
	Linear_sum_kAttrib():Attr("Linear_sum_k",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_sum_kAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_sum_k(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_sum_k(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_sum_k_allowed(ty);}
};

//	Attribute Linear_sum_offs class definition
class Linear_sum_offsAttrib: public Tango::Attr
{
public:
	Linear_sum_offsAttrib():Attr("Linear_sum_offs",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Linear_sum_offsAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Linear_sum_offs(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Linear_sum_offs(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Linear_sum_offs_allowed(ty);}
};

//	Attribute Signal_expansion class definition
class Signal_expansionAttrib: public Tango::Attr
{
public:
	Signal_expansionAttrib():Attr("Signal_expansion",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Signal_expansionAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Signal_expansion(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Signal_expansion(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Signal_expansion_allowed(ty);}
};

//	Attribute Interlock_enabled class definition
class Interlock_enabledAttrib: public Tango::Attr
{
public:
	Interlock_enabledAttrib():Attr("Interlock_enabled",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~Interlock_enabledAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Interlock_enabled(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Interlock_enabled(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Interlock_enabled_allowed(ty);}
};

//	Attribute Limit_min_x class definition
class Limit_min_xAttrib: public Tango::Attr
{
public:
	Limit_min_xAttrib():Attr("Limit_min_x",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Limit_min_xAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Limit_min_x(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Limit_min_x(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Limit_min_x_allowed(ty);}
};

//	Attribute Limit_min_y class definition
class Limit_min_yAttrib: public Tango::Attr
{
public:
	Limit_min_yAttrib():Attr("Limit_min_y",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Limit_min_yAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Limit_min_y(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Limit_min_y(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Limit_min_y_allowed(ty);}
};

//	Attribute Limit_max_x class definition
class Limit_max_xAttrib: public Tango::Attr
{
public:
	Limit_max_xAttrib():Attr("Limit_max_x",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Limit_max_xAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Limit_max_x(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Limit_max_x(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Limit_max_x_allowed(ty);}
};

//	Attribute Limit_max_y class definition
class Limit_max_yAttrib: public Tango::Attr
{
public:
	Limit_max_yAttrib():Attr("Limit_max_y",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~Limit_max_yAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Limit_max_y(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Limit_max_y(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Limit_max_y_allowed(ty);}
};

//	Attribute Overflow_threshold class definition
class Overflow_thresholdAttrib: public Tango::Attr
{
public:
	Overflow_thresholdAttrib():Attr("Overflow_threshold",
			Tango::DEV_ULONG, Tango::READ_WRITE) {};
	~Overflow_thresholdAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Overflow_threshold(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Overflow_threshold(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Overflow_threshold_allowed(ty);}
};

//	Attribute Interlock_status class definition
class Interlock_statusAttrib: public Tango::Attr
{
public:
	Interlock_statusAttrib():Attr("Interlock_status",
			Tango::DEV_ULONG, Tango::READ) {};
	~Interlock_statusAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Interlock_status(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Interlock_status_allowed(ty);}
};

//	Attribute Status_x class definition
class Status_xAttrib: public Tango::Attr
{
public:
	Status_xAttrib():Attr("Status_x",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~Status_xAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Status_x(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Status_x_allowed(ty);}
};

//	Attribute Status_y class definition
class Status_yAttrib: public Tango::Attr
{
public:
	Status_yAttrib():Attr("Status_y",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~Status_yAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Status_y(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Status_y_allowed(ty);}
};

//	Attribute Status_adc_overflow class definition
class Status_adc_overflowAttrib: public Tango::Attr
{
public:
	Status_adc_overflowAttrib():Attr("Status_adc_overflow",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~Status_adc_overflowAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Status_adc_overflow(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Status_adc_overflow_allowed(ty);}
};

//	Attribute X class definition
class XAttrib: public Tango::Attr
{
public:
	XAttrib():Attr("X",
			Tango::DEV_DOUBLE, Tango::READ) {};
	~XAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_X(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_X_allowed(ty);}
};

//	Attribute Y class definition
class YAttrib: public Tango::Attr
{
public:
	YAttrib():Attr("Y",
			Tango::DEV_DOUBLE, Tango::READ) {};
	~YAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Y(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Y_allowed(ty);}
};

//	Attribute Sum class definition
class SumAttrib: public Tango::Attr
{
public:
	SumAttrib():Attr("Sum",
			Tango::DEV_DOUBLE, Tango::READ) {};
	~SumAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Sum(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Sum_allowed(ty);}
};

//	Attribute EnableADC class definition
class EnableADCAttrib: public Tango::Attr
{
public:
	EnableADCAttrib():Attr("EnableADC",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~EnableADCAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_EnableADC(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_EnableADC(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_EnableADC_allowed(ty);}
};

//	Attribute Q class definition
class QAttrib: public Tango::Attr
{
public:
	QAttrib():Attr("Q",
			Tango::DEV_DOUBLE, Tango::READ) {};
	~QAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Q(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Q_allowed(ty);}
};

//	Attribute External_trigger_delay class definition
class External_trigger_delayAttrib: public Tango::Attr
{
public:
	External_trigger_delayAttrib():Attr("External_trigger_delay",
			Tango::DEV_ULONG, Tango::READ_WRITE) {};
	~External_trigger_delayAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_External_trigger_delay(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_External_trigger_delay(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_External_trigger_delay_allowed(ty);}
};

//	Attribute Attenuation_id class definition
class Attenuation_idAttrib: public Tango::Attr
{
public:
	Attenuation_idAttrib():Attr("Attenuation_id",
			Tango::DEV_SHORT, Tango::READ_WRITE) {};
	~Attenuation_idAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Attenuation_id(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Attenuation_id(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Attenuation_id_allowed(ty);}
};

//	Attribute Attenuation_mode class definition
class Attenuation_modeAttrib: public Tango::Attr
{
public:
	Attenuation_modeAttrib():Attr("Attenuation_mode",
			Tango::DEV_SHORT, Tango::READ_WRITE) {};
	~Attenuation_modeAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Attenuation_mode(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Attenuation_mode(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Attenuation_mode_allowed(ty);}
};

//	Attribute Bunch_Threshold class definition
class Bunch_ThresholdAttrib: public Tango::Attr
{
public:
	Bunch_ThresholdAttrib():Attr("Bunch_Threshold",
			Tango::DEV_ULONG, Tango::READ_WRITE) {};
	~Bunch_ThresholdAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_Bunch_Threshold(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->write_Bunch_Threshold(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_Bunch_Threshold_allowed(ty);}
};

//	Attribute ADCChannelA class definition
class ADCChannelAAttrib: public Tango::SpectrumAttr
{
public:
	ADCChannelAAttrib():SpectrumAttr("ADCChannelA",
			Tango::DEV_SHORT, Tango::READ, 10000) {};
	~ADCChannelAAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_ADCChannelA(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_ADCChannelA_allowed(ty);}
};

//	Attribute ADCChannelB class definition
class ADCChannelBAttrib: public Tango::SpectrumAttr
{
public:
	ADCChannelBAttrib():SpectrumAttr("ADCChannelB",
			Tango::DEV_SHORT, Tango::READ, 10000) {};
	~ADCChannelBAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_ADCChannelB(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_ADCChannelB_allowed(ty);}
};

//	Attribute ADCChannelC class definition
class ADCChannelCAttrib: public Tango::SpectrumAttr
{
public:
	ADCChannelCAttrib():SpectrumAttr("ADCChannelC",
			Tango::DEV_SHORT, Tango::READ, 10000) {};
	~ADCChannelCAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_ADCChannelC(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_ADCChannelC_allowed(ty);}
};

//	Attribute ADCChannelD class definition
class ADCChannelDAttrib: public Tango::SpectrumAttr
{
public:
	ADCChannelDAttrib():SpectrumAttr("ADCChannelD",
			Tango::DEV_SHORT, Tango::READ, 10000) {};
	~ADCChannelDAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<LiberaSinglePassE *>(dev))->read_ADCChannelD(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<LiberaSinglePassE *>(dev))->is_ADCChannelD_allowed(ty);}
};


//=========================================
//	Define classes for commands
//=========================================
//	Command Reset class definition
class ResetClass : public Tango::Command
{
public:
	ResetClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	ResetClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~ResetClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<LiberaSinglePassE *>(dev))->is_Reset_allowed(any);}
};

//	Command ResetInterlockStatus class definition
class ResetInterlockStatusClass : public Tango::Command
{
public:
	ResetInterlockStatusClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	ResetInterlockStatusClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~ResetInterlockStatusClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<LiberaSinglePassE *>(dev))->is_ResetInterlockStatus_allowed(any);}
};

//	Command MagicCommand class definition
class MagicCommandClass : public Tango::Command
{
public:
	MagicCommandClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	MagicCommandClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~MagicCommandClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<LiberaSinglePassE *>(dev))->is_MagicCommand_allowed(any);}
};


/**
 *	The LiberaSinglePassEClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  LiberaSinglePassEClass : public Tango::DeviceClass
#else
class LiberaSinglePassEClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(LiberaSinglePassEClass::Additionnal DServer data members) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	LiberaSinglePassEClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static LiberaSinglePassEClass *init(const char *);
		static LiberaSinglePassEClass *instance();
		~LiberaSinglePassEClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		LiberaSinglePassEClass(string &);
		static LiberaSinglePassEClass *_instance;
		void command_factory();
		void attribute_factory(vector<Tango::Attr *> &);
		void write_class_property();
		void set_default_property();
		void get_class_property();
		string get_cvstag();
		string get_cvsroot();
	
	private:
		void device_factory(const Tango::DevVarStringArray *);
		void create_static_attribute_list(vector<Tango::Attr *> &);
		void erase_dynamic_attributes(const Tango::DevVarStringArray *,vector<Tango::Attr *> &);
		vector<string>	defaultAttList;
		Tango::Attr *get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname);
};

}	//	End of namespace

#endif   //	LiberaSinglePassE_H
