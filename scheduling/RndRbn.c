#include<stdio.h>


int isFinish(int finish[], int n_process)
{
    int i;
    for(i=0;i<n_process;i++)
    {
        if(finish[i]==0)
        {
            return 0;
        }
    }

    return 1;
}


int InQueue(int tmpQue[], int tq, int i)
{
    int j;
    for(j=0;j<=tq;j++)
    {
        if(tmpQue[j]==i)
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n_process,i,j,x,f;

    printf("\nEnter no of process: ");
    scanf("%d", &n_process);

    int values[n_process][3];

    printf("\nEnter Arrival Time and Burst Time\n");
    for(i=0;i<n_process;i++)
    {
        scanf("%d %d", &values[i][1], &values[i][2]);
        values[i][0] = i;
    }


    int timeQ;
    printf("\nEnter Time Quantum: ");
    scanf("%d", &timeQ);

    int finish[n_process];
    for(i=0;i<n_process;i++)
    {
        finish[i] = 0;
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

                x = values[i][0];                           //  Sorting based on Arrival Time
                values[i][0] = values[j][0];
                values[j][0] = x;

                x = values[i][2];
                values[i][2] = values[j][2];
                values[j][2] = x;
            }
        }
    }


    int rmng[n_process];
    for(i=0;i<n_process;i++)
    {
        rmng[values[i][0]] = values[i][2];
    }

    int IdleTime[10000];
    int it=-1;

    int tmpQue[n_process];
    int tq = -1;
    int prs_Seq[10000];
    int tp = -1;

    int time = 0;
    int p = 0;

    int finish_Time[n_process];

    while(!(isFinish(finish, n_process)))
    {
        f = 0;
        for(i=0;i<n_process;i++)
        {
            if(!(InQueue(tmpQue, tq, i)))
            {
                if(!(finish[values[i][0]]))
                {
                    if(values[i][1]<=time)
                    {
                        tq++;
                        tmpQue[tq] = i;
                        f = 1;
                    }
                    else
                    {
                        if(!f)
                        {
                            tp++;
                            prs_Seq[tp] = -1;
                            it++;
                            IdleTime[it] = time;
                        }
                        break;
                    }
                }
            }
        }


        if(tq!=-1)
        {
            
            
            p = (p+1)%(tq+1);
            while(finish[values[tmpQue[p]][0]])
            {
                p = (p+1)%(tq+1);
            }
            

            tp++;
            prs_Seq[tp] = values[tmpQue[p]][0] + 1;
            if(tp!=0)
            {
                if(prs_Seq[tp]!=prs_Seq[tp-1])
                {
                    printf("Context Switch from P%d to P%d at Time %d\n", prs_Seq[tp-1], prs_Seq[tp], time);
                }
            }

            if(rmng[values[tmpQue[p]][0]] <= timeQ)
            {
                time = time + rmng[values[tmpQue[p]][0]] - 1;

                finish_Time[values[tmpQue[p]][0]] = time + 1;
                finish[values[tmpQue[p]][0]] = 1;                
            }
            else
            {
                rmng[values[tmpQue[p]][0]] = rmng[values[tmpQue[p]][0]] - timeQ;
                time = time + timeQ - 1;
            }
            
        }


        time++;

    }

    printf("\nProcess TimeLine\n");
    for(i=0;i<=tp;i++)
    {
        printf("%d ", prs_Seq[i]);
    }


    printf("\n\nFinish Times\nProcess : Time\n");
    for(i=0;i<n_process;i++)
    {
        printf("%d\t%d\n", i+1, finish_Time[i]);
    }

    int Tat[n_process];
    int waitTime[n_process];
    for(i=0;i<n_process;i++)
    {
        Tat[values[i][0]] = finish_Time[values[i][0]] - values[i][1];
        waitTime[values[i][0]] = Tat[values[i][0]] - values[i][2];
    }


    printf("\n\nTurn Around Time\nProcess : Time\n");
    for(i=0;i<n_process;i++)
    {
        printf("%d\t%d\n", i+1, Tat[i]);
    }


    printf("\n\nWait Time\nProcess : Time\n");
    for(i=0;i<n_process;i++)
    {
        printf("%d\t%d\n", i+1, waitTime[i]);
    }

    printf("\n\nIdle Time\n");
    for(i=0;i<=it;i++)
    {
        printf("%d ", IdleTime[i]);
    }

}