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


int main()
{
    int n_process,i,x,j,f;
    printf("\nEnter no of Process: ");
    scanf("%d", &n_process);

    int values[n_process][4];
    printf("\nEnter arrival Time, Burst Time and Priority\n");

    for(i=0;i<n_process;i++)
    {
        scanf("%d %d %d", &values[i][1], &values[i][2], &values[i][3]);
        values[i][0] = i;
    }

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

                x = values[i][3];
                values[i][3] = values[j][3];
                values[j][3] = x;

            }
        }
    }


    int time = 0;
    int tmpQue[n_process];
    int tq = -1; 
    int prs_Seq[10000];
    int tp = -1;
    int min;

    int prs_Time[n_process][2];

    while (!(isFinish(finish, n_process)))
    {
        tq = -1;
        f = 0;

        for(i=0;i<n_process;i++)
        {
            if(!finish[values[i][0]])
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
                    }

                    break;
                }
                

            }
        }

        if(f)
        {
            min = 100000;

            for(i=0;i<=tq;i++)
            {
                if(values[ tmpQue[i] ][3]<min)
                {
                    min = values[ tmpQue[i] ][3];
                    j = tmpQue[i];
                }
            }

            prs_Time[values[j][0]][0] = time;
            time = time + values[j][2] - 1;
            finish[values[j][0]] = 1;
            prs_Time[values[j][0]][1] = time + 1;

            tp++;
            prs_Seq[tp] = values[j][0]+1;
        }
        time++;

    }
    

    printf("\nProcess Timeline\n");
    for(i=0;i<=tp;i++)
    {
        printf("%d  ", prs_Seq[i]);
    }

    printf("\n\nProcess Start End\n");
    for(i=0;i<n_process;i++)
    {
        printf("%d\t%d\t%d\n", i+1, prs_Time[i][0], prs_Time[i][1]);
    }



    int Tat[n_process];
    int WaitTime[n_process];

    for(i=0;i<n_process;i++)
    {
        Tat[values[i][0]] = prs_Time[values[i][0]][1] - values[i][1];
        WaitTime[values[i][0]] = Tat[values[i][0]] - values[i][2];
    }

    printf("\n\nProcess number  Turn Around Time");
    for(i=0;i<n_process;i++)
    {
        printf("\n%d \t\t %d", i+1, Tat[i]);
    }

    printf("\n\nProcess number  Waiting Time");
    for(i=0;i<n_process;i++)
    {
        printf("\n%d \t\t %d", i+1, WaitTime[i]);
    }


    
    
    int CntxtSw[10000][3];
    int tc = -1;
    int IdleTime[1000][2];
    int it = -1;
    int c;

    for(i=0;i<=tp;i++)
    {
        if(prs_Seq[i]!=-1)
        {
            if(i!=tp)
            {
                tc++;
                CntxtSw[tc][0] = prs_Seq[i];
                CntxtSw[tc][1] = prs_Seq[i+1];
                CntxtSw[tc][2] = prs_Time[ prs_Seq[i]-1 ][1];
            }
        }
    }


    for(i=0;i<=tp;i++)
    {
        c = 0;
        if(prs_Seq[i]==-1)
        {
            if(i==0)
            {
                j = i;
                while(prs_Seq[j]==-1)
                {
                    c++;
                    j++;
                }

                it++;
                IdleTime[it][0] = i;
                IdleTime[it][1] = i+c;
                i = j - 1;
            }
            else
            {
                it++;
                IdleTime[it][0] = prs_Time[ prs_Seq[i-1] ][1];
                j = i;
                while(prs_Seq[j]==-1)
                {
                    c++;
                    j++;
                }

                IdleTime[it][1] = IdleTime[it][0] + c;
                i = j-1;
            }
            
        }
    }


    printf("\n\nContext Switch\nFrom  To  Time\n");
    for(i=0;i<=tc;i++)
    {
            printf("%d\t%d\t%d\n", CntxtSw[i][0], CntxtSw[i][1], CntxtSw[i][2]);
    }

    printf("\n\nIdle Time\nStart  End\n");
    for(i=0;i<=it;i++)
    {
        printf("%d\t%d\n", IdleTime[i][0], IdleTime[i][1]);
    }


    printf("\n");



}