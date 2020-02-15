#include<stdio.h>

int main()
{
    int n_process,i,j,x;
    printf("\nEnter no of Process: ");
    scanf("%d", &n_process);

    int values[n_process][3];        // values[x][0] = Process number, values[x][1] = Arrival Time , values[x][2] = Burst Time


    printf("\nEnter Arrival Time and Burst Time\n");
    for(i=0;i<n_process;i++)
    {
        scanf("%d %d", &values[i][1], &values[i][2]);
        values[i][0] = i;
    }


    for(i=0;i<n_process;i++)
    {
        for(j=i+1;j<n_process;j++)
        {
            if(values[i][1]>values[j][1])
            {
                x = values[i][1];
                values[i][1] = values[j][1];
                values[j][1] = x;

                x = values[i][0];
                values[i][0] = values[j][0];
                values[j][0] = x;

                x = values[i][2];
                values[i][2] = values[j][2];
                values[j][2] = x;
            }
        }
    }

    x = 0;

    int prs_Seq[n_process][3];  // prs_Seq[x][0] = start Time ; prs_Seq[x][1] = end Time ; prs_Seq[x][2] = process number
    int tp = -1;

    int IdleTime[n_process][2];   // IdleTime[x][0] = start time ;  IdleTime[x][1] = end time
    int ti = -1;

    int TaT[n_process];
    int waitTime[n_process];

    for(i=0;i<n_process;i++)
    {
        if(x<values[i][1])
        {
            ti++;
            IdleTime[ti][0] = x;
            IdleTime[ti][1] = values[i][1];

            x = values[i][1] + values[i][2];

            

            tp++;
            prs_Seq[tp][0] = values[i][1];
            prs_Seq[tp][1] = x;
            prs_Seq[tp][2] = values[i][0];

        }
        else
        {
            tp++;
            prs_Seq[tp][0] = x;

            x = x + values[tp][2];

            prs_Seq[tp][1] = x;
            prs_Seq[tp][2] = values[i][0];

            
        }


        TaT[values[i][0]] = x - values[i][1];
        waitTime[values[i][0]] = TaT[values[i][0]] - values[i][2];
        
    }


    printf("\n\nProcess Timeline");
    for(i=0;i<n_process;i++)
    {
        printf("\n%d---%d Process = %d",prs_Seq[i][0], prs_Seq[i][1], prs_Seq[i][2] + 1);
    }

    printf("\n\nCPU Idle Time");
    for(i=0;i<=ti;i++)
    {
        printf("\n%d---%d", IdleTime[i][0], IdleTime[i][1]);
    }

    printf("\n\nProcess number  Turn Around Time");
    for(i=0;i<n_process;i++)
    {
        printf("\n%d \t\t %d", i+1, TaT[i]);
    }

    printf("\n\nProcess number  Waiting Time");
    for(i=0;i<n_process;i++)
    {
        printf("\n%d \t\t %d", i+1, waitTime[i]);
    }

    printf("\n");
}
