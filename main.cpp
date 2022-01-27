#include <iostream>
#include <fstream>
#include <algorithm>
#define INT_MAX 9999999
using namespace std;

struct server
{
    int size, power, pool, id;
    float dv;
    bool used = false;
};

bool sbs (server& a, server& b)
{
    return a.dv > b.dv;
}


int possible(int *mas, int size, int sz = 100)
{
    int s = 0;
    int mx = 0;
    int pos = -1;
    for(int i = 0; i < sz; i++)
    {
        if (s >= size)
        {
            return i - s;
        }

        if(mas[i] != -1)
        {    
            s = 0;
        }
        
        else
            s++;
    } 
    
    
    return -1;
    
}



int main ()
{
    //read
    int rows, cells, unav, pools, num;
    ifstream fin ("dp.in");
    fin >> rows >> cells >> unav >> pools >> num;
    cout << rows << ' ' << cells << ' ' << unav << ' ' << pools << ' ' << num << endl;

    int field [rows] [cells];
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < cells; j ++) {field [i] [j] = -1;}
    }
    for (int i = 0; i < unav; i ++)
    {
        int x, y;
        fin >> x >> y;
        field [x] [y] = -2;
    }

    server servers [num];
    for (int i = 0; i < num; i ++)
    {
        fin >> servers [i].size >> servers [i].power;
        servers [i].dv = float (servers [i].power) / servers [i].size;
        servers [i].id = i;

    }
    fin.close ();


    //solution
    //224
    sort(servers, servers + num, sbs);


    int cur_row = 0;
    int cur_pool = 0;
    int pos;
    
    
    for(int i = 0; i < num; i++)
    {
         
        pos = possible(field[cur_row], servers[i].size);
        if (pos != -1)
        {
                cout << cur_row << ' ' << cur_pool << ' ' << pos << ' ' << servers[i].size << endl;
                for(int q = pos; q < pos+servers[i].size; q++)
                {
                    field[cur_row][q] = i;
                    
                    
                }
               
                servers[i].pool = cur_pool;
                cur_row = (cur_row + 1 < rows)? cur_row+1: 0;
                cur_pool = (cur_pool + 1 < pools)? cur_pool + 1: 0;

        }


    }
    
     for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < cells; j ++ )
        {
            if (field [i] [j] == -2) {cout << "x ";}
            else if (field [i] [j] == -1) {cout << "o ";}
            else {cout << servers [field [i] [j]].id << ' ';}
        }
        cout << endl;
    }
    
    


    
    //check
    int minv = INT_MAX;
    for (int cl = 0; cl < rows; cl ++)
    {
        int minpools [pools];
        for (int i = 0; i < pools; i ++) {minpools [i] = 0;}
        for (int i = 0; i < rows; i ++)
        {
            if (i == cl) {continue;}
            for (int j = 0; j < cells; j ++)
            {
                if (field [i] [j] < 0) {continue;}
                server cs = servers [field [i] [j]];
                //if (minpools [cs.pool] == 0 || cs.power < minpools [cs.pool]) {minpools [cs.pool] = cs.power;}
                minpools [cs.pool] += cs.power;
            }
        }
        for (int i = 0; i < pools; i ++)
        {
            if (minpools [i] < minv) {minv = minpools [i];}
        }
    }
    cout << minv << endl;
    return 0;
}
