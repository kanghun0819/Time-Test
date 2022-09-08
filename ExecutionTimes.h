#if !defined(__EXECUTIONTIMES_H__)
#define __EXECUTIONTIMES_H__

#include <vector>
#include <string>
#include <map>


using namespace std;


//-----------------------------------------------------------------------------
/** \brief	The CExecutionTimes class do the following function.
\author		Kyung-dong Song (kdsong@netian.com)
\version	1.0.0
\date		2006-05-17 17:35:38*/
//-----------------------------------------------------------------------------
class CExecutionTimes
{
public:
	typedef struct tagEXECTIME
	{
		double	Max;
		double	Min;
		double	Sum;
		double	StartTime;
		double   EndTime;
		double	Count;
		double	MillCount;
		double	Start;
	    string 	Title;  //??
	} EXECTIME, *PEXECTIME;



	int Add(string title)
	{
	
		EXECTIME et;
		et.Max = -9E50;
		et.Min = 9E50;	
		et.Sum = 0.0;
		et.StartTime = 0.0;
		et.EndTime=0.0;
		et.Count = 0;
		et.MillCount = 0;
		et.Title = "Status";
		et.Title = title;
		m_vExecTime.push_back(et);
		return m_vExecTime.size();
		

		
	}

	void Begin(int nID)				 
	{
		
		EXECTIME& et = m_vExecTime[nID-1];
		et.StartTime = micros(); 
		//??QueryPerformanceCounter(&et.Start);
	}

	double End(int nID)
	{
		
		EXECTIME& et = m_vExecTime[nID-1];
		String title;
		//std::string title = et.Title;
		et.EndTime = micros();
		et.EndTime = (double)(et.EndTime-et.StartTime)/1000000;
		//??LARGE_INTEGER current;
		//??QueryPerformanceCounter(&current);
		//??et.CurrTime = (double)(current.QuadPart-et.Start.QuadPart)/
		//??			  (double)m_freq.QuadPart;

		if (et.EndTime > et.Max) et.Max = et.EndTime;
		if (et.EndTime < et.Min) et.Min = et.EndTime;
		et.Count++;
		et.Sum += et.EndTime;
		if (et.Count == 10)
		{
			//Serial.print("Title\t");
			Serial.print("Last\t");
			Serial.print("Average\t");
			Serial.print("Min\t");
			Serial.print("Max\t");
			Serial.print("Count\t");
			Serial.print("M C\t");
			Serial.print("\n");
			//Serial.print(title);
			//Serial.print("\t");
			Serial.print(et.EndTime);
			Serial.print("\t");
			Serial.print(et.Sum/et.Count);
			Serial.print("\t");
			Serial.print(et.Min);
			Serial.print("\t");
			Serial.print(et.Max);
			Serial.print("\t");
			Serial.print(et.MillCount);
			Serial.print("\n");
			et.Count = 0;
		}
		return et.EndTime;
	

	}

	
	void SetTitle(int nID, string title)
	{
		if ((nID <= 0) || (nID > m_vExecTime.size())) return;

		m_vExecTime[nID-1].Title = title;
	}

	void Clear(int nID)
	{
		if (nID == -1)
		{
			for (int i=0; i<m_vExecTime.size(); ++i)
			{
				EXECTIME& et = m_vExecTime[i];
				et.Max = -9E50;
				et.Min = 9E50;	
				et.Sum = 0.0;
				et.StartTime=0.0;
				et.EndTime = 0.0;
				et.Count = 0;
				et.MillCount = 0;
			}
			return;
		}

		if ((nID <= 0) || (nID > m_vExecTime.size())) return;
		EXECTIME& et = m_vExecTime[nID-1];

		et.Max = -9E50;
		et.Min = 9E50;	
		et.Sum = 0.0;
		et.StartTime=0.0;
		et.EndTime=0.0;
		et.Count = 0;
		et.MillCount = 0;
	}

protected:

  
// member variables   
protected:
	vector<EXECTIME>	m_vExecTime;
};

#endif // !defined(__EXECUTIONTIMES_H__)
