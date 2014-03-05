#include "StdAfx.h"
#include "Recorded.h"


CRecorded::CRecorded(void)
{
	m_sampleRate = 44100;
	m_duration = 0;
	m_beatDuration = 0;
	m_time = 0;
	LoadFile();
}

bool CRecorded::LoadFile(void)
{
	if(!m_waveFile.Open(".\\media\\shortskirtmet2.wav"))
		return FALSE;

	m_sampleRate = m_waveFile.SampleRate();
	m_duration = m_waveFile.GetDuration();
	m_beatDuration = m_duration * (m_bpmMaster / 60);
   
	return TRUE;
}


CRecorded::~CRecorded(void)
{
}

void CRecorded::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for(int i=0;  i<len;  i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "sample")
        {
        }
    }
}

void CRecorded::ProcessReadFrame(short *p_frame)
{
   m_waveFile.ReadFrame(p_frame);
}

void CRecorded::Start(void)
{
	m_time = 0;
	m_waveFile.Rewind();
}

bool CRecorded::Generate(void)
{
	short temp[2];
	ProcessReadFrame(temp);
	m_frame[0] = double(temp[0]) / 32767.0;
	m_frame[1] = double(temp[1]) / 32767.0;
	m_time += GetSamplePeriod();
	return m_time < m_duration;
}
