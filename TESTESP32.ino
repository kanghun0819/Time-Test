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
