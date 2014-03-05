#pragma once
#include "Instrument.h"
#include "audio/wave.h"
#include "audio/DirSoundStream.h"
#include "audio/DirSoundSource.h"
#include "audio/WaveformBuffer.h"
class CRecorded :
	public CInstrument
{
public:
	CRecorded(void);
	virtual ~CRecorded(void);

	virtual void SetNote(CNote *note);

	virtual void Start();
	virtual bool Generate();

	void ProcessReadFrame(short *p_frame);

	bool LoadFile();

private:
	CDirSoundSource m_waveFile; //The wavefile

	double m_duration; //Length of the sample
	double m_beatDuration; //Length of sample in beats
	double m_time; //Current time
};

