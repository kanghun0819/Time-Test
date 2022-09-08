#include "ExecutionTimes.h"
#include <math.h>
#include <stdlib.h>

CExecutionTimes g_ets;
short g_id1;
short g_id2;
long g_count;
int g_cnt1;
int g_cnt2;
void setup()
{
	Serial.begin(115200);
    g_id1 = g_ets.Add("1ST Time");
    g_id2 = g_ets.Add("2ST Time");
    g_count = 0;
    g_cnt2=0;
   
}

void loop()
{   
    g_ets.Begin(g_id1);
        delay(1000);
    g_ets.End(g_id1);
    //Serial.print(g_id2);

    g_ets.Begin(g_id2);
        double sum = 0;
        g_cnt2 = g_cnt2+1;
        Serial.println(g_cnt2);
        for (int i=0; i<10000; ++i)
        {
            sum += (double)i;
            
        }
    (g_ets.End(g_id2));

  
}
