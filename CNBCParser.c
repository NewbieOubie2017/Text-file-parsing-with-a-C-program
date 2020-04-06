#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>     /* exit */

/* Maximum number of lines to read */
#define TEXT_LINES_CAPACITY 800
/* Maximum length of a line including EOL and NUL */
#define MAX_LINE_LEN 200

/* Global variables */
char text_lines[TEXT_LINES_CAPACITY][MAX_LINE_LEN];  /* text of lines */
int number_of_lines = 0;  /* number of lines in text_lines */
void read_in_text_file(void);
void writer_in_text_file(void);
int startLatest = 0, endLatest = 0, startLatestNews = 0, endLatestNews = 0;
char stringA[] = "## Latest News";
char stringB[] = "[Market Movers]";
char stringC[] = "### Latest Market News";
char stringD[] = "### Special Reports";
FILE *file_ptr;
int i = 0;
FILE *file_pointer;

int main() {
    time_t elapsed ;
    struct tm *now ;

    /* Get the current time. */
    elapsed = time(NULL) ;

    /* Convert it to local time representation. */
    now = localtime( &elapsed ) ;

    file_pointer = fopen("cnbcLog.txt", "a");
    file_ptr = fopen("cnbc2.txt", "r");
    fputs(asctime( now ), file_pointer );
    fputs("\n", file_pointer );

    /* Read in the contents of the file. */
    read_in_text_file();
    writer_in_text_file();


}

/* Open a text file and read it in line by line.  The lines are stored in the
 * global variable text_lines and the number of lines in number_of_lines. */
void read_in_text_file(void)
{
    static const char filename[] = "cnbc2.txt";
    FILE *file = fopen(filename,"r"); /* opens the cnbc2 file */

    if (file == NULL)
    {
        /* Print error message after the file name. */
        perror(filename);
        exit(1);  /* Exit with failure code (nonzero) */
    }
    else
    {
        /* Read each line of the text file. */
        while (number_of_lines < TEXT_LINES_CAPACITY &&
                fgets(text_lines[number_of_lines], MAX_LINE_LEN, file) != NULL)
        {
            if((strstr(text_lines[number_of_lines], stringA) != NULL) && (startLatest == 0))
            {
                startLatest = number_of_lines;
                /*
                printf("latest news line is  ");
                printf(text_lines[number_of_lines]);
                printf(" line number = %d", number_of_lines);
                printf("\n"); */
            }
            if((strstr(text_lines[number_of_lines], stringB) != NULL) && (endLatest == 0))
            {
                endLatest = number_of_lines;
            }
            if(strstr(text_lines[number_of_lines], stringD) != NULL)
            {
                endLatestNews = number_of_lines;
            }
            if(strstr(text_lines[number_of_lines], stringC) != NULL)
            {
                startLatestNews = number_of_lines;
            }
            ++number_of_lines;
        }
    fclose(file);
    }
}

void writer_in_text_file(void)
{
    static const char filename[] = "cnbc2.txt";
    FILE *file = fopen(filename,"r"); /* opens the cnbc2 file */

if (file == NULL)
    {
        /* Print error message after the file name. */
        perror(filename);
        exit(1);  /* Exit with failure code (nonzero) */
    }
    else
    {
        /* Write each line of the selected text. */
        char stringS[] = "\n*********************\n";
        fputs(stringS, file_pointer);
        number_of_lines = 0;
        while (number_of_lines < TEXT_LINES_CAPACITY &&
                fgets(text_lines[number_of_lines], MAX_LINE_LEN, file) != NULL)
        {
            //printf("number of line = %d, startLatest = %d", number_of_lines, startLatest);
            if((number_of_lines >= startLatest) && (number_of_lines < endLatest))
            {
                fputs(text_lines[number_of_lines], file_pointer);
            }
            if(number_of_lines == (endLatest + 1))
            {
                fputs(stringS, file_pointer);
            }
            if((number_of_lines >= startLatestNews) && (number_of_lines < endLatestNews))
            {
                fputs(text_lines[number_of_lines], file_pointer);
            }
            ++number_of_lines;
        }
        fputs(stringS, file_pointer);
        fclose(file_pointer);
        fclose(file);

    }

}


