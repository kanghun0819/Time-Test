#include <Arduino.h>
#line 22 "c:\\Users\\SWSEO\\source\\GHKIM\\ESP32\\TESTESP32.ino"
void setup();
#line 38 "c:\\Users\\SWSEO\\source\\GHKIM\\ESP32\\TESTESP32.ino"
void loop();
#line 0 "c:\\Users\\SWSEO\\source\\GHKIM\\ESP32\\TESTESP32.ino"
#line 1 "c:\\Users\\SWSEO\\source\\GHKIM\\ESP32\\ExecutionTimes.h"
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
		double  EndTime;
		double	Start;
		long	Count;
		long	MillCount;
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

	void End(int nID, double *Last, double *Avg, double *Max, double *Min, int *mcnt)
	{
		
		EXECTIME& et = m_vExecTime[nID-1];
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
		
		
		*Last = et.EndTime;
		*Avg = et.Sum/et.Count;
		*Max = et.Max;
		*Min = et.Min;
		//*cnt = et.Count;
		*mcnt = et.MillCount;
		//return et.EndTime;
	

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

#line 1 "c:\\Users\\SWSEO\\source\\GHKIM\\ESP32\\TESTESP32.ino"
#include "ExecutionTimes.h"
#include <math.h>
#include <stdlib.h>

CExecutionTimes g_ets;
short g_id1;
short g_id2;

long g_count;
int g_cnt1;
int g_cnt2;


double g_avg[2];
double g_max[2];
double g_min[2];
double g_last[2];
int g_mc[2];

int g_temp;

void setup()
{
	Serial.begin(115200);
    g_id1 = g_ets.Add("1ST Time");
    g_id2 = g_ets.Add("2ST Time");
    g_count = 0;
    g_cnt2=0;
    Serial.print("Last\t");
	Serial.print("Average\t");
	Serial.print("Min\t");
	Serial.print("Max\t");
	Serial.print("Count\t");
	Serial.print("M C\t");
	Serial.print("\n");
}

void loop()
{   

    g_count++;
    g_ets.Begin(g_id1);
        delay(1000);
    g_ets.End(g_id1, &g_last[0], &g_avg[0], &g_max[0], &g_min[0], &g_mc[0]);
    
    Serial.print(g_id1);
    Serial.print("\t");
    Serial.print(g_last[0]);
    Serial.print("\t");
    Serial.print(g_avg[0]);
    Serial.print("\t");
    Serial.print(g_max[0]);
    Serial.print("\t");
    Serial.print(g_min[0]);
    Serial.print("\t");
    Serial.print(g_mc[0]);
    Serial.println();
    
  
    

    g_ets.Begin(g_id2);
        double sum = 0;
        for (int i=0; i<1000000; ++i)
        {
            sum += (double)(rand()%10);            
        }
    g_ets.End(g_id2, &g_last[1], &g_avg[1], &g_max[1], &g_min[1], &g_mc[1]);

    Serial.print(g_id2);
    Serial.print("\t");
    Serial.print(g_last[1]);
    Serial.print("\t");
    Serial.print(g_avg[1]);
    Serial.print("\t");
    Serial.print(g_max[1]);
    Serial.print("\t");
    Serial.print(g_min[1]);
    Serial.print("\t");
    Serial.print(g_mc[1]);
    Serial.print("\t");
    Serial.print(sum);
    Serial.println();


  
}

