#include <stdio.h>
#include <stdlib.h>

int find(int no_of_frames, int *frames, int tofound)
{
    int index = -1;
    for (int i = 0; i < no_of_frames; i++)
    {
        if (frames[i] == tofound)
        {
            index = i;
        }
    }
    return index;
}

int traverse(int no_of_pages, int *pageString, int i, int tofound)
{
    int index = -1;
    for (int j = i + 1; j < no_of_pages; j++)
    {
        if (pageString[j] == tofound)
        {
            return j;
        }
    }
    return index;
}

int find_optimal(int *pageString, int i, int no_of_pages, int no_of_frames, int *frames)
{
    int *flag;
    flag = (int *)calloc(no_of_frames, sizeof(int));
    for (int j = 0; j < no_of_frames; j++)
    {
        flag[j] = 0;
    }
    int index = -1;
    int idx = -1;
    int max = -1;
    for (int j = 0; j < no_of_frames; j++)
    {
        idx = traverse(no_of_pages, pageString, i, frames[j]);
        if (idx != -1)
        {
            if (idx > max)
            {
                max = idx;
                index = j;
            }
            flag[j] = 1;
        }
    }
    for (int j = 0; j < no_of_frames; j++)
    {
        if (flag[j] == 0)
        {
            index = j;
            break;
        }
    }
    free(flag);
    return index;
}

int main()
{
    int no_of_frames, no_of_pages;
    printf("Enter the no of frames:\n");
    scanf("%d", &no_of_frames);
    printf("Enter the no of pages:\n");
    scanf("%d", &no_of_pages);
    printf("Enter the pageString\n");
    int *pageString;
    pageString = (int *)calloc(no_of_pages, sizeof(int));
    for (int i = 0; i < no_of_pages; i++)
    {
        scanf("%d", &pageString[i]);
    }
    int *frames;
    frames = (int *)calloc(no_of_frames, sizeof(int));
    for (int i = 0; i < no_of_frames; i++)
    {
        frames[i] = -1;
    }
    int index = 0;
    int no_of_page_faults = 0;
    int no_of_page_hits = 0;
    int idx;
    int count = 0;
    for (int i = 0; i < no_of_pages; i++)
    {
        if (count < no_of_frames)
        {
            idx = find(no_of_frames, frames, pageString[i]);
            if (idx != -1)
            {
                no_of_page_hits++;
                printf("Page Hit : Succesfully found Page %d at %d Frame\n", pageString[i], idx + 1);
            }
            else
            {
                frames[count] = pageString[i];
                printf("Page Miss : Storing %d Page no in %d Frame:\n", pageString[i], count + 1);
                count++;
                no_of_page_faults++;
            }
        }
        else
        {
            idx = find(no_of_frames, frames, pageString[i]);
            if (idx != -1)
            {
                no_of_page_hits++;
                printf("Page Hit : Succesfully found Page %d at %d Frame\n", pageString[i], idx + 1);
            }
            else
            {
                index = find_optimal(pageString, i, no_of_pages, no_of_frames, frames);
                printf("Page Miss : Replacing %d Frame Page with %d Page no:\n", index + 1, pageString[i]);
                no_of_page_faults++;
                frames[index] = pageString[i];
            }
        }
    }
    printf("The total number of page faults are : %d\n", no_of_page_faults);
    printf("The total number of page hits are : %d\n", no_of_page_hits);
    return 0;
}