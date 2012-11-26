//=============================================================================
//
// file :        LiberaSinglePassEDataTask.h
//
// description : Include for the LiberaSinglePassEDataTask class.
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

#ifndef LIBERASINGLEPASSEDATATASK_H
#define LIBERASINGLEPASSEDATATASK_H

#include <pthread.h>

#include <tango.h>

#include "LiberaSinglePassE.h"
#include "LiberaCommon.h"

namespace LiberaSinglePassE_ns
{

#define FATAL_STREAM_TASK \
  if (tango_dev->get_logger()->is_fatal_enabled()) \
    tango_dev->get_logger()->fatal_stream() \
      << log4tango::LogInitiator::_begin_log \
      << __FILE__ << " " << __func__ << "[" << __LINE__ << "] " \
      << "MCI path " << mci_path << " "

#define ERROR_STREAM_TASK \
  if (tango_dev->get_logger()->is_error_enabled()) \
    tango_dev->get_logger()->error_stream() \
      << log4tango::LogInitiator::_begin_log \
      << __FILE__ << " " << __func__ << "[" << __LINE__ << "] " \
      << "MCI path " << mci_path << " "

#define WARN_STREAM_TASK \
  if (tango_dev->get_logger()->is_warn_enabled()) \
    tango_dev->get_logger()->warn_stream() \
      << log4tango::LogInitiator::_begin_log \
      << __FILE__ << " " << __func__ << "[" << __LINE__ << "] " \
      << "MCI path " << mci_path << " "

#define INFO_STREAM_TASK \
  if (tango_dev->get_logger()->is_info_enabled()) \
    tango_dev->get_logger()->info_stream() \
      << log4tango::LogInitiator::_begin_log \
      << __FILE__ << " " << __func__ << "[" << __LINE__ << "] " \
      << "MCI path " << mci_path << " "

#define DEBUG_STREAM_TASK \
  if (tango_dev->get_logger()->is_debug_enabled()) \
  	tango_dev->get_logger()->debug_stream() \
      << log4tango::LogInitiator::_begin_log \
      << __FILE__ << " " << __func__ << "[" << __LINE__ << "] " \
      << "MCI path " << mci_path << " "

#define ENDLOG_TASK \
  log4tango::LogSeparator::_end_log

class LiberaSinglePassEDataTask
{
    typedef isig::SignalTraitsVarInt32::BaseType BaseType;
    typedef isig::DataOnDemandRemoteSource<isig::SignalTraitsVarInt32> RSource;
    typedef RSource::Client Client;
    typedef RSource::Buffer Buffer;

public:
	LiberaSinglePassEDataTask (Tango::DeviceImpl *, mci::Node &, Tango::DevLong);
	virtual ~LiberaSinglePassEDataTask(void);
	void thread_task(void);

protected:
	bool read_data();
	bool mci_signal_init();
	void mci_signal_enable();
	void mci_signal_disable();
	void mci_set_buffer_size(Tango::DevLong *buffer_size);

private:
	Tango::DeviceImpl *tango_dev;
	mci::Node mci_signal;
	std::string mci_path;

	pthread_t thread;
	pthread_mutex_t mutex;
	pthread_cond_t condition;
	bool finish;

    std::shared_ptr<RSource> dod_source;
    Client *dod_client;
    Buffer dod_buffer;
	size_t dod_buffer_size;
	size_t new_dod_buffer_size;
    isig::AccessMode_e dod_mode;
    isig::SignalMeta dod_meta;
	isig::ComponentNames dod_component_names;
	struct timeval now;
	Tango::DevLong acq_period;

	friend class LiberaSinglePassE;
};

} // namespace LiberaSP_ns

#endif // LIBERASINGLEPASSEDATATASK_H
