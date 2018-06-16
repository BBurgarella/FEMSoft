class Elastic
{
    public:

        // Attributes

        int self_Young;
        double self_Nu;

        // Methods

        int Get_Params(int New_Young, double New_Nu)
        {
            self_Young = New_Young;
            self_Nu = New_Nu;
            return 0;
        }



};
