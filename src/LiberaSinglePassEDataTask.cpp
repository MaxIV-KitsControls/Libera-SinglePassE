static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        LiberaSinglePassEDataTask.cpp
//
// description : C++ source for the LiberaSinglePassEDataTask.
//               The class is derived from yat4tango::DeviceTask.
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

#include "LiberaSinglePassEDataTask.h"

#include <sys/time.h>
#include <unistd.h>

namespace LiberaSinglePassE_ns
{

//-----------------------------------------------------------------------------
//
// function : 		c_task_wrapper
//
// description : 	LiberaSinglePassEDataTask C thread wrapper
//
//-----------------------------------------------------------------------------

static void *c_task_wrapper(void *ptr) {
	LiberaSinglePassEDataTask *p = static_cast<LiberaSinglePassEDataTask *>(ptr);

	// create new data acquisition task
	p->thread_task();

	return NULL;
}

//-----------------------------------------------------------------------------
//
// method : 		LiberaSinglePassEDataTask::ctor, dtor
//
// description : 	LiberaSinglePassEDataTask class constructor and destructor
//
//-----------------------------------------------------------------------------

LiberaSinglePassEDataTask::LiberaSinglePassEDataTask(Tango::DeviceImpl *dev,
		mci::Node &node, Tango::DevLong per_time) :
		tango_dev(dev), acq_period(per_time) {

	// default minimum size
	dod_buffer_size = 10;
	new_dod_buffer_size = 10;
	dod_client = NULL;
	mci_path = "unset yet";
	DEBUG_STREAM_TASK << "enter" << std::endl;

	// signal destructor not to wait for thread (if it does not start)
	finish = true;

	try {
		mci_signal = node;
		mci_path = mci::ToString(mci_signal.GetRelPath());
	} catch (istd::Exception &e) {
		ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
		return;
	}
	DEBUG_STREAM_TASK << "MCI node connected" << std::endl;


	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condition, NULL);

	pthread_mutex_lock(&mutex);
	int ret = pthread_create(&thread, NULL, c_task_wrapper, this);
	// thread will signal us when it is starting up
	pthread_cond_wait(&condition, &mutex);
	pthread_mutex_unlock(&mutex);

	if (ret != 0) {
		ERROR_STREAM_TASK << "failed to create task thread" << ret << std::endl;
		return;
	}

	DEBUG_STREAM_TASK << "task thread created" << std::endl;
}

LiberaSinglePassEDataTask::~LiberaSinglePassEDataTask(void) {
	DEBUG_STREAM_TASK << "enter" << std::endl;

	pthread_mutex_lock(&mutex);
	if (finish == false) {
		finish = true;
		// XXX: what happens if thread if not active?
		pthread_cond_wait(&condition, &mutex);
		pthread_join(thread, NULL);
		thread = 0;
	}
	pthread_mutex_unlock(&mutex);

	DEBUG_STREAM_TASK << "thread joined" << std::endl;

	delete dod_client;
	dod_client = NULL;

	DEBUG_STREAM_TASK << "object destroyed" << std::endl;
}

void LiberaSinglePassEDataTask::thread_task(void) {
	DEBUG_STREAM_TASK << "enter" << std::endl;

	// signal main thread that we are starting here
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&condition);
	pthread_mutex_unlock(&mutex);
	DEBUG_STREAM_TASK << "thread is running, ID " << pthread_self() << std::endl;

	// ADC data readout *must* be in the SingleEvent mode!
	// This a) avoids Read() I/O errors, b) allows arbitrary data sizes at
	// arbitrary rates
	dod_mode = isig::eModeDodSingleEvent;

	// initialize the dod signal
	try {
		if (! mci_signal_init()) {
			ERROR_STREAM_TASK << "failed to initialize MCI signal" << std::endl;
			return;
		}
	} catch (istd::Exception &e) {
		ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
		return;
	}

	// enable the dod signal
	try {
		mci_signal_enable();
	} catch (istd::Exception &e) {
		ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
		return;
	}

	DEBUG_STREAM_TASK << "MCI signal initialized & enabled" << std::endl;

	// let the thread run
	finish = false;

	while (1) {
		// do we need to stop?
		pthread_mutex_lock(&mutex);
		if (finish) {
			DEBUG_STREAM_TASK << "thread finish signaled" << std::endl;
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);

		// doze off for the requested time
		DEBUG_STREAM_TASK << "thread sleeping for "
				<< acq_period << " ms" << std::endl;
		for (int zz = 0; zz < acq_period; zz++) {
			usleep(1000);
		}
		DEBUG_STREAM_TASK << "thread awaken" << std::endl;

		// see if buffer size changed
		if (new_dod_buffer_size != dod_buffer_size) {
			// disabling and enabling the the dod signal will take new buffer
			// size into account
			try {
				mci_signal_disable();
				dod_buffer_size = new_dod_buffer_size;
				mci_signal_enable();
			} catch (istd::Exception &e) {
				ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
				return;
			}
		}

		// go ahead.. try to read data now
		try {
			if (! read_data()) {
				mci_signal_disable();
			}
		} catch (istd::Exception &e) {
			ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
		}
	}

	// stop the dod signal before we die
	try {
		mci_signal_disable();
	} catch (istd::Exception &e) {
		ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
		return;
	}

	// signal main thread that we are done here
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&condition);
	pthread_mutex_unlock(&mutex);
	DEBUG_STREAM_TASK << "thread finished" << std::endl;
}

bool LiberaSinglePassEDataTask::mci_signal_init() {
	DEBUG_STREAM_TASK << "enter" << std::endl;

	auto rSignal = mci::CreateRemoteSignal(mci_signal);
	if (!rSignal) {
		ERROR_STREAM_TASK << "not a MCI signal node" << std::endl;
		return false;
	}

	if (rSignal->AccessType() != isig::eAccessDataOnDemand) {
		ERROR_STREAM_TASK << "signal type not eAccessDataOnDemand" << std::endl;
		return false;
	}

	dod_source = std::dynamic_pointer_cast < RSource > (rSignal);
	if (! dod_source) {
		ERROR_STREAM_TASK << "can't connect to MCI signal" << std::endl;
		return false;
	}

	dod_client = new Client(dod_source->CreateClient("dod_client"));
	if (! dod_client) {
		ERROR_STREAM_TASK << "failed to create client for MCI signal" << std::endl;
		return false;
	}

	dod_component_names = rSignal->GetComponentNames();

	// set buffer length to group size if needed
	if (dod_buffer_size < dod_source->GroupSize()) {
		dod_buffer_size = dod_source->GroupSize();
		new_dod_buffer_size = dod_buffer_size;
	}

	return true;
}

void LiberaSinglePassEDataTask::mci_signal_enable() {
	DEBUG_STREAM_TASK << "enter" << std::endl;

	// catch Close() failure - possible when MCI node is not alive?
	try {
		dod_client->Close();
	} catch (istd::Exception &e) {
		ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
	}

	// resize the DOD buffer
	dod_buffer = Buffer(dod_client->CreateBuffer(dod_buffer_size));

	DEBUG_STREAM_TASK << "allocated dod buffer of " << dod_buffer_size
			<< " ADC atoms" << std::endl;

	DEBUG_STREAM_TASK << "opening pipe in mode " << dod_mode << std::endl;
	isig::SuccessCode_e ret = dod_client->Open(dod_mode, dod_buffer_size, 0);

	if (ret != isig::eSuccess) {
		ERROR_STREAM_TASK << "can't open pipe: " << ret << std::endl;
		return;
	}

	DEBUG_STREAM_TASK << "pipe opened" << std::endl;
}

void LiberaSinglePassEDataTask::mci_signal_disable() {
	DEBUG_STREAM_TASK << "enter" << std::endl;

	// catch Close() failure - possible when MCI node is not alive?
	try {
		if (dod_client->IsOpen()) {
			dod_client->Close();
		}
	} catch (istd::Exception &e) {
		ERROR_STREAM_TASK << "MCI exception :" << e.what() << std::endl;
	}

	DEBUG_STREAM_TASK << "pipe closed" << std::endl;
}

bool LiberaSinglePassEDataTask::read_data() {
	DEBUG_STREAM_TASK << "enter" << std::endl;

	DEBUG_STREAM_TASK << "DOD mode " << dod_mode << std::endl;

	if (! dod_client->IsOpen()) {
		DEBUG_STREAM_TASK << "pipe is closed" << std::endl;
		return false;
	}

	LiberaSinglePassE *dev = static_cast<LiberaSinglePassE *>(tango_dev);
	assert(dev != NULL);

	// Read() will block if data on event is requested, until the event
	// arrives (Event mode)
	// Read() also blocks if more than requested atoms are in the buffer,
	// (Position, LMT mode)
	isig::SuccessCode_e ret = dod_client->Read(dod_buffer, dod_meta, 0);
	if (ret != isig::eSuccess) {
		ERROR_STREAM_TASK << "Read() failed: " << ret << std::endl;

		// invalidate the data buffers
		memset(dev->attr_Left_read, 0, sizeof(dev->attr_Left_read));
		memset(dev->attr_Down_read, 0, sizeof(dev->attr_Down_read));
		memset(dev->attr_Right_read, 0, sizeof(dev->attr_Right_read));
		memset(dev->attr_Up_read, 0, sizeof(dev->attr_Up_read));

		return false;
	}

	// this is possible when user changed the buffer size while the Read()
	// was blocking
	if (new_dod_buffer_size != dod_buffer_size) {
		ERROR_STREAM_TASK << "DOD buffer size changed during Read()"
				<< " old " << dod_buffer_size
				<< " new " << new_dod_buffer_size
				<< std::endl;

		// invalidate the data buffers
		memset(dev->attr_Left_read, 0, sizeof(dev->attr_Left_read));
		memset(dev->attr_Down_read, 0, sizeof(dev->attr_Down_read));
		memset(dev->attr_Right_read, 0, sizeof(dev->attr_Right_read));
		memset(dev->attr_Up_read, 0, sizeof(dev->attr_Up_read));
		return false;
	}

	// Read() can return less than requested
	if (dod_buffer.GetLength() != dod_buffer_size) {
		ERROR_STREAM_TASK << "Read() returned short "
				<< " wanted " << dod_buffer_size
				<< " got " << dod_buffer.GetLength()
				<< std::endl;
	}

	size_t row_cnt = dod_buffer.GetLength();
	size_t col_cnt = dod_component_names.size();
	DEBUG_STREAM_TASK << "ADC data row count " << row_cnt
			<< " column count " << col_cnt << std::endl;
	assert(col_cnt == 4);

	std::stringstream ss;
	ss << std::endl;

	// copy the data from MCI buffer over to the Tango attributes
	for (size_t row = 0; row < row_cnt; ++row) {
		ss << dod_buffer[row][0] << " "
				<< dod_buffer[row][1] << " "
				<< dod_buffer[row][2] << " "
				<< dod_buffer[row][3] << std::endl;
		*(dev->attr_Left_read + row) =
				static_cast<Tango::DevUShort>(dod_buffer[row][0]);
		*(dev->attr_Down_read + row) =
				static_cast<Tango::DevUShort>(dod_buffer[row][1]);
		*(dev->attr_Right_read + row) =
				static_cast<Tango::DevUShort>(dod_buffer[row][2]);
		*(dev->attr_Up_read + row) =
				static_cast<Tango::DevUShort>(dod_buffer[row][3]);
	}

	DEBUG_STREAM_TASK << "Read() returned: " << ss.str() << std::endl;

	// increment trigger count
	dev->trig_ctr++;
	DEBUG_STREAM_TASK << "trigger count " << dev->trig_ctr << std::endl;

	// data task heart beat
	gettimeofday(&now, NULL);
	dev->heartbeat_sec = now.tv_sec;
	DEBUG_STREAM_TASK << "heart beat " << now.tv_sec << std::endl;

	return true;
}

void LiberaSinglePassEDataTask::mci_set_buffer_size(Tango::DevLong *buffer_size) {
	DEBUG_STREAM_TASK << "enter" << std::endl;

	if (new_dod_buffer_size == static_cast<size_t>(*buffer_size)) {
		DEBUG_STREAM_TASK << "buffer size remains unchanged" << std::endl;
		return;
	}

	pthread_mutex_lock(&mutex);
	new_dod_buffer_size = *buffer_size;
	pthread_mutex_unlock(&mutex);

	DEBUG_STREAM_TASK << "new buffer size " << new_dod_buffer_size
			<< " ADC atoms" << std::endl;
}


} // namespace
