#include <mysql.h>
#include "PJ_RPI.h"
#include <stdio.h>
#include <stdbool.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}
int main(int argc, char **argv)
{
    bool inp17 = false;
    bool inp26 = false;
    bool inp10 = false;

    if (map_peripheral(&gpio) == -1)
    {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -1;
    }

    // Define a few GPIO's as input
    INP_GPIO(17); // black
    INP_GPIO(26); // yellow
    INP_GPIO(10); // red

    MYSQL *con = mysql_init(NULL);
    printf("MySQL client version: %s\n", mysql_get_client_info());
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    if (mysql_real_connect(con, "localhost", "webuser", "secretpassword_vives", "GPIOLoggings", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    while (1)
    {
        /////////////
        // GPIO 17 //
        /////////////
        if (GPIO_READ(17))
        {
            if (inp17 == false)
            {
                printf("GPIO17 switched to high\n");
                inp17 = true;
                // add to database
                if (mysql_query(con, "INSERT INTO `GPIOLoggings`.`logs` (`GPIO`, `state`) VALUES ('17', '1');"))
                {
                    finish_with_error(con);
                }
            }
        }
        else
        {
            if (inp17 == true)
            {
                printf("GPIO17 switched to low\n");
                inp17 = false;
                // add to database
                if (mysql_query(con, "INSERT INTO `GPIOLoggings`.`logs` (`GPIO`, `state`) VALUES ('17', '0');"))
                {
                    finish_with_error(con);
                }
            }
        }
        /////////////
        // GPIO 26 //
        /////////////
        if (GPIO_READ(26))
        {
            if (inp26 == false)
            {
                printf("GPIO26 switched to high\n");
                inp26 = true;
                // add to database
            }
        }
        else
        {
            if (inp26 == true)
            {
                printf("GPIO26 switched to low\n");
                inp26 = false;
                // add to database
            }
        }
        /////////////
        // GPIO 10 //
        /////////////
        if (GPIO_READ(10))
        {
            if (inp10 == false)
            {
                printf("GPIO10 switched to high\n");
                inp10 = true;
                // add to database
            }
        }
        else
        {
            if (inp10 == true)
            {
                printf("GPIO10 switched to low\n");
                inp10 = false;
                // add to database
            }
        }
        sleep(1);
    }
    mysql_close(con);
    return 0;
}