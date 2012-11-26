/*
 * Copyright (c) 2008-2012 Instrumentation Technologies
 * All Rights Reserved.
 *
 * $Id: libera_dummy.cpp 18000 2012-10-21 11:33:27Z hinko.kocevar $
 */

#include <isig/signal_source.h>
#include <isig/random_access_file.h>

#include <ireg/node.h>
#include <ireg/reg_node.h>
#include <ireg/remote_node.h>
#include <ireg/signal_node.h>
#include <ireg/reg_value_node.h>
#include <ireg/reg_reference_node.h>
#include <ireg/reg_reference_enum_node.h>
#include <ireg/reg_fnc_node.h>
#include <ireg/reg_value_enum_node.h>
#include <ireg/reg_fnc_enum_node.h>
#include <ireg/reg_config_node.h>
#include <ireg/reg_reference_bit_node.h>
#include <ireg/reg_exec_node.h>
#include "ireg/expression_operations.h"
#include "ireg/expression_terminals.h"

#include <ireg/ireg_util.h>

#include "platform_dummy.h"

static const std::string c_applicationName("platform-dummy");

/*-----------------------------------------------------------------------------*/
/* return application name                                                     */

const std::string& platformDummy::ApplicationName() const {
	return c_applicationName;
}

/*-----------------------------------------------------------------------------*/
/* constructor                                                                 */

platformDummy::platformDummy() : LiberaApplication(c_applicationName)
{
	istd::TraceFile::GetInstance().SetPrintFile(true);
	istd::TraceFile::GetInstance().SetDumpStack(true);

	m_exitThread1 = false;
	m_id0 = 0;
	m_id1 = 0;
	m_id2 = 0;
	m_fan1 = 4544;
	m_fan2 = 4544;
}

/*-----------------------------------------------------------------------------*/
/* destructor                                                                  */

platformDummy::~platformDummy()
{
	istd_FTRC();
}

/*-----------------------------------------------------------------------------*/
/* virtual event handler, triggered after all boards are instantiated and      */
/* before registry is defined                                                  */

void platformDummy::OnPreInit()
{
	istd_FTRC();
}

/*-----------------------------------------------------------------------------*/
/* virtual event handler, triggered after all boards are instantiated and      */
/* registry is defined                                                         */

void platformDummy::OnPostInit()
{
	istd_FTRC();

    // MCI registry is ready to be used from now on
    mci::Node root = GetRegistry();

	// Trace info - what is expored by platform daemon
	istd_TRC(istd::eTrcLow,
        "Exporting following nodes through the ireg:"
        << std::endl << root.DumpSubTree()
    );

}

/*-----------------------------------------------------------------------------*/
/* virtual event thread that sets values to some registry nodes to see the     */
/* changes and notifications appear                                            */

void platformDummy::EventThread()
{
    istd_FTRC();
    double noiseAmplitude = 10658.123;

    while (1) {
    	if (m_exitThread1) {
    		break;
    	}

    	usleep(200000);

    	m_id0++;
    	if (m_id0 > 100) {
    		m_id0 = 55;
    	}
    	m_nodeid0->Emit();

    	m_id1 = (m_id0 / 2) + 3;
    	if (m_id1 > 80) {
    		m_id1 = 33;
    	}
    	m_nodeid1->Emit();

    	m_id2 = (m_id1 * 4) - 3;
    	if (m_id2 > 150) {
    		m_id2 = 47;
    	}
    	m_nodeid2->Emit();

    	m_fan1--;
    	if (m_fan1 < 4000) {
    		m_fan1 = 4544;
    	}
    	m_nodefan1->Emit();

    	m_fan2++;
    	if (m_fan2 > 5000) {
    		m_fan2 = 4544;
    	}
    	m_nodefan2->Emit();

    	usleep(300000);
    }
}

/*-----------------------------------------------------------------------------*/
/* virtual event handler, used for application initialization after            */
/* registry is updated with persistent configuration.                          */

void platformDummy::OnPostConfig() {
	istd_FTRC();

	m_thread1 = std::thread(std::bind(&platformDummy::EventThread, this));
}


/*-----------------------------------------------------------------------------*/
/* expose our functionality to outside world                                   */

void platformDummy::OnRegistryAdd(ireg::TreeNodePtr &parent) {
	istd_FTRC();

	uint64_t f_read_write = mci::eNfDefault;
	uint64_t f_read_only = mci::eNfReadable;
	uint64_t f_write_only = mci::eNfWritable;

	/* Simulate some of Libera SPE production daemon MCI node locations that
	 * of interest to Tango DS */

	mci::Node regroot = GetRegistry();
	m_nodefan1 = Create<RegReferenceDoubleNode>("left_front", m_fan1, f_read_only);
	m_nodefan2 = Create<RegReferenceDoubleNode>("right_front", m_fan2, f_read_only);
	regroot.GetTreeNode()->Attach(Create<RegNode>("fans"));
	mci::Node fans = GetRegistry()["fans"];
	fans.GetTreeNode()->Attach(m_nodefan1);
	fans.GetTreeNode()->Attach(m_nodefan2);

	mci::Node boards = GetRegistry()["boards"];

	m_nodeid0 = Create<RegReferenceDoubleNode>("value", m_id0, f_read_only);
	m_nodeid1 = Create<RegReferenceDoubleNode>("value", m_id1, f_read_only);
	m_nodeid2 = Create<RegReferenceDoubleNode>("value", m_id2, f_read_only);
    boards.GetTreeNode()->Attach( Create<RegNode>("icb0")->Attach( Create<RegNode>("sensors")->Attach( Create<RegNode>("ID_0")->Attach(m_nodeid0))));
	mci::Node sensors = GetRegistry()["boards"]["icb0"]["sensors"];
	sensors.GetTreeNode()->Attach( Create<RegNode>("ID_1")->Attach(m_nodeid1));
	sensors.GetTreeNode()->Attach( Create<RegNode>("ID_2")->Attach(m_nodeid2));
}

/*-----------------------------------------------------------------------------*/
/* virtual event handler, used for application specific shutdown procedure     */

void platformDummy::OnShutdown() {
	istd_FTRC();

	m_exitThread1 = true;

    if (m_thread1.joinable()) {
       m_thread1.join();
    }
}

/*-----------------------------------------------------------------------------*/
/* no boards to create here */

iapp::LiberaBoard *platformDummy::CreateBoard(const bmc::Board* a_board) {
	istd_FTRC();

	return NULL;
}

/*-----------------------------------------------------------------------------*/
/* Instantiate iapp:LiberaApplivarion in main()                                */

int main(int argc, char *argv[])
{
    auto ld( std::make_shared<platformDummy>() );
    bool success = ld->Run(argc, argv);
    return (success ? EXIT_SUCCESS : EXIT_FAILURE);
}

