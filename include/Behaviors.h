class ElasticMaterial
{
    public:

        // Attributes

        int self_Young;
        int self_ID;
        double self_Nu;
        ElasticMaterial(void);
        ElasticMaterial(int Young, double Nu, int MatID);

        // Methods

        int Get_Params(int New_Young, double New_Nu)
        {
            self_Young = New_Young;
            self_Nu = New_Nu;
            return 0;
        }

        double HookeLaw(double Strain)
        // a simple hooke law implementation to calculate the stress in the bar element
        //  (given the strain)
        {
            return self_Young*Strain;
        }

};

ElasticMaterial::ElasticMaterial(void)
{
    self_Young = 0;
    self_Nu = 0;
    self_ID = -1;
    return;
}


ElasticMaterial::ElasticMaterial(int Young, double Nu, int ID)
{
    self_Young = Young;
    self_Nu = Nu;
    self_ID = ID;
    return;
}
