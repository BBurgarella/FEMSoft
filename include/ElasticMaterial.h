#ifndef ELASTICMATERIAL_H
#define ELASTICMATERIAL_H


class ElasticMaterial
{
    public:
        ElasticMaterial();
        virtual ~ElasticMaterial();

        int GetYoung() { return m_Young; }
        void SetYoung(int val) { m_Young = val; }

    protected:

    private:
        int m_Young;
};

#endif // ELASTICMATERIAL_H
