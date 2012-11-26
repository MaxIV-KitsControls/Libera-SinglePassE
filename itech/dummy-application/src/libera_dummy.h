/*
 * Copyright (c) 2008-2012 Instrumentation Technologies
 * All Rights Reserved.
 *
 * $Id: $
 */

#ifndef LIBERA_DUMMY_H
#define LIBERA_DUMMY_H

#include "iapp/libera_application.h"
// enum node
static const int cEnum1 = 0;
static const int cEnum2 = -1;
static const int cEnum3 = -2;
static const int cEnum4 = -3;
static const int cEnum5 = -4;
static const int cEnum6 = -5;
static const int cEnum7 = -6;
static const int cEnum8 = -7;
static const int cEnum9 = -8;
static const int cEnum10 = -9;
static const int cEnum11 = -10;
static const int cEnum12 = -11;
static const int cEnum13 = -12;
static const int cEnum14 = -13;
static const int cEnum15 = -14;
static const int cEnum16 = -15;
static const int cEnum17 = -16;
static const int cEnum18 = -17;
static const int cEnum19 = -18;
static const int cEnum20 = -19;
static const int cEnum21 = -20;
static const int cEnum22 = -21;
static const int cEnum23 = -22;
static const int cEnum24 = -23;
static const int cEnum25 = -24;
static const int cEnum26 = -25;
static const int cEnum27 = -26;
static const int cEnum28 = -27;
static const int cEnum29 = -28;
static const int cEnum30 = -29;
static const int cEnum31 = -30;
static const int cEnum32 = -31;



enum myEnum {
	myEnum1 = cEnum1,
	myEnum2 = cEnum2,
	myEnum3 = cEnum3,
	myEnum4 = cEnum4,
	myEnum5 = cEnum5,
	myEnum6 = cEnum6,
	myEnum7 = cEnum7,
	myEnum8 = cEnum8,
	myEnum9 = cEnum9,
	myEnum10 = cEnum10,
	myEnum11 = cEnum11,
	myEnum12 = cEnum12,
	myEnum13 = cEnum13,
	myEnum14 = cEnum14,
	myEnum15 = cEnum15,
	myEnum16 = cEnum16,
	myEnum17 = cEnum17,
	myEnum18 = cEnum18,
	myEnum19 = cEnum19,
	myEnum20 = cEnum20,
	myEnum21 = cEnum21,
	myEnum22 = cEnum22,
	myEnum23 = cEnum23,
	myEnum24 = cEnum24,
	myEnum25 = cEnum25,
	myEnum26 = cEnum26,
	myEnum27 = cEnum27,
	myEnum28 = cEnum28,
	myEnum29 = cEnum29,
	myEnum30 = cEnum30,
	myEnum31 = cEnum31,
	myEnum32 = cEnum32,
	myEnumUnknown
};

template<>
const istd::EnumMap<myEnum>::Items istd::EnumMap<myEnum>::items = {
		{myEnum1 , "gt_0"},
		{myEnum2 , "gt_1"},
		{myEnum3 , "gt_2"},
		{myEnum4 , "gt_3"},
		{myEnum5 , "gt_4"},
		{myEnum6 , "gt_5"},
		{myEnum7 , "gt_6"},
		{myEnum8 , "gt_7"},
		{myEnum9 , "gt_8"},
		{myEnum10 , "gt_9"},
		{myEnum11 , "gt_10"},
		{myEnum12 , "gt_11"},
		{myEnum13 , "gt_12"},
		{myEnum14 , "gt_13"},
		{myEnum15 , "gt_14"},
		{myEnum16 , "gt_15"},
		{myEnum17 , "gt_16"},
		{myEnum18 , "gt_17"},
		{myEnum19 , "gt_18"},
		{myEnum20 , "gt_19"},
		{myEnum21 , "gt_20"},
		{myEnum22 , "gt_21"},
		{myEnum23 , "gt_22"},
		{myEnum24 , "gt_23"},
		{myEnum25 , "gt_24"},
		{myEnum26 , "gt_25"},
		{myEnum27 , "gt_26"},
		{myEnum28 , "gt_27"},
		{myEnum29 , "gt_28"},
		{myEnum30 , "gt_29"},
		{myEnum31 , "gt_30"},
		{myEnum32 , "gt_31"},

};



/*--------------------------------------------------------------------------------------*/
/* Dummy Application class                                                              */

class liberaDummy: public virtual iapp::LiberaApplication {
public:
	liberaDummy();
	virtual ~liberaDummy();

	virtual const std::string &ApplicationName() const;

protected:
	void OnRegistryAdd(ireg::TreeNodePtr &parent);
	void OnPreInit();
	void OnPostInit();
	void OnPostConfig();
	void OnShutdown();
	virtual iapp::LiberaBoard *CreateBoard(const bmc::Board* a_board);
	void EventThread();
	bool set_param(const double &a_val);
	bool get_param(double &a_val) const;

private:
	/* Dummy internal parameters */
	int m_exitThread1;

	int32_t m_longChg3;
	int32_t m_longChg4;
	int32_t m_longChg5;
	int32_t m_longChg6;

	std::thread m_thread1;

	ireg::TreeNodePtr m_nodeLongChg3;
	ireg::TreeNodePtr m_nodeLongChg4;
	ireg::TreeNodePtr m_nodeLongChg5;
	ireg::TreeNodePtr m_nodeLongChg6;

	std::vector<isig::SignalSourceSharedPtr> m_signals;
};

#endif // LIBERA_DUMMY_H
