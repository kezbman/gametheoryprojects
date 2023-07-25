#include <iostream>
using namespace std;

void getData(int **nig, int row, int col, char mode)
{
    if (mode == 'b')
    {
        for (int i = 0; i < row; i++)
        {
            cout << "\tRow " << i + 1 << endl;
            for (int j = 0; j < col; j++)
            {
                cout << "Enter the element [" << i << "][" << j << "]: ";
                cin >> nig[i][j];
            }
        }
    }
    else if (mode == 'g')
    {
        for (int i = 0; i < col; i++)
        {
            cout << "\tColumn " << i + 1 << endl;
            for (int j = 0; j < row; j++)
            {
                cout << "Enter the element [" << j << "][" << i << "]: ";
                cin >> nig[j][i];
            }
        }
    }
}

int findPartner(int girl, int *result, int size)
{
    for (int i = 0; i < size; i++)
        if (result[i] == girl)
            return i;
}
void matching(int **boy, int **girl, int *result, int rows, int columns)
{

    for (int i = 0; i < rows; i++)
        result[i] = -1;
    bool firstFlag[rows] = {0};
    bool secondFlag[columns] = {0};
    bool bruh = true;
    while (bruh)
    {
        for (int i = 0; i < rows; i++)
        {
            if (firstFlag[i] == true) // either already engaged or has no one to propose to
                continue;
            else if (firstFlag[i] == false)
            {
                if (boy[i][result[i]] == columns)
                {
                    // This player is going to have to be alone.
                    result[i] = -1;
                    firstFlag[i] = true;
                    continue;
                }
                for (int j = result[i] == -1 ? 1 : boy[i][result[i]] + 1; j <= columns; j++) // finding the next person to propose to
                {
                    for (int k = 0; k < columns; k++)
                    {
                        if (boy[i][k] == j)
                        {
                            if (secondFlag[k] == false)
                            { // They will get engaged
                                firstFlag[i] = true;
                                secondFlag[k] = true;
                                result[i] = k;
                                j = columns + 1;
                            }
                            else if (secondFlag[k] == true)
                            {
                                int temp = findPartner(k, result, rows);
                                if (girl[i][k] < girl[temp][k])
                                { // exchange
                                    result[i] = k;
                                    secondFlag[k] = true;
                                    firstFlag[i] = true;
                                    firstFlag[temp] = false;
                                    j = columns + 1;
                                }
                            }
                            if (j == columns && firstFlag[i] == false)
                            { // they are all either engaged or don't want to exchange
                                result[i] = -1;
                                firstFlag[i] = true;
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (columns <= rows)
        {
            for (int i = 0; i < columns; i++)
            {
                if (secondFlag[i] == false)
                    break;
                else if (i == columns - 1 && secondFlag[i] == true)
                {
                    bruh = false;
                    break;
                }
            }
        }
        else if (columns > rows)
        {
            for (int i = 0; i < rows; i++)
            {
                if (firstFlag[i] == false)
                    break;
                else if (i == rows - 1 && firstFlag[i] == true)
                {
                    bruh = false;
                    break;
                }
            }
        }
    }
}
int main()
{
    int rows, columns;
    cout << "Enter the number of boys (the amount of rows): ";
    cin >> rows;
    while (rows <= 0)
    {
        cout << "Please enter a positive number: " << endl;
        cin >> rows;
    }
    cout << "Enter the number of girls (the amount of columns): ";
    cin >> columns;
    while (columns <= 0)
    {
        cout << "Please enter a positive number: " << endl;
        cin >> columns;
    }
    int **boys = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        boys[i] = new int[columns];
    }
    int **girls = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        girls[i] = new int[columns];
    }
    cout << "Getting the preferences of the boys..." << endl;
    getData(boys, rows, columns, 'b');
    cout << "Getting the prefrences of the girls..." << endl;
    getData(girls, rows, columns, 'g');
    string choice;
    cout << "Do you want the matching to be boy-optimal ot girl-optimal?(boy/girl) " << endl;
    cin >> choice;
    if (choice == "boy")
    {
        int res[rows];
        matching(boys, girls, res, rows, columns);
        for (int i = 0; i < rows; i++)
        {
            if (res[i] == -1)
                cout << "The boy[" << i + 1 << "] is single." << endl;
            else
                cout << "The boy[" << i + 1 << "] is married to girl[" << res[i] + 1 << "]." << endl;
        }
    }
    else
    {
        int res[columns];
        matching(girls, boys, res, rows, columns); // we assume that girls are boys and boys are girls :)
        for (int i = 0; i < columns; i++)
        {
            if (res[i] == -1)
                cout << "The girl[" << i + 1 << "] is single." << endl;
            else
                cout << "The girl[" << i + 1 << "] is married to boy[" << res[i] + 1 << "]." << endl;
        }
    }
    return 0;
}
