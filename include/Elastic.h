#ifndef ELASTIC_H
#define ELASTIC_H


class Elastic
{
    public:
        int Get_Params(int New_Young, double New_Nu)
        {
            self_Young = New_Young;
            self_Nu = New_Nu;
            return 0;
        }

        int self_Young;
        double self_Nu;

};


#endif // ELASTIC_H
