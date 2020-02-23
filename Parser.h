#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <math.h>
class Parser
{
public:
    char sep = ';'; //разделитель между данными
    double* string_to_doubles(char *data)
    {
        double buf = 0;
        int sign = 1;
        int n = 0;
        int shift = 0;
        int flag = 0;
        double *res = (double*) malloc(4 * sizeof(double));
        for(int j = 0; j < 4; ++j)
        {
                    n = 0;
                    sign = 1;
                    flag = 0;
                    buf = 0;
                    if(data[n + shift] == '-')
                    {
                        shift += 1;
                        sign = -1;
                    }
                    while(true)
        {
            if(!flag)
            {
                if(data[n + shift] != ',') ++n;
                else
                {
                    for(int i = 0; i < n; ++i) buf = buf + (((int)data[i + shift]) - 48) * pow(10, n - i - 1);
                    flag = 1;
                }
            }
            else
            {
                ++n;
                double q = 0.1;
                while(true)
                {
                    buf = buf + q * (((int)data[shift + n]) - 48);
                    q = q * q;
                    ++n;
                    if(data[shift + n] == ';' || data[shift + n] == '\0')
                    {
                        res[j] = sign * buf;
                        break;
                    }
                }
            }
            if(data[n + shift] == ';' || data[n + shift] == '\0')

            {
               // std::cout<<"res["<<j<<"}"<<" = "<<res[j]<<std::endl;
                shift = shift + n + 1;
                break;
            }
        }

    }
   // std::cout<<res[0]<<" "<<res[1]<<" "<<res[2]<<" "<<res[3]<<std::endl;
    return res;
    }

};


#endif // PARSER_H_INCLUDED
