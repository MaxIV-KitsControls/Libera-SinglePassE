/*
 * Copyright (c) 2008-2012 Instrumentation Technologies
 * All Rights Reserved.
 *
 * $Id: simul_stream.h 17861 2012-10-08 11:01:53Z hinko.kocevar $
 */

#include <stdint.h>
#include <math.h>
#include <fstream>

#include "isig/stream.h"
#include "isig/data_on_demand_source.h"
#include "isig/circular_buffer_controller_base.h"

#include "pink_noise.h"

#define ATOM_COUNT		10000
#define MAX_ADC 		(32 * 1024)

const size_t c_dod_bufferLen(1);
const size_t c_stream_bufferLen(1);
const double c_signalAmpAC(1e4);
const double c_signalAmpBD(1e3);
const double c_signalFrq(1/70.0);


template<typename T>
struct Simul5Atom {
    T a0, a1, a2, a3;
};

template<typename T>
struct Simul5AtomSPE {
    T a0, a1, a2;
};

// template typedef
template<typename T>
struct Simul5Traits {
    typedef isig::SignalTraits<T, Simul5Atom<T>, c_dod_bufferLen> type;
};

// template typedef
template<typename T>
struct Simul5TraitsSPE {
    typedef isig::SignalTraits<T, Simul5AtomSPE<T>, c_stream_bufferLen> type;
};

typedef Simul5Traits<int16_t>::type Simul5Short;
typedef Simul5Traits<int32_t>::type Simul5Long;
typedef Simul5Traits<double>::type Simul5Double;

typedef Simul5TraitsSPE<int16_t>::type Simul5ShortSPE;
typedef Simul5TraitsSPE<int32_t>::type Simul5LongSPE;
typedef Simul5TraitsSPE<double>::type Simul5DoubleSPE;

template<>
const Simul5Short::Names Simul5Short::names =
    {{"A", "B", "C", "D"}};

template<>
const Simul5Long::Names Simul5Long::names =
	{{"A", "B", "C", "D"}};

template<>
const Simul5ShortSPE::Names Simul5ShortSPE::names =
    {{"X", "Y", "SUM"}};

template<>
const Simul5LongSPE::Names Simul5LongSPE::names =
	{{"X", "Y", "SUM"}};


/*****************************************************************************/

template<typename _Traits>
class SimulStream : public isig::Stream<_Traits> {

public:

    SimulStream()
    : isig::Stream<_Traits>("simul-stream-" + istd::CppName(typeid(_Traits)), _Traits()),
      m_sleep(1.0),
      m_index(0)
    {
    };

    virtual ~SimulStream()
    {
        this->ShutDown();
    }

    double m_sleep;

private:

    int32_t                  m_index;
    std::mutex               m_mutex;
    std::condition_variable  m_cond;

    virtual void CloseInput()
    {
        m_cond.notify_all();
    };

    typedef isig::Stream<_Traits> _Base;
    virtual isig::SuccessCode_e ReadInput(typename _Base::Buffer &a_buf) {

        std::unique_lock<std::mutex> lk(m_mutex);

        if (m_cond.wait_for(lk, std::chrono::duration<double>(m_sleep))
            != std::cv_status::timeout) {
            // Condition has been notified,
            // it must happened because the input has been closed.
            return isig::eClosed;
        }

        size_t len(a_buf.GetLength());

        for (size_t i(0); i<len; ++i) {
            a_buf[i].a1 = c_signalAmpBD*sin(m_index*M_PI*c_signalFrq);
            a_buf[i].a2 = c_signalAmpBD*cos(m_index*M_PI*c_signalFrq);
            a_buf[i].a0 = m_index++;
        }

        return isig::eSuccess;
    }
};

/*****************************************************************************/

template<typename _Traits>
class SimulStreamSPE : public isig::Stream<_Traits> {

public:

    SimulStreamSPE()
    : isig::Stream<_Traits>("simul-stream2-" + istd::CppName(typeid(_Traits)), _Traits()),
      m_sleep(1.0),
      m_index(0)
    {
    };

    virtual ~SimulStreamSPE()
    {
        this->ShutDown();
    }

    double m_sleep;

private:

    int32_t                  m_index;
    std::mutex               m_mutex;
    std::condition_variable  m_cond;

    virtual void CloseInput()
    {
        m_cond.notify_all();
    };

    typedef isig::Stream<_Traits> _Base;
    virtual isig::SuccessCode_e ReadInput(typename _Base::Buffer &a_buf) {

        std::unique_lock<std::mutex> lk(m_mutex);

        if (m_cond.wait_for(lk, std::chrono::duration<double>(m_sleep))
            != std::cv_status::timeout) {
            // Condition has been notified,
            // it must happened because the input has been closed.
            return isig::eClosed;
        }

        size_t len(a_buf.GetLength());

        for (size_t i(0); i<len; ++i) {
            a_buf[i].a1 = c_signalAmpAC*sin(m_index*M_PI*c_signalFrq);
            a_buf[i].a2 = c_signalAmpAC*cos(m_index*M_PI*c_signalFrq);
            a_buf[i].a0 = m_index++;
        }

        return isig::eSuccess;
    }
};

/*****************************************************************************/

class TestCircularBufferController:
    public isig::CircularBufferControllerBase,
    public isig::Clonable<TestCircularBufferController> {

public:
    TestCircularBufferController(
        size_t                  a_size,
        const uint64_t&         a_frequency)
    : isig::CircularBufferControllerBase(a_size, a_frequency) {
        isig::LMT lmt;
        GetCurrentLmt(lmt);
        SetStartLmt(lmt);
    }

    virtual ~TestCircularBufferController() {}


private:

    virtual isig::SuccessCode_e GetEventLmt(isig::LMT& a_lmt) const
    {
        ::sleep(1);
        return GetCurrentLmt(a_lmt);
    }
    virtual isig::SuccessCode_e GetCurrentLmt(isig::LMT& a_lmt) const
    {
        // get time
        a_lmt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return isig::eSuccess;
    }

};

/*****************************************************************************/

template<typename _Traits>
class TestFile {
public:
    typedef typename _Traits::Atom     Atom;
    typedef typename _Traits::BaseType BaseType;

    TestFile(const std::string& a_fname)
    {
        std::ofstream fs;
        fs.open(a_fname.c_str(), std::ios::out|std::ios::binary|std::ios::trunc);

        double signalNoise[4*ATOM_COUNT] = {1.0};
        pink_noise(signalNoise);

        for (size_t i(0); i<ATOM_COUNT; ++i) {
/*
        	Atom smpl = {
                //static_cast<BaseType>(i),
                static_cast<BaseType>(-c_signalAmpAC*cos(i*M_PI*c_signalFrq)),
                static_cast<BaseType>(c_signalAmpBD*sin(i*M_PI*c_signalFrq)),
                static_cast<BaseType>(c_signalAmpAC*cos(i*M_PI*c_signalFrq)),
                static_cast<BaseType>(-c_signalAmpBD*sin(i*M_PI*c_signalFrq)),
                //static_cast<BaseType>(-c_signalAmp*cos(i*M_PI*c_signalFrq))
            };
*/

        	if (i < 300) {
            	Atom smpl = {
					static_cast<BaseType>(MAX_ADC * signalNoise[i+0] * 0.01),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+1] * 0.01),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+2] * 0.01),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+3] * 0.01),
            	};
                fs.write(reinterpret_cast<const char*>(&smpl),  sizeof(Atom));
        	} else if (i >= 300 && i < 350) {
            	Atom smpl = {
					static_cast<BaseType>(MAX_ADC * signalNoise[i+0] * 0.35),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+1] * 0.35),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+2] * 0.35),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+3] * 0.35),
            	};
                fs.write(reinterpret_cast<const char*>(&smpl),  sizeof(Atom));
        	} else if (i >= 350 && i < 400) {
            	Atom smpl = {
					static_cast<BaseType>(MAX_ADC * signalNoise[i+0] * 0.66),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+1] * 0.66),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+2] * 0.66),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+3] * 0.66),
            	};
                fs.write(reinterpret_cast<const char*>(&smpl),  sizeof(Atom));
        	} else if (i >= 400 && i < 450) {
            	Atom smpl = {
					static_cast<BaseType>(MAX_ADC * signalNoise[i+0] * 0.97),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+1] * 0.97),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+2] * 0.97),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+3] * 0.97),
            	};
                fs.write(reinterpret_cast<const char*>(&smpl),  sizeof(Atom));
        	} else if (i >= 450 && i < 500) {
            	Atom smpl = {
					static_cast<BaseType>(MAX_ADC * signalNoise[i+0] * 0.66),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+1] * 0.66),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+2] * 0.66),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+3] * 0.66),
            	};
                fs.write(reinterpret_cast<const char*>(&smpl),  sizeof(Atom));
        	} else if (i >= 500 && i < 550) {
            	Atom smpl = {
					static_cast<BaseType>(MAX_ADC * signalNoise[i+0] * 0.35),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+1] * 0.35),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+2] * 0.35),
					static_cast<BaseType>(MAX_ADC * signalNoise[i+3] * 0.35),
            	};
                fs.write(reinterpret_cast<const char*>(&smpl),  sizeof(Atom));
        	} else {
				Atom smpl = {
						static_cast<BaseType>(MAX_ADC * signalNoise[i+0] * 0.01),
						static_cast<BaseType>(MAX_ADC * signalNoise[i+1] * 0.01),
						static_cast<BaseType>(MAX_ADC * signalNoise[i+2] * 0.01),
						static_cast<BaseType>(MAX_ADC * signalNoise[i+3] * 0.01),
				};
	            fs.write(reinterpret_cast<const char*>(&smpl),  sizeof(Atom));
        	}

        }
        fs.close();
    }

    void pink_noise(double *signalNoise) {
    	/*
    	  Purpose:
    	    TEST04 tests RAN1F.
    	  Licensing:
    	    This code is distributed under the GNU LGPL license.
    	  Modified:
    	    31 May 2010
    	  Author:
    	    John Burkardt
    	*/
		unsigned int b;
		unsigned int i;
		int *q;
		int rep;
		double *u;
		double y;

		fprintf(stdout, "\n");
		fprintf(stdout, "TEST04\n");
		fprintf(stdout,
				"  RAN1F generates random values with an approximate\n");
		fprintf(stdout, "  1/F distribution.\n");

		unsigned int idx = 0;

		fprintf(stdout, "\n");
		fprintf(stdout, "   B   I      Y\n");
		fprintf(stdout, "\n");
		while (idx < ATOM_COUNT) {

			for (b = 1; b < 32; b = b * 2) {
				u = (double *) malloc(b * sizeof(double));
				q = (int *) malloc(b * sizeof(int));
				for (rep = 1; rep <= 4; rep++) {
					for (i = 0; i < b; i++) {
						u[i] = (double) rand() / (double) (RAND_MAX) - 0.5;
					}
					for (i = 0; i < b; i++) {
						q[i] = 0;
					}

					for (i = 1; i <= 20; i++) {
						i = 1;
						y = ran1f(b, u, q);
//						fprintf(stdout, "  %2d  %6d  %10f\n", b, idx, y);
						//*(signalNoise + idx) = y;
						*(signalNoise + idx + rep - 1) = y;
						//*(signalNoise[rep - 1] + idx) = y;
						if (++idx >= ATOM_COUNT) {
							return;
						}
					}
				}
				free(q);
				free(u);
			}
		}

		return;
	}
};

/*****************************************************************************/

template <typename _Traits>
struct Test {
    Test(const std::string &a_fName) :
      m_fName(a_fName), m_file(a_fName),
      m_input(std::make_shared<isig::RandomAccessFile>(a_fName)) {}
    ~Test()
    {
        remove(m_fName.c_str());
    }

    const std::string           m_fName;
    TestFile<_Traits>           m_file;
    isig::RandomAccessBufferPtr m_input;
};

Test<Simul5Long> g_testLong("./simul_dod_long.bin");
Test<Simul5Double> g_testDouble("./simul_dod_double.bin");

/*****************************************************************************/

template <typename _Traits>
class SimulDoDFile : public isig::DataOnDemandSource<_Traits> {
public:
    typedef isig::DataOnDemandSource<_Traits> BaseDoD;
public:
    SimulDoDFile(Test<_Traits> &a_test)
    : BaseDoD("simul-dod-" + istd::CppName(typeid(_Traits)), a_test.m_input)
    {
        auto bc = std::make_shared<TestCircularBufferController>(ATOM_COUNT, 1);
        auto dc = std::dynamic_pointer_cast<isig::DodPositionController>(bc);
        istd_TRC(istd::eTrcLow, "Configuring DdcSignalNew");
        this->SetPositionController(dc);
        this->Open();
    }

    virtual ~SimulDoDFile() {
        this->Close();
    }
};

class SimulBuffer: public isig::RandomAccessBuffer {
public:
    SimulBuffer() : RandomAccessBuffer(ATOM_COUNT) {}
    virtual ~SimulBuffer() {}
protected:
    virtual size_t QueryByteSize()
    {
        size_t s(ATOM_COUNT*sizeof(int32_t)*4);
        return s;
    }
    virtual void OpenInput() {}
    virtual void CloseInput() {}
    virtual std::size_t  ReadInput(
        void* a_buf,
        size_t a_count,
        size_t a_position)
    {
        static const double c_maxLevel(10000); // sampled signal level
        static const double c_decay = 0.99; // decay factor
        static const double c_rise = 0.1; // rise factor
        static const double c_fo = 0.95; //sample frequency offset

        int32_t *buf = static_cast<int32_t *>(a_buf);
        size_t cnt = a_count/sizeof(int32_t)/4;

        // random phase noise
        double phA = rand()/(double)RAND_MAX;
        double phB = rand()/(double)RAND_MAX;
        double phC = rand()/(double)RAND_MAX;
        double phD = rand()/(double)RAND_MAX;

        double signal = 0;
        for (size_t i(0); i < cnt; ++i) {
            if (i>300 && i < 350) { // pulse interval
                signal += (1-signal)*c_rise;
            }
            signal *= c_decay;
            buf[4*i+0] = signal*sin(i*M_PI/2*c_fo+phA)*c_maxLevel;
            buf[4*i+1] = signal*sin(i*M_PI/2*c_fo+phB)*c_maxLevel;
            buf[4*i+2] = signal*sin(i*M_PI/2*c_fo+phC)*c_maxLevel;
            buf[4*i+3] = signal*sin(i*M_PI/2*c_fo+phD)*c_maxLevel;
        }
        return a_count;
    }
};

isig::RandomAccessBufferPtr g_simulBuffer(std::make_shared<SimulBuffer>());

class SimulDoD : public isig::DataOnDemandSource<Simul5Long> {
public:
    typedef isig::DataOnDemandSource<Simul5Long> BaseDoD;
    SimulDoD() : BaseDoD("simul-dod", g_simulBuffer)
    {
        auto bc = std::make_shared<TestCircularBufferController>(ATOM_COUNT, 1);
        auto dc = std::dynamic_pointer_cast<isig::DodPositionController>(bc);
        istd_TRC(istd::eTrcLow, "Configuring DdcSignalNew");
        this->SetPositionController(dc);
        this->Open();
    }
};

